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
 *  \date   22. 10. 2014
 *  \brief  Definitions of classes and functions implementing common
 *          functionality using VPI API.
 */

#ifndef FLIMEMORY_VPI_COMMON_H_
#define FLIMEMORY_VPI_COMMON_H_

#include "simulator/flimemory/foreign_common.h"
#include "utility/check_condition.h"
#include "utility/number_cast.h"

#include <sv_vpi_user.h>

#define CODASIP_FOREIGN_UNSUPPORTED_VPI_FORMAT(value)                               \
    THROW_ERROR() << "Unsupported VPI format of data parameter: " << (value).format \
                  << ". Supported formats are "                                     \
                  << "vpiIntVal(" << vpiIntVal << ") and "                          \
                  << "vpiScalarVal(" << vpiScalarVal << "), "                       \
                  << "vpiVectorVal(" << vpiVectorVal << ")."

namespace codasip {
namespace foreign {
namespace vpi {

// error messages
const std::string ERR_NULL_HANDLE_I = "Failed to find register/memory array '";
const std::string ERR_NULL_HANDLE_II = "'. Please, check whether or not it is a valid hierarchical "
                                       "path.";

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ReadArrayArgs
 *  \brief  Simple class to store arguments of function designed to read values
 *          of addressable resources using VPI.
 *  \}
 */
class ReadArrayArgs
{
public:
    /**
     *  \brief  Initialize internal attributes to default value
     */
    explicit ReadArrayArgs();
    /**
     *  \{
     *  \brief  Provide access to stored attribute.
     */
    vpiHandle GetRAM();
    vpiHandle GetTask();
    vpiHandle GetPath();
    /**
     *  \} \{
     *  \brief  Update value of given attribute.
     *  \param  value new updated value
     */
    void SetRam(vpiHandle value);
    void SetTask(vpiHandle value);
    void SetPath(vpiHandle value);
    /** \} */
private:
    /// handle to the RAM signal representing array storage
    vpiHandle m_RAM;
    /// handle to parent task instance
    vpiHandle m_Task;
    /// handle to second function argument holding HDL path
    vpiHandle m_Path;
};

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ArrayReaderBase
 *  \brief  Simple class to read values of addressable resources using VPI. The
 *          class does not contain constructor, because it is allocated using
 *          malloc.
 *  \}
 */
class ArrayReaderBase : public ReadArrayArgs
{
public:
    /**
     *  \brief  Initialize used value format.
     */
    explicit ArrayReaderBase();
    /**
     *  \brief  Default virtual destructor.
     */
    virtual ~ArrayReaderBase();
    /**
     *  \brief  Check parameters of given task and save handles to its arguments
     *          for later usage.
     *  \param  task source task to compile
     */
    void Compile(vpiHandle task);

protected:
    /**
     *  \brief  Check output data parameter where read data should be stored and
     *          store VPI handle for later usage.
     *  \param  handle source VPI handle to check
     */
    virtual void CheckTarget(vpiHandle handle);
    /**
     *  \brief  Check second parameter with hierarchical path to the array
     *          module, checks its existence and attributes. Stores VPI handle
     *          for later usage.
     *  \param  handle source VPI handle to check
     *  \param  finishOnError indicates whether to finish simulation when path
     *          is not valid or not (do nothing).
     */
    virtual void CheckAndStorePath(vpiHandle handle, const bool finishOnError);
    /**
     *  \brief  Check third parameter with read address. Stores VPI handle for
     *          later usage.
     *  \param  handle source VPI handle to check
     */
    void CheckAddress(vpiHandle handle);
    /**
     *  \brief  Return name of the task.
     */
    std::string GetTaskName();
    /**
     *  \brief  Generates file and line prefix for all error messages which
     *          should be displayed to the end-user.
     */
    std::string GetErrorPrefix();
    /**
     *  \brief  Read value of current address.
     *  \param  handle updated address handle
     */
    int32_t ReadAddr(vpiHandle handle);
    /**
     *  \brief  Read value of current address. If given pointer is not valid,
     *          updates target, path and address internals.
     *  \param  ram used to detect whether to update internals or not
     */
    int32_t ReadCurrentTargetAndAddr(vpiHandle& target, const void* ram);

private:
    /// structure used to read address value using VPI
    s_vpi_value m_AddrValue;
    /// bit-width of the actual address
    PLI_INT32 m_AddrBits;
};

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ::codasip::foreign::vpi::ArrayIterator
 *  \brief  Wrapper class used to work with ::codasip::foreign::AddressAccessor.
 *  \}
 */
