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
 *  \brief  Definition of the class codasip::foreign::vpi::ArrayReader.
 */

#ifndef FLIMEMORY_VPI_READER_H_
#define FLIMEMORY_VPI_READER_H_

#include "simulator/flimemory/vpi_common.h"

namespace codasip {
namespace foreign {
namespace vpi {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ArrayReader
 *  \brief  Simple class to read values of addressable resources using VPI. The
 *          class does not contain constructor, because it is allocated using
 *          malloc.
 *  \}
 */
class ArrayReader : public ArrayReaderBase, private VpiAddressAccessor
{
public:
    /**
     *  \brief  Initialize used value format.
     */
    explicit ArrayReader();
    /**
     *  \brief  Store user data for stored task.
     */
    void StoreUserData();
    /**
     *  \brief  Read single array element and store it in output parameter based
     *          on current argument values.
     */
    void Read();

protected:
    /**
     *  \copydoc ArrayReaderBase::CheckAndStorePath()
     */
    void CheckAndStorePath(vpiHandle handle, const bool finishOnError) override;

private:
    /// structure used to read values using VPI
    s_vpi_value m_Value;
};

}   // namespace vpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VPI_READER_H_
