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
 *  \date   29. 10. 2014
 *  \brief  Definition of the class codasip::foreign::fli::FliSignalArrayReader
 *          and codasip::foreign::fli::FliVariableArrayReader.
 */

#ifndef FLIMEMORY_FLI_READER_H_
#define FLIMEMORY_FLI_READER_H_

#include "simulator/flimemory/fli_reader_base.h"

namespace codasip {
namespace foreign {
namespace fli {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  FliSignalArrayReader
 *  \brief  Simple class to read values from array of std_logic or std_logic_vector
 *          declared as VHDL signal using FLI.
 *  \}
 */
class FliSignalArrayReader : public FliArrayReaderBase
{
public:
    /**
     *  \brief  Initialize used value format.
     */
    explicit FliSignalArrayReader();
    /**
     *  \brief  Deallocate stored array of signal pointers, but not the pointers.
     */
    ~FliSignalArrayReader();
    /**
     *  \brief  Read single array element and store it in output parameter based
     *          on current argument values.
     */
    void Read() override;

protected:
    /**
     *  \copydoc FliArrayReaderBase::CheckAndStorePath()
     */
    void CheckAndStorePath(vpiHandle handle, const bool finishOnError) override;

private:
    void SetBitWidth();

    /// array of signal identifiers, where every signal identifier provides
    /// access to array element, valid after calling the Compile()
    mtiSignalIdT* m_Array;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline FliSignalArrayReader::FliSignalArrayReader()
  : FliArrayReaderBase()
  , m_Array(NULL)
{}

////////////////////////////////////////////////////////////////////////////////
inline FliSignalArrayReader::~FliSignalArrayReader()
{
    mti_VsimFree(m_Array);
    m_Array = NULL;
}

////////////////////////////////////////////////////////////////////////////////
inline void FliSignalArrayReader::Read()
{
    vpiHandle target = NULL;
    const auto addr = ReadCurrentTargetAndAddr(target, m_Array);
    mti_GetArraySignalValue(m_Array[addr], GetValueBuffer());
    DoRead(target);
}

////////////////////////////////////////////////////////////////////////////////
inline void FliSignalArrayReader::CheckAndStorePath(vpiHandle handle, const bool finishOnError)
{
    ArrayReaderBase::CheckAndStorePath(handle, finishOnError);
    const std::string path =
        vpi::CheckAndReadStringParam(handle, GetErrorPrefix(), GetTaskName(), 2, !finishOnError);
    if (!path.empty() || finishOnError)
    {
        const std::string rtlPath = CheckFullHierPath(path);
        m_Array = CheckArrayAttributes(mti_FindSignal(const_cast<char*>(rtlPath.c_str())),
            rtlPath,
            GetErrorPrefix());
        SetBitWidth();
        AllocateVectorValue();
        AllocateFliVectorValue();
    }
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Detect bit-width of single array element and store it for later
 *          usage.
 */
inline void FliSignalArrayReader::SetBitWidth()
{
    CHECK_NOT_NULL(m_Array);
    FliArrayReaderBase::SetBitWidth(mti_GetSignalType(m_Array[0]));
}

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  FliVariableArrayReader
 *  \brief  Simple class to read values from array of std_logic or std_logic_vector
 *          declared as VHDL variable using FLI.
 *  \}
 */
class FliVariableArrayReader : public FliArrayReaderBase
{
public:
    /**
     *  \brief  Initialize used value format.
     */
    explicit FliVariableArrayReader();
    /**
     *  \brief  Deallocate stored array of variable pointers, but not the pointers.
     */
    ~FliVariableArrayReader();
    /**
     *  \brief  Read single array element and store it in output parameter based
     *          on current argument values.
     */
    void Read() override;

protected:
    /**
     *  \copydoc FliArrayReaderBase::CheckAndStorePath()
     */
    void CheckAndStorePath(vpiHandle handle, const bool finishOnError) override;

private:
    void SetBitWidth();

    /// array of signal identifiers, where every signal identifier provides
    /// access to array element, valid after calling the Compile()
    mtiVariableIdT* m_Array;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline FliVariableArrayReader::FliVariableArrayReader()
  : FliArrayReaderBase()
  , m_Array(NULL)
{}

////////////////////////////////////////////////////////////////////////////////
inline FliVariableArrayReader::~FliVariableArrayReader()
{
    mti_VsimFree(m_Array);
    m_Array = NULL;
}

////////////////////////////////////////////////////////////////////////////////
inline void FliVariableArrayReader::Read()
{
    vpiHandle target = NULL;
    const auto addr = ReadCurrentTargetAndAddr(target, m_Array);
    mti_GetArrayVarValue(m_Array[addr], GetValueBuffer());
    DoRead(target);
}

////////////////////////////////////////////////////////////////////////////////
inline void FliVariableArrayReader::CheckAndStorePath(vpiHandle handle, const bool finishOnError)
{
    ArrayReaderBase::CheckAndStorePath(handle, finishOnError);
    const std::string path =
        vpi::CheckAndReadStringParam(handle, GetErrorPrefix(), GetTaskName(), 2, !finishOnError);
    if (!path.empty() || finishOnError)
    {
        const std::string rtlPath = CheckFullHierPath(path);
        m_Array = CheckArrayAttributes(mti_FindVar(const_cast<char*>(rtlPath.c_str())),
            rtlPath,
            GetErrorPrefix());
        SetBitWidth();
        AllocateVectorValue();
        AllocateFliVectorValue();
    }
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Detect bit-width of single array element and store it for later
 *          usage.
 */
inline void FliVariableArrayReader::SetBitWidth()
{
    CHECK_NOT_NULL(m_Array);
    FliArrayReaderBase::SetBitWidth(mti_GetVarType(m_Array[0]));
}

}   // namespace fli
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_FLI_VHDL_READER_H_
