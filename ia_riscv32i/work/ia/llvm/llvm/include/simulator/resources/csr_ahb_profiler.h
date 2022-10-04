/**
 * Codasip s.r.o.
 * 
 * CONFIDENTIAL 
 *
 * Copyright 2019 Codasip s.r.o.
 * 
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of 
 * Codasip s.r.o. and its suppliers, if any. 
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to 
 * Codasip s.r.o. and are protected by trade secret and copyright law.  In addition, elements of the 
 * technical concepts may be patent pending.  
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this 
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained 
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Pavel Richtarik
 *  \date   Oct 17, 2017
 *  \brief  AHB protocol profiler - checks the state of the protocol, values of signals, 
 *          forbidden combinations.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_PROFILER_H_
#define SIMULATOR_RESOURCES_CSR_AHB_PROFILER_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"   // Logging

//#define CODASIP_AHB_PROFILER_DBG_OUT
#ifdef CODASIP_AHB_PROFILER_DBG_OUT
#    define CODASIP_AHB_PROFILER_DBG_OUT_PRINT(text)                              \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() \
                  << ": AHB profiler: " << text << std::endl
#else
#    define CODASIP_AHB_PROFILER_DBG_OUT_PRINT(text)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  AhbProfiler
 *  \brief  Checks the AMBA 3 AHB protocol - checks the state of the protocol,
 *          values of signals, forbidden combinations. Mostly checks sequence
 *          of transaction cycle by cycle (CA only) during BURST.
 *  \}
 */
template<class T>
class AhbProfiler : public T
{
public:
    /// \brief  Local shortcut used for payload type
    typedef Payload<typename T::data_type> PayloadType;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    AhbProfiler(const std::string& name, const Uid uid);
    /**
     *  \copydoc PayloadSentinel::transport_d
     */
    void transport_d(PayloadType& p, const Phase phase);
    /**
     *  \copydoc PayloadSentinel::clock_cycle
     */
    void clock_cycle();
    /**
     *  \copydoc PayloadSentinel::reset
     */
    void reset();

private:
    enum : codasip_address_t
    {   /// address boundary that cannot be crossed during a burst
        ADDRESS_BOUNDARY = 1024
    };

    void AddressPhase(const PayloadType&);
    void DataPhase(const PayloadType&);

    void CheckBurstUnchangedSignals(const PayloadType&) const;
    void CheckBurstAddrSequence(const codasip_address_t) const;
    void CheckBurstAddrBoundary(const codasip_address_t) const;
    void CheckAddrUnchanged(const codasip_address_t) const;

    void LogTransferInit(const AHBTransferType) const;
    void LogBurstEarlyTermination() const;
    void LogBurstContinueFinished() const;
    void LogBurstBusy() const;
    void LogBurstChanged(const char*, const unsigned, const unsigned) const;
    void LogBurstAddrSeq(const codasip_address_t, const codasip_address_t) const;
    void LogBurstAddrBoundary() const;
    void LogAddrChanged() const;
    void LogZeroWait(const char*) const;
    void LogErrorResp(const char*, const char*) const;

    bool IsFixedSizedBurst() const;
    bool IsBurstComplete() const;
    bool HasBurstStarted() const;

    static unsigned GetBeatsCount(const AHBBurstMode);
    static unsigned GetAddressMod(const AHBBurstMode);
    static codasip_address_t
    WrapNextAddress(const codasip_address_t, const AHBBurstMode, const AHBTransferSize);
    static std::string GetTransStr(const AHBTransferType);

