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
 *  \author Potesil Josef
 *  \date   7. 6. 2016
 *  \brief  Declaration of the class codasip::foreign::vhpi::ArrayReader.
 */

#ifndef FLIMEMORY_VHPI_READER_H_
#define FLIMEMORY_VHPI_READER_H_

#include "simulator/flimemory/vhpi_common.h"
#include "simulator/flimemory/vpi_common.h"

namespace codasip {
namespace foreign {
namespace vhpi {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ArrayReader
 *  \brief  Implements reading of VHDL one-dimensional arrays of \em std_logic or
 *          \em std_logic_vector using VHPI. The value will be stored into
 *          Verilog variables/registers using VPI.
 *  \}
 */
class ArrayReader : public vpi::ArrayReaderBase, private VhpiAddressAccessor
{
public:
    /// local shortcut to target API
    typedef vhpiValueT ValueType;
    /**
     *  \brief  Initialize used value formats to automatic detection of native
     *          format.
     */
    ArrayReader();
    /**
     *  \brief  Deallocate memory buffer if allocated.
     */
    ~ArrayReader();
    /**
     *  \brief  Store user data for stored task.
     */
    void StoreUserData();
    /**
     *  \brief  Read single array element and store it in output parameter based
     *          on current argument values.
     */
    void Read();
    /**
     *  \copydoc vpi::CheckArrayAttributes()
     */
    static unsigned CheckArrayAttributes(HandleType ram,
        const std::string& hdl,
        const std::string& prefix = std::string());

protected:
    /**
     *  \copydoc vpi::ArrayReaderBase::CheckAndStorePath()
     */
    void CheckAndStorePath(vpiHandle handle, const bool finishOnError) override;
    /**
     *  \copydoc vpi::ArrayReaderBase::CheckTarget()
     */
    void CheckTarget(vpiHandle handle) override;

private:
    static void DoCheckArrayAttributes(HandleType, const std::string&, const std::string&);
    static unsigned DoCheckArrayElemAttributes(HandleType, const std::string&, const std::string&);
    HandleType GetRAM();
    void ConvertValueVhpi2Vpi();
    void ConvertValueVhpi2VpiFromEnum();
    void ConvertValueVhpi2VpiFromEnumVec();
    void ClearTargetVector();
    unsigned GetSourceBits() const;
    unsigned GetTargetBits() const;
    unsigned GetTargetSize() const;

    /// VHPI handle to source array
    HandleType m_RAM;
    /// structure used to read values using VHPI
    ValueType m_SourceValue;
    /// structure used to write values using VPI
    t_vpi_value m_TargetValue;
    /// bit-width of the source value (single array element)
    unsigned m_SourceBits;
    /// bit-width of the destination variable
    unsigned m_TargetBits;
};

////////////////////////////////////////////////////////////////////////////////
inline void ArrayReader::StoreUserData()
{
    vpi_put_userdata(GetTask(), this);
}

}   // namespace vhpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VHPI_READER_H_
