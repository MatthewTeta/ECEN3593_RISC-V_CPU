//===-- ThreadPlanStepInstruction.h -----------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_ThreadPlanStepCycle_h_
#define liblldb_ThreadPlanStepCycle_h_

#include "lldb/Target/Thread.h"
#include "lldb/Target/ThreadPlan.h"
#include "lldb/lldb-private.h"

namespace lldb_private {

class ThreadPlanStepCycle : public ThreadPlan {
public:
  ThreadPlanStepCycle(Thread &thread, bool stop_other_threads, Vote stop_vote,
    Vote run_vote);

  ~ThreadPlanStepCycle() override;

  void GetDescription(Stream *s, lldb::DescriptionLevel level) override;
  bool ValidatePlan(Stream *error) override;
  bool ShouldStop(Event *event_ptr) override;
  bool StopOthers() override;
  lldb::StateType GetPlanRunState() override;
  bool WillStop() override;
  bool MischiefManaged() override;
  bool IsPlanStale() override;

protected:
  bool DoPlanExplainsStop(Event *event_ptr) override;

  void SetUpState();

private:
  friend lldb::ThreadPlanSP Thread::QueueThreadPlanForStepSingleInstruction(
      bool step_over, bool abort_other_plans, bool stop_other_threads,
      Status &status);

  lldb::addr_t m_instruction_addr;
  bool m_stop_other_threads;

  DISALLOW_COPY_AND_ASSIGN(ThreadPlanStepCycle);
};

} // namespace lldb_private

#endif // liblldb_ThreadPlanStepCycle_h_