    /// slave ready state in current clock cycle
    AHBReadyCode m_SlaveReadyNew;
    /// slave ready state in previous clock cycle (flip-flop logic)
    AHBReadyCode m_SlaveReadyOld;
    /// transfer type in current clock cycle
    AHBTransferType m_TransferTypeNew;
    /// transfer type in previous clock cycle (flip-flop logic)
    AHBTransferType m_TransferTypeOld;
    /// active burst mode, must not change during a burst
    AHBBurstMode m_BurstMode;
    /// active transfer size, must not change during a burst
    AHBTransferSize m_Hsize;
    /// active transfer direction (read/write), must not change during a burst
    AHBReadWriteCode m_Hwrite;
    /// slave error flag
    bool m_SlaveError;
    /// Second tick of error flag
    bool m_ErrorComplete;
    /// previous address of a burst
    codasip_address_t m_LastAddress;
    /// number of processed beats during a burst
    Counter m_ActualBeat;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline AhbProfiler<T>::AhbProfiler(const std::string& name, const Uid uid)
  : T(name, uid)
  , m_SlaveReadyNew(CP_AHB_READY)
  , m_SlaveReadyOld(CP_AHB_READY)
  , m_TransferTypeNew(CP_AHB_IDLE)
  , m_TransferTypeOld(CP_AHB_IDLE)
  , m_BurstMode(CP_AHB_SINGLE)
  , m_Hsize(CP_AHB_SIZE_8)
  , m_Hwrite(CP_AHB_READ)
  , m_SlaveError(false)
  , m_ErrorComplete(false)
  , m_LastAddress(0)
  , m_ActualBeat(0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::transport_d(PayloadType& p, const Phase phase)
{
    T::transport_d(p, phase);

    if (phase == CP_PHS_ADDRESS)
    {
        AddressPhase(p);
    }
    else
    {
        DataPhase(p);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::clock_cycle()
{
    T::clock_cycle();
    // beats are interesting only for SEQUENTIAL transport
    // if slave is busy, beat is not counted
    if (m_SlaveReadyNew == CP_AHB_READY &&
        (m_TransferTypeNew == CP_AHB_SEQ || m_TransferTypeNew == CP_AHB_NONSEQ))
    {
        m_ActualBeat++;
    }
    m_TransferTypeOld = m_TransferTypeNew;
    m_SlaveReadyOld = m_SlaveReadyNew;
    m_TransferTypeNew = CP_AHB_IDLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::reset()
{
    T::reset();
    m_SlaveReadyNew = CP_AHB_READY;
    m_SlaveReadyOld = CP_AHB_READY;
    m_TransferTypeNew = CP_AHB_IDLE;
    m_TransferTypeOld = CP_AHB_IDLE;
    m_BurstMode = CP_AHB_SINGLE;
    m_Hwrite = CP_AHB_READ;
    m_Hsize = CP_AHB_SIZE_8;
    m_SlaveError = false;
    m_ErrorComplete = false;
    m_LastAddress = 0;
    m_ActualBeat = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::AddressPhase(const PayloadType& p)
{
    CODASIP_AHB_PROFILER_DBG_OUT_PRINT("address phase: " << p.PrintAhbLite());
    // idle/single must be followed by idle/nonseq
    if (m_TransferTypeOld == CP_AHB_IDLE || m_BurstMode == CP_AHB_SINGLE)
    {
        if (p.get_ahb_htrans() != CP_AHB_IDLE && p.get_ahb_htrans() != CP_AHB_NONSEQ)
        {
            LogTransferInit(p.get_ahb_htrans());
        }
    }

    // new transfer type
    switch (p.get_ahb_htrans())
    {
        // end of the old burst
        // check if the end of the old burst is valid
        case CP_AHB_NONSEQ:
        case CP_AHB_IDLE:
            if (IsFixedSizedBurst() && !IsBurstComplete() && !m_SlaveError)
            {
                LogBurstEarlyTermination();
            }
            break;

        // continue an existing burst - previous state does not matter
        case CP_AHB_SEQ:
            // burst length must not be overflowed
            if (IsFixedSizedBurst() && IsBurstComplete())
            {
                LogBurstContinueFinished();
            }
            // assert correct addresses sequence (only if slave is ready and master has not been busy)
            if (m_SlaveReadyOld == CP_AHB_READY && m_TransferTypeOld != CP_AHB_BUSY)
            {
                CheckBurstAddrSequence(p.get_address());
            }
            // slave is busy or master has been busy address must not change
            else
            {
                CheckAddrUnchanged(p.get_address());
            }
            // check unchanged signals
            CheckBurstUnchangedSignals(p);
            // check burst size
            CheckBurstAddrBoundary(p.get_address());
            break;

        // go busy
        case CP_AHB_BUSY:
            // busy must not follow fixed size bursts
            if (IsFixedSizedBurst() && IsBurstComplete())
            {
                LogBurstBusy();
            }
            // check unchanged signals
            CheckBurstUnchangedSignals(p);
            // busy states must contain the next burst address and keep it unchanged
            if (m_TransferTypeOld == CP_AHB_BUSY)
            {
                CheckAddrUnchanged(p.get_address());
            }
            else if (HasBurstStarted())
            {
                CheckBurstAddrSequence(p.get_address());
            }
            break;
    }

    // set new burst parameters
    if (p.get_ahb_htrans() == CP_AHB_NONSEQ && m_SlaveReadyNew == CP_AHB_READY)
    {
        m_BurstMode = p.get_ahb_hburst();
        m_Hsize = p.get_ahb_hsize();
        m_Hwrite = p.get_ahb_hwrite();
        m_ActualBeat = 0;
    }

    m_TransferTypeNew = p.get_ahb_htrans();

    // address is ignored during IDLE state
    if (p.get_ahb_htrans() != CP_AHB_IDLE)
    {
        m_LastAddress = p.get_address();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::DataPhase(const PayloadType& p)
{
    CODASIP_AHB_PROFILER_DBG_OUT_PRINT("data phase: " << p.PrintAhbLite());
    // set error flag
    if (p.get_ahb_hresp() == CP_AHB_ERROR)
    {
        // first error cycle
        if (!m_SlaveError || m_ErrorComplete)
        {
            // for BUSY transfer, response must be OKAY
            if (m_TransferTypeOld == CP_AHB_BUSY)
            {
                LogZeroWait("BUSY");
            }
            // for IDLE transfer, response must be OKAY
            else if (m_TransferTypeOld == CP_AHB_IDLE)
            {
                LogZeroWait("IDLE");
            }

            if (p.get_ahb_hready() != CP_AHB_WAIT)
            {
                LogErrorResp("WAIT", "first");
            }

            m_SlaveError = true;
            m_ErrorComplete = false;
        }
        // second error cycle
        else
        {
            m_ErrorComplete = true;
            if (p.get_ahb_hready() != CP_AHB_READY)
            {
                LogErrorResp("READY", "second");
            }
        }
    }
    else
    {
        // clear the error flag
        m_SlaveError = false;
        m_ErrorComplete = false;
    }

    m_SlaveReadyNew = p.get_ahb_hready();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::CheckBurstUnchangedSignals(const PayloadType& p) const
{
    if (p.get_ahb_hburst() != m_BurstMode)
    {
        LogBurstChanged("HBURST", m_BurstMode, p.get_ahb_hburst());
    }
    if (p.get_ahb_hsize() != m_Hsize)
    {
        LogBurstChanged("HSIZE", m_Hsize, p.get_ahb_hsize());
    }
    // hwrite can only be checked during active transfer
    if (p.is_ahb_active_transfer() && p.get_ahb_hwrite() != m_Hwrite)
    {
        LogBurstChanged("HWRITE", m_Hwrite, p.get_ahb_hwrite());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::CheckBurstAddrSequence(const codasip_address_t addr) const
{
    const codasip_address_t expectedAddress = WrapNextAddress(m_LastAddress, m_BurstMode, m_Hsize);
    if (addr != expectedAddress)
    {
        LogBurstAddrSeq(expectedAddress, addr);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::CheckBurstAddrBoundary(const codasip_address_t addr) const
{
    if ((addr / ADDRESS_BOUNDARY) != (m_LastAddress / ADDRESS_BOUNDARY))
    {
        LogBurstAddrBoundary();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AhbProfiler<T>::CheckAddrUnchanged(const codasip_address_t addr) const
{
    if (addr != m_LastAddress)
    {
        LogAddrChanged();
    }
}

/**
 *  \brief  Generate error message when transfer starts with invalid HTRANS.
 *  \param  htrans value of the HTRANS port
 */
template<class T>
void AhbProfiler<T>::LogTransferInit(const AHBTransferType htrans) const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature() << "': only CP_AHB_IDLE and CP_AHB_NONSEQ are allowed after "
        << (m_TransferTypeOld == CP_AHB_IDLE ? "CP_AHB_IDLE" : "CP_AHB_SINGLE")
        << ". Detected: " << GetTransStr(htrans);
}

/**
 *  \brief  Generate error message when burst is terminated too early.
 */
template<class T>
void AhbProfiler<T>::LogBurstEarlyTermination() const
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature() << "': invalid early burst termination.";
}

/**
 *  \brief  Generate error message when trying to continue after burst ended.
 */
template<class T>
void AhbProfiler<T>::LogBurstContinueFinished() const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature() << "': continues in AHB burst after the burst end.";
}

/**
 *  \brief  Generate error message when master tries to issue busy state during
 *          fixed-sized burst.
 */
template<class T>
void AhbProfiler<T>::LogBurstBusy() const
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': busy state is not allowed after a fixed-sized burst.";
}

/**
 *  \brief  Generate error message when port changes value during an active burst.
 *  \param  port port identifier which has changed its value
 *  \param  previous previous value
 *  \param  actual current/changed value
 */
template<class T>
void AhbProfiler<T>::LogBurstChanged(const char* port, const unsigned previous, const unsigned actual) const
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature() << "': " << port
                               << " must not change during a burst. " << previous << " -> " << actual;
}

/**
 *  \brief  Generate error message when address changes to an unexpected value
 *          during an active burst.
 *  \param  expected expected value
 *  \param  actual current/changed value
 */
template<class T>
void AhbProfiler<T>::LogBurstAddrSeq(const codasip_address_t expected, const codasip_address_t actual) const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature() << "': invalid address within the burst: 0x" << std::hex
        << actual << ". Should be: 0x" << expected << "." << std::dec;
}

/**
 *  \brief  Generate error message when burst address crosses 1KB address boundary.
 */
template<class T>
void AhbProfiler<T>::LogBurstAddrBoundary() const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature() << "': burst crosses 1KB address boundary.";
}

/**
 *  \brief  Generate error message when address changes during a busy or waiting state.
 */
template<class T>
void AhbProfiler<T>::LogAddrChanged() const
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': address must not change during a busy or waiting state.";
}

/**
 *  \brief  Generate error message when slave didn't provide OKAY response.
 *  \param  type transfer type
 */
template<class T>
void AhbProfiler<T>::LogZeroWait(const char* type) const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature()
        << "': slave did not provide a zero wait state OKAY response to " << type << " transfer.";
}

/**
 *  \brief  Generate error message when slave violated two-cycle error response sequence.
 *  \param  expected expected value of the HREADY
 *  \param  order clock cycle number
 */
template<class T>
void AhbProfiler<T>::LogErrorResp(const char* expected, const char* order) const
{
    RES_LOG(LOG_TYPE_ERROR, 0)
        << "'" << this->get_signature() << "': two-cycle error violation - HREADY has to be set to "
        << expected << " in the " << order << " error cycle.";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool AhbProfiler<T>::IsFixedSizedBurst() const
{
    return m_BurstMode != CP_AHB_INCR && m_BurstMode != CP_AHB_SINGLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool AhbProfiler<T>::IsBurstComplete() const
{
    return m_ActualBeat == GetBeatsCount(m_BurstMode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool AhbProfiler<T>::HasBurstStarted() const
{
    return m_BurstMode == CP_AHB_INCR || (IsFixedSizedBurst() && !IsBurstComplete());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE unsigned AhbProfiler<T>::GetBeatsCount(const AHBBurstMode burstMode)
{
    switch (burstMode)
    {
        case CP_AHB_SINGLE:
            return 1;
        case CP_AHB_INCR4:
        case CP_AHB_WRAP4:
            return 4;
        case CP_AHB_INCR8:
        case CP_AHB_WRAP8:
            return 8;
        case CP_AHB_INCR16:
        case CP_AHB_WRAP16:
            return 16;
        default:
            return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE unsigned AhbProfiler<T>::GetAddressMod(const AHBBurstMode burstMode)
{
    switch (burstMode)
    {
        case CP_AHB_WRAP4:
            return 4;
        case CP_AHB_WRAP8:
            return 8;
        case CP_AHB_WRAP16:
            return 16;
        default:
            return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE codasip_address_t AhbProfiler<T>::WrapNextAddress(const codasip_address_t addr,
    const AHBBurstMode burstMode,
    const AHBTransferSize hsize)
{
    const unsigned mod = GetAddressMod(burstMode);
    const unsigned bc = 1u << hsize;
    if (mod)
    {
        const codasip_address_t wrapMask = (mod << hsize) - 1;
        const codasip_address_t base = addr & ~wrapMask;
        const codasip_address_t offset = addr & wrapMask;
        return base + ((offset + bc) & wrapMask);
    }
    else
    {
        return addr + bc;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
std::string AhbProfiler<T>::GetTransStr(const AHBTransferType type)
{
    switch (type)
    {
        case CP_AHB_IDLE:
            return "CP_AHB_IDLE";
        case CP_AHB_BUSY:
            return "CP_AHB_BUSY";
        case CP_AHB_SEQ:
            return "CP_AHB_SEQ";
        default:
            return "CP_AHB_NONSEQ";
    }
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AHB_PROFILER_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AHB_PROFILER_H_
