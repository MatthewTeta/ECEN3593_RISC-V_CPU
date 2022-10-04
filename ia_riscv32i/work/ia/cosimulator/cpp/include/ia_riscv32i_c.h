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
 * \brief   Contains C interface to control Codasip simulator.
 * \project ia_riscv32i
 */

#ifndef _IA_RISCV32I_C_H_
#define _IA_RISCV32I_C_H_

#include <stdint.h>

/**
 *  \addtogroup COSINT Cosimulator interfaces
 *  \{
 */
/**
 *  \defgroup CINT C interface
 *  CINT interface to control Codasip simulator.
 *  \section S1 Resources
 *  This section contains lists of available resources.
 *
 *  \subsection SS2 Registers
 *  \li r_pc
 *
 *  \subsection SS3 Register files
 *  \li rf_xpr
 *
 *  \{
 */
#ifdef __cplusplus
extern "C" {
#endif

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

// bus payload type
struct ahb_payload_t
{
    uint64_t m_HADDR;
    uint8_t* m_Data;
    uint8_t* m_Reserved0;
    uint16_t m_DataLength;
    uint8_t m_Command;
    uint8_t m_HTRANS;
    uint8_t m_HWRITE;
    uint8_t m_HSIZE;
    uint8_t m_HPROT;
    uint8_t m_HMASTLOCK;
    uint8_t m_HBURST;
    uint8_t m_HREADY;
    uint8_t m_HRESP;
    uint8_t m_Reserved1;
    uint8_t m_Reserved2;
    uint8_t m_Reserved3;
    uint8_t m_Reserved4;
    uint8_t m_Reserved5;
};
// callback functions (set unused to NULL)
struct callbacks_t
{
    void (*if_fetch_blocking_cb)(const int h, ahb_payload_t* p);
    void (*ldst_blocking_cb)(const int h, ahb_payload_t* p);
};
/**
 *  \brief  Construct new simulator instance.
 *  \param  cbs Pointer to a structure which contains function pointers to 
 *          callbacks for bus transactions.
 *  \return Returns it's handle that will be used for following method calls (the h parameter).
 */
CODASIP_EXPORT int ia_riscv32i_constructor(callbacks_t* cbs);

/**
 *  \brief  Construct new simulator instance.
 *  \param  cbs Pointer to a structure which contains function pointers to 
 *          callbacks for bus transactions.
 *  \param  name simulator name
 *  \param  codal_parameters comma separated codal parameters, e.g. "memory_size_p=0x40000"
 *  \return Returns it's handle that will be used for following method calls (the h parameter).
 */
CODASIP_EXPORT int ia_riscv32i_constructor_params(callbacks_t* cbs, const char* name, const char* codal_parameters);
/**
 *  \brief  Destructs the simulator instance.
 *  \param  h Handle to a simulator instance.
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_destructor(const int h);
/**
 *  \brief  Resets the simulator.
 *  \param  h Handle to a simulator instance.
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_reset(const int h);
/**
 *  \brief  Executes one clock cycle.
 *  \param  h Handle to a simulator instance.
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_clock_cycle(const int h);
/**
 *  \brief  Returns current cycle counter value.
 *  \param  h Handle to a simulator instance.
 */
CODASIP_EXPORT int ia_riscv32i_get_cycle_count(const int h);
/**
 *  \brief  Dumps profiler data to file.
 *  \param  h Handle to a simulator instance.
 *  \return Returns SIM_OK on success, SIM_FAIL otherwise.
 */
CODASIP_EXPORT int ia_riscv32i_dump_profiler(const int h, const uint64_t cycleCounter);
/**
 *  \brief  Halts simulator.
 *  \description A reentrant function that can be called from a signal handler to gracefully halt the simulator.
 */
CODASIP_EXPORT void ia_riscv32i_halt_all();
/**
 *  \brief  Starts the whole simulation and let simulator handle clock cycles.
 *  \param  h Handle to a simulator instance.
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_run(const int h);
/**
 *  \brief  Starts RSP server inside the simulator.
 *  \param  h Handle to a simulator instance.
 *  \param  port TCP port.
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_start_rsp_server(const int h, const int rspPort);
/**
 *  \brief  Returns last occurred error message from the simulator.
 *  \param  h Handle to a simulator instance.
 */
CODASIP_EXPORT const char* ia_riscv32i_get_last_error_msg(const int h);
/**
 *  \brief  Sets logging settings for all log types.
 *  \param  h Handle to a simulator instance.
 *  \param  options String describing which types of the log type are to be enabled/disabled.
 *          For example:
 *          - "1": enable single type
 *          - "-2": disable single type
 *          - "3+": enable all types from 3 up (including 3)
 *          - "0-4": enable range of types
 *          - "h": enable printing of headers for prints as well
 *          - "q<1000": suppress/silent prints until 1000. clock cycle
 */
CODASIP_EXPORT void ia_riscv32i_set_logging(const int h, const char* options);
/**
 *  \brief  Loads an executable into simulator.
 *  \param  h Handle to a simulator instance.
 *  \param  executable System path to an application to be loaded.
 *          For example: "/home/user/bitcnt.xexe".
 *  \param  arguments Arguments to an executable program in the same format as used in commandline.
 *          For example: "-i --arg test".
 *  \return Returns the simulation status code.
 */
CODASIP_EXPORT int ia_riscv32i_load_executable(const int h, const char* executable, const char* arguments);
/**
 *  \brief  Returns instance name of the simulator.
 *  \param  h Handle to a simulator instance.
 */
CODASIP_EXPORT const char* ia_riscv32i_get_name(const int h);
/**
 *  \brief  Create and start new profiler instance
 *  \param  h Handle to a simulator instance.
 *  \param  output_file Path to the output file.
 */
CODASIP_EXPORT void ia_riscv32i_init_profiler(const int h, const char* outputFile, const unsigned int samplingRate, const bool enabledCallStack, const uint32_t* sequenceLengthsArray, const uint32_t sequenceLengthsArrayLength);
/**
 *  \brief  Reads from a simulator resource.
 *  \param  h Handle to a simulator instance.
 *  \param  output A pointer to where read data should be stored.
 *  \param  outputLen Size of output buffer (in bytes). If size is smaller than read value,
 *          the value is clipped. If size is larger the remaining bits are set to zero.
 *  \param  resource Unique name of a resource in the simulator.
 *  \param  addr An address in the resource from which data should be read.
 *  \return Returns 0 if given resource was found and successfully read from,
 *          otherwise positive number is returned.
 */
CODASIP_EXPORT int ia_riscv32i_resource_read(const int h, uint8_t* output, const unsigned outputLen, const char* resource, const uint64_t addr = 0);
/**
 *  \brief  Writes to a simulator resource.
 *  \param  h Handle to a simulator instance.
 *  \param  data A pointer to data to be written into a resource.
 *  \param  dataLen Size of data to be written. If size is smaller then expected write value,
 *          the remaining bits of value are set to zero. If size is large than expected write value,
 *          the value is clipped.
 *  \param  resource Unique name of a resource in the simulator.
 *  \param  addr An address in the resource to which data should be written.
 *  \return Returns 0 if given resource was found and successfully written into,
 *          otherwise positive number is returned.
 */
CODASIP_EXPORT int ia_riscv32i_resource_write(const int h, const uint8_t* data, const unsigned dataLen, const char* resource, const uint64_t addr = 0);

#ifdef __cplusplus
}   // extern "C"
#endif

/** \} */
/** \} */
#endif // _IA_RISCV32I_C_H_
