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


// definition of auxiliary patterns
    
def rule_BRCOND_0: Pattern<(brcond (i32 (seteq (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_1: Pattern<(brcond (i32 (setne (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_2: Pattern<(brcond (i32 (setge (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_3: Pattern<(brcond (i32 (setlt (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_4: Pattern<(brcond (i32 (setuge (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_5: Pattern<(brcond (i32 (setult (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))), bb:$op2),
[(i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__ (i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), bb:$op2)]>;

def rule_BRCOND_6: Pattern<(brcond (i32 CheckFI_i32_xpr_general:$op0), bb:$op1),
[(i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__ (i32 CheckFI_i32_xpr_general:$op0), bb:$op1)]>;

def rule_SELECT_7: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (seteq (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_8: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setne (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_9: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setge (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_10: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setgt (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_11: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setle (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_12: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setlt (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_13: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setuge (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_14: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setugt (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_15: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setule (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_16: CodasipInst<(outs xpr_general:$op2_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2, xpr_general:$op3) > {
let Pattern = [(set xpr_general:$op2_out, (select (i32 (setult (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), (i32 CheckFI_i32_xpr_general:$op2), (i32 CheckFI_i32_xpr_general:$op3)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SELECT_17: CodasipInst<(outs xpr_general:$op1_out), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2) > {
let Pattern = [(set xpr_general:$op1_out, (select (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2)))];
let usesCustomInserter = 1;
let hasNoSchedulingInfo = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
}

def rule_SETCC_18: Pattern<(i32 (seteq (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__ (i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1)), 1)]>;

def rule_SETCC_19: Pattern<(i32 (seteq (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))),
[(i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__ (i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), 1)]>;

def rule_SETCC_20: Pattern<(i32 (setne (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__ (i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1)))]>;

def rule_SETCC_21: Pattern<(i32 (setne (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))),
[(i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__ (i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)))]>;

def rule_SETCC_22: Pattern<(i32 (setge (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1)), 1)]>;

def rule_SETCC_23: Pattern<(i32 (setge (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), 1)]>;

def rule_SETCC_24: Pattern<(i32 (setle (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op0)), 1)]>;

def rule_SETCC_25: Pattern<(i32 (setuge (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1)), 1)]>;

def rule_SETCC_26: Pattern<(i32 (setuge (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__ (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1)), 1)]>;

def rule_SETCC_27: Pattern<(i32 (setule (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))),
[(i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__ (i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__ (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op0)), 1)]>;




// patterns linking intrinsics with instructions



// patterns for moi instructions



// patterns for general vector shuffles


