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
 *  \date   Feb 18, 2013
 *  \brief
 */

#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include "common/codasip_integer.h"
#include "common/toolstypes.h"

#include <map>

#ifdef _WIN32
#    include <time.h>
#endif

namespace codasip {
namespace simulator {
// forwards
class SimulatorPrivateInterface;

// These 2 typedefs are the same, but should be used
// as named sim_fd for simulation side descriptors and
// host_fd for host side descriptors for better
// clarity.
typedef int sim_fd;
typedef int host_fd;

/**
 * \brief Class handling Codasip SysCalls. For running on little endian host.
 * \class SysCalls
 */
class SysCalls
{
public:
    /**
     * \brief Holding user/explicit address of a syscall payload
     * \class UserAddress
     */
    class UserAddress
    {
    public:
        /**
         * \brief Default constructor
         */
        UserAddress();
        /**
         * \brief Explicit constructor that sets the address
         * \param address Address
         */
        UserAddress(const codasip_address_t address);
        /**
         * \{
         * \brief Getter
         */
        bool IsValid() const;
        codasip_address_t GetAddress() const;
        /** \} */
    private:
        /// If true, address is valid
        bool m_Valid;
        /// Address of a syscall payload
        codasip_address_t m_Address;
    };

    /**
     * \brief Constructor, it initialize internal structures
     * \param simulator Reference to the simulator object
     * \param fieldSize Size of syscall structure field (needed for syscall parameter indexing)
     */
    SysCalls(SimulatorPrivateInterface& simulator, unsigned int fieldSize, unsigned int clockSize);
    /**
     * \brief Entry point of the syscall, at the given address information
     *        about the syscall is stored
     * \param firstParamAddress
     */
    int SysCall(const codasip_address_t first_param_address);
    /**
     * \brief Sets the field size
     */
    void SetFieldSize(unsigned int fieldSize);
    /**
     * \brief Sets the clock field size
     */
    void SetClockSize(unsigned int clockSize);
    /**
     * \brief Sets speed of the processor in mhz for time computation
     *        Default is 100MHz
     */
    void SetMhz(unsigned int mhz);
    /**
     * \brief Address of the syscall
     * \param address Address for a syscall
     */
    void SetUserAddress(const codasip_address_t address);
    /**
     * \brief Return user address
     */
    const UserAddress& GetUserAddress() const;
    /**
     * \brief Sets errno if condition is true
     */
    void SetErrnoIf(const bool condition, bool* errno_updated, int* errno_value);

private:
    // enum has to be synchronized with the one in newlib
    enum
    {
        CODASIP_SYSCALL_READ = 1,
        CODASIP_SYSCALL_WRITE = 2,
        CODASIP_SYSCALL_OPEN = 3,
        CODASIP_SYSCALL_CLOSE = 4,
        CODASIP_SYSCALL_LSEEK = 5,
        CODASIP_SYSCALL_FSTAT = 6,

        CODASIP_SYSCALL_CHOWN_UNSUPPORTED = 7,
        CODASIP_SYSCALL_EXECVE_UNSUPPORTED = 8,
        CODASIP_SYSCALL_FORK_UNSUPPORTED = 9,
        CODASIP_SYSCALL_GETPID_UNSUPPORTED = 10,

        CODASIP_SYSCALL_GETTIMEOFDAY = 11,
        CODASIP_SYSCALL_ISATTY = 12,

        CODASIP_SYSCALL_KILL_UNSUPPORTED = 13,
        CODASIP_SYSCALL_LINK_UNSUPPORTED = 14,
        CODASIP_SYSCALL_READLINK_UNSUPPORTED = 15,

        CODASIP_SYSCALL_STAT = 16,

        CODASIP_SYSCALL_SYMLINK_UNSUPPORTED = 17,

        CODASIP_SYSCALL_TIMES = 18,

        CODASIP_SYSCALL_UNLINK_UNSUPPORTED = 19,
        CODASIP_SYSCALL_WAIT_UNSUPPORTED = 20
    };

    /// mapping from the simulation descriptors to the host descriptors
    typedef std::map<sim_fd, host_fd> descriptors_t;

    void InitStdFDs();
    host_fd GetHostFD(const sim_fd);
    int TranslateFileOpenFlags(int sim_flags);

