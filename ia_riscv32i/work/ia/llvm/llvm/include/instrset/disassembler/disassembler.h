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
 *  \date   Jan 10, 2013
 *  \brief  Main disassemble header
 */

#ifndef _DISASSEMBLER_H_
#define _DISASSEMBLER_H_

#include "common/codasip_integer.h"
#include "common/toolstypes.h"
#include "utility/c_vector.h"

#include <memory>
#include <vector>

namespace llvm {
class CodasipObjectFile;
}   // namespace llvm

namespace codasip {
namespace disassembler {
namespace detail {
class DisassemblerImpl;
}   // namespace detail

/// Return codes for disassembler
enum
{
    /// generator failed to generate output
    INSTGENERATOR_FAIL,
    /// generator succeeded to generate output
    INSTGENERATOR_OK,
    /// parser succeeded to parse input
    INSTPARSER_OK,
    /// there are no more data to parse
    INSTPARSER_DONE,
    /// parser failed to parse input
    INSTPARSER_INVALIDCODE,
    /// debundle function succeed
    DEBUNDLE_OK,
    /// debundle function failed
    DEBUNDLE_FAIL,
    /// disassembler finished
    DSM_DONE,
    /// one instruction was successfully disassembled
    DSM_OK
};

/// Single disassembler output containing address, binary and textual form of single instruction
class Instruction
{
public:
    /// Constructor, creates zeroed element
    Instruction()
      : m_Address(0)
      , m_NextAddress(0)
      , m_Label(nullptr)
      , m_Binary(nullptr)
      , m_Text(nullptr)
    {}
    /// Main constructor
    Instruction(const codasip_address_t address,
        const codasip_address_t nextAddress,
        const std::string& label,
        const std::string& binary,
        const std::string& text)
      : m_Address(address)
      , m_NextAddress(nextAddress)
      , m_Label(strdup(label.c_str()))
      , m_Binary(strdup(binary.c_str()))
      , m_Text(strdup(text.c_str()))
    {}
    /// Copy constructor
    Instruction(const Instruction& cpy)
      : m_Address(cpy.m_Address)
      , m_NextAddress(cpy.m_NextAddress)
      , m_Label(nullptr)
      , m_Binary(nullptr)
      , m_Text(nullptr)
    {
        if (cpy.m_Label != nullptr)
        {
            m_Label = strdup(cpy.m_Label);
        }
        if (cpy.m_Binary != nullptr)
        {
            m_Binary = strdup(cpy.m_Binary);
        }
        if (cpy.m_Text != nullptr)
        {
            m_Text = strdup(cpy.m_Text);
        }
    }
    /// Assign operand
    Instruction& operator=(const Instruction& cpy)
    {
        m_Address = cpy.m_Address;
        m_NextAddress = cpy.m_NextAddress;

        if (cpy.m_Label != nullptr)
        {
            free(m_Label);
            m_Label = strdup(cpy.m_Label);
        }
        if (cpy.m_Binary != nullptr)
        {
            free(m_Binary);
            m_Binary = strdup(cpy.m_Binary);
        }
        if (cpy.m_Text != nullptr)
        {
            free(m_Text);
            m_Text = strdup(cpy.m_Text);
        }

        return *this;
    }
    /// delete what we have allocated
    ~Instruction()
    {
        free(m_Label);
        free(m_Binary);
        free(m_Text);
    }
    /**
     * \{
     * \brief Getter
     */
    codasip_address_t GetAddress() const
    {
        return m_Address;
    }
    codasip_address_t GetNextAddress() const
    {
        return m_NextAddress;
    }
    std::string GetLabel() const
    {
        if (m_Label == nullptr)
        {
            return "";
        }
        return m_Label;
    }
    std::string GetBinary() const
    {
        if (m_Binary == nullptr)
        {
            return "";
        }
        return m_Binary;
    }
    std::string GetText() const
    {
        if (m_Text == nullptr)
        {
            return "";
        }
        return m_Text;
    }
    /** \} */

private:
    /// Address of instruction
    codasip_address_t m_Address;
    /// Address of following instruction
    codasip_address_t m_NextAddress;
    /// If there is an label on address, the text representation is here
    char* m_Label;
    /// Binary string for instruction
    char* m_Binary;
    //// Textual string for instruction
    char* m_Text;
};

/// Array of instruction returned from disassembler. Last element has m_Text
/// and m_Binary members zeroed.
typedef CVector<Instruction> Instructions;
/// data vector, could be words, bytes etc.
typedef CVector<MaxUint> DataParts;

/**
 *  \brief  Abstract class, interface mentioned here must be implemented by
 *          each disassembler. This interface is exported from DLL so it can
 *          contain only PDO data (Plain Old Data = C structures) so it can be
 *          passed between executable and shared library.
 */
class Disassembler
{
public:
    Disassembler();
    ~Disassembler();
    /**
     *  \brief  Entry point for disassembling of executable data.
     *          Used by Codasip Profiler.
     *  \param[out] output Pointer to array where disassembled code will be saved.
     *                     Last element in this array contains zeroes.
     *  \param[in]  objectFile Disassembled Codasip object file
     *  \return if it succeeded, it returns DSM_DONE, otherwise != DSM_DONE code is returned
     */
    int Disassemble(Instructions& output, const llvm::CodasipObjectFile& objectFile);
    /**
     *  \brief  Entry point for codasip_disassembler built-in.
     *          Used by Codasip Simulator.
     *          It is already deparceled and debundled.
     *          In case of the architecture with multiple instruction bit-widths largest bit-width
     *          should be passed and smaller instructions should be aligned to the right.
     *  \example    Multiple bit-widths data '0xAAAAAAAA' and '0x0000BBBB', datasize = 32
     *  \param[out] output Pointer to array where disassembled code will be saved.
     *                     Last element in this array contains zeroes.
     *  \param[in]  data input data
     *  \param[in]  dataSize input data size (in bits)
     *  \param[in]  address address where to start
     *  \param[in]  bbw byte bit-width
     */
    int Disassemble(Instructions& output,
        const MaxUint& data,
        const size_t dataSize,
        const codasip_address_t address,
        const unsigned int bbw);

private:
    /// Disassembler implementation
    std::unique_ptr<detail::DisassemblerImpl> m_Disassembler;
};

}   // namespace disassembler
}   // namespace codasip

#endif   // _DISASSEMBLER_H_
