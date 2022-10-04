/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2022 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2022-09-10
 * \author  Codasip (c) foreign generator
 * \version 9.1.1-1255
 * \brief   Foreign simulator class
 * \project ia_riscv32i
 */
#ifndef IA_RISCV32I_FOREIGN_2_H_
#define IA_RISCV32I_FOREIGN_2_H_

#include <stdint.h>
#include "simulator/simbase/codasip_interface.h"
#if !defined(CODASIP_EXPORT)
#    ifdef _WIN32
#        ifdef CODASIP_SHARED_LIBRARY
#            define CODASIP_EXPORT __declspec(dllexport)
#        else
#            define CODASIP_EXPORT __declspec(dllimport)
#        endif
#    else
#       define CODASIP_EXPORT __attribute__ ((visibility ("default")))
#    endif
#endif

/** \defgroup COSINT Codasip Interfaces */

namespace codasip {
namespace simulator {
class SimulatorInterface;
class SimulatorInfo;
}
}
namespace codasip {
namespace simulator {
namespace MI11ia_riscv32i {
class Bridge;
}
}
}

namespace codasip {
namespace simulator {
namespace ia_riscv32i {

/**
 *  \class  Foreign
 *  \ingroup COSINT
 *  \ingroup CPPINT
 *  \ingroup SYSTEMCINT
 */
class CODASIP_EXPORT Foreign  {
private:
    SimulatorInterface* m_Simulator;
    codasip::simulator::MI11ia_riscv32i::Bridge* bridge;
public:
    /**
     *  \brief  Foreign
     */
    Foreign(const char* name = "ia_riscv32i", const char* codal_parameters = nullptr);
    /**
     *  \brief  ~Foreign
     */
    ~Foreign();
private:
    Foreign(const Foreign&);
    Foreign& operator=(const Foreign&);
public:
    /**
     *  \brief  Returns instance name of the simulator.
     */
    const char* GetName() const ;
    /**
     *  \brief  InitProfiler
     */
    void InitProfiler(const char* outputFile, const unsigned int samplingRate, const bool enabledCallStack, const uint32_t* sequenceLengthsArray, const uint32_t sequenceLengthsArrayLength);
    /**
     *  \brief  Resets the simulator.
     *  \return Returns the simulation status code.
     */
    int Reset();
    /**
     *  \brief  Returns current cycle counter value.
     */
    int GetCycleCount();
    /**
     *  \brief  Dumps profiler data to file.
     *  \return Returns SIM_OK on success, SIM_FAIL otherwise.
     */
    int DumpProfiler(const uint64_t cycleCounter);
    /**
     *  \brief  Halts simulator.
     *  \description A reentrant function that can be called from a signal handler to
     * gracefully halt the simulator.
     */
    static void HaltAll();
    /**
     *  \brief  Executes clock cycle.
     *  \return Returns the simulation status code.
     */
    int ClockCycle();
    /**
     *  \brief  Starts the whole simulation and let simulator handle clock cycles.
     *  \return Returns the simulation status code.
     */
    int Run();
    /**
     *  \brief  Starts the RSP Server.
     *  \return Returns the RSP status code.
     */
    int StartRspServer(const int rspPort);
    /**
     *  \brief  Reads from a simulator resource.
     *  \param  output A pointer to where read data should be stored.
     *  \param  outputLen Size of output buffer (in bytes). If size is smaller than read value,
     *          the value is clipped. If size is larger the remaining bits are set to zero.
     *  \param  resource Unique name of a resource in the simulator.
     *  \param  addr An address in the resource from which data should be read.
     *  \return Returns true if given resource was found and read access succeeded, otherwise false is returned.
     */
    bool ResourceRead(Data* output, const unsigned outputLen, const char* resource, const Address addr = 0);
    /**
     *  \brief  Writes to a simulator resource.
     *  \param  data A pointer to data to be written into.
     *  \param  dataLen Size of data to be written. If size is smaller then expected write value,
     *          the remaining bits of value are set to zero. If size is large than expected write value,
     *          the value is clipped.
     *  \param  resource Unique name of a resource in the simulator.
     *  \param  addr An address in the resource to which data should be written.
     *  \return Returns true if given resource was found and write access succeeded, otherwise false is returned.
     */
    bool ResourceWrite(const Data* data, const unsigned dataLen, const char* resource, const Address addr = 0);
    /**
     *  \brief  Loads an executable into the simulator.
     *  \param  executable System path to an application to be loaded.
     *          For example: "/home/user/bitcnt.xexe".
     *  \param  arguments Arguments to an executable program in the same format as used in command line.
     *          For example: "-i --arg test".
     *  \return Returns the simulation status code.
     */
    int LoadExecutable(const char* executable, const char* arguments);
    /**
     *  \brief  Gets the simulator interface. Available methods are listed in installed codasip_interface.h.
     *  \return Returns the simulator interface.
     */
    SimulatorInterface& GetInterface();
    /**
     *  \brief  if_fetch_blocking_cb
     */
    virtual void if_fetch_blocking_cb(ForeignPayload& fp) = 0;
    /**
     *  \brief  ldst_blocking_cb
     */
    virtual void ldst_blocking_cb(ForeignPayload& fp) = 0;
};
} // namespace ia_riscv32i
} // namespace simulator
} // namespace codasip

#endif // IA_RISCV32I_FOREIGN_2_H_
