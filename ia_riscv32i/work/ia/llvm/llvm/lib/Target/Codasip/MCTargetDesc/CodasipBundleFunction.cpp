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
 *  \author Martin Ministr
 *  \date   9. 4. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#include "CodasipBundleFunction.h"

#include <cstdarg>
#include <set>

#include "llvm/Support/raw_ostream.h"

//#define DEBUG_CLASS

namespace llvm {

void CodasipBundleFunction::Instruction::DebugPrint(raw_ostream& out) const {
  out << (uint64_t)GetBinary() << " " << GetBitWidth() << "\n";
  out << GetBinary().get_bin(false, false, GetBitWidth())
    << "(" << GetBitWidth() <<  ")" << "\n";
  for (const MCFixup& fixup : GetFixups())
    out << "Fixup\n"
        << "  Offset=" <<  fixup.getOffset() << "\n"
        << "  MsbValue=" <<  fixup.getMsbValue() << "\n"
        << "  LsbValue=" <<  fixup.getLsbValue() << "\n"
        << "  ByteCount=" << fixup.getByteCount() << "\n"
        << "  MsbOut=" <<  fixup.getMsbOut() << "\n"
        << "  LsbOut=" <<  fixup.getLsbOut() << "\n"
        << "  SignPart=" << fixup.isSignPart() << "\n"
        << "  Signed=" << fixup.isSigned() << "\n";

}

/////////////////////////////////////////////////////////////////////////////////
void CodasipBundleFunction::Run(Instructions& outputInstructions, const Instructions& inputInstructions)
{
#ifdef DEBUG_CLASS
    errs() << "Input\n";
    for (const Instruction& instruction : inputInstructions)
      instruction.DebugPrint(errs());
#endif

    Parts parts;
    Call(parts, inputInstructions);

#ifdef DEBUG_CLASS
    for (bundle<64>& part : parts)
    {
        CodasipBundlingBitInfo::PrintContent(part.value.GetContent());
        errs() << "Part size: " << part.size << "\n";
    }
#endif

    // Compute total size
    size_t totalSize = 0;
    for (bundle<64>& part : parts)
    {
        totalSize += part.size;
    }

    Instruction outputInstruction(totalSize);

    size_t partOffset = 0;
    std::string binary;
    // Currently processed fixup temporary information
    const MCFixup* fixup = nullptr;
    size_t msbValue = 0;
    size_t lsbValue = 0;
    size_t msbOut = 0;
    size_t lsbOut = 0;
    // Complete parts look like:    0,  1,  2, ..., 32, ..., 63
    //                             63, 62, 61, ..., 31, ..., 0
    // Incomplete parts look like:  0,  1,  2, ..., 32, ..., 63
    //                             .., .., .., ..., 31, ..., 0
    for (bundle<64>& part : parts)
    {
        const size_t partBytesSize = part.size / 8;
        for (size_t bit = 64 - part.size; bit < 64; bit++)
        {
            const CodasipBundlingBitInfo& bitInfo = part.value.GetContent()[bit];
#ifdef DEBUG_CLASS
            errs() << "Processing bit: " << bitInfo.GetIndex() << "\n";
#endif
            // Append bit to binary
            binary += bitInfo.GetValue();

            // Current bit does not have any fixup
            int fixupIndex = bitInfo.GetOriginFixupIndex();
            if (fixupIndex == CodasipBundlingBitInfo::UNDEFINED_INDEX)
            {
                if (fixup)
                {
                    StoreFixup(outputInstruction, fixup, msbValue, lsbValue, msbOut, lsbOut, partOffset, partBytesSize);
                }
            }
            // Current bit has a fixup
            else
            {
                const MCFixup& currentFixup = inputInstructions[bitInfo.GetSlot()].GetFixups()[fixupIndex];
                // There is no previous fixup
                if (!fixup)
                {
                    // Set temporary fixup information
                    fixup = &currentFixup;
                    msbValue = bitInfo.GetOriginFixupBitIndex();
                    lsbValue = bitInfo.GetOriginFixupBitIndex();
                    msbOut = bitInfo.GetIndex();
                    lsbOut = bitInfo.GetIndex();
                }
                // There is a previous fixup
                else
                {
                    // Current fixup is same as previous fixup and continues in previous fixup
                    if (&currentFixup == fixup &&
                        ((size_t)bitInfo.GetOriginFixupBitIndex() + 1 == lsbValue))
                    {
                        lsbValue = bitInfo.GetOriginFixupBitIndex();
                        lsbOut = bitInfo.GetIndex();
                    }
                    // Current fixup is different from previous fixup or does not continue in previous fixup
                    else
                    {
                        StoreFixup(outputInstruction, fixup, msbValue, lsbValue, msbOut, lsbOut, partOffset, partBytesSize);
                        // Set temporary fixup information
                        fixup = &currentFixup;
                        msbValue = bitInfo.GetOriginFixupBitIndex();
                        lsbValue = bitInfo.GetOriginFixupBitIndex();
                        msbOut = bitInfo.GetIndex();
                        lsbOut = bitInfo.GetIndex();
                    }
                }
            }
        }

        // Print previous fixup on part end, no fixup should cross boundaries of binary parts
        if (fixup)
        {
            StoreFixup(outputInstruction, fixup, msbValue, lsbValue, msbOut, lsbOut, partOffset, partBytesSize);
        }

        partOffset += partBytesSize;
    }

    // Set binary to the output instruction
    outputInstruction.SetBinary(codasip::MaxUint("0b" + binary));

#ifdef DEBUG_CLASS
    errs() << "Output\n";
    outputInstruction.DebugPrint(errs());
#endif

    // Add instruction to vector and pass it more later
    outputInstructions.emplace_back(outputInstruction);
}

void CodasipBundleFunction::codasip_print(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
}

void CodasipBundleFunction::codasip_info(const int, const char* fmt, ...)
{
    codasip_print("info: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}

void CodasipBundleFunction::codasip_warning(const int, const char* fmt, ...)
{
    codasip_print("warning: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}

void CodasipBundleFunction::codasip_error(const int, const char* fmt, ...)
{
    codasip_print("error: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}

void CodasipBundleFunction::codasip_fatal(const int, const char*, ...)
{}

const CodasipBundleFunction::Instruction& CodasipBundleFunction::GetInputInstruction(
    const Instructions& inputInstructions, const size_t index)
{
    CHECK_CONDITION(index < inputInstructions.size())
        << "Missing input instruction of index " << index << ". "
        "Bundles with instructions over multiple slots are not supported.";
    return inputInstructions[index];
}

/**
 *  \brief  Stores new fixup to the instruction.
 *  \param[in, out] instruction Output instruction
 *  \param[in, out] fixup
 *  \param[in, out] msbValue
 *  \param[in, out] lsbValue
 *  \param[in, out] msbOut
 *  \param[in, out] lsbOut
 *  \param[in]      partOffset Offset of the current binary part
 *  \param[in]      partBytesSize Current part size in bytes
 */
void CodasipBundleFunction::StoreFixup(Instruction& instruction, const MCFixup*& fixup,
    size_t& msbValue, size_t& lsbValue, size_t& msbOut, size_t& lsbOut,
    const size_t partOffset, const size_t partBytesSize)
{
    // Store current fixup
    instruction.GetFixups().emplace_back(MCFixup::createCodasip(partOffset, fixup->getValue(),
        fixup->getKind(), fixup->getLoc(), msbValue, lsbValue, partBytesSize, msbOut, lsbOut,
        fixup->isSignPart() && msbValue == fixup->getMsbValue(), fixup->isSigned()));
    // Clear temporary information about current fixup
    fixup = nullptr;
    msbValue = 0;
    lsbValue = 0;
    msbOut = 0;
    lsbOut = 0;
}

}   // namespace llvm
