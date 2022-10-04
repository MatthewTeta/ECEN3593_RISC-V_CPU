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
 *  \date   Oct 25, 2012
 *  \brief
 */

#include "common/codasip_integer.h"
#include "common/toolstypes.h"
#include "os/compiler.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/simbase/codasip_interface.h"   // ForeignPayload
#include "utility/codasiputils.h"                  // IntegerToByteArray, ByteArrayToInteger

#ifndef SIMULATOR_RESOURCES_CSR_FOREIGN_H_
#    define SIMULATOR_RESOURCES_CSR_FOREIGN_H_
#    ifdef USE_DPI

#        include <svdpi.h>

namespace codasip {
namespace dpi {
namespace detail {

/**
 *  \brief  Convert source value from SystemVerilog logic vector into target
 *          type.
 *  \param  dst target to assign
 *  \param  src source value
 *  \param  bw how many bits to assign (\em src and \em dst must be big enough)
 */
template<typename T>
inline void FromSVLV(T& dst, const svLogicVecVal* src, const int bw)
{
    dst = 0;
    for (int ii = 0; ii < bw; ++ii)
    {
        dst |= (static_cast<T>((svGetBitselLogic(src, ii) == sv_1) ? 1 : 0) << ii);
    }
}

/**
 *  \brief  Convert source value into SystemVerilog logic vector.
 *  \copydetails FromSVLV()
 */
template<typename T>
inline void ToSVLV(svLogicVecVal* dst, const T& src, const int bw)
{
    for (int ii = 0; ii < bw; ++ii)
    {
        svPutBitselLogic(dst, ii, ((src >> ii) & 1) ? sv_1 : sv_0);
    }
}

inline void FromSVLV(uint8_t* dst, const svLogicVecVal* src, const int bw)
{
    for (int ii = 0, byte = 0; ii < bw; ++byte)
    {
        uint8_t dstValue = 0;
        for (int jj = 0; jj < 8 && ii < bw; ++jj, ++ii)
        {
            dstValue |= ((svGetBitselLogic(src, ii) == sv_1) ? 1 : 0) << jj;
        }
        dst[byte] = dstValue;
    }
}

inline void ToSVLV(svLogicVecVal* dst, const uint8_t* src, const int bw)
{
    for (int ii = 0, byte = 0; ii < bw; ++byte)
    {
        const uint8_t srcValue = src[byte];
        for (int jj = 0; jj < 8 && ii < bw; ++jj, ++ii)
        {
            svPutBitselLogic(dst, ii, ((srcValue >> jj) & 1) ? sv_1 : sv_0);
        }
    }
}

}   // namespace detail

template<typename T>
inline typename std::enable_if<!std::is_pointer<typename std::decay<T>::type>::value, void>::type
SVL2CI(T& dst, const svLogic src)
{
    dst = (src == sv_1);
}

template<typename T>
inline void SVLV2CI(T& dst, const svLogicVecVal* src, const int bw)
{
    detail::FromSVLV(dst, src, bw);
}

template<typename T>
inline typename std::enable_if<!std::is_pointer<typename std::decay<T>::type>::value, void>::type
CI2SVL(svLogic* dst, const T& src)
{
    *dst = (src == 1);
}

template<typename T>
inline void CI2SVLV(svLogicVecVal* dst, const T& src, const int bw)
{
    detail::ToSVLV(dst, src, bw);
}

inline void SVL2CI(uint8_t* dst, const svLogic src)
{
    *dst = (src == sv_1);
}

inline void CI2SVL(svLogic* dst, const uint8_t* src)
{
    *dst = (*src == 1);
}

}   // namespace dpi
}   // namespace codasip

#    endif   // USE_DPI

