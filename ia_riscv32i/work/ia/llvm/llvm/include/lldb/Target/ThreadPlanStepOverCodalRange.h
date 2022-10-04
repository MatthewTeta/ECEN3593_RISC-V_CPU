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
 *  \date   2019-05-30
 *  \brief  Symbol file for codal debug info support.
 */

#ifndef liblldb_ThreadPlanStepOverCodalRange_h_
#define liblldb_ThreadPlanStepOverCodalRange_h_

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Target/ThreadPlanShouldStopHere.h"

namespace lldb_private {

class ThreadPlanStepOverCodalRange : public ThreadPlan, ThreadPlanShouldStopHere {
public:
  ThreadPlanStepOverCodalRange(Thread &thread, lldb::RunMode stop_others);

  ~ThreadPlanStepOverCodalRange() override;

  void GetDescription(Stream *s, lldb::DescriptionLevel level) override;
  bool ShouldStop(Event *event_ptr) override;
  bool ValidatePlan(lldb_private::Stream*) override;
  bool WillStop() override;
  bool MischiefManaged() override;
  bool IsStepInCodal() const override;
protected:
  lldb::StateType GetPlanRunState() override;

  bool DoPlanExplainsStop(Event *event_ptr) override;
  bool DoWillResume(lldb::StateType resume_state, bool current_plan) override;

  void SetFlagsToDefault() override {
    GetFlags().Set(ThreadPlanStepOverCodalRange::s_default_flag_values);
  }
private:
  static uint32_t s_default_flag_values;

  /// max depth of codal stack frame where we should stop
  int32_t m_target_codal_frame_depth;

  DISALLOW_COPY_AND_ASSIGN(ThreadPlanStepOverCodalRange);
}; // ThreadPlanStepOverCodalRange

} // namespace lldb_private

#endif // liblldb_ThreadPlanStepOverCodalRange_h_