class ArrayIterator
{
public:
    /// local shortcut to target API handle type
    typedef vpiHandle HandleType;
    /// local shortcut to target addresses type
    typedef codasip_address_t AddressType;
    /**
     *  \brief  Access array element and move the iterator to the next element.
     *  \param  it source array iterator
     *  \return handle to array element pointed by given iterator
     */
    static HandleType Scan(HandleType it);
    /**
     *  \brief  Release/free previously created handle/object/iterator.
     *  \param  h source handle to release
     */
    static void Release(HandleType h);
    /**
     *  \brief  Create iterator to an array element.
     *  \param  array source array to iterate over
     */
    static HandleType CreateIterator(HandleType array);
    /**
     *  \brief  Return size of given array handle.
     *  \param  array source array to iterate over
     *  \param  elem handle to single array element (actually unused)
     */
    static AddressType Size(HandleType array, HandleType elem);
};

/// \brief  Provide array address iteration using VPI
typedef AddressAccessor<ArrayIterator> VpiAddressAccessor;

/**
 *  \brief  Sets error message to the TCL global variable and indicates fatal
 *          error.
 *  \param  msg source error message.
 */
void HandleException(const std::string& msg);

/**
 *  \brief  Set error message when application loader fails.
 *  \param  msg source error message.
 *  \param  executable file path to the executable
 *  \param  name memory storage name.
 */
void HandleLoadException(const std::string& msg, const std::string& executable, const std::string& name);

/**
 *  \brief  Return name of the task.
 *  \param  handle source handle to the task or function
 */
std::string GetTaskName(vpiHandle handle);

/**
 *  \brief  Return string holding file and line informations from given handle.
 *  \param  handle source handle to the task or function
 */
std::string GetFileLineInfo(vpiHandle handle);

/**
 *  \brief  Generates file and line prefix for all error messages which
 *          should be displayed to the end-user.
 *  \param  handle source handle to the task or function
 */
std::string GetErrorPrefix(vpiHandle handle);

/**
 *  \brief  Read argument value as simple integer value.
 *  \param  arg actual argument handle
 *  \param  value structure used to read values using VPI
 */
PLI_INT32 ReadIntegerValue(vpiHandle arg, s_vpi_value& value);

/**
 *  \brief  Read argument value as simple integer value.
 *  \param  arg actual argument handle
 */
PLI_INT32 ReadIntegerValue(vpiHandle arg);

/**
 *  \brief  Read string represented by given handle and return its value.
 *  \param  handle source argument to check and read
 *  \return Actual value of the argument
 */
std::string ReadStringValue(vpiHandle handle);

/**
 *  \brief  Indicates whether given type represents valid register/variable or not.
 *  \param  type handle type
 */
bool IsVarOrReg(const PLI_INT32 type);

/**
 *  \{
 *  \brief  Check whether given handle represents valid variable or constant of
 *          integer type and return its value.
 *  \param  handle source argument to check and read
 *  \param  prefix error message prefix should contain function name and its
 *          location (file, line) in source code
 *  \param  name description for error message
 *  \param  index argument index to improve error message
 *  \return Actual value of the argument
 */
PLI_INT32 CheckAndReadIntegerOrConstParam(vpiHandle handle,
    const std::string& prefix,
    const std::string& name,
    const PLI_INT32 index);
