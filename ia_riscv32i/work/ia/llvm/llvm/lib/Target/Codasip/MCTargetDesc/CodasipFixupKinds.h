/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2022 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2022-09-10
 * \author  Codasip (c) C compiler backend generator
 * \version 9.1.1-1255
 * \brief   Source for compiler backend
 * \project ia_riscv32i.ia
 * \note          Codasip Studio version: 9.1.1-1255
 *                Licensee: Lockular Limited  (C60_2111_2104)
 *                Project: ia_riscv32i.ia
 *                Date: 2022-09-10 04:29:16
 *                Copyright (C) 2022 Codasip s.r.o.
 */


#ifndef LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_codasipFIXUPKINDS_H
#define LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_codasipFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

#undef Codasip

namespace llvm {
namespace Codasip {
enum Fixups {
  // Taken from RISC-V target
  // fixup_riscv_hi20 - 20-bit fixup corresponding to hi(foo) for
  // instructions like lui
  fixup_riscv_hi20 = FirstTargetFixupKind,
  // fixup_riscv_lo12_i - 12-bit fixup corresponding to lo(foo) for
  // instructions like addi
  fixup_riscv_lo12_i,
  // fixup_riscv_lo12_s - 12-bit fixup corresponding to lo(foo) for
  // the S-type store instructions
  fixup_riscv_lo12_s,
  // fixup_riscv_pcrel_hi20 - 20-bit fixup corresponding to pcrel_hi(foo) for
  // instructions like auipc
  fixup_riscv_pcrel_hi20,
  // fixup_riscv_pcrel_lo12_i - 12-bit fixup corresponding to pcrel_lo(foo) for
  // instructions like addi
  fixup_riscv_pcrel_lo12_i,
  // fixup_riscv_pcrel_lo12_s - 12-bit fixup corresponding to pcrel_lo(foo) for
  // the S-type store instructions
  fixup_riscv_pcrel_lo12_s,
  // fixup_riscv_got_hi20 - 20-bit fixup corresponding to got_pcrel_hi(foo) for
  // instructions like auipc
  fixup_riscv_got_hi20,
  // fixup_riscv_tprel_hi20 - 20-bit fixup corresponding to tprel_hi(foo) for
  // instructions like lui
  fixup_riscv_tprel_hi20,
  // fixup_riscv_tprel_lo12_i - 12-bit fixup corresponding to tprel_lo(foo) for
  // instructions like addi
  fixup_riscv_tprel_lo12_i,
  // fixup_riscv_tprel_lo12_s - 12-bit fixup corresponding to tprel_lo(foo) for
  // the S-type store instructions
  fixup_riscv_tprel_lo12_s,
  // fixup_riscv_tprel_add - A fixup corresponding to %tprel_add(foo) for the
  // add_tls instruction. Used to provide a hint to the linker.
  fixup_riscv_tprel_add,
  // fixup_riscv_tls_got_hi20 - 20-bit fixup corresponding to
  // tls_ie_pcrel_hi(foo) for instructions like auipc
  fixup_riscv_tls_got_hi20,
  // fixup_riscv_tls_gd_hi20 - 20-bit fixup corresponding to
  // tls_gd_pcrel_hi(foo) for instructions like auipc
  fixup_riscv_tls_gd_hi20,
  // fixup_riscv_jal - 20-bit fixup for symbol references in the jal
  // instruction
  fixup_riscv_jal,
  // fixup_riscv_branch - 12-bit fixup for symbol references in the branch
  // instructions
  fixup_riscv_branch,
  // fixup_riscv_rvc_jump - 11-bit fixup for symbol references in the
  // compressed jump instruction
  fixup_riscv_rvc_jump,
  // fixup_riscv_rvc_branch - 8-bit fixup for symbol references in the
  // compressed branch instruction
  fixup_riscv_rvc_branch,
  // fixup_riscv_call - A fixup representing a call attached to the auipc
  // instruction in a pair composed of adjacent auipc+jalr instructions.
  fixup_riscv_call,
  // fixup_riscv_call_plt - A fixup representing a procedure linkage table call
  // attached to the auipc instruction in a pair composed of adjacent auipc+jalr
  // instructions.
  fixup_riscv_call_plt,
  // fixup_riscv_relax - Used to generate an R_RISCV_RELAX relocation type,
  // which indicates the linker may relax the instruction pair.
  fixup_riscv_relax,
  // fixup_riscv_align - Used to generate an R_RISCV_ALIGN relocation type,
  // which indicates the linker should fixup the alignment after linker
  // relaxation.
  fixup_riscv_align,
  FK_Codasip_MI5valueIH1_13default_start7_5uimm53imm1_5uimm5,
  FK_Codasip_MI5valueIH1_13default_start8_6simm124simm1_6simm12,
  FK_Codasip_MI5valueIH1_13default_start8_6uimm203imm1_6uimm20,
  FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12,
  FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12,
  FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20,
  FK_Codasip_Invalid,

  NumTargetFixupKinds = FK_Codasip_Invalid - FirstTargetFixupKind
};
} // end namespace codasip
} // end namespace llvm

#endif
