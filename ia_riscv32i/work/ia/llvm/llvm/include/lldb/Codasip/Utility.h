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
 *  \author zdeny
 *  \date   Aug 23, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_UTILITY_H_
#define INCLUDE_LLDB_CODASIP_UTILITY_H_

#include "lldb/lldb-enumerations.h"
#include "lldb/lldb-types.h"

#include "llvm/ADT/APInt.h"
#include "llvm/IR/Type.h"

namespace codasip {

// Forward declaration.
class AddressBase;


/**
 *  \brief  Convert byte array to APInt.
 */
llvm::APInt BytesToIntN(
    const uint8_t bytes[], const unsigned length, const lldb::ByteOrder byte_order);

/**
 *  \brief  Convert LLVM type to string.
 */
std::string LLVMTypeToString(llvm::Type* type);
/**
 *  \brief  Prepare correct Codasip address for reads and stores based on given LLVM type.
 */
AddressBase PrepareAddress(const lldb::addr_t& addr, llvm::Type* type);

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_UTILITY_H_