codasip_address_t CheckAndReadAddressParam(vpiHandle handle,
    const std::string& prefix,
    const std::string& name,
    const PLI_INT32 index);

/**
 *  \}
 *  \brief  Check whether given handle represents valid variable or constant of
 *          string type and return its value.
 *  \copydetails CheckAndReadIntegerOrConstParam()
 *  \param  allowEmpty indicates whether empty value is allowed or not
 */
std::string CheckAndReadStringParam(vpiHandle handle,
    const std::string& prefix,
    const std::string& name,
    const PLI_INT32 index,
    const bool allowEmpty = false);

/**
 *  \brief  Convert 4-state logic value of length 32 bits to simple C integer.
 *          Meta-values will be treated as zeros.
 *  \param  a first from the Verilog PLI pair representing 4-state values
 *  \param  b second from the Verilog PLI pair representing 4-state values
 */
inline PLI_INT32 Get4StateValue(const PLI_INT32 a, const PLI_INT32 b)
{   // Verilog table definition and its implementation
    // | a | b | logic value | integer value | (a & b) ^ (a) |
    // | 0 | 0 |      0      |       0       | (  0  ) 0 (0) |
    // | 1 | 0 |      1      |       1       | (  0  ) 1 (1) |
    // | 0 | 1 |      Z      |       0       | (  0  ) 0 (0) |
    // | 1 | 1 |      X      |       0       | (  1  ) 0 (1) |
    return ((a & b) ^ a);
}

/**
 *  \brief  Return number of actual parameters of given function or task.
 *  \param  systf handle representing function or task
 */
PLI_INT32 GetParameterCount(vpiHandle systf);

/**
 *  \brief  Checks whether given argument represents valid memory handle.
 *  \param[out] size stores size of the array
 *  \param[out] bits stores bit-width of single array element
 *  \param  ram actual argument handle
 *  \param  hdl source HDL path to given handle
 *  \param  prefix error message prefix
 */
void CheckArrayAttributes(codasip_address_t& size,
    unsigned& bits,
    vpiHandle ram,
    const std::string& hdl,
    const std::string& prefix = std::string());

/**
 *  \brief  Checks the Verilog HDL path and creates full hierarchical path.
 *          Removes leading "$root.".
 *  \param  hdl source Verilog HDL path
 */
std::string CheckFullHierPath(const std::string& hdl);

////////////////////////////////////////////////////////////////////////////////
inline vpiHandle ReadArrayArgs::GetRAM()
{
    return m_RAM;
}

////////////////////////////////////////////////////////////////////////////////
inline vpiHandle ReadArrayArgs::GetTask()
{
    return m_Task;
}

////////////////////////////////////////////////////////////////////////////////
inline vpiHandle ReadArrayArgs::GetPath()
{
    return m_Path;
}

////////////////////////////////////////////////////////////////////////////////
inline void ReadArrayArgs::SetRam(vpiHandle ram)
{
    m_RAM = ram;
}

////////////////////////////////////////////////////////////////////////////////
inline void ReadArrayArgs::SetTask(vpiHandle value)
{
    m_Task = value;
}

////////////////////////////////////////////////////////////////////////////////
inline void ReadArrayArgs::SetPath(vpiHandle value)
{
    m_Path = value;
}

////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::HandleType ArrayIterator::Scan(HandleType it)
{
    return vpi_scan(it);
}

////////////////////////////////////////////////////////////////////////////////
inline void ArrayIterator::Release(HandleType h)
{
    vpi_free_object(h);
}

////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::HandleType ArrayIterator::CreateIterator(HandleType array)
{
    return vpi_iterate(vpiReg, array);
}

////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::AddressType ArrayIterator::Size(HandleType array, HandleType)
{
    return vpi_get(vpiSize, array);
}

}   // namespace vpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VPI_COMMON_H_
