/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2018 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip Ltd and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip Ltd and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author jan
 *  \date   19 Feb 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_MISC_CUSTOMMVT_H_
#define INCLUDE_CODASIP_MISC_CUSTOMMVT_H_

namespace llvm {

class MVT;

static inline unsigned getCustomSizeInBits(MVT VT);
static MVT getCustomVectorVT(MVT VT, unsigned NumElements);
static inline MVT getCustomVectorElementType(MVT VT);
static inline unsigned getCustomVectorNumElements(MVT VT);

} // namespace llvm

#endif // INCLUDE_CODASIP_MISC_CUSTOMMVT_H_
