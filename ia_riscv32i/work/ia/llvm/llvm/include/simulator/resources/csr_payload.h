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
 *  \author Zdenek Prikryl
 *  \date   Feb 23, 2016
 *  \brief  Definition of the class codasip::resources::Payload.
 */

#ifndef SIMULATOR_RESOURCES_CSR_PAYLOAD_H_
#define SIMULATOR_RESOURCES_CSR_PAYLOAD_H_

#include "simulator/resources/csr_helpers.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Payload
 *  \brief  Generic payload for data transfer over interface. Contains attributes
 *          for all supported bus protocols.
 *          Mapping of attributes in different payloads to the generic payload:
 *          ITEM      | AHB       | AXI4-Lite | AXI4      | CPB       | CPB Lite
 *          =========================================================
 *          m_Address | HADDR     | AxADDR    | AxADDR    | ADDR      | ADDR
 *          m_Command | Command   | Command   | Command   | Command   | Command
 *          m_Bc      | HSIZE/BC  |                Transfer Size/BC/AxSIZE
 *          m_Item0   | HTRANS    | (A)xVALID | (A)xVALID | AVALID    | AVALID
 *          m_Item1   | HWRITE    | -         | xLAST     | WRITE     | WRITE
 *          m_Item2   | HPROT     | AxPROT    | AxPROT    | -         | -
 *          m_Item3   | HMASTLOCK | WSTRB     | Phase     | VALID     | -
 *          m_Item4   | HBURST    |                Address Offset
 *          m_Item5   | HREADY    | (A)xREADY | (A)xREADY | AREADY    | -
 *          m_Item6   | HRESP     | xRESP     | xRESP     | RESP      | RESP
 *          m_Item7   | HSEL      | -         | xID       | -         | -
 *          m_Item8   | -         | -         | AxLEN     | -         | -
 *          m_Item9   | -         | -         | AxBURST   | -         | -
 *          m_Item10  | -         | -         | AxLOCK    | -         | -
 *          m_Item11  | -         | -         | AxCACHE   | -         | -
 *          m_Item12  | -         | -         | AxQOS     | -         | -
 *          m_Item13  | -         | -         | AxREGION  | -         | -
 *          Data      | Data      | Data      | Data      | Data      | Data
 *          WSTRB     | -         | -         | *WSTRB    | *WSTRB    | *WSTRB
 *  \}
 */
template<class T>
class Payload
{
public:
    /// \brief  Data type used for the word
    typedef T data_type;
    /// \brief  Shortcut for this type
    typedef Payload<data_type> payload_type;
    /// \brief  Type used for effective parameter passing
    typedef typename detail::CallTraits<data_type>::param_type param_type;
    /// \brief  Type used for effective value returns
    typedef typename detail::CallTraits<data_type>::return_type return_type;
    /// \brief  Underlying type holding write strobe (may not be the exact bit-width)
    typedef typename TypeSelector<BitWidthTypeSelector<T>::value / 8, false>::type write_strobe_type;
    /// \brief  Data type used for effective parameter passing of the write strobe
    typedef typename detail::CallTraits<write_strobe_type>::param_type write_strobe_param_type;
    /// \brief  Data type used for effective parameter write strobe returns
    typedef typename detail::CallTraits<write_strobe_type>::return_type write_strobe_return_type;

