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
 *  \author Codasip s.r.o..
 *  \brief  Codasip simulator and debugger interfaces that can be re-implemented to support
 *          custom implementation.
 */

#ifndef _CODASIP_INTERFACE_H_
#define _CODASIP_INTERFACE_H_

#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace codasip {
namespace simulator {

/// ID of ASIP thread, indexed from 0
/// Typedef for addresses
typedef uint64_t Address;
/// Data type that is used to store binary data for data watchpoint or access to resources
typedef uint8_t Data;

/// Invalid address
static const Address INVALID_ADDRESS = Address(-1);

/// Values of global halt flag
typedef enum
{
    /// Run
    GLOBAL_HALT_OK = 0,
    /// Exit simulator
    GLOBAL_HALT_EXIT = 1,
} GlobalHaltFlag;

/// Type of logging message
typedef enum
{
    /// Invalid log type
    LOG_TYPE_INVALID = 0,
    /// Informative messages using codasip_print
    LOG_TYPE_PRINT,
    /// Informative messages using codasip_info
    LOG_TYPE_INFO,
    /// Warning messages using codasip_warning
    LOG_TYPE_WARNING,
    /// Warning messages using codasip_error
    LOG_TYPE_ERROR,
    /// Warning messages using codasip_fatal
    LOG_TYPE_FATAL
} LogType;

/// Return codes for simulator
typedef enum
{
    /// Success return code
    SIM_OK = 0,
    /// Simulation successfully halted
    SIM_HALT,
    /// Simulation failed
    SIM_FAIL,
    /// Simulation was killed from debugger
    SIM_KILLED,
    /// Instruction generator failed to generate output
    INSTGENERATOR_FAIL,
    /// Instruction generator succeeded to generate output
    INSTGENERATOR_OK,
    /// Instruction parser succeeded to parse input
    INSTPARSER_OK,
    /// There are no more data to parse for instruction parser
    INSTPARSER_DONE,
    /// Instruction parser failed to parse input
    INSTPARSER_INVALIDCODE,
    /// disassembler finished
    DSM_DONE,
    /// one instruction was successfully disassembled
    DSM_OK,
    /// Marks last return code
    SIM_RETURN_CODE_END
} SimulatorReturnCode;

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  SimulatorInterface
 *  \brief  Interface that is implemented by every Codasip simulator. Can be used to control
 *          the simulation, register a debugger interface and retrieve the state of simulation.
 */
class SimulatorInterface
{
public:
    /// Halt flag for use in signal handlers
    static sig_atomic_t m_GlobalHalt;

public:
    /**
     *  \brief  Return the full path of the simulator.
     */
    virtual const char* GetPath() const = 0;
    /**
     *  \brief  Destructor
     */
    virtual ~SimulatorInterface() {}
    /**
     *  \brief  Reset simulator. Will activate reset CodAL event and wait until its execution
     *          finishes.
     *  \return SIM_OK on success, SIM_HALT when simulation halted, other return codes on error.
     */
    virtual int Reset() = 0;
    /**
     *  \brief  Simulate single clock cycle of the simulator and all its parts. Returns simulator
     *          code SimulatorReturnCode
     *  \return SIM_OK on success, SIM_HALT when simulation halted, other return codes on error.
     */
    virtual int ClockCycle() = 0;
    /**
     *  \brief  Return current clock count for given
     */
    virtual uint64_t GetCycleCount() const = 0;
    /**
     *  \brief  Tell profiler to dump current data to file
     */
    virtual bool DumpProfiler(const uint64_t cycleCounter) = 0;
    /**
     * \brief Gracefully halts all simulators
     */
    inline static void HaltAll();
    /**
     *  \brief  Load executable into given ASIP instance.
     *  \param  executable Path to the executable (.xexe file) to be loaded
     *  \param  arguments String containing arguments that will be available in C main function
     *          argc and argv arguments.
     *  \return Success of executable loading.
     */
    virtual bool LoadExecutable(const char* executable, const char* arguments = "") = 0;
    /**
     *  \brief  Read simulator resource
     *  \param  output Output buffer where data will be stored
     *  \param  outputLen Length of the output buffer in bytes (sizeof operator)
     *  \param  resource Path to resource that should be read
     *  \param  addr Optional address for addressed resources, for simple registers use 0
     *  \return Success of read
     */
    virtual bool
    ResourceRead(Data* output, unsigned outputLen, const char* resource, const Address addr = 0) = 0;
    /**
     *  \brief  Write into simulator resource
     *  \param  resource Path to resource that should be written to
     *  \param  data Input buffer with data that should be written
     *  \param  dataLen Length of the output buffer in bytes (sizeof operator)
     *  \param  addr Optional address for addressed resources, for simple registers use 0
     *  \return Success of write
     */
    virtual bool ResourceWrite(const Data* data,
        const unsigned dataLen,
        const char* resource,
        const Address addr = 0) = 0;
    /**
     *  \brief  Controls of single logging type logging for simulator.
     *  \param  options Options setting enabled logging type verbosity levels. Format:
     *          0,1,2-3,-4,5+,h,q<1000:
     *          0  : enable single type
     *          2-3: enable range
     *          -4 : disable single type
     *          5+ : enable all types from 5 up including 5
     *          h  : enable printing of headers for prints as well
     *          q<1000: suppress/silent prints until 1000. clock cycle. The
     *          1000. clock cycle triggers the prints.
     */
    virtual void SetLogging(const char* options) = 0;
    /**
     *  \brief  Set profiler options for given simulator.
     *  \param  output Path to the output file
     *  \param  samplingRate Sampling rate in number of clock cycle. E.g. sampling rate 10
     *          issues profiler data dump every 10th clock cycle.
     *  \param  enabledCallStack Enabled call stack tracking
     *  \param  sequenceLengths All tracked sequences of instructions
     */
    virtual void InitProfiler(const char* output,
        const unsigned int samplingRate,
        const bool enabledCallStack,
        const uint32_t* sequenceLengthsArray,
        const uint32_t sequenceLengthsArrayLength) = 0;
    /**
     *  \brief  Return last error message from simulator
     */
    virtual const char* GetLastError() const = 0;
    /**
     *  \brief  Set simulation timeout (max clock cycles).
     *  \param  timeout Maximum number of clock cycles
     */
    virtual void SetTimeout(const uint64_t timeout) = 0;
    /**
     * \brief Start RSP Server for a simulator. LLDB can be used for a connection to the target
     * \param rspPort TCP port of RSP Server
     * \param lldbPort LLDB uses this port to start simulator, should not be used by a user
     */
    virtual void StartRspServer(const unsigned int rspPort, const unsigned int lldbPort = 0) = 0;
    /**
     * \brief Sets an address of the syscall payload and overrides the address in the debugger
     *        settings
     * \param addr New address for the syscall payload
     */
    virtual void SetSyscall(const Address addr) = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SimulatorInterface::HaltAll()
{
    SimulatorInterface::m_GlobalHalt = GLOBAL_HALT_EXIT;
}

/**
 *  \class  ForeignPayload 18 elements
 *  \brief  Generic payload used in foreign simulators for memory related.
 *          Mapping of attributes in different payloads to the generic payload:
 *         | ITEM           | AHB       | AXI4 lite   | AXI4       | CPB            | CPB Lite   |
 *         |================|===========|=============|============|================|============|
 *         | m_Address      | HADDR     | Address     | Address    | Address        | Address    |
 *         | m_Data         | *Data     | *Data       | *Data      | *Data          | *Data      |
 *         | m_WriteStrobes | -         | -           | *WSTRB     | *WSTRB         | *WSTRB     |
 *         | m_DataLength   | DataLen   | DataLen     | DataLen    | DataLen        | DataLen    |
 *         | m_Command      | Command   | Command     | Command    | Command        | Command    |
 *         | m_Item0        | HTRANS    | (A)xVALID   | (A)xVALID  | AVALID         | AVALID     |
 *         | m_Item1        | HWRITE    | (A)xREADY   | (A)xREADY  | WRITE          | WRITE      |
 *         | m_Item2        | HSIZE     | AxPROT      | AxPROT     | RESP           | RESP       |
 *         | m_Item3        | HPROT     | -           | xID        | AREADY         | -          |
 *         | m_Item4        | HMASTLOCK | xRESP       | xRESP      | VALID          | -          |
 *         | m_Item5        | HBURST    |------------------Address Offset------------------------|
 *         | m_Item6        | HREADY    |-------------------Transfer Size------------------------|
 *         | m_Item7        | -         | -           | AxLen      | -              | -          |
 *         | m_Item8        | -         | -           | AxBURST    | -              | -          |
 *         | m_Item9        | -         | -           | AxLOCK     | -              | -          |
 *         | m_Item10       | -         | -           | AxCACHE    | -              | -          |
 *         | m_Item11       | -         | -           | AxQOS      | -              | -          |
 *         | m_Item12       | -         | -           | AxREGION   | -              | -          |
 *         | m_Item13       | -         | -           | AxLAST     | -              | -          |
 */
class ForeignPayload
{
public:
    /**
     *  \brief  Default constructor
     */
    ForeignPayload();
    /**
     *  \brief  Reset all attributes to 0
     */
    void Reset();
    /**
     *  \{
     *  \brief  Generic getter for all bus protocols.
     */
    Address GetAddress() const;
    uint8_t GetCommand() const;
    uint8_t* GetData();
    const uint8_t* GetData() const;
    uint16_t GetDataLength() const;
    /**
     *  \} \{
     *  \brief  Generic setter for all bus protocols.
     *  \param  value new updated value
     */
    void SetAddress(const Address value);
    void SetCommand(const uint8_t value);
    void SetData(uint8_t* value);
    void SetDataLength(const uint16_t value);
    /**
     *  \} \{
     *  \brief  Getter for AMBA AHB bus protocol.
     */
    Address GetHADDR() const;
    uint8_t GetHBURST() const;
    bool GetHMASTLOCK() const;
    uint8_t GetHPROT() const;
    uint8_t GetHSIZE() const;
    uint8_t GetHTRANS() const;
    bool GetHWRITE() const;
    bool GetHREADY() const;
    uint8_t GetHRESP() const;
    /**
     *  \} \{
     *  \brief  Setter for AMBA AHB bus protocol.
     *  \param  value new updated value
     */
    void SetHADDR(const Address value);
    void SetHBURST(const uint8_t value);
    void SetHMASTLOCK(const uint8_t value);
    void SetHPROT(const uint8_t value);
    void SetHSIZE(const uint8_t value);
    void SetHTRANS(const uint8_t value);
    void SetHWRITE(const uint8_t value);
    void SetHREADY(const uint8_t value);
    void SetHRESP(const uint8_t value);
    /**
     *  \} \{
     *  \brief Old getter for AMBA AXI4-Lite bus protocol.
     */
    bool GetAxiValid() const;
    bool GetAxiReady() const;
    uint8_t* GetAxiWriteStrobe() const;
    uint8_t GetAxiResponse() const;
    uint8_t GetAxiProtectionMode() const;
    uint8_t GetAxiAddressOffset() const;
    uint8_t GetAxiTransferSize() const;
    /**
     *  \} \{
     *  \brief Old setter for AMBA AXI4-Lite bus protocol.
     *  \param  value new updated value
     */
    void SetAxiValid(const uint8_t value);
    void SetAxiReady(const uint8_t value);
    void SetAxiWriteStrobe(uint8_t* value);
    void SetAxiResponse(const uint8_t value);
    void SetAxiProtectionMode(const uint8_t value);
    void SetAxiAddressOffset(const uint8_t value);
    void SetAxiTransferSize(const uint8_t value);
    /**
     *  \} \{
     *  \brief Getter for AMBA AXI4-Lite bus protocol.
     */
    bool GetAxi4LiteValid() const;
    bool GetAxi4LiteReady() const;
    uint8_t* GetAxi4LiteWriteStrobe() const;
    uint8_t GetAxi4LiteResponse() const;
    uint8_t GetAxi4LiteProtectionMode() const;
    uint8_t GetAxi4LiteAddressOffset() const;
    uint8_t GetAxi4LiteTransferSize() const;
    /**
     *  \} \{
     *  \brief Setter for AMBA AXI4-Lite bus protocol.
     *  \param  value new updated value
     */
    void SetAxi4LiteValid(const uint8_t value);
    void SetAxi4LiteReady(const uint8_t value);
    void SetAxi4LiteWriteStrobe(uint8_t* value);
    void SetAxi4LiteResponse(const uint8_t value);
    void SetAxi4LiteProtectionMode(const uint8_t value);
    void SetAxi4LiteAddressOffset(const uint8_t value);
    void SetAxi4LiteTransferSize(const uint8_t value);
    /**
     *  \} \{
     *  \brief Getter for AMBA AXI4 bus protocol.
     */
    bool GetAxi4Valid() const;
    bool GetAxi4Ready() const;
    uint8_t* GetAxi4WriteStrobe() const;
    uint8_t GetAxi4Response() const;
    uint8_t GetAxi4ProtectionMode() const;
    uint8_t GetAxi4AddressOffset() const;
    uint8_t GetAxi4TransferSize() const;
    uint8_t GetAxi4Id() const;
    uint8_t GetAxi4Len() const;
    uint8_t GetAxi4Burst() const;
    uint8_t GetAxi4Lock() const;
    uint8_t GetAxi4Cache() const;
    uint8_t GetAxi4QOS() const;
    uint8_t GetAxi4Region() const;
    uint8_t GetAxi4Last() const;
    /**
     *  \} \{
     *  \brief Setter for AMBA AXI4 bus protocol.
     *  \param  value new updated value
     */
    void SetAxi4Valid(const uint8_t value);
    void SetAxi4Ready(const uint8_t value);
    void SetAxi4WriteStrobe(uint8_t* value);
    void SetAxi4Response(const uint8_t value);
    void SetAxi4ProtectionMode(const uint8_t value);
    void SetAxi4AddressOffset(const uint8_t value);
    void SetAxi4TransferSize(const uint8_t value);
    void SetAxi4Id(const uint8_t value);
    void SetAxi4Len(const uint8_t value);
    void SetAxi4Burst(const uint8_t value);
    void SetAxi4Lock(const uint8_t value);
    void SetAxi4Cache(const uint8_t value);
    void SetAxi4QOS(const uint8_t value);
    void SetAxi4Region(const uint8_t value);
    void SetAxi4Last(const uint8_t value);
    /**
     *  \} \{
     *  \brief Getter for Codasip Processor Bus protocol.
     */
    bool GetCpbAReady() const;
    bool GetCpbAValid() const;
    bool GetCpbWrite() const;
    uint8_t* GetCpbWriteStrobe();
    const uint8_t* GetCpbWriteStrobe() const;
    bool GetCpbValid() const;
    bool GetCpbResponse() const;
    uint8_t GetCpbAddressOffset() const;
    uint8_t GetCpbTransferSize() const;
    /**
     *  \} \{
     *  \brief Setter for Codasip Processor Bus protocol.
     *  \param  value new updated value
     */
    void SetCpbAReady(const uint8_t value);
    void SetCpbAValid(const uint8_t value);
    void SetCpbWrite(const uint8_t value);
    void SetCpbWriteStrobe(uint8_t* value);
    void SetCpbValid(const uint8_t value);
    void SetCpbResponse(const uint8_t value);
    void SetCpbAddressOffset(const uint8_t value);
    void SetCpbTransferSize(const uint8_t value);
    /** \} */
private:
    /// Address of the request
    Address m_Address;
    /// data that should be written
    uint8_t* m_Data;
    /// CPB / AXI4 full write strobes, same size as data
    uint8_t* m_WriteStrobes;
    /// Length of data
    uint16_t m_DataLength;
    /// Command for the request (contains debug commands as well)
    uint8_t m_Command;
    /// \{  Generic member, its meaning depends on specific bus protocol
    uint8_t m_Item0;
    uint8_t m_Item1;
    uint8_t m_Item2;
    uint8_t m_Item3;
    uint8_t m_Item4;
    uint8_t m_Item5;
    uint8_t m_Item6;
    uint8_t m_Item7;
    uint8_t m_Item8;
    uint8_t m_Item9;
    uint8_t m_Item10;
    uint8_t m_Item11;
    uint8_t m_Item12;
    uint8_t m_Item13;
    /// \}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
inline ForeignPayload::ForeignPayload()
{
    Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::Reset()
{
    m_Address = 0;
    m_Data = 0;
    m_WriteStrobes = 0;
    m_DataLength = 0;
    m_Command = 0;
    m_Item0 = 0;
    m_Item1 = 0;
    m_Item2 = 0;
    m_Item3 = 0;
    m_Item4 = 0;
    m_Item5 = 0;
    m_Item6 = 0;
    m_Item7 = 0;
    m_Item8 = 0;
    m_Item9 = 0;
    m_Item10 = 0;
    m_Item11 = 0;
    m_Item12 = 0;
    m_Item13 = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Address ForeignPayload::GetAddress() const
{
    return m_Address;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetCommand() const
{
    return m_Command;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t* ForeignPayload::GetData()
{
    return m_Data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const uint8_t* ForeignPayload::GetData() const
{
    return m_Data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint16_t ForeignPayload::GetDataLength() const
{
    return m_DataLength;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAddress(const Address address)
{
    m_Address = address;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCommand(const uint8_t command)
{
    m_Command = command;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetData(uint8_t* data)
{
    m_Data = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetDataLength(const uint16_t length)
{
    m_DataLength = length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Address ForeignPayload::GetHADDR() const
{   // reuse address
    return GetAddress();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHADDR(const Address value)
{   // reuse address
    SetAddress(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetHTRANS() const
{
    return m_Item0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHTRANS(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetHWRITE() const
{
    return m_Item1 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHWRITE(const uint8_t value)
{
    m_Item1 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetHSIZE() const
{
    return m_Item2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHSIZE(const uint8_t value)
{
    m_Item2 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetHPROT() const
{
    return m_Item3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHPROT(const uint8_t value)
{
    m_Item3 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetHMASTLOCK() const
{
    return m_Item4 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHMASTLOCK(const uint8_t value)
{
    m_Item4 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetHBURST() const
{
    return m_Item5;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHBURST(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetHREADY() const
{
    return m_Item6 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHREADY(const uint8_t value)
{
    m_Item6 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetHRESP() const
{
    return m_Item7;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetHRESP(const uint8_t value)
{
    m_Item7 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxiValid() const
{
    return m_Item0 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiValid(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxiReady() const
{
    return m_Item1 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiReady(const uint8_t value)
{
    m_Item1 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxiProtectionMode() const
{
    return m_Item2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiProtectionMode(const uint8_t value)
{
    m_Item2 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t* ForeignPayload::GetAxiWriteStrobe() const
{
    return m_WriteStrobes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiWriteStrobe(uint8_t* value)
{
    m_WriteStrobes = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxiResponse() const
{
    return m_Item4;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiResponse(const uint8_t value)
{
    m_Item4 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxiAddressOffset() const
{
    return m_Item5;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiAddressOffset(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxiTransferSize() const
{
    return m_Item6;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxiTransferSize(const uint8_t value)
{
    m_Item6 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxi4LiteValid() const
{
    return GetAxiValid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxi4LiteReady() const
{
    return GetAxiReady();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t* ForeignPayload::GetAxi4LiteWriteStrobe() const
{
    return GetAxiWriteStrobe();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4LiteResponse() const
{
    return GetAxiResponse();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4LiteProtectionMode() const
{
    return GetAxiProtectionMode();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4LiteAddressOffset() const
{
    return GetAxiAddressOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4LiteTransferSize() const
{
    return GetAxiTransferSize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteValid(const uint8_t value)
{
    return SetAxiValid(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteReady(const uint8_t value)
{
    return SetAxiReady(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteWriteStrobe(uint8_t* value)
{
    return SetAxiWriteStrobe(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteResponse(const uint8_t value)
{
    return SetAxiResponse(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteProtectionMode(const uint8_t value)
{
    return SetAxiProtectionMode(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteAddressOffset(const uint8_t value)
{
    return SetAxiAddressOffset(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4LiteTransferSize(const uint8_t value)
{
    return SetAxiTransferSize(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxi4Valid() const
{
    return GetAxi4LiteValid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetAxi4Ready() const
{
    return GetAxi4LiteReady();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t* ForeignPayload::GetAxi4WriteStrobe() const
{
    return m_WriteStrobes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Response() const
{
    return GetAxi4LiteResponse();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4ProtectionMode() const
{
    return GetAxi4LiteProtectionMode();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4AddressOffset() const
{
    return GetAxi4LiteAddressOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4TransferSize() const
{
    return GetAxi4LiteTransferSize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Id() const
{
    return m_Item3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Len() const
{
    return m_Item7;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Burst() const
{
    return m_Item8;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Lock() const
{
    return m_Item9;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Cache() const
{
    return m_Item10;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4QOS() const
{
    return m_Item11;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Region() const
{
    return m_Item12;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetAxi4Last() const
{
    return m_Item13;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Valid(const uint8_t value)
{
    SetAxi4LiteValid(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Ready(const uint8_t value)
{
    SetAxi4LiteReady(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4WriteStrobe(uint8_t* value)
{
    m_WriteStrobes = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Response(const uint8_t value)
{
    SetAxi4LiteResponse(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4ProtectionMode(const uint8_t value)
{
    SetAxi4LiteProtectionMode(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4AddressOffset(const uint8_t value)
{
    SetAxi4LiteAddressOffset(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4TransferSize(const uint8_t value)
{
    SetAxi4LiteTransferSize(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Id(const uint8_t value)
{
    m_Item3 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Len(const uint8_t value)
{
    m_Item7 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Burst(const uint8_t value)
{
    m_Item8 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Lock(const uint8_t value)
{
    m_Item9 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Cache(const uint8_t value)
{
    m_Item10 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4QOS(const uint8_t value)
{
    m_Item11 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Region(const uint8_t value)
{
    m_Item12 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetAxi4Last(const uint8_t value)
{
    m_Item13 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetCpbAValid() const
{
    return m_Item0 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbAValid(const uint8_t value)
{
    m_Item0 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetCpbWrite() const
{
    return m_Item1 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbWrite(const uint8_t value)
{
    m_Item1 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetCpbResponse() const
{
    return m_Item2 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbResponse(const uint8_t value)
{
    m_Item2 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetCpbAReady() const
{
    return m_Item3 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbAReady(const uint8_t value)
{
    m_Item3 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool ForeignPayload::GetCpbValid() const
{
    return m_Item4 == 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbValid(const uint8_t value)
{
    m_Item4 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetCpbAddressOffset() const
{
    return m_Item5;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbAddressOffset(const uint8_t value)
{
    m_Item5 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t ForeignPayload::GetCpbTransferSize() const
{
    return m_Item6;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbTransferSize(const uint8_t value)
{
    m_Item6 = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ForeignPayload::SetCpbWriteStrobe(uint8_t* value)
{
    m_WriteStrobes = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t* ForeignPayload::GetCpbWriteStrobe()
{
    return m_WriteStrobes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const uint8_t* ForeignPayload::GetCpbWriteStrobe() const
{
    return m_WriteStrobes;
}

}   // namespace simulator
}   // namespace codasip

#endif   // _CODASIP_INTERFACE_H_
