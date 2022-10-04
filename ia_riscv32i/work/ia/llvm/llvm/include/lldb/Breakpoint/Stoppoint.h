//===-- Stoppoint.h ---------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_Stoppoint_h_
#define liblldb_Stoppoint_h_

#include "lldb/Utility/UserID.h"
#include "lldb/lldb-private.h"

namespace lldb_private {

class Stoppoint {
public:
  // Constructors and Destructors
  Stoppoint();

  virtual ~Stoppoint();

  // Methods
  virtual void Dump(Stream *) = 0;

  virtual bool IsEnabled() = 0;

  virtual void SetEnabled(bool enable) = 0;

  lldb::break_id_t GetID() const;

  void SetID(lldb::break_id_t bid);

  /// ==== CODASIP ====
  bool IsCodalStoppoint() const;
  void SetIsCodalStoppoint(const bool is_codal_stop);
  /// =================
protected:
  lldb::break_id_t m_bid;

  /// ==== CODASIP ====
  bool m_codal_stoppoint;
  /// =================
private:
  // For Stoppoint only
  DISALLOW_COPY_AND_ASSIGN(Stoppoint);
};

} // namespace lldb_private

#endif // liblldb_Stoppoint_h_