    /**
     *  \brief  Constructor
     */
    Payload();
    /**
     *  \brief  Clear all data
     */
    void reset(const uint8_t ready = 0u);
    /**
     *  \{
     *  \brief  Generic getters
     */
    codasip_address_t get_address() const;
    return_type get_data() const;
    Command get_command() const;
    bool is_error() const;
    Index get_bc() const;
    /**
     *  \}
     *  \brief  Indicates whether current payload represents debug access or not.
     */
    bool is_debug_access() const;
    /**
     *  \{
     *  \brief  Generic setters
     *  \param  value new updated value
     */
    void set_address(const codasip_address_t value);
    void set_data(param_type value);
    void set_command(const Command value);
    void set_error(const bool value);
    void set_bc(const Index value);
    /**
     *  \} \{
     *  \brief  AMBA 3 AHB-Lite specific getters for address phase.
     */
    AHBBurstMode get_ahb_hburst() const;
    AHBMasterLockCode get_ahb_hmastlock() const;
    uint8_t get_ahb_hprot() const;
    AHBTransferSize get_ahb_hsize() const;
    AHBTransferType get_ahb_htrans() const;
    AHBReadWriteCode get_ahb_hwrite() const;
    /**
     *  \} \{
     *  \brief  AMBA 3 AHB-Lite specific getters for data phase.
     */
    AHBReadyCode get_ahb_hready() const;
    AHBResponseCode get_ahb_hresp() const;
    /**
     *  \}
     *  \brief  Indicates whether non-sequential or sequential transfer is
     *          specified.
     */
    bool is_ahb_active_transfer() const;
    /**
     *  \brief  Compute value of HSIZE for AMBA 3 AHB-Lite from byte count.
     *  \param  bc transfer size in bytes (byte count)
     */
    static constexpr AHBTransferSize get_ahb_hsize(const Index bc);
    /**
     *  \brief  Compute value of SIZE for AXI4 or AXI4-Lite from byte count.
     *  \param  bc transfer size in bytes (byte count)
     */
    static constexpr AXIBurstSize get_axi_size(const Index bc);
    /**
     *  \brief  AMBA 3 AHB-Lite HSEL port value.
     */
    bool get_ahb_hsel() const;
    /**
     *  \{
     *  \brief  AMBA 3 AHB-Lite HPROT flag indication.
     */
    bool is_ahb_hprot_data() const;
    bool is_ahb_hprot_privileged() const;
    bool is_ahb_hprot_bufferable() const;
    bool is_ahb_hprot_cacheable() const;
    /**
     *  \} \{
     *  \brief  AMBA 3 AHB-Lite specific setters for address phase.
     *  \param  value new updated value
     */
    void set_ahb_hburst(const uint8_t value);
    void set_ahb_hmastlock(const uint8_t value);
    void set_ahb_hprot(const uint8_t value);
    void set_ahb_hsize(const uint8_t value);
    void set_ahb_htrans(const uint8_t value);
    void set_ahb_hwrite(const uint8_t value);
    /**
     *  \} \{
     *  \brief  AMBA 3 AHB-Lite specific setters for data phase.
     *  \param  value new updated value
     */
    void set_ahb_hready(const uint8_t value);
    void set_ahb_hresp(const uint8_t value);
    void set_ahb_hsel(const uint8_t value);
    /**
     *  \} \{
     *  \brief  AMBA AXI4 specific getters.
     */
    AXIValidCode get_axi_valid() const;
    AXIReadyCode get_axi_ready() const;
    uint8_t get_axi_prot() const;
    write_strobe_return_type get_axi_wstrb() const;
    AXIResponseCode get_axi_resp() const;
    uint8_t get_axi_id() const;
    uint8_t get_axi_len() const;
    AXIBurstSize get_axi_size() const;
    AXIBurstType get_axi_burst() const;
    AXILockCode get_axi_lock() const;
    uint8_t get_axi_cache() const;
    uint8_t get_axi_qos() const;
    uint8_t get_axi_region() const;
    AXILastCode get_axi_last() const;

