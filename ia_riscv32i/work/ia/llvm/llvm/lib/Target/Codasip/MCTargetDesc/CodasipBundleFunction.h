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
 *  \date   29. 3. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_BUNDLEFUNCTION_H_
#define LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_BUNDLEFUNCTION_H_

#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"

#include "CodasipBundlingInt.h"
#include "utility/codasiputils.h"

namespace llvm {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Structure that represents bundle type.
 */
template<int BITS>
struct bundle
{
    bundle()
      : size(0)
    {}

    template<int R_BITS>
    bundle(const bundle<R_BITS>& copy) :
        value(copy.value),
        size(copy.size)
    {}

    CodasipBundlingInt<BITS> value;
    uint32_t size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Class that provides access to generated bundle function.
 *          It is interface to the generated object.
 */
class CodasipBundleFunction
{
public:
    class Instruction
    {
    public:
        typedef SmallVector<MCFixup, 4> Fixups;

        Instruction(const uint64_t bw);

        /**
         *  \{
         *  \brief  Getter.
         */
        const codasip::MaxUint& GetBinary() const;
        uint64_t GetBitWidth() const;
        Fixups& GetFixups();
        const Fixups& GetFixups() const;
        /**
         *  \}
         *  \{
         *  \brief  Setter.
         */
        void SetBinary(const codasip::MaxUint&);
        /// \}

        void DebugPrint(raw_ostream& out) const;

    private:
        /// Binary coding
        codasip::MaxUint m_Binary;
        /// Bit-width of the binary coding
        uint64_t m_BitWidth;
        /// Fixups related to this instruction
        Fixups m_Fixups;
    };
    typedef SmallVector<Instruction, 4> Instructions;
    /// Large bundles should be split into 64 bit parts to be possible to encode them in Codasip ELF
    typedef std::vector< bundle<64> > Parts;

    virtual ~CodasipBundleFunction()
    {}

    /**
     *  \brief  Do the bundling and parcelling process.
     *  \param[in]  outputInstructions Output instructions
     *  \param[in]  inputInstructions Input instructions
     */
    void Run(Instructions& outputInstructions, const Instructions& inputInstructions);
    /**
     *  \brief  Wrapper function around generated bundle function,
     *          it processes input instructions and returns content of result's bundling_int.
     *  \param[out] parts Parts of output instructions
     *  \param[in]  inputInstructions slot instructions of bundle instruction or single instruction
     */
    virtual void Call(Parts& parts, const Instructions& inputInstructions) const = 0;

protected:
    typedef struct
    {
        bool is_align_end;
        uint64_t current_address;
    } bundle_state_t;

    template<int BITS>
    static void InitializeInstruction(bundle<BITS>& instruction,
        const Instructions& inputInstructions, const size_t index)
    {
        const Instruction& inputInstruction = GetInputInstruction(inputInstructions, index);
        instruction.value = CodasipBundlingInt<BITS>(inputInstruction.GetBinary().get_bin(false, false, inputInstruction.GetBitWidth()), index);
        instruction.size = inputInstruction.GetBitWidth();
        FillFixupInfo(instruction.value, inputInstruction);
    }
    template<int BITS>
    static void ParcelInstruction(bundle<BITS>& res, const unsigned int parcelBits)
    {
        // Does nothing when invalid operands are given
        if (res.size % parcelBits)
        {
            return;
        }
        const unsigned int parcelCount = res.size / parcelBits;
        // Do parceling
        // 64bit instruction and 4 parcel bytes: (AAAA BBBB) (CCCC DDDD) => (CCCC DDDD) (AAAA BBBB)
        // 64bit instruction and 2 parcel bytes: (AAAA) (BBBB) (CCCC) (DDDD) => (DDDD) (CCCC) (BBBB) (AAAA)
        bundle<BITS> tmp;
        tmp.value = res.value;
        tmp.size = res.size;
        res.value = 0;
        for (unsigned int i = 0; i < parcelCount; i++)
        {
            res.value <<= parcelBits;
            res.value |= ((tmp.value >> (i * parcelBits)) & codasip::BitMask<uint64_t>(parcelBits));
        }
    }
    template<int BITS>
    static void SplitBundleToParts(Parts& parts, const unsigned int slotBitWidth, bundle<BITS>& res)
    {
        // Resulting bundle is already moved to the right of bundle:
        // AAAAAAAABBBBBBBBCCCCCCCC........ => ........AAAAAAAABBBBBBBBCCCCCCCC
        CHECK_CONDITION((res.size % slotBitWidth) == 0) << "Output bundle ("
            << res.size << ") is not divisible by slot bit-width " << slotBitWidth << ".";
        uint32_t readBits = res.size;
        const unsigned int slotCount = res.size / slotBitWidth; // Bundling could remove some slots
        for (unsigned int i = 0; i < slotCount; i++)
        {
            bundle<64> dst;
            dst.value = (res.value >> (readBits - slotBitWidth)) & codasip::BitMask<uint64_t>(slotBitWidth);
            dst.size = slotBitWidth;
            readBits -= slotBitWidth;
            // Pass bit contents of output instructions to the parts, endian does not affect slots
            parts.emplace_back(dst);
        }
    }

    static void codasip_print(const char* fmt, ...);
    static void codasip_info(const int type, const char* fmt, ...);
    static void codasip_warning(const int type, const char* fmt, ...);
    static void codasip_error(const int type, const char* fmt, ...);
    static void codasip_fatal(const int rc, const char* fmt, ...);

private:
    template<int BITS>
    static void FillFixupInfo(CodasipBundlingInt<BITS>& value, const Instruction& inputInstruction)
    {
        const Instruction::Fixups& fixups = inputInstruction.GetFixups();
        for (size_t fixupIndex = 0; fixupIndex < fixups.size(); fixupIndex++)
        {
            const MCFixup& fixup = fixups[fixupIndex];
            for (size_t bit = fixup.getLsbOut(), fixupBit = fixup.getLsbValue();
                bit <= fixup.getMsbOut(); bit++, fixupBit++)
            {
                value.SetFixupBit(bit, fixupIndex, fixupBit);
            }
        }
    }
    static const Instruction& GetInputInstruction(const Instructions& inputInstructions, const size_t index);
    static void StoreFixup(Instruction& instruction, const MCFixup*& fixup,
        size_t& msbValue, size_t& lsbValue, size_t& msbOut, size_t& lsbOut,
        const size_t partOffset, const size_t partBytesSize);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline CodasipBundleFunction::Instruction::Instruction(const uint64_t bw)
  : m_Binary(0),
    m_BitWidth(bw)
{}

inline const codasip::MaxUint& CodasipBundleFunction::Instruction::GetBinary() const
{
    return m_Binary;
}

inline uint64_t CodasipBundleFunction::Instruction::GetBitWidth() const
{
    return m_BitWidth;
}

inline CodasipBundleFunction::Instruction::Fixups& CodasipBundleFunction::Instruction::GetFixups()
{
    return m_Fixups;
}

inline const CodasipBundleFunction::Instruction::Fixups& CodasipBundleFunction::Instruction::GetFixups() const
{
    return m_Fixups;
}

inline void CodasipBundleFunction::Instruction::SetBinary(const codasip::MaxUint& binary)
{
    m_Binary = binary;
}

}   // namespace llvm

#endif  // LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_BUNDLEFUNCTION_H_
