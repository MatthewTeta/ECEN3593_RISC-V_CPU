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
 *  \author Albert Miko
 *  \date   2019-11-14
 *  \brief  Helper functions for RISC-V Debug Module RSP target support.
 */

#ifndef SIMULATOR_SIMBASE_SIMULATOR_RISCV_DEBUG_H_
#define SIMULATOR_SIMBASE_SIMULATOR_RISCV_DEBUG_H_

#include "simulator/resources/csr_register.h"
#include "simulator/resources/csr_register_file.h"
#include "simulator/rspl/rsp_interface.h"

namespace codasip {
namespace debugger {
namespace riscv {

/**
 * \brief Update the RISC-V Debug Module triggers with a new breakpoint.
 * \param info Information about the breakpoint to update/add/remove.
 * \param tdata1rf Simulator resource containing tdata1 register file.
 * \param tdata2rf Simulator resource containing tdata2 register file.
 * \return true if the update was successful, false otherwise.
 */
template<class T>
inline bool RiscvUpdateBreakpointCallback(const debugger::BreakpointInfo& info,
    resources::RegisterFile<T>& tdata1rf,
    resources::RegisterFile<T>& tdata2rf)
{
    // only handle HW breakpoints
    if (info.GetType() != debugger::BreakpointInfo::HW)
    {
        return true;
    }

    // XLEN wide integer data type
    typedef typename T::data_type XlenType;
    const unsigned XLEN = resources::BitWidthTypeSelector<XlenType>::value;

    const XlenType MATCH_EQ = 0;
    // find trigger count
    const unsigned riscvTriggerCount = T::SIZE;
    if (info.IsEnabled())
    {
        // adding breakpoint:
        // - first check if breakpoint already set (1st for loop)
        // - if bp not set, find an empty trigger unit and set br (2nd for loop)
        for (unsigned addr = 0; addr < riscvTriggerCount; ++addr)
        {
            const XlenType tdata1 = tdata1rf.dread(addr);
            const XlenType type = (tdata1 >> (XLEN - 4)) & 0xf;
            // check if breakpoint is not already set
            if (type == 2)
            {
                const XlenType match = (tdata1 >> 7) & 0xful;
                // if tdata2 == bpaddr and match is eq --> return
                if (match == MATCH_EQ && (tdata1 & 0x1000ul /*match address*/) &&
                    (tdata1 & 0x4ul /*trig on execute*/) && tdata2rf.dread(addr) == info.GetAddress())
                {
                    // breakpoint already in trigger unit
                    return true;
                }
            }
        }
        for (unsigned addr = 0; addr < riscvTriggerCount; ++addr)
        {
            const XlenType tdata1 = tdata1rf.dread(addr);
            const XlenType type = (tdata1 >> (XLEN - 4)) & 0xf;
            const XlenType exldst = tdata1 &
                0x7ul;   // if exectute, load, store bits for mcontrol are all low, trigger is not active
            // empty trigger unit, can add breakpoint
            if (type == 0 || type == 15 || (type == 2 && exldst == 0))
            {
                const XlenType tdata1NewValue = (static_cast<XlenType>(0x2ul) << (XLEN - 4)) |   // type
                    (static_cast<XlenType>(0x1ul) << (XLEN - 5)) |   // dmode - only Debug Mode can write tdata
                    (0x1 << 12) |   // action -> 1: enter debug mode on exception; 0: trigger exception
                    (0xb << 3) |   // m0su -> enable trigger in all modes (M, S, U)
                    0x4;           // trigger on execute
                tdata1rf.dwrite(tdata1NewValue, addr);
                tdata2rf.dwrite(info.GetAddress(), addr);
                return true;
            }
        }
        // if it gets here, no free trigger module found, failed to set breakpoint
    }
    else
    {
        // removing breakpoint
        for (unsigned addr = 0; addr < riscvTriggerCount; ++addr)
        {
            const XlenType tdata1 = tdata1rf.dread(addr);
            const XlenType type = (tdata1 >> (XLEN - 4)) & 0xf;
            // mcontrol trigger unit, check if matches what we want to remove
            if (type == 2)
            {
                // check if tdata2 == addr and match is eq --> clear trigger
                const XlenType match = (tdata1 >> 7) & 0xful;
                // if tdata2 == bpaddr and match is eq --> return
                if (match == MATCH_EQ && tdata2rf.dread(addr) == info.GetAddress())
                {
                    // clear out breakpoint from trigger unit -- set type to 'unused', other bits to zero
                    const XlenType data = static_cast<XlenType>(0xful) << (XLEN - 4);
                    tdata1rf.dwrite(data, addr);
                    return true;
                }
            }
        }
        // not found, nothing to remove
        return true;
    }
    return false;
}

/**
 * \brief Check if any trigger unit in the RISC-V Debug Module got a hit.
 * \param dpcReg Simulator resource containing DPC register.
 * \param tdata1rf Simulator resource containing tdata1 register file.
 * \param tdata2rf Simulator resource containing tdata2 register file.
 * \return true if any trigger unit was hit, false otherwise.
 */
template<class T, class S>
inline bool IsHwBreakTriggered(resources::Register<T>& dpcReg,
    resources::RegisterFile<S>& tdata1rf,
    resources::RegisterFile<S>& tdata2rf)
{
    // XLEN wide integer data type
    typedef typename S::data_type XlenType;
    const unsigned XLEN = resources::BitWidthTypeSelector<XlenType>::value;

    const XlenType MCONTROL_HIT_MASK = 0x100000ul;
    const XlenType MCONTROL_SELECT_MASK = 0x80000ul;
    const XlenType MCONTROL_MATCH_MASK = 0x780ul;
    const XlenType MCONTROL_EXECUTE_MASK = 0x4ul;
    const XlenType HIT_MATCH = 0x100000ul;
    const XlenType SELECT_ADDRESS_MATCH = 0u;
    const XlenType EXECUTE_MATCH = 4u;
    const XlenType EQ_MATCH = 0u;
    const unsigned riscvTriggerCount = S::SIZE;
    // check if any trigger module fired
    for (unsigned trigModuleIdx = 0; trigModuleIdx < riscvTriggerCount; trigModuleIdx++)
    {
        const XlenType tdata1 = tdata1rf.dread(trigModuleIdx);
        const XlenType trigType = (tdata1 >> (XLEN - 4)) & 0xful;   // top 4 bits of mcontrol
        switch (trigType)
        {
            case 0:
                return false;
                break;
            case 2:   // mcontrol
                if (((tdata1 & MCONTROL_SELECT_MASK) == SELECT_ADDRESS_MATCH) &&
                    ((tdata1 & MCONTROL_EXECUTE_MASK) == EXECUTE_MATCH) &&
                    ((tdata1 & MCONTROL_MATCH_MASK) == EQ_MATCH) &&
                    (tdata2rf.dread(trigModuleIdx) == dpcReg.dread()))
                {
                    return true;
                }
                break;
        }
    };
    return false;
}

}   // namespace riscv
}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_SIMBASE_SIMULATOR_RISCV_DEBUG_H_
