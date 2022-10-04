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
 * Codasip s.r.o. and are protected by trade secret and copyright law. In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Albert Miko
 *  \date   2019-12-04
 *  \brief  SBDynamicRegisterInfo wrapper for Plugins/Utility/DynamicRegisterInfo.
 */

#ifndef LLDB_CODASIP_SBDynamicRegisterInfo_h_
#define LLDB_CODASIP_SBDynamicRegisterInfo_h_

#include "lldb/API/SBDefines.h"
#include "lldb/API/SBError.h"

namespace lldb {

class LLDB_API SBDynamicRegisterInfo {
public:
  size_t GetNumRegisters() const;

  size_t GetNumRegisterSets() const;

  size_t GetRegisterDataByteSize() const;

  const lldb_private::RegisterInfo *GetRegisterInfoAtIndex(uint32_t i) const;

  const lldb_private::RegisterSet *GetRegisterSet(uint32_t i) const;

  void SetDynamicRegisterInfo(const DynamicRegisterInfo* dri);

protected:
  const DynamicRegisterInfo* GetSP() const;

  const DynamicRegisterInfo* m_opaque_ptr = nullptr;
}; // SBDynamicRegisterInfo

} // namespace lldb

#endif // LLDB_CODASIP_SBDynamicRegisterInfo_h_