namespace codasip {
namespace foreign {

inline void
MaskToByteArray(uint8_t* dst, const unsigned int len, const unsigned int bi, const unsigned int bc)
{
    for (unsigned int ii = 0; ii < len; ++ii)
    {
        if (ii >= bi && ii <= (bi + bc - 1))
        {
            dst[ii] = 0xff;
        }
        else
        {
            dst[ii] = 0;
        }
    }
}

inline void
ByteArrayToMask(unsigned int& bi, unsigned int& bc, const uint8_t* dst, const unsigned int len)
{
    bi = 0;
    for (unsigned int ii = 0; ii < len; ++ii)
    {
        if (dst[ii] == 0xff)
        {
            bi = ii;
            break;
        }
    }
    bc = 0;
    for (unsigned int ii = bi; ii < len; ++ii)
    {
        if (dst[ii] == 0xff)
        {
            ++bc;
        }
    }
}

/**
 *  \brief  Conversion between foreign and simulator internal payload structures
 *          with AMBA AHB-Lite protocol.
 *  \param[out] fp foreign payload structure
 *  \param[in]  cp internal Codasip payload structure used by the simulator
 */
template<class T>
inline void Cp2FpAhb(simulator::ForeignPayload& fp, const T& cp)
{
    const int len = resources::BitWidthTypeSelector<typename T::data_type>::value /
        resources::BitWidthTypeSelector<uint8_t>::value;

    fp.SetCommand(cp.get_command());
    fp.SetHADDR(cp.get_address());
    IntegerToByteArray(fp.GetData(), len, cp.get_data());
    fp.SetHBURST(cp.get_ahb_hburst());
    fp.SetHSIZE(cp.get_ahb_hsize());
    fp.SetHREADY(cp.get_ahb_hready());
    fp.SetHRESP(cp.get_ahb_hresp());
    fp.SetDataLength(len);
    fp.SetHTRANS(cp.get_ahb_htrans());
    fp.SetHPROT(cp.get_ahb_hprot());
    fp.SetHWRITE(cp.get_ahb_hwrite());
    fp.SetHMASTLOCK(cp.get_ahb_hmastlock());
}

/**
 *  \brief  Conversion between simulator internal and foreign payload structures
 *          with AMBA AHB-Lite protocol.
 *  \param[out] cp internal Codasip payload structure used by the simulator
 *  \param[in]  fp foreign payload structure
 *  \param[in]  fillDefault True if AHB specific signals should be filled with default values
 */
template<class T>
inline void Fp2CpAhb(T& cp, const simulator::ForeignPayload& fp, const bool fillDefault = false)
{   // temporary used for the data conversion
    typename T::data_type ldata;

    if (fillDefault)
    {
        cp.set_ahb_hburst(resources::CP_AHB_SINGLE);
        cp.set_ahb_hmastlock(resources::CP_AHB_UNLOCK);
        cp.set_ahb_hprot(resources::CP_AHB_PROT_DEFAULT);
        cp.set_ahb_htrans(resources::CP_AHB_NONSEQ);
        cp.set_ahb_hready(resources::CP_AHB_READY);
        cp.set_ahb_hresp(resources::CP_AHB_OKAY);
        switch (fp.GetCommand())
        {
            case resources::CP_CMD_READ:
                cp.set_ahb_hwrite(resources::CP_AHB_READ);
                break;
            case resources::CP_CMD_WRITE:
                cp.set_ahb_hwrite(resources::CP_AHB_WRITE);
                break;
        }
        cp.set_ahb_hsize(cp.get_ahb_hsize(resources::BitWidthTypeSelector<typename T::data_type>::value /
            resources::BitWidthTypeSelector<uint8_t>::value));
    }
    else
    {
        cp.set_ahb_hburst(fp.GetHBURST());
        cp.set_ahb_hmastlock(fp.GetHMASTLOCK());
        cp.set_ahb_hprot(fp.GetHPROT());
        cp.set_ahb_htrans(fp.GetHTRANS());
        cp.set_ahb_hready(fp.GetHREADY());
        cp.set_ahb_hresp(fp.GetHRESP());
        cp.set_ahb_hwrite(fp.GetHWRITE());
        cp.set_ahb_hsize(fp.GetHSIZE());
    }

    cp.set_address(fp.GetHADDR());
    if (fp.GetCommand() == resources::CP_CMD_LOAD || fp.GetCommand() == resources::CP_CMD_DREAD ||
        fp.GetCommand() == resources::CP_CMD_DWRITE)
    {
        cp.set_command(static_cast<resources::Command>(fp.GetCommand()));
    }
    ByteArrayToInteger(ldata, fp.GetData(), fp.GetDataLength());
    cp.set_data(ldata);
}

/**
 *  \brief  Conversion between foreign and simulator internal payload structures
 *          with AMBA AXI4-Lite protocol.
 *  \param[out] fp foreign payload structure
 *  \param[in]  cp internal Codasip payload structure used by the simulator
 */
template<class T>
inline void Cp2FpAxi4Lite(simulator::ForeignPayload& fp, const T& cp)
{
    const int len = resources::BitWidthTypeSelector<typename T::data_type>::value /
        resources::BitWidthTypeSelector<uint8_t>::value;

    fp.SetCommand(cp.get_command());
    fp.SetAddress(cp.get_address());
    IntegerToByteArray(fp.GetData(), len, cp.get_data());
    fp.SetDataLength(len);
    fp.SetAxiProtectionMode(cp.get_axi_prot());

    fp.SetAxiValid(cp.get_axi_valid());
    fp.SetAxiReady(cp.get_axi_ready());
    IntegerToByteArray(fp.GetAxi4LiteWriteStrobe(), 1, cp.get_axi_wstrb());
    fp.SetAxiResponse(cp.get_axi_resp());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    fp.SetAxiAddressOffset(cp.get_axi_address_offset());
    fp.SetAxiTransferSize(cp.get_axi_transfer_size());
}

/**
 *  \brief  Conversion between simulator internal and foreign payload structures
 *          with AMBA AXI4-Lite protocol.
 *  \param[out] cp internal Codasip payload structure used by the simulator
 *  \param[in]  fp foreign payload structure
 */
template<class T>
inline void Fp2CpAxi4Lite(T& cp, const simulator::ForeignPayload& fp)
{
    typename T::data_type ldata;
    // common or reused members
    cp.set_command(static_cast<resources::Command>(fp.GetCommand()));
    cp.set_address(fp.GetAddress());
    ByteArrayToInteger(ldata, fp.GetData(), fp.GetDataLength());
    cp.set_data(ldata);
    auto writeStrobeDst = cp.get_axi_wstrb();
    ByteArrayToInteger(writeStrobeDst, fp.GetAxi4LiteWriteStrobe(), 1);
    cp.set_axi_wstrb(writeStrobeDst);
    cp.set_axi_prot(fp.GetAxiProtectionMode());
    cp.set_axi_valid(fp.GetAxiValid());
    cp.set_axi_ready(fp.GetAxiReady());
    cp.set_axi_resp(fp.GetAxiResponse());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    cp.set_axi_address_offset(fp.GetAxiAddressOffset());
    cp.set_axi_transfer_size(fp.GetAxiTransferSize());
}

/**
 *  \brief  Conversion between foreign and simulator internal payload structures
 *          with AMBA AXI4 protocol.
 *  \param[out] fp foreign payload structure
 *  \param[in]  cp internal Codasip payload structure used by the simulator
 */
template<class T>
inline void Cp2FpAxi4(simulator::ForeignPayload& fp, const T& cp)
{
    const int len = resources::BitWidthTypeSelector<typename T::data_type>::value /
        resources::BitWidthTypeSelector<uint8_t>::value;

    const unsigned writeStrobeSize = (len / 8) ? (len / 8) : 1;

    fp.SetCommand(cp.get_command());
    fp.SetAddress(cp.get_address());
    IntegerToByteArray(fp.GetData(), len, cp.get_data());
    fp.SetDataLength(len);
    fp.SetAxi4ProtectionMode(cp.get_axi_prot());
    fp.SetAxi4Valid(cp.get_axi_valid());
    fp.SetAxi4Ready(cp.get_axi_ready());
    IntegerToByteArray(fp.GetAxi4WriteStrobe(), writeStrobeSize, cp.get_axi_wstrb());
    fp.SetAxi4Response(cp.get_axi_resp());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    fp.SetAxi4AddressOffset(cp.get_axi_address_offset());
    fp.SetAxi4TransferSize(cp.get_axi_transfer_size());
    fp.SetAxi4Burst(cp.get_axi_burst());
    fp.SetAxi4Cache(cp.get_axi_cache());
    fp.SetAxi4Id(cp.get_axi_id());
    fp.SetAxi4Last(cp.get_axi_last());
    fp.SetAxi4Len(cp.get_axi_len());
    fp.SetAxi4Lock(cp.get_axi_lock());
    fp.SetAxi4QOS(cp.get_axi_qos());
    fp.SetAxi4Region(cp.get_axi_region());
}

/**
 *  \brief  Conversion between simulator internal and foreign payload structures
 *          with AMBA AXI4 protocol.
 *  \param[out] cp internal Codasip payload structure used by the simulator
 *  \param[in]  fp foreign payload structure
 */
template<class T>
inline void Fp2CpAxi4(T& cp, const simulator::ForeignPayload& fp)
{
    const int len = resources::BitWidthTypeSelector<typename T::data_type>::value /
        resources::BitWidthTypeSelector<uint8_t>::value;

    const unsigned writeStrobeSize = (len / 8) ? (len / 8) : 1;

    typename T::data_type ldata;
    // common or reused members
    cp.set_command(static_cast<resources::Command>(fp.GetCommand()));
    cp.set_address(fp.GetAddress());
    ByteArrayToInteger(ldata, fp.GetData(), fp.GetDataLength());
    cp.set_data(ldata);
    cp.set_axi_prot(fp.GetAxi4ProtectionMode());
    cp.set_axi_valid(fp.GetAxi4Valid());
    cp.set_axi_ready(fp.GetAxi4Ready());
    auto writeStrobeDst = cp.get_axi_wstrb();
    ByteArrayToInteger(writeStrobeDst, fp.GetAxi4WriteStrobe(), writeStrobeSize);
    cp.set_axi_wstrb(writeStrobeDst);
    cp.set_axi_resp(fp.GetAxi4Response());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    cp.set_axi_address_offset(fp.GetAxi4AddressOffset());
    cp.set_axi_transfer_size(fp.GetAxi4TransferSize());
    cp.set_axi_burst(fp.GetAxi4Burst());
    cp.set_axi_cache(fp.GetAxi4Cache());
    cp.set_axi_id(fp.GetAxi4Id());
    cp.set_axi_last(fp.GetAxi4Last());
    cp.set_axi_len(fp.GetAxi4Len());
    cp.set_axi_lock(fp.GetAxi4Lock());
    cp.set_axi_qos(fp.GetAxi4QOS());
    cp.set_axi_region(fp.GetAxi4Region());
}

/**
 *  \brief  Conversion between foreign and simulator internal payload structures
 *          with Codasip Processor Bus protocol.
 *  \tparam BC byte count, number of bytes per word. It is used to correctly
 *          encode write strobes.
 *  \param[out] fp foreign payload structure
 *  \param[in]  cp internal Codasip payload structure used by the simulator
 */
template<unsigned BC, class T>
inline void Cp2FpCpb(simulator::ForeignPayload& fp, const T& cp)
{
    enum
    {
        WORD_BITS = resources::BitWidthTypeSelector<typename T::data_type>::value,
        BYTE_BITS = resources::BitWidthTypeSelector<uint8_t>::value,
        DATA_LENGTH = (WORD_BITS + BYTE_BITS - 1) / BYTE_BITS
    };

    fp.SetCommand(cp.get_command());
    fp.SetAddress(cp.get_address());
    fp.SetCpbAReady(cp.get_cpb_aready());
    fp.SetCpbAValid(cp.get_cpb_avalid());
    fp.SetCpbWrite(cp.get_cpb_write());
    IntegerToByteArray(fp.GetData(), DATA_LENGTH, cp.get_data());

    if (BC == 1)
    {   // expand single bit to the whole word
        std::memset(fp.GetCpbWriteStrobe(), !cp.get_cpb_wstrb() ? 0 : -1, DATA_LENGTH);
    }
    else
    {
        for (unsigned ii = 0; ii < DATA_LENGTH; ++ii)
        {   // byte is 8 bits wide
            fp.GetCpbWriteStrobe()[ii] = 0 - (static_cast<uint8_t>(cp.get_cpb_wstrb() >> ii) & 1u);
        }
    }
    fp.SetDataLength(DATA_LENGTH);
    fp.SetCpbValid(cp.get_cpb_valid());
    fp.SetCpbResponse(cp.get_cpb_resp());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    fp.SetCpbAddressOffset(cp.get_cpb_address_offset());
    fp.SetCpbTransferSize(cp.get_cpb_transfer_size());
}

/**
 *  \brief  Conversion between simulator internal and foreign payload structures
 *          with Codasip Processor Bus protocol.
 *  \tparam BC byte count, number of bytes per word. It is used to correctly
 *          encode write strobes.
 *  \param[out] cp internal Codasip payload structure used by the simulator
 *  \param[in]  fp foreign payload structure
 */
template<unsigned BC, class T>
inline void Fp2CpCpb(T& cp, const simulator::ForeignPayload& fp)
{
    enum
    {
        WORD_BITS = resources::BitWidthTypeSelector<typename T::data_type>::value,
        BYTE_BITS = resources::BitWidthTypeSelector<uint8_t>::value,
        DATA_LENGTH = (WORD_BITS + BYTE_BITS - 1) / BYTE_BITS
    };

    typename T::data_type ldata;
    // common or reused members
    cp.set_cpb_aready(fp.GetCpbAReady());
    cp.set_cpb_avalid(fp.GetCpbAValid());
    cp.set_cpb_write(fp.GetCpbWrite());
    // command must be set after avalid/write because the set the command as well
    cp.set_command(static_cast<resources::Command>(fp.GetCommand()));
    cp.set_address(fp.GetAddress());

    ByteArrayToInteger(ldata, fp.GetData(), fp.GetDataLength());
    cp.set_data(ldata);
    if (BC == 1)
    {   // reduce WSTRB to single bit
        ByteArrayToInteger(ldata, fp.GetCpbWriteStrobe(), fp.GetDataLength());
        cp.set_cpb_wstrb(static_cast<bool>(ldata));
    }
    else
    {
        ldata = 0u;
        for (int ii = DATA_LENGTH - 1; ii >= 0; --ii)
        {   // reduce WSTRB from 8 to one bit
            ldata <<= 1;
            ldata |= fp.GetCpbWriteStrobe()[ii] != 0;
        }
        cp.set_cpb_wstrb(ldata);
    }
    cp.set_cpb_valid(fp.GetCpbValid());
    cp.set_cpb_resp(fp.GetCpbResponse());
    // set the address offset and transfer size (BC)
    // they are required for internal checks of data alignment in IA mode
    cp.set_cpb_address_offset(fp.GetCpbAddressOffset());
    cp.set_cpb_transfer_size(fp.GetCpbTransferSize());
}

}   // namespace foreign
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_FOREIGN_H_
