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
 *  \date   7. 11. 2014
 *  \brief  Definition of the class codasip::foreign::fli::FliArrayReaderBase.
 */

#ifndef FLIMEMORY_FLI_READER_BASE_H_
#define FLIMEMORY_FLI_READER_BASE_H_

#include "simulator/flimemory/fli_common.h"
#include "simulator/flimemory/vpi_common.h"

#include <limits>

namespace codasip {
namespace foreign {
namespace fli {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  FliArrayReaderBase
 *  \brief  Simple base class to read values of addressable resources using FLI.
 *  \}
 */
class FliArrayReaderBase : public vpi::ArrayReaderBase
{
public:
    /// underlying type return by FLI value functions
    typedef char ValueType;

    /**
     *  \brief  Default constructor.
     */
    FliArrayReaderBase();
    /**
     *  \brief  Deallocate stored array of signal pointers, but not the pointers.
     */
    virtual ~FliArrayReaderBase();
    /**
     *  \brief  Store user data for stored task.
     */
    void StoreUserData();
    /**
     *  \brief  Read single array element and store it in output parameter based
     *          on current argument values.
     */
    virtual void Read() = 0;

protected:
    enum
    {   /// PLI stores 4state logic using pair of 32bit integer values
        PLI_INT32_BIT_WIDTH = std::numeric_limits<PLI_UINT32>::digits
    };
    /**
     *  \brief  Access bit-width of single array element.
     */
    uint32_t GetBitWidth() const;
    /**
     *  \brief  Return FLI value buffer.
     */
    ValueType* GetValueBuffer();
    /**
     *  \brief  Detect bit-width of single array element and store it for later
     *          usage.
     */
    void SetBitWidth(mtiTypeIdT typeId);
    /**
     *  \brief  Update value of the bit-width of single array element.
     *  \param  value updated value
     */
    void SetBitWidth(const uint32_t value);
    /**
     *  \brief  Allocate enough space for vector value pair.
     */
    void AllocateVectorValue();
    /**
     *  \brief  Compute vector size required to hold Verilog vector value.
     */
    uint32_t GetValueVectorSize() const;
    /**
     *  \brief  Allocate enough space for FLI value.
     */
    void AllocateFliVectorValue();
    /**
     *  \brief  Convert value stored in internal buffer and drive the target
     *          using the VPI value structure.
     *  \param  target handle to the target
     */
    void DoRead(vpiHandle target);
    /**
     *  \brief  Update value of the target handle with value stored in internal
     *          VPI value structure.
     *  \param  target handle to the target
     */
    void UpdateTarget(vpiHandle target);

    /// structure used to write values using VPI
    t_vpi_value m_Value;

private:
    void ReadImpl();

    /// bit-width of a single array element
    uint32_t m_BitWidth;
    /// union which should be used to access values using FLI API
    ValueType* m_ValueBuffer;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline FliArrayReaderBase::FliArrayReaderBase()
  : m_BitWidth(0)
  , m_ValueBuffer(nullptr)
{
    m_Value.value.vector = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
inline FliArrayReaderBase::~FliArrayReaderBase()
{
    delete[] m_Value.value.vector;
    m_Value.value.vector = nullptr;

    delete[] GetValueBuffer();
    m_ValueBuffer = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::StoreUserData()
{
    vpi_put_userdata(GetTask(), this);
}

////////////////////////////////////////////////////////////////////////////////
//                            Protected interface                             //
////////////////////////////////////////////////////////////////////////////////
inline uint32_t FliArrayReaderBase::GetBitWidth() const
{
    return m_BitWidth;
}

////////////////////////////////////////////////////////////////////////////////
inline FliArrayReaderBase::ValueType* FliArrayReaderBase::GetValueBuffer()
{
    return m_ValueBuffer;
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::SetBitWidth(mtiTypeIdT typeId)
{
    if (mti_GetTypeKind(typeId) == MTI_TYPE_ARRAY)
    {
        SetBitWidth(mti_TickLength(typeId));
    }
    else
    {
        SetBitWidth(1);
    }
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::SetBitWidth(const uint32_t value)
{
    m_BitWidth = value;
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::AllocateVectorValue()
{
    m_Value.format = vpiVectorVal;
    m_Value.value.vector = new t_vpi_vecval[GetValueVectorSize()];
    for (uint32_t ii = 0; ii < GetValueVectorSize(); ++ii)
    {
        m_Value.value.vector[ii].aval = 0;
        m_Value.value.vector[ii].bval = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline uint32_t FliArrayReaderBase::GetValueVectorSize() const
{
    return ((GetBitWidth() + PLI_INT32_BIT_WIDTH) / PLI_INT32_BIT_WIDTH) -
        ((GetBitWidth() % PLI_INT32_BIT_WIDTH) == 0);
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::AllocateFliVectorValue()
{
    m_ValueBuffer = new ValueType[GetBitWidth()];
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::DoRead(vpiHandle target)
{
    ReadImpl();
    UpdateTarget(target);
}

////////////////////////////////////////////////////////////////////////////////
inline void FliArrayReaderBase::UpdateTarget(vpiHandle target)
{
    vpi_put_value(target, &m_Value, nullptr, vpiNoDelay);
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Provides read implementation from array and writes the result to
 *          VPI value structure in 4-state vector format.
 */
inline void FliArrayReaderBase::ReadImpl()
{
    for (mtiInt32T vecIdx = 0, bitIdx = GetBitWidth(); bitIdx > 0; ++vecIdx)
    {
        PLI_INT32 aval = 0, bval = 0;
        for (mtiInt32T ii = 0; (ii < PLI_INT32_BIT_WIDTH) && (bitIdx > 0); --bitIdx, ++ii)
        {
            switch (GetValueBuffer()[bitIdx - 1])
            {
                case STD_LOGIC_0:
                    // no change, zero remains zero
                    break;
                case STD_LOGIC_1:
                    aval |= 1 << ii;
                    break;
                case STD_LOGIC_Z:
                    // aval is zero
                    bval |= 1 << ii;
                    break;
                default:
                    // default value is X
                    aval |= 1 << ii;
                    bval |= 1 << ii;
                    break;
            }
        }
        m_Value.value.vector[vecIdx].aval = aval;
        m_Value.value.vector[vecIdx].bval = bval;
    }
}

}   // namespace fli
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_FLI_READER_BASE_H_