    bool is_axi_prot_privileged() const;
    bool is_axi_prot_nonsecure() const;
    bool is_axi_prot_instruction() const;
    bool is_axi_cache_bufferable() const;
    bool is_axi_cache_modifiable() const;
    bool is_axi_cache_allocate() const;
    bool is_axi_cache_other_allocate() const;
    /**
     *  \} \{
     *  \brief  AMBA AXI4 specific API used by the UVM data verification.
     */
    bool is_axi_read_address_valid() const;
    bool is_axi_read_address_ready() const;
    bool is_axi_read_data_valid() const;
    bool is_axi_read_data_ready() const;
    bool is_axi_write_address_valid() const;
    bool is_axi_write_address_ready() const;
    bool is_axi_write_data_valid() const;
    bool is_axi_write_data_ready() const;
    bool is_axi_write_response_valid() const;
    bool is_axi_write_response_ready() const;
    bool is_axi_address_phase() const;
    bool is_axi_data_phase() const;
    bool is_axi_response_phase() const;
    void set_axi_address_phase();
    void set_axi_data_phase();
    void set_axi_response_phase();
    void clear_axi_phase();
    /**
     *  \} \{
     *  \internal
     *  \brief  AMBA AXI4 internal getters used to support full IA access checks.
     */
    Index get_axi_address_offset() const;
    Index get_axi_transfer_size() const;
    /**
     *  \} \{
     *  \brief  AMBA AXI4 specific setters.
     *  \param  value new updated value
     */
    void set_axi_valid(const uint8_t value);
    void set_axi_ready(const uint8_t value);
    void set_axi_prot(const uint8_t value);
    void set_axi_wstrb(write_strobe_param_type value);
    void set_axi_resp(const uint8_t value);
    void set_axi_id(const uint8_t value);
    void set_axi_len(const uint8_t value);
    void set_axi_size(const uint8_t value);
    void set_axi_burst(const uint8_t value);
    void set_axi_lock(const uint8_t value);
    void set_axi_cache(const uint8_t value);
    void set_axi_qos(const uint8_t value);
    void set_axi_region(const uint8_t value);
    void set_axi_last(const uint8_t value);
    /**
     *  \} \{
     *  \internal
     *  \brief  AMBA AXI4 internal setters used to support full IA access checks.
     *  \param  value new value of the attribute
     */
    void set_axi_address_offset(const Index value);
    /// transfer size in bytes (not in AXISizeCode)
    void set_axi_transfer_size(const Index value);
    /**
     *  \} \{
     *  \brief  CPB specific getters for address phase.
     */
    CPBReadyCode get_cpb_aready() const;
    CPBValidCode get_cpb_avalid() const;
    CPBReadWriteCode get_cpb_write() const;
    write_strobe_return_type get_cpb_wstrb() const;
    /**
     *  \} \{
     *  \brief  CPB specific getters for data phase.
     */
    CPBValidCode get_cpb_valid() const;
    CPBResponseCode get_cpb_resp() const;
    /**
     *  \} \{
     *  \brief  CPB specific setters for address phase.
     *  \param  value new value of the attribute
     */
    void set_cpb_aready(const uint8_t value);
    void set_cpb_avalid(const uint8_t value);
    void set_cpb_write(const uint8_t value);
    void set_cpb_wstrb(write_strobe_param_type value);
    /**
     *  \} \{
     *  \brief  CPB specific setters for data phase.
     *  \param  value new value of the attribute
     */
    void set_cpb_valid(const uint8_t value);
    void set_cpb_resp(const uint8_t value);
    /**
     *  \} \{
     *  \internal
     *  \brief  CPB internal getters used to support full IA access checks.
     */
    Index get_cpb_address_offset() const;
    Index get_cpb_transfer_size() const;
    /**
     *  \} \{
     *  \internal
     *  \brief  CPB internal setters used to support full IA access checks.
     *  \param  value new value of the attribute
     */
    void set_cpb_address_offset(const Index value);
    void set_cpb_transfer_size(const Index value);
    /**
     *  \} \{
     *  \brief  Equivalence comparison operator.
     *  \param  p second payload to compare with
     */
    bool operator==(const payload_type& p) const;
    bool operator!=(const payload_type& p) const;
    /**
     *  \} \{
     *  \brief  Debug prints specific per protocol. Lists only attributes used
     *          by the protocol.
     */
    std::string PrintAhbLite() const;
    std::string PrintAxiLite() const;
    std::string PrintAxi() const;
    std::string PrintCpb() const;
    /** \} */
private:
    /// Address of the request
    codasip_address_t m_Address;
    /// Command for the request, mostly used for IA and debug access
    uint8_t m_Command;
    /// byte count
    uint8_t m_Bc;
    /// attribute used for HTRANS, (A)xVALID, AVALID
    uint8_t m_Item0;
    /// attribute used for HWRITE, xRESP, WRITE
    uint8_t m_Item1;
    /// attribute used for HPROT, AxPROT
    uint8_t m_Item2;
    /// attribute used for HMASTLOCK, WSTRB, VALID
    uint8_t m_Item3;
    /// attribute used for HBURST, internal address offset
    uint8_t m_Item4;
    /// attribute used for HREADY, xxREADY, AREADY - status of slave
    uint8_t m_Item5;
    /// attribute used for HRESP, -, RESP one bit response from the slave
    /// the attribute should be set by the AXI4 as well indicating error
    /// but the precise error code for AXI4 is elsewhere
    /// the unified error code is used by component which are not aware of the protocol
    uint8_t m_Item6;
    /// AHB slave select (HSEL), required for verification of component project
    /// reused for xID
    uint8_t m_Item7;
    /// attribute used for AxLEN
    uint8_t m_Item8;
    /// attribute used for AxBURST
    uint8_t m_Item9;
    /// attribute used for AxLOCK
    uint8_t m_Item10;
    /// attribute used for AxCACHE
    uint8_t m_Item11;
    /// attribute used for AxQOS
    uint8_t m_Item12;
    /// attribute used for AxREGION
    uint8_t m_Item13;
    /// CPB/AXI4 (full) specific write strobe
    /// (cannot reuse AXI4-Lite WSTRB since AXI4-Lite is limited to 64-bit words and 8-bit bytes)
    write_strobe_type m_WSTRB;
    /// data that should be written
    T m_Data;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Payload<T>::Payload()
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::reset(const uint8_t ready)
{
    m_Address = 0;
    m_Bc = 0;
    m_Command = CP_CMD_NONE;
    m_Item0 = 0;
    m_Item1 = 0;
    m_Item2 = 0;
    m_Item3 = 0;
    m_Item4 = 0;
    m_Item5 = ready;
    m_Item6 = 0;
    m_Item7 = 0;
    m_Item8 = 0;
    m_Item9 = 0;
    m_Item10 = 0;
    m_Item11 = 0;
    m_Item12 = 0;
    m_Item13 = 0;
    m_Data = 0;
    m_WSTRB = 0;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE codasip_address_t Payload<T>::get_address() const
{
    return m_Address;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_address(const codasip_address_t value)
{
    m_Address = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename Payload<T>::return_type Payload<T>::get_data() const
{
    return m_Data;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_data(param_type value)
{
    m_Data = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Command Payload<T>::get_command() const
{
    return static_cast<Command>(m_Command);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_command(const Command value)
{
    m_Command = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_error() const
{
    return m_Item6 != 0;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_error(const bool value)
{
    m_Item6 = value ? CP_AXI_SLVERR : CP_AXI_OKAY;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Index Payload<T>::get_bc() const
{
    return m_Bc;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_bc(const Index value)
{   // maximum transfer size for 1024/8 = 128
    m_Bc = static_cast<uint8_t>(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_debug_access() const
{
    return (get_command() == CP_CMD_DREAD) || (get_command() == CP_CMD_DWRITE) ||
        (get_command() == CP_CMD_LOAD);
}

////////////////////////////////////////////////////////////////////////////////
//                             AMBA 3 AHB-Lite                                //
////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBBurstMode Payload<T>::get_ahb_hburst() const
{
    return static_cast<AHBBurstMode>(m_Item4);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hburst(const uint8_t value)
{
    m_Item4 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBMasterLockCode Payload<T>::get_ahb_hmastlock() const
{
    return static_cast<AHBMasterLockCode>(m_Item3);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hmastlock(const uint8_t value)
{
    m_Item3 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_ahb_hprot() const
{
    return m_Item2;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hprot(const uint8_t value)
{   // only bottom 4 bits are meaningful
    m_Item2 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBTransferSize Payload<T>::get_ahb_hsize() const
{
    return get_ahb_hsize(get_bc());
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hsize(const uint8_t value)
{
    /* AHB transfers are aligned based on transfer size
     * index is always 0
     * transfer size mapping to HSIZE[2:0] signal:
     *   000     8 bits   1 byte
     *   001    16 bits   2 bytes
     *   010    32 bits   4 bytes
     *   011    64 bits   8 bytes
     *   100   128 bits  16 bytes
     *   101   256 bits  32 bytes
     *   110   512 bits  64 bytes
     *   111  1024 bits 128 bytes
     * maximum allowed size is width of the data bus
     */
    set_bc(1u << value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline constexpr AHBTransferSize Payload<T>::get_ahb_hsize(const Index bc)
{
    return static_cast<AHBTransferSize>((bc == 1) ? CP_AHB_SIZE_8
            : (bc == 2)                           ? CP_AHB_SIZE_16
            : (bc == 4)                           ? CP_AHB_SIZE_32
            : (bc == 8)                           ? CP_AHB_SIZE_64
            : (bc == 16)                          ? CP_AHB_SIZE_128
            : (bc == 32)                          ? CP_AHB_SIZE_256
            : (bc == 64)                          ? CP_AHB_SIZE_512
            : (bc == 128)                         ? CP_AHB_SIZE_1024
                                                  : (CP_AHB_SIZE_INVALID));
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline constexpr AXIBurstSize Payload<T>::get_axi_size(const Index bc)
{
    return static_cast<AXIBurstSize>(get_ahb_hsize(bc));
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBTransferType Payload<T>::get_ahb_htrans() const
{
    return static_cast<AHBTransferType>(m_Item0);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_htrans(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_ahb_active_transfer() const
{
    return (get_ahb_htrans() == CP_AHB_NONSEQ) || (get_ahb_htrans() == CP_AHB_SEQ);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBReadWriteCode Payload<T>::get_ahb_hwrite() const
{
    return static_cast<AHBReadWriteCode>(m_Item1);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hwrite(const uint8_t value)
{
    m_Item1 = value;
    m_Command = !is_ahb_active_transfer()    ? CP_CMD_NONE
        : (get_ahb_hwrite() == CP_AHB_WRITE) ? CP_CMD_WRITE
                                             : CP_CMD_READ;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBReadyCode Payload<T>::get_ahb_hready() const
{
    return static_cast<AHBReadyCode>(m_Item5);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hready(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AHBResponseCode Payload<T>::get_ahb_hresp() const
{
    return (m_Item6 != 0u) ? CP_AHB_ERROR : CP_AHB_OKAY;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_ahb_hresp(const uint8_t value)
{
    set_error(value != CP_AHB_OKAY);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::get_ahb_hsel() const
{
    return m_Item7;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void Payload<T>::set_ahb_hsel(const uint8_t value)
{
    m_Item7 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_ahb_hprot_data() const
{
    return (get_ahb_hprot() & CP_AHB_DATA_ACCESS) != 0;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_ahb_hprot_privileged() const
{
    return (get_ahb_hprot() & CP_AHB_PRIVILEGED) != 0;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_ahb_hprot_bufferable() const
{
    return (get_ahb_hprot() & CP_AHB_BUFFERABLE) != 0;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_ahb_hprot_cacheable() const
{
    return (get_ahb_hprot() & CP_AHB_CACHEABLE) != 0;
}

////////////////////////////////////////////////////////////////////////////////
//                              AMBA AXI4-Lite                                //
////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXIValidCode Payload<T>::get_axi_valid() const
{
    return static_cast<AXIValidCode>(m_Item0);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_valid(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXIReadyCode Payload<T>::get_axi_ready() const
{
    return static_cast<AXIReadyCode>(m_Item5);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_ready(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_prot() const
{
    return m_Item2;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_prot(const uint8_t value)
{
    m_Item2 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename Payload<T>::write_strobe_return_type Payload<T>::get_axi_wstrb() const
{
    return m_WSTRB;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_wstrb(write_strobe_param_type value)
{
    m_WSTRB = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXIResponseCode Payload<T>::get_axi_resp() const
{
    return static_cast<AXIResponseCode>(m_Item6);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_resp(const uint8_t value)
{
    m_Item6 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_id(const uint8_t value)
{
    m_Item7 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_id() const
{
    return m_Item7;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_len(const uint8_t value)
{
    m_Item8 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_len() const
{
    return m_Item8;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_size(const uint8_t value)
{
    set_ahb_hsize(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXIBurstSize Payload<T>::get_axi_size() const
{
    return static_cast<AXIBurstSize>(get_ahb_hsize());
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_burst(const uint8_t value)
{
    m_Item9 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXIBurstType Payload<T>::get_axi_burst() const
{
    return static_cast<AXIBurstType>(m_Item9);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_lock(const uint8_t value)
{
    m_Item10 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXILockCode Payload<T>::get_axi_lock() const
{
    return static_cast<AXILockCode>(m_Item10);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_cache(const uint8_t value)
{
    m_Item11 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_cache() const
{
    return m_Item11;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_qos(const uint8_t value)
{
    m_Item12 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_qos() const
{
    return m_Item12;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_region(const uint8_t value)
{
    m_Item13 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE uint8_t Payload<T>::get_axi_region() const
{
    return m_Item13;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_last(const uint8_t value)
{
    m_Item1 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE AXILastCode Payload<T>::get_axi_last() const
{
    return static_cast<AXILastCode>(m_Item1);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Index Payload<T>::get_axi_address_offset() const
{
    return get_cpb_address_offset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Index Payload<T>::get_axi_transfer_size() const
{
    return get_cpb_transfer_size();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_address_offset(const Index value)
{   // reuse CPB implementation
    set_cpb_address_offset(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_transfer_size(const Index value)
{   // maximum transfer size for 1024/8 = 128
    set_bc(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_prot_privileged() const
{
    return m_Item2 & CP_AXI_PROT_PRIVILEGED;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_prot_nonsecure() const
{
    return m_Item2 & CP_AXI_PROT_NON_SECURE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_prot_instruction() const
{
    return m_Item2 & CP_AXI_PROT_INSTR;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_cache_bufferable() const
{
    return m_Item11 & CP_AXI_CACHE_BUFFERABLE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_cache_modifiable() const
{
    return m_Item11 & CP_AXI_CACHE_MODIFIABLE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_cache_allocate() const
{
    return m_Item11 & CP_AXI_CACHE_ALLOCATE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_cache_other_allocate() const
{
    return m_Item11 & CP_AXI_CACHE_OTHER_ALLOCATE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_read_address_valid() const
{
    return (get_command() == CP_CMD_READ) && (get_axi_valid() == CP_AXI_VALID) &&
        is_axi_address_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_read_address_ready() const
{
    return (get_command() == CP_CMD_READ) && (get_axi_ready() == CP_AXI_READY) &&
        is_axi_address_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_read_data_valid() const
{
    return (get_command() == CP_CMD_READ) && (get_axi_valid() == CP_AXI_VALID) && is_axi_data_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_read_data_ready() const
{
    return (get_command() == CP_CMD_READ) && (get_axi_ready() == CP_AXI_READY) && is_axi_data_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_address_valid() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_valid() == CP_AXI_VALID) &&
        is_axi_address_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_address_ready() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_ready() == CP_AXI_READY) &&
        is_axi_address_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_data_valid() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_valid() == CP_AXI_VALID) && is_axi_data_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_data_ready() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_ready() == CP_AXI_READY) && is_axi_data_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_response_valid() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_valid() == CP_AXI_VALID) &&
        is_axi_response_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool Payload<T>::is_axi_write_response_ready() const
{
    return (get_command() == CP_CMD_WRITE) && (get_axi_ready() == CP_AXI_READY) &&
        is_axi_response_phase();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_axi_address_phase() const
{
    return m_Item3 & CP_AXI_PHASE_ADDRESS;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_axi_data_phase() const
{
    return m_Item3 & CP_AXI_PHASE_DATA;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::is_axi_response_phase() const
{
    return m_Item3 & CP_AXI_PHASE_RESPONSE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_address_phase()
{
    m_Item3 |= CP_AXI_PHASE_ADDRESS;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_data_phase()
{
    m_Item3 |= CP_AXI_PHASE_DATA;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_axi_response_phase()
{
    m_Item3 |= CP_AXI_PHASE_RESPONSE;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::clear_axi_phase()
{
    m_Item3 = 0;
}

////////////////////////////////////////////////////////////////////////////////
//                          Codasip Processor Bus                             //
////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE CPBReadyCode Payload<T>::get_cpb_aready() const
{
    return static_cast<CPBReadyCode>(m_Item5);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_aready(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE CPBValidCode Payload<T>::get_cpb_avalid() const
{
    return static_cast<CPBValidCode>(m_Item0);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_avalid(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE CPBReadWriteCode Payload<T>::get_cpb_write() const
{
    return static_cast<CPBReadWriteCode>(m_Item1);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_write(const uint8_t value)
{
    m_Item1 = value;
    set_command((get_cpb_avalid() == CP_CPB_INVALID) ? CP_CMD_NONE
            : (get_cpb_write() == CP_CPB_WRITE)      ? CP_CMD_WRITE
                                                     : CP_CMD_READ);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename Payload<T>::write_strobe_return_type Payload<T>::get_cpb_wstrb() const
{
    return m_WSTRB;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_wstrb(write_strobe_param_type value)
{
    m_WSTRB = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE CPBValidCode Payload<T>::get_cpb_valid() const
{
    return static_cast<CPBValidCode>(m_Item3);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_valid(const uint8_t value)
{
    m_Item3 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE CPBResponseCode Payload<T>::get_cpb_resp() const
{
    return (m_Item6 != 0u) ? CP_CPB_ERROR : CP_CPB_OKAY;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_resp(const uint8_t value)
{
    m_Item6 = value;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Index Payload<T>::get_cpb_address_offset() const
{
    return m_Item4;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_address_offset(const Index value)
{   // max address offset for 1024/8 -> 127, should fit to uint8_t
    m_Item4 = static_cast<uint8_t>(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Index Payload<T>::get_cpb_transfer_size() const
{
    return get_bc();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Payload<T>::set_cpb_transfer_size(const Index value)
{   // maximum transfer size for 1024/8 = 128
    set_bc(value);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::operator==(const payload_type& p) const
{
    return (m_Address == p.m_Address) && (m_Bc == p.m_Bc) && (m_Command == p.m_Command) &&
        (m_Item0 == p.m_Item0) && (m_Item1 == p.m_Item1) && (m_Item2 == p.m_Item2) &&
        (m_Item3 == p.m_Item3) && (m_Item4 == p.m_Item4) && (m_Item5 == p.m_Item5) &&
        (m_Item6 == p.m_Item6) && (m_Item7 == p.m_Item7) && (m_Item8 == p.m_Item8) &&
        (m_Item9 == p.m_Item9) && (m_Item10 == p.m_Item10) && (m_Item11 == p.m_Item11) &&
        (m_Item12 == p.m_Item12) && (m_Item13 == p.m_Item13) && (m_WSTRB == p.m_WSTRB) &&
        (m_Data == p.m_Data);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool Payload<T>::operator!=(const payload_type& p) const
{
    return !(this->operator==(p));
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::string Payload<T>::PrintAhbLite() const
{
    std::ostringstream out;
    out << "HREADY: " << get_ahb_hready() << ", HRESP: " << get_ahb_hresp()
        << ", HTRANS: " << get_ahb_htrans() << ", HWRITE: " << get_ahb_hwrite()
        << ", HSIZE: " << get_ahb_hsize() << ", HADDR: 0x" << std::hex << get_address() << std::dec
        << ", HPROT: " << static_cast<uint16_t>(get_ahb_hprot())
        << ", HMASTLOCK: " << get_ahb_hmastlock() << ", HBURST: " << get_ahb_hburst() << ", HDATA: 0x"
        << std::setfill('0') << std::setw(BitWidthTypeSelector<T>::value / 4) << std::hex;
    // do not print 8 bit data as character, but as an integer
    if (std::is_same<uint8_t, data_type>::value)
    {
        out << static_cast<uint16_t>(get_data());
    }
    else
    {
        out << get_data();
    }
    out << ", command: " << std::dec << get_command() << ", bc: " << get_bc()
        << ", is_error: " << is_error();

    return out.str();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::string Payload<T>::PrintAxiLite() const
{
    std::ostringstream out;
    out << "xVALID: " << get_axi_valid() << ", xREADY: " << get_axi_ready() << ", AxADDR: 0x"
        << std::hex << get_address() << std::dec
        << ", AxPROT: " << static_cast<uint16_t>(get_axi_prot()) << ", xDATA: 0x"
        << std::setfill('0') << std::setw(BitWidthTypeSelector<T>::value / 4) << std::hex;
    // do not print 8 bit data as character, but as an integer
    if (std::is_same<uint8_t, data_type>::value)
    {
        out << static_cast<uint16_t>(get_data());
    }
    else
    {
        out << get_data();
    }
    out << ", WSTRB: 0x" << std::setfill('0') << std::setw((BitWidthTypeSelector<T>::value / 8) / 4)
        << std::hex;
    // do not print write strobes as character, but as an integer
    if (std::is_same<uint8_t, write_strobe_type>::value)
    {
        out << static_cast<uint16_t>(get_axi_wstrb());
    }
    else
    {
        out << get_axi_wstrb();
    }
    out << ", xRESP: " << std::dec << get_axi_resp() << ", command: " << get_command()
        << ", offset: " << get_axi_address_offset() << ", bc: " << get_bc()
        << ", is_error: " << is_error();

    return out.str();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::string Payload<T>::PrintAxi() const
{
    std::ostringstream out;
    out << "xVALID: " << get_axi_valid() << ", xREADY: " << get_axi_ready() << ", AxADDR: 0x"
        << std::hex << get_address() << ", AxPROT: " << static_cast<uint16_t>(get_axi_prot())
        << ", AxLEN: " << static_cast<uint16_t>(get_axi_len())
        << ", AxSIZE: " << static_cast<uint16_t>(get_axi_size())
        << ", AxBURST: " << static_cast<uint16_t>(get_axi_burst())
        << ", AxLOCK: " << static_cast<uint16_t>(get_axi_lock())
        << ", AxCACHE: " << static_cast<uint16_t>(get_axi_cache())
        << ", AxQOS: " << static_cast<uint16_t>(get_axi_qos())
        << ", AxREGION: " << static_cast<uint16_t>(get_axi_region())
        << ", AxID: " << static_cast<uint16_t>(get_axi_id())
        << ", AxLAST: " << static_cast<uint16_t>(get_axi_last()) << ", xDATA: 0x"
        << std::setfill('0') << std::setw(BitWidthTypeSelector<T>::value / 4) << std::hex;
    // do not print 8 bit data as character, but as an integer
    if (std::is_same<uint8_t, data_type>::value)
    {
        out << static_cast<uint16_t>(get_data());
    }
    else
    {
        out << get_data();
    }
    out << ", WSTRB: 0x" << std::setfill('0') << std::setw((BitWidthTypeSelector<T>::value / 8) / 4)
        << std::hex;
    // do not print write strobes as character, but as an integer
    if (std::is_same<uint8_t, write_strobe_type>::value)
    {
        out << static_cast<uint16_t>(get_axi_wstrb());
    }
    else
    {
        out << get_axi_wstrb();
    }
    out << ", xRESP: " << std::dec << get_axi_resp() << ", command: " << get_command()
        << ", offset: " << get_axi_address_offset() << ", bc: " << get_bc()
        << ", is_error: " << is_error();

    return out.str();
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::string Payload<T>::PrintCpb() const
{
    std::ostringstream out;
    out << "AREADY: " << get_cpb_aready() << ", AVALID: " << get_cpb_avalid()
        << ", WRITE: " << get_cpb_write() << ", ADDR: 0x" << std::hex << get_address() << std::dec
        << ", xDATA: 0x" << std::setfill('0') << std::setw(BitWidthTypeSelector<T>::value / 4)
        << std::hex;
    // do not print 8 bit data as character, but as an integer
    if (std::is_same<uint8_t, data_type>::value)
    {
        out << static_cast<uint16_t>(get_data());
    }
    else
    {
        out << get_data();
    }
    out << ", WSTRB: 0x" << std::setfill('0') << std::setw((BitWidthTypeSelector<T>::value / 8) / 4);
    // do not print write strobes as character, but as an integer
    if (std::is_same<uint8_t, write_strobe_type>::value)
    {
        out << static_cast<uint16_t>(get_cpb_wstrb());
    }
    else
    {
        out << get_cpb_wstrb();
    }
    out << ", VALID: " << std::dec << get_cpb_valid() << ", RESP: " << get_cpb_resp()
        << ", command: " << get_command() << ", offset: " << get_cpb_address_offset()
        << ", bc: " << get_bc() << ", is_error: " << is_error();

    return out.str();
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_PAYLOAD_H_
