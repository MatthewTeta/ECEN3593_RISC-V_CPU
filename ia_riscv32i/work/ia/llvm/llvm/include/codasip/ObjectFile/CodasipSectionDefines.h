/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip s.r.o. and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author Martin Ministr
 *  \date   19. 3. 2019
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONDEFINES_H_
#define INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONDEFINES_H_

#include <string>

namespace llvm {

/// Special section names
const std::string CODASIP_ADDRESS_SPACE_NAME = ".codasip_as";
const std::string CODASIP_PROFILE_INFO_NAME = ".profile_info";

typedef enum {
  CODASIP_PROFILE_FLAG_NONE = 0,
  CODASIP_PROFILE_FLAG_START = 1 << 0,
  CODASIP_PROFILE_FLAG_END = 1 << 1
} CodasipProfileFlag;

static const int CODASIP_PROFILE_INFO_ADDRESS_BYTES = 8;
static const int CODASIP_PROFILE_INFO_FLAG_BYTES = 8;

} // namespace llvm

#endif // INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONDEFINES_H_