    // aux methods
    codasip::MaxInt ReadField(const codasip_address_t);
    codasip::MaxInt ReadFieldClock(const codasip_address_t);
    void WriteField(const codasip_address_t, const codasip::MaxInt&);
    void WriteFieldClock(const codasip_address_t, const codasip::MaxInt&);
    char ReadByte(const codasip_address_t);
    void WriteByte(const codasip_address_t, const char);
    codasip::MaxInt GetParam(const codasip_address_t, const int);
    codasip::MaxInt GetParamClock(const codasip_address_t, const int);
    void SetParam(const codasip_address_t, const int, const codasip::MaxInt&);
    void SetParamClockTime(const codasip_address_t, const int, const codasip::MaxInt&);
    void SetParamClockRet(const codasip_address_t, const codasip::MaxInt&);
    char* GetData(const codasip_address_t, const int);
    void SetData(const codasip_address_t, const int, const char*);

    // syscalls

    void syscall_write(const codasip_address_t, int*, bool*, int*);
    void syscall_read(const codasip_address_t, int*, bool*, int*);
    void syscall_close(const codasip_address_t, int*, bool*, int*);
    void syscall_open(const codasip_address_t, int*, bool*, int*);
    void syscall_lseek(const codasip_address_t, int*, bool*, int*);
    void syscall_fstat(const codasip_address_t, int*, bool*, int*);
    void syscall_gettimeofday(const codasip_address_t, int*, bool*, int*);
    void syscall_isatty(const codasip_address_t, int*, bool*, int*);
    void syscall_times(const codasip_address_t, clock_t*, bool*, int*);
    void syscall_stat(const codasip_address_t, int*, bool*, int*);

    void do_fstat(host_fd, codasip_address_t, int*, bool*, int*);

    /// mapping from internal simulator descriptors to opened files
    /// TODO: add info about read/write permissions
    descriptors_t m_Descriptors;
    /// simulator object
    SimulatorPrivateInterface& m_Simulator;
    /// size of one syscall structure field in bytes
    unsigned int m_FieldSize;
    /// size of one syscall clock structure field in bytes
    unsigned int m_ClockSize;
    /// Counter holding simulation file descriptors
    sim_fd m_NextSimFd;
    /// Speed in megahertz
    unsigned m_Mhz;
    /// Timeval for measuring simulated processor
    time_t m_Time;
    /// Explicitly set address from user
    UserAddress m_UserAddress;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool SysCalls::UserAddress::IsValid() const
{
    return m_Valid;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline codasip_address_t SysCalls::UserAddress::GetAddress() const
{
    return m_Address;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
inline codasip::MaxInt SysCalls::GetParam(const codasip_address_t address, const int index)
{
    return ReadField(address + index * m_FieldSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void
SysCalls::SetParam(const codasip_address_t address, const int index, const codasip::MaxInt& value)
{
    WriteField(address + index * m_FieldSize, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline codasip::MaxInt SysCalls::GetParamClock(const codasip_address_t address, const int index)
{
    // First 4 fields are op | ret | errno set | errno value
    // Where op, errno set, errno value are int type and ret is clock_t type
    return ReadFieldClock(address + (index + 1) * m_ClockSize + 3 * m_FieldSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SysCalls::SetParamClockTime(const codasip_address_t address,
    const int index,
    const codasip::MaxInt& value)
{
    // First 4 fields are op | dummy | ret | errno set | errno value
    // Where op, errno set, errno value are int type and ret is clock_t type
    WriteFieldClock(address + (index + 1) * m_ClockSize + 4 * m_FieldSize, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SysCalls::SetParamClockRet(const codasip_address_t address, const codasip::MaxInt& value)
{
    // Skip just op and dummy field and write ret
    WriteFieldClock(address + 2 * m_FieldSize, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// allocates data buffer, must be freed when is not needed anymore
inline char* SysCalls::GetData(const codasip_address_t ptr, const int len)
{
    char* data = new char[len + 1];

    for (int i = 0; i < len; i++)
        data[i] = ReadByte(ptr + i);

    data[len] = 0;

    return data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SysCalls::SetData(const codasip_address_t ptr, const int len, const char* data)
{
    for (int i = 0; i < len; i++)
        WriteByte(ptr + i, data[i]);
}

}   // namespace simulator
}   // namespace codasip

#endif   // _SYSCALLS_H_
