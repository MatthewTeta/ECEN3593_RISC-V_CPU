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


include "CodasipInstrFormats.td"

// All instructions, including invalid and dummy ones

def i_ret_alias__: CodasipMicroClass_<(outs), (ins variable_ops)>
{
let AsmString = "ret";
let Pattern = [(Return)];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000001000000001100111;
// i_ret_alias
}

def i_call_reg_alias__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, variable_ops)>
{
let Pattern = [(Call (i32 CheckFI_i32_xpr_general:$op0))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// 
}

def i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(brind (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isBranch = 1;
let isIndirectBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
//let Pattern = [(set i32:$op0, (i32 GET_PC)), (brind (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isBranch = 1;
let isIndirectBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_call_alias__relative_addr20__: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let AsmString = "call $op0";
let Pattern = [(Call (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000011101111;
// i_call_alias(relative_addr20)
}
def i_call_alias__relative_addr20__ES: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let AsmString = "call $op0";
let Pattern = [(Call (i32 (GAWrap (i32 texternalsym:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000011101111;
// i_call_alias(relative_addr20)
}
def i_call_alias__relative_addr20__MC: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let AsmString = "call $op0";
let Pattern = [(Call (i32 (GAWrap (i32 mcsym:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000011101111;
// i_call_alias(relative_addr20)
}
def i_call_alias__relative_addr20__BA: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let AsmString = "call $op0";
let Pattern = [(Call (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000011101111;
// i_call_alias(relative_addr20)
}

def i_jal_abs_calias__opc_jal__x_0__relative_addr20__: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_brtarg:$op0)>
{
let AsmString = "jal x0, $op0";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,x_0,relative_addr20)
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_brtarg:$op1)>
{
let AsmString = "jal $op0, $op1";
//let Pattern = [(set i32:$op0, (i32 GET_PC)), (br bb:$op1)];
let Size = 4;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,xpr_general,relative_addr20)
}

def i_jtype_jlink__opc_jal__x_0__relative_addr20__: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_brtarg:$op0)>
{
let AsmString = "jal x0 ,  $op0";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000001101111;
// i_jtype_jlink(opc_jal,x_0,relative_addr20)
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_jtype_jlink__opc_jal__xpr_general__relative_addr20__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_brtarg:$op1)>
{
let AsmString = "jal $op0 ,  $op1";
//let Pattern = [(set i32:$op0, (i32 GET_PC)), (br bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<20> op1;
let Inst{31} = op1{19-19};
let Inst{30-21} = op1{9-0};
let Inst{20} = op1{10-10};
let Inst{19-12} = op1{18-11};
let Inst{11-7} = op0;
let Inst{6-0} = 0b1101111;
// i_jtype_jlink(opc_jal,xpr_general,relative_addr20)
}

def i_btype_branches__opc_beq__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op0)>
{
let AsmString = "beq x0, x0, $op0";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0,x_0,relative_addr12)
}

def i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "beq x0, $op0, $op1";
let Pattern = [(brcond (i32 (seteq  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000000;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "beq $op0, x0, $op1";
let Pattern = [(brcond (i32 (seteq  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b000;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,xpr_general,x_0,relative_addr12)
}

def i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "beq $op0, $op1, $op2";
let Pattern = [(brcond (i32 (seteq  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b000;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bge__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op0)>
{
let AsmString = "bge x0, x0, $op0";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0,x_0,relative_addr12)
}

def i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bge x0, $op0, $op1";
let Pattern = [(brcond (i32 (setlt  (i32 CheckFI_i32_xpr_general:$op0), (i32 1))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bge $op0, x0, $op1";
let Pattern = [(brcond (i32 (setgt  (i32 CheckFI_i32_xpr_general:$op0), (i32 -1))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,xpr_general,x_0,relative_addr12)
}

def i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "bge $op0, $op1, $op2";
let Pattern = [(brcond (i32 (setge  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op0)>
{
let AsmString = "bgeu x0, x0, $op0";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0,x_0,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bgeu x0, $op0, $op1";
let Pattern = [(brcond (i32 (seteq  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "bgeu $op0, $op1, $op2";
let Pattern = [(brcond (i32 (setuge  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b111;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "blt x0, $op0, $op1";
let Pattern = [(brcond (i32 (setgt  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "blt $op0, x0, $op1";
let Pattern = [(brcond (i32 (setlt  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,xpr_general,x_0,relative_addr12)
}

def i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "blt $op0, $op1, $op2";
let Pattern = [(brcond (i32 (setlt  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bltu x0, $op0, $op1";
let Pattern = [(brcond (i32 (setne  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "bltu $op0, $op1, $op2";
let Pattern = [(brcond (i32 (setult  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b110;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bne x0, $op0, $op1";
let Pattern = [(brcond (i32 (setne  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000001;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op1)>
{
let AsmString = "bne $op0, x0, $op1";
let Pattern = [(brcond (i32 (setne  (i32 CheckFI_i32_xpr_general:$op0), (i32 0))), bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b001;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,xpr_general,x_0,relative_addr12)
}

def i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let AsmString = "bne $op0, $op1, $op2";
let Pattern = [(brcond (i32 (setne  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-12} = 0b001;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,xpr_general,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let Pattern = [(brcond (i32 (setle  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let Pattern = [(brcond (i32 (setule  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let Pattern = [(brcond (i32 (setgt  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_brtarg:$op2)>
{
let Pattern = [(brcond (i32 (setugt  (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))), bb:$op2)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_call_reg_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let AsmString = "call_reg, $op0 ( x0 )";
let Pattern = [(Call (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000011100111;
// i_call_reg_alias(simm12,x_0)
}
def i_call_reg_alias__simm12__x_0__ES: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let AsmString = "call_reg, $op0 ( x0 )";
let Pattern = [(Call (i32 (GAWrap (i32 texternalsym:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000011100111;
// i_call_reg_alias(simm12,x_0)
}
def i_call_reg_alias__simm12__x_0__MC: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let AsmString = "call_reg, $op0 ( x0 )";
let Pattern = [(Call (i32 (GAWrap (i32 mcsym:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000011100111;
// i_call_reg_alias(simm12,x_0)
}
def i_call_reg_alias__simm12__x_0__BA: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let AsmString = "call_reg, $op0 ( x0 )";
let Pattern = [(Call (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Defs = [rf_xpr_1];
let Uses = [rf_xpr_2];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000011100111;
// i_call_reg_alias(simm12,x_0)
}

def i_itype_jlreg__opc_jalr__x_0__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_brtarg:$op0)>
{
let AsmString = "jalr x0 ,  $op0 ( x0 )";
let Pattern = [(br bb:$op0)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000001100111;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0)
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_brtarg:$op1)>
{
let AsmString = "jalr $op0 ,  $op1 ( x0 )";
//let Pattern = [(set i32:$op0, (i32 GET_PC)), (br bb:$op1)];
let Size = 4;
let isBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b1100111;
// i_itype_jlreg(opc_jalr,xpr_general,simm12,x_0)
}

def i_itype_alu__opc_addi__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "addi $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_addi,xpr_general,x_0,simm12)
}

def i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "addi $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_addi,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "andi $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (and (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_andi,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_ori__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "ori $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_ori,xpr_general,x_0,simm12)
}

def i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "ori $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (or (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_ori,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_slti__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "slti $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (setgt  (i32 sext12To32imm:$op1), (i32 0))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_slti,xpr_general,x_0,simm12)
}

def i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "slti $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (setlt  (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_slti,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sltiu $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (setne  (i32 sext12To32imm:$op1), (i32 0))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_sltiu,xpr_general,x_0,simm12)
}

def i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "sltiu $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (setult  (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_sltiu,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_xori__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "xori $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_xori,xpr_general,x_0,simm12)
}

def i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "xori $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (xor (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_xori,xpr_general,xpr_general,simm12)
}

def i_itype_loads__opc_lb__x_0__simm12__x_0__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "lb x0 ,  $op0 ( x0 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000000011;
// i_itype_loads(opc_lb,x_0,simm12,x_0)
}

def i_itype_loads__opc_lb__x_0__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, xpr_general:$op1)>
{
let AsmString = "lb x0 ,  $op0 ( $op1 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b000000000000011;
// i_itype_loads(opc_lb,x_0,simm12,xpr_general)
}

def i_itype_loads__opc_lb__xpr_general__simm12__x_0__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "lb $op0 ,  $op1 ( x0 )";
let Pattern = [(set i32:$op0, (i32 (sextloadi8_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lb,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "lb $op0 ,  $op2 ( $op1 )";
let Pattern = [(set i32:$op0, (i32 (sextloadi8_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lb,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lbu__x_0__simm12__x_0__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "lbu x0 ,  $op0 ( x0 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000000011;
// i_itype_loads(opc_lbu,x_0,simm12,x_0)
}

def i_itype_loads__opc_lbu__x_0__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, xpr_general:$op1)>
{
let AsmString = "lbu x0 ,  $op0 ( $op1 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b100000000000011;
// i_itype_loads(opc_lbu,x_0,simm12,xpr_general)
}

def i_itype_loads__opc_lbu__xpr_general__simm12__x_0__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "lbu $op0 ,  $op1 ( x0 )";
let Pattern = [(set i32:$op0, (i32 (zextloadi8_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lbu,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "lbu $op0 ,  $op2 ( $op1 )";
let Pattern = [(set i32:$op0, (i32 (zextloadi8_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lbu,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lh__x_0__simm12__x_0__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "lh x0 ,  $op0 ( x0 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000001000000000011;
// i_itype_loads(opc_lh,x_0,simm12,x_0)
}

def i_itype_loads__opc_lh__x_0__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, xpr_general:$op1)>
{
let AsmString = "lh x0 ,  $op0 ( $op1 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b001000000000011;
// i_itype_loads(opc_lh,x_0,simm12,xpr_general)
}

def i_itype_loads__opc_lh__xpr_general__simm12__x_0__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "lh $op0 ,  $op1 ( x0 )";
let Pattern = [(set i32:$op0, (i32 (sextloadi16_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lh,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "lh $op0 ,  $op2 ( $op1 )";
let Pattern = [(set i32:$op0, (i32 (sextloadi16_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lh,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lhu__x_0__simm12__x_0__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "lhu x0 ,  $op0 ( x0 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000101000000000011;
// i_itype_loads(opc_lhu,x_0,simm12,x_0)
}

def i_itype_loads__opc_lhu__x_0__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, xpr_general:$op1)>
{
let AsmString = "lhu x0 ,  $op0 ( $op1 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b101000000000011;
// i_itype_loads(opc_lhu,x_0,simm12,xpr_general)
}

def i_itype_loads__opc_lhu__xpr_general__simm12__x_0__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "lhu $op0 ,  $op1 ( x0 )";
let Pattern = [(set i32:$op0, (i32 (zextloadi16_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lhu,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "lhu $op0 ,  $op2 ( $op1 )";
let Pattern = [(set i32:$op0, (i32 (zextloadi16_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lhu,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lw__x_0__simm12__x_0__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "lw x0 ,  $op0 ( x0 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000000011;
// i_itype_loads(opc_lw,x_0,simm12,x_0)
}

def i_itype_loads__opc_lw__x_0__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, xpr_general:$op1)>
{
let AsmString = "lw x0 ,  $op0 ( $op1 )";
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b010000000000011;
// i_itype_loads(opc_lw,x_0,simm12,xpr_general)
}

def i_itype_loads__opc_lw__xpr_general__simm12__x_0__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "lw $op0 ,  $op1 ( x0 )";
let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lw,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "lw $op0 ,  $op2 ( $op1 )";
let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lw,xpr_general,simm12,xpr_general)
}

def i_nop_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "nop";
let Pattern = [];
let Size = 4;
let mayLoad = 0;
let mayStore = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000010011;
// i_nop_alias
}

def i_rtype_alu__opc_add__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0,x_0)
}

def i_rtype_alu__opc_add__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "add $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_add__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "add $op0 ,  x0 ,  $op1";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_add__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "add $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "add $op0 ,  $op2 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isCommutable = 1;
bits<5> op0;
bits<5> op2;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op2;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_and__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0,x_0)
}

def i_rtype_alu__opc_and__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "and $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_and__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "and $op0 ,  $op2 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (and (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isCommutable = 1;
bits<5> op0;
bits<5> op2;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op2;
let Inst{14-12} = 0b111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_or__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0,x_0)
}

def i_rtype_alu__opc_or__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "or $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_or__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "or $op0 ,  x0 ,  $op1";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_or__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "or $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "or $op0 ,  $op2 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (or (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isCommutable = 1;
bits<5> op0;
bits<5> op2;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op2;
let Inst{14-12} = 0b110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sll__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0,x_0)
}

def i_rtype_alu__opc_sll__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "sll $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_sll__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "sll $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_sll__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "sll $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (shl (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_slt__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0,x_0)
}

def i_rtype_alu__opc_slt__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "slt $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_slt__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "slt $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (setgt  (i32 CheckFI_i32_xpr_general:$op1), (i32 0))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_slt__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "slt $op0 ,  $op1 ,  x0";
let Pattern = [(set i32:$op0, (i32 (srl (i32 CheckFI_i32_xpr_general:$op1), (i32 31))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "slt $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (setlt  (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sltu__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0,x_0)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "sltu $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "sltu $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (setne  (i32 CheckFI_i32_xpr_general:$op1), (i32 0))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "sltu $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (setult  (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sra__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0,x_0)
}

def i_rtype_alu__opc_sra__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "sra $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_sra__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "sra $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "sra $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (sra (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_srl__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0,x_0)
}

def i_rtype_alu__opc_srl__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "srl $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_srl__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "srl $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "srl $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (srl (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sub__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0,x_0)
}

def i_rtype_alu__opc_sub__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "sub $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_sub__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "sub $op0 ,  x0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (sub (i32 0), (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_sub__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "sub $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "sub $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (sub (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_xor__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor x0 ,  x0 ,  x0";
let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0,x_0)
}

def i_rtype_alu__opc_xor__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let AsmString = "xor $op0 ,  x0 ,  x0";
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0,x_0)
}

def i_rtype_alu__opc_xor__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "xor $op0 ,  x0 ,  $op1";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0,xpr_general)
}

def i_rtype_alu__opc_xor__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let AsmString = "xor $op0 ,  $op1 ,  x0";
//let Pattern = [(set i32:$op0, (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,xpr_general,x_0)
}

def i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "xor $op0 ,  $op2 ,  $op1";
let Pattern = [(set i32:$op0, (i32 (xor (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isCommutable = 1;
bits<5> op0;
bits<5> op2;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op2;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,xpr_general,xpr_general)
}

def i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_i32:$op2)>
{
let AsmString = "slli $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (shl (i32 CheckFI_i32_xpr_general:$op1), (i32 zext5To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_slli,xpr_general,xpr_general,uimm5)
}

def i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_i32:$op2)>
{
let AsmString = "srai $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (sra (i32 CheckFI_i32_xpr_general:$op1), (i32 zext5To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srai,xpr_general,xpr_general,uimm5)
}

def i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_i32:$op2)>
{
let AsmString = "srli $op0 ,  $op1 ,  $op2";
let Pattern = [(set i32:$op0, (i32 (srl (i32 CheckFI_i32_xpr_general:$op1), (i32 zext5To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srli,xpr_general,xpr_general,uimm5)
}

def i_stype_store__opc_sb__x_0__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "sb x0 ,  $op0 ( x0 )";
let Pattern = [(store_a1_s0 (i8 0), (i32 sext12To32imm:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000000;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0,simm12,x_0)
}

def i_stype_store__opc_sb__x_0__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sb x0 ,  $op1 ( $op0 )";
let Pattern = [(store_a1_s0 (i8 0), (i32 (add (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op1;
bits<5> op0;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b000;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0,simm12,xpr_general)
}

def i_stype_store__opc_sb__xpr_general__simm12__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sb $op0 ,  $op1 ( x0 )";
let Pattern = [(truncstorei8_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,xpr_general,simm12,x_0)
}

def i_stype_store__opc_sb__xpr_general__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "sb $op0 ,  $op2 ( $op1 )";
let Pattern = [(truncstorei8_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-25} = op2{11-5};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op2{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,xpr_general,simm12,xpr_general)
}

def i_stype_store__opc_sh__x_0__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "sh x0 ,  $op0 ( x0 )";
let Pattern = [(store_a1_s0 (i16 0), (i32 sext12To32imm:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000001;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0,simm12,x_0)
}

def i_stype_store__opc_sh__x_0__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sh x0 ,  $op1 ( $op0 )";
let Pattern = [(store_a1_s0 (i16 0), (i32 (add (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op1;
bits<5> op0;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b001;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0,simm12,xpr_general)
}

def i_stype_store__opc_sh__xpr_general__simm12__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sh $op0 ,  $op1 ( x0 )";
let Pattern = [(truncstorei16_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,xpr_general,simm12,x_0)
}

def i_stype_store__opc_sh__xpr_general__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "sh $op0 ,  $op2 ( $op1 )";
let Pattern = [(truncstorei16_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-25} = op2{11-5};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op2{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,xpr_general,simm12,xpr_general)
}

def i_stype_store__opc_sw__x_0__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let AsmString = "sw x0 ,  $op0 ( x0 )";
let Pattern = [(store_a1_s0 (i32 0), (i32 sext12To32imm:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000010;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0,simm12,x_0)
}

def i_stype_store__opc_sw__x_0__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sw x0 ,  $op1 ( $op0 )";
let Pattern = [(store_a1_s0 (i32 0), (i32 (add (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<12> op1;
bits<5> op0;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b010;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0,simm12,xpr_general)
}

def i_stype_store__opc_sw__xpr_general__simm12__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "sw $op0 ,  $op1 ( x0 )";
let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,xpr_general,simm12,x_0)
}

def i_stype_store__opc_sw__xpr_general__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "sw $op0 ,  $op2 ( $op1 )";
let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-25} = op2{11-5};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op2{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,xpr_general,simm12,xpr_general)
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_utype_ops__opc_auipc__xpr_general__uimm20__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "auipc $op0 ,  $op1";
//let Pattern = [(set i32:$op0, (i32 (add (i32 (add (i32 GET_PC), (i32 Trunc12_i32imm:$op1))), (i32 -4))))];
let Size = 4;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<20> op1;
let Inst{31-12} = op1;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010111;
// i_utype_ops(opc_auipc,xpr_general,uimm20)
}

def i_utype_ops__opc_lui__xpr_general__uimm20__: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "lui $op0 ,  $op1";
let Pattern = [(set i32:$op0, (i32 Trunc12_i32imm:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
bits<5> op0;
bits<20> op1;
let Inst{31-12} = op1;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110111;
// i_utype_ops(opc_lui,xpr_general,uimm20)
}

def i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__1__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let Pattern = [(set i32:$op0, (i32 1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let Pattern = [(set i32:$op0, (i32 0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__1__: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
let Pattern = [(set i32:$op0, (i32 1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lb__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs), (ins xpr_general:$op0)>
{
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lb,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lb,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (sextloadi8_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lbu,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lbu,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (zextloadi8_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi8_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lh__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs), (ins xpr_general:$op0)>
{
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lh,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lh,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (sextloadi16_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lhu,xpr_general,simm12,x_0)
}

def i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 sext12To32imm:$op2))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lhu,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (zextloadi16_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (extloadi16_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lw__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs), (ins xpr_general:$op0)>
{
//let Pattern = [];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 CheckFI_i32_xpr_general:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (setgt  (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (setugt  (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let isCompare = 1;
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (sra (i32 CheckFI_i32_xpr_general:$op1), (i32 (and (i32 CheckFI_i32_xpr_general:$op2), (i32 31))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_rtype_alu(opc_sra,xpr_general,xpr_general,xpr_general)
}

def i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
let Pattern = [(set i32:$op0, (i32 (srl (i32 CheckFI_i32_xpr_general:$op1), (i32 (and (i32 CheckFI_i32_xpr_general:$op2), (i32 31))))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_rtype_alu(opc_srl,xpr_general,xpr_general,xpr_general)
}

def i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(store_a1_s0 (i8 0), (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sb__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let Pattern = [(truncstorei8_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(store_a1_s0 (i16 0), (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sh__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let Pattern = [(truncstorei16_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sw__x_0__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(store_a1_s0 (i32 0), (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 CheckFI_i32_xpr_general:$op1))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

// note: (BGN545): The instruction contains invalid operation ('GET_PC') even after the high-level analysis. The semantic pattern will be commented out.
def i_utype_ops__opc_auipc__xpr_general__uimm20__immspec_1_: CodasipMicroClass_<(outs xpr_general:$op0), (ins)>
{
//let Pattern = [(set i32:$op0, (i32 (add (i32 GET_PC), (i32 -4))))];
let Size = 4;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def e_movi32__: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 imm:$op1))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__GA: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 tglobaladdr:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__ES: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 texternalsym:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__MC: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 mcsym:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__BA: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 tblockaddress:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__JT: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 tjumptable:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}
def e_movi32__CP: CodasipMicroClass_<(outs xpr_general:$op0), (ins i32imm:$op1)>
{
let Pattern = [(set i32:$op0, (i32 (GAWrap (i32 tconstpool:$op1))))];
let Defs = [rf_xpr_30];
let Size = 16;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let isMoveImm = 1;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_ret_alias__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins variable_ops)>
{
let Pattern = [(TailCall (i32 NotFI_i32_rf_xpr_1))];
let Uses = [rf_xpr_1];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_ret_alias
}

def i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// 
}

def i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,x_0,relative_addr20)
}
def i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,x_0,relative_addr20)
}
def i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,x_0,relative_addr20)
}
def i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jal_abs_calias(opc_jal,x_0,relative_addr20)
}

def i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jtype_jlink(opc_jal,x_0,relative_addr20)
}
def i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jtype_jlink(opc_jal,x_0,relative_addr20)
}
def i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jtype_jlink(opc_jal,x_0,relative_addr20)
}
def i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_jtype_jlink(opc_jal,x_0,relative_addr20)
}

def i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_beq,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_beq,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_beq,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_beq,x_0,x_0,relative_addr12)
}

def i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bge,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bge,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bge,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bge,x_0,x_0,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bgeu,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bgeu,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bgeu,x_0,x_0,relative_addr12)
}
def i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_btype_branches(opc_bgeu,x_0,x_0,relative_addr12)
}

def i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tglobaladdr:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0)
}
def i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 texternalsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0)
}
def i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 mcsym:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0)
}
def i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0, variable_ops)>
{
let Pattern = [(TailCall (i32 (GAWrap (i32 tblockaddress:$op0))))];
let Size = 4;
let hasExtraSrcRegAllocReq = 1;
let isCall = 1;
let isReturn = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let isCodeGenOnly = 1;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0)
}

def i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let Pattern = [(truncstorei8_a1_s0 (i32 0), (i32 sext12To32imm:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sb,x_0,simm12,x_0)
}

def i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(truncstorei8_a1_s0 (i32 0), (i32 (add (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sb,x_0,simm12,xpr_general)
}

def i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op0)>
{
let Pattern = [(truncstorei16_a1_s0 (i32 0), (i32 sext12To32imm:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sh,x_0,simm12,x_0)
}

def i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let Pattern = [(truncstorei16_a1_s0 (i32 0), (i32 (add (i32 CheckFI_i32_xpr_general:$op0), (i32 sext12To32imm:$op1))))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sh,x_0,simm12,xpr_general)
}

def i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(truncstorei8_a1_s0 (i32 0), (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let Pattern = [(truncstorei16_a1_s0 (i32 0), (i32 CheckFI_i32_xpr_general:$op0))];
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// 
}

def i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2)>
{
//let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))];
let Size = 8;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let hasSideEffects = 0;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sw,xpr_general,simm12,xpr_general)
}

def i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))];
let Defs = [rf_xpr_30];
let Size = 24;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sw,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, xpr_general:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 CheckFI_i32_xpr_general:$op2))))))];
let Size = 8;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let hasSideEffects = 0;
let usesCustomInserter = 1;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lw,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))))];
let Defs = [rf_xpr_30];
let Size = 24;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lw,xpr_general,simm12,xpr_general)
}

def i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(store_a1_s0 (i32 CheckFI_i32_xpr_general:$op0), (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))];
let Defs = [rf_xpr_30];
let Size = 24;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 1;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_stype_store(opc_sw,xpr_general,simm12,xpr_general)
}

def i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_: CodasipMicroClass_sc_load<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (load_a1_s0 (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))))];
let Defs = [rf_xpr_30];
let Size = 24;
let isReMaterializable = 1;
let mayLoad = 1;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_loads(opc_lw,xpr_general,simm12,xpr_general)
}

def i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))];
let Defs = [rf_xpr_30];
let Size = 20;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_alu(opc_addi,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))];
let Defs = [rf_xpr_30];
let Size = 20;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_alu(opc_addi,xpr_general,xpr_general,simm12)
}

def i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
//let Pattern = [(set i32:$op0, (i32 (add (i32 CheckFI_i32_xpr_general:$op1), (i32 imm:$op2))))];
let Defs = [rf_xpr_30];
let Size = 20;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_itype_alu(opc_addi,xpr_general,xpr_general,simm12)
}

def i_beqz_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "beqz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_beqz_alias(x_0,relative_addr12)
}

def i_beqz_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "beqz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_beqz_alias(x_0_alias,relative_addr12)
}

def i_beqz_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "beqz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b000;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_beqz_alias(xpr_general,relative_addr12)
}

def i_bgez_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgez x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgez_alias(x_0,relative_addr12)
}

def i_bgez_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgez zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgez_alias(x_0_alias,relative_addr12)
}

def i_bgez_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgez $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgez_alias(xpr_general,relative_addr12)
}

def i_bgt_alias__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgt x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0,x_0,relative_addr12)
}

def i_bgt_alias__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgt x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0,x_0_alias,relative_addr12)
}

def i_bgt_alias__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgt x0, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0,xpr_general,relative_addr12)
}

def i_bgt_alias__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgt zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0_alias,x_0,relative_addr12)
}

def i_bgt_alias__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgt zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0_alias,x_0_alias,relative_addr12)
}

def i_bgt_alias__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgt zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(x_0_alias,xpr_general,relative_addr12)
}

def i_bgt_alias__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgt $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(xpr_general,x_0,relative_addr12)
}

def i_bgt_alias__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgt $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(xpr_general,x_0_alias,relative_addr12)
}

def i_bgt_alias__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op2)>
{
let AsmString = "bgt $op0, $op1, $op2";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_bgt_alias(xpr_general,xpr_general,relative_addr12)
}

def i_bgtu_alias__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtu x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0,x_0,relative_addr12)
}

def i_bgtu_alias__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtu x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0,x_0_alias,relative_addr12)
}

def i_bgtu_alias__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgtu x0, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0,xpr_general,relative_addr12)
}

def i_bgtu_alias__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtu zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0_alias,x_0,relative_addr12)
}

def i_bgtu_alias__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtu zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0_alias,x_0_alias,relative_addr12)
}

def i_bgtu_alias__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgtu zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(x_0_alias,xpr_general,relative_addr12)
}

def i_bgtu_alias__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgtu $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(xpr_general,x_0,relative_addr12)
}

def i_bgtu_alias__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgtu $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(xpr_general,x_0_alias,relative_addr12)
}

def i_bgtu_alias__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op2)>
{
let AsmString = "bgtu $op0, $op1, $op2";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b110;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtu_alias(xpr_general,xpr_general,relative_addr12)
}

def i_bgtz_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtz_alias(x_0,relative_addr12)
}

def i_bgtz_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgtz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtz_alias(x_0_alias,relative_addr12)
}

def i_bgtz_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgtz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bgtz_alias(xpr_general,relative_addr12)
}

def i_ble_alias__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "ble x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0,x_0,relative_addr12)
}

def i_ble_alias__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "ble x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0,x_0_alias,relative_addr12)
}

def i_ble_alias__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "ble x0, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0,xpr_general,relative_addr12)
}

def i_ble_alias__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "ble zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0_alias,x_0,relative_addr12)
}

def i_ble_alias__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "ble zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0_alias,x_0_alias,relative_addr12)
}

def i_ble_alias__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "ble zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(x_0_alias,xpr_general,relative_addr12)
}

def i_ble_alias__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "ble $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(xpr_general,x_0,relative_addr12)
}

def i_ble_alias__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "ble $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(xpr_general,x_0_alias,relative_addr12)
}

def i_ble_alias__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op2)>
{
let AsmString = "ble $op0, $op1, $op2";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_ble_alias(xpr_general,xpr_general,relative_addr12)
}

def i_bleu_alias__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bleu x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0,x_0,relative_addr12)
}

def i_bleu_alias__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bleu x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0,x_0_alias,relative_addr12)
}

def i_bleu_alias__x_0__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bleu x0, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0,xpr_general,relative_addr12)
}

def i_bleu_alias__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bleu zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0_alias,x_0,relative_addr12)
}

def i_bleu_alias__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bleu zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0_alias,x_0_alias,relative_addr12)
}

def i_bleu_alias__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bleu zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(x_0_alias,xpr_general,relative_addr12)
}

def i_bleu_alias__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bleu $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(xpr_general,x_0,relative_addr12)
}

def i_bleu_alias__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bleu $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(xpr_general,x_0_alias,relative_addr12)
}

def i_bleu_alias__xpr_general__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op2)>
{
let AsmString = "bleu $op0, $op1, $op2";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
bits<12> op2;
let Inst{31} = op2{11-11};
let Inst{30-25} = op2{9-4};
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-12} = 0b111;
let Inst{11-8} = op2{3-0};
let Inst{7} = op2{10-10};
let Inst{6-0} = 0b1100011;
// i_bleu_alias(xpr_general,xpr_general,relative_addr12)
}

def i_blez_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blez x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_blez_alias(x_0,relative_addr12)
}

def i_blez_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blez zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_blez_alias(x_0_alias,relative_addr12)
}

def i_blez_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "blez $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_blez_alias(xpr_general,relative_addr12)
}

def i_bltz_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bltz_alias(x_0,relative_addr12)
}

def i_bltz_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bltz_alias(x_0_alias,relative_addr12)
}

def i_bltz_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bltz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bltz_alias(xpr_general,relative_addr12)
}

def i_bnez_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bnez x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bnez_alias(x_0,relative_addr12)
}

def i_bnez_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bnez zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_bnez_alias(x_0_alias,relative_addr12)
}

def i_bnez_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bnez $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b001;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_bnez_alias(xpr_general,relative_addr12)
}

def i_btype_branches__opc_beq__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "beq x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_beq__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "beq zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_beq__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "beq zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000000;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_beq__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "beq zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000000;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_beq__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "beq $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b000;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_beq,xpr_general,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bge__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bge x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bge__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bge zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_bge__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bge zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000101;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bge__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bge zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bge__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bge $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b101;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bge,xpr_general,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgeu x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgeu zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bgeu zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000111;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bgeu__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgeu zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bgeu__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgeu $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,xpr_general,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_blt__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blt x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_blt__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blt zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_blt__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blt zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_blt__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "blt zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_blt__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "blt $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b100;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,xpr_general,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bltu__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltu x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bltu__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltu zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_bltu__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltu zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bltu__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bltu zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bltu__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bltu $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,xpr_general,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bne__x_0__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bne x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bne__x_0_alias__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bne zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0_alias,x_0,relative_addr12)
}

def i_btype_branches__opc_bne__x_0_alias__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bne zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0_alias,x_0_alias,relative_addr12)
}

def i_btype_branches__opc_bne__x_0_alias__xpr_general__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bne zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000001;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0_alias,xpr_general,relative_addr12)
}

def i_btype_branches__opc_bne__xpr_general__x_0_alias__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bne $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b001;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,xpr_general,x_0_alias,relative_addr12)
}

def i_call_reg_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "call_reg, $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000011100111;
// i_call_reg_alias(simm12,x_0_alias)
}

def i_halt__opc_halt__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "halt";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let Inst{31-0} = 0b00000000000000000000000000111111;
// i_halt(opc_halt)
}

def i_itype_alu__opc_addi__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "addi x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_itype_alu(opc_addi,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_addi__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "addi zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_itype_alu(opc_addi,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_addi__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "addi zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_itype_alu(opc_addi,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_addi__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "addi zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000010011;
// i_itype_alu(opc_addi,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_addi__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "addi $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_addi,xpr_general,x_0_alias,simm12)
}

def i_itype_alu__opc_andi__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "andi x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000111000000010011;
// i_itype_alu(opc_andi,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_andi__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "andi zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000111000000010011;
// i_itype_alu(opc_andi,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_andi__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "andi zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000111000000010011;
// i_itype_alu(opc_andi,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_andi__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "andi zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000010011;
// i_itype_alu(opc_andi,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_andi__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "andi $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_andi,xpr_general,x_0_alias,simm12)
}

def i_itype_alu__opc_ori__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "ori x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000110000000010011;
// i_itype_alu(opc_ori,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_ori__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "ori zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000110000000010011;
// i_itype_alu(opc_ori,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_ori__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "ori zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000110000000010011;
// i_itype_alu(opc_ori,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_ori__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "ori zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000010011;
// i_itype_alu(opc_ori,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_ori__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "ori $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_ori,xpr_general,x_0_alias,simm12)
}

def i_itype_alu__opc_slti__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "slti x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000010011;
// i_itype_alu(opc_slti,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_slti__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "slti zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000010011;
// i_itype_alu(opc_slti,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_slti__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "slti zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000010011;
// i_itype_alu(opc_slti,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_slti__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "slti zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000010011;
// i_itype_alu(opc_slti,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_slti__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "slti $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_slti,xpr_general,x_0_alias,simm12)
}

def i_itype_alu__opc_sltiu__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sltiu x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000011000000010011;
// i_itype_alu(opc_sltiu,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_sltiu__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sltiu zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000011000000010011;
// i_itype_alu(opc_sltiu,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_sltiu__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sltiu zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000011000000010011;
// i_itype_alu(opc_sltiu,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_sltiu__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sltiu zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000010011;
// i_itype_alu(opc_sltiu,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_sltiu__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sltiu $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_sltiu,xpr_general,x_0_alias,simm12)
}

def i_itype_alu__opc_xori__x_0__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "xori x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000010011;
// i_itype_alu(opc_xori,x_0,x_0_alias,simm12)
}

def i_itype_alu__opc_xori__x_0_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "xori zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000010011;
// i_itype_alu(opc_xori,x_0_alias,x_0,simm12)
}

def i_itype_alu__opc_xori__x_0_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "xori zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000010011;
// i_itype_alu(opc_xori,x_0_alias,x_0_alias,simm12)
}

def i_itype_alu__opc_xori__x_0_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "xori zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000010011;
// i_itype_alu(opc_xori,x_0_alias,xpr_general,simm12)
}

def i_itype_alu__opc_xori__xpr_general__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "xori $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_xori,xpr_general,x_0_alias,simm12)
}

def i_itype_jlreg__opc_jalr__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "jalr x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000001100111;
// i_itype_jlreg(opc_jalr,x_0,simm12,x_0_alias)
}

def i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "jalr zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000001100111;
// i_itype_jlreg(opc_jalr,x_0_alias,simm12,x_0)
}

def i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "jalr zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000001100111;
// i_itype_jlreg(opc_jalr,x_0_alias,simm12,x_0_alias)
}

def i_itype_jlreg__opc_jalr__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "jalr zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b000000001100111;
// i_itype_jlreg(opc_jalr,x_0_alias,simm12,xpr_general)
}

def i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "jalr $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b1100111;
// i_itype_jlreg(opc_jalr,xpr_general,simm12,x_0_alias)
}

def i_itype_loads__opc_lb__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lb x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000000011;
// i_itype_loads(opc_lb,x_0,simm12,x_0_alias)
}

def i_itype_loads__opc_lb__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lb zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000000011;
// i_itype_loads(opc_lb,x_0_alias,simm12,x_0)
}

def i_itype_loads__opc_lb__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lb zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000000011;
// i_itype_loads(opc_lb,x_0_alias,simm12,x_0_alias)
}

def i_itype_loads__opc_lb__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "lb zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b000000000000011;
// i_itype_loads(opc_lb,x_0_alias,simm12,xpr_general)
}

def i_itype_loads__opc_lb__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "lb $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lb,xpr_general,simm12,x_0_alias)
}

def i_itype_loads__opc_lbu__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lbu x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000000011;
// i_itype_loads(opc_lbu,x_0,simm12,x_0_alias)
}

def i_itype_loads__opc_lbu__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lbu zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000000011;
// i_itype_loads(opc_lbu,x_0_alias,simm12,x_0)
}

def i_itype_loads__opc_lbu__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lbu zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000000011;
// i_itype_loads(opc_lbu,x_0_alias,simm12,x_0_alias)
}

def i_itype_loads__opc_lbu__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "lbu zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b100000000000011;
// i_itype_loads(opc_lbu,x_0_alias,simm12,xpr_general)
}

def i_itype_loads__opc_lbu__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "lbu $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lbu,xpr_general,simm12,x_0_alias)
}

def i_itype_loads__opc_lh__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lh x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000001000000000011;
// i_itype_loads(opc_lh,x_0,simm12,x_0_alias)
}

def i_itype_loads__opc_lh__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lh zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000001000000000011;
// i_itype_loads(opc_lh,x_0_alias,simm12,x_0)
}

def i_itype_loads__opc_lh__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lh zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000001000000000011;
// i_itype_loads(opc_lh,x_0_alias,simm12,x_0_alias)
}

def i_itype_loads__opc_lh__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "lh zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b001000000000011;
// i_itype_loads(opc_lh,x_0_alias,simm12,xpr_general)
}

def i_itype_loads__opc_lh__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "lh $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lh,xpr_general,simm12,x_0_alias)
}

def i_itype_loads__opc_lhu__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lhu x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000101000000000011;
// i_itype_loads(opc_lhu,x_0,simm12,x_0_alias)
}

def i_itype_loads__opc_lhu__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lhu zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000101000000000011;
// i_itype_loads(opc_lhu,x_0_alias,simm12,x_0)
}

def i_itype_loads__opc_lhu__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lhu zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000101000000000011;
// i_itype_loads(opc_lhu,x_0_alias,simm12,x_0_alias)
}

def i_itype_loads__opc_lhu__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "lhu zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b101000000000011;
// i_itype_loads(opc_lhu,x_0_alias,simm12,xpr_general)
}

def i_itype_loads__opc_lhu__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "lhu $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lhu,xpr_general,simm12,x_0_alias)
}

def i_itype_loads__opc_lw__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lw x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000000011;
// i_itype_loads(opc_lw,x_0,simm12,x_0_alias)
}

def i_itype_loads__opc_lw__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lw zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000000011;
// i_itype_loads(opc_lw,x_0_alias,simm12,x_0)
}

def i_itype_loads__opc_lw__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "lw zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000000011;
// i_itype_loads(opc_lw,x_0_alias,simm12,x_0_alias)
}

def i_itype_loads__opc_lw__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "lw zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b010000000000011;
// i_itype_loads(opc_lw,x_0_alias,simm12,xpr_general)
}

def i_itype_loads__opc_lw__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "lw $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0000011;
// i_itype_loads(opc_lw,xpr_general,simm12,x_0_alias)
}

def i_j_alias__relative_addr20__: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_iAny:$op0)>
{
let AsmString = "j $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000001101111;
// i_j_alias(relative_addr20)
}

def i_jr_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "jr x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000001100111;
// i_jr_alias(x_0)
}

def i_jr_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "jr zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000001100111;
// i_jr_alias(x_0_alias)
}

def i_jr_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "jr $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000001100111;
// i_jr_alias(xpr_general)
}

def i_jtype_jlink__opc_jal__x_0_alias__relative_addr20__: CodasipMicroClass_<(outs), (ins MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20_iAny:$op0)>
{
let AsmString = "jal zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31} = op0{19-19};
let Inst{30-21} = op0{9-0};
let Inst{20} = op0{10-10};
let Inst{19-12} = op0{18-11};
let Inst{11-0} = 0b000001101111;
// i_jtype_jlink(opc_jal,x_0_alias,relative_addr20)
}

def i_li_alias__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "li x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_li_alias(x_0,simm12)
}

def i_li_alias__x_0_alias__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "li zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_li_alias(x_0_alias,simm12)
}

def i_li_alias__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "li $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_li_alias(xpr_general,simm12)
}

def i_mv_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "mv x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000010011;
// i_mv_alias(x_0,x_0)
}

def i_mv_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "mv x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000010011;
// i_mv_alias(x_0,x_0_alias)
}

def i_mv_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "mv x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000010011;
// i_mv_alias(x_0,xpr_general)
}

def i_mv_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "mv zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000010011;
// i_mv_alias(x_0_alias,x_0)
}

def i_mv_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "mv zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000010011;
// i_mv_alias(x_0_alias,x_0_alias)
}

def i_mv_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "mv zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000010011;
// i_mv_alias(x_0_alias,xpr_general)
}

def i_mv_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "mv $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_mv_alias(xpr_general,x_0)
}

def i_mv_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "mv $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_mv_alias(xpr_general,x_0_alias)
}

def i_mv_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "mv $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_mv_alias(xpr_general,xpr_general)
}

def i_neg_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "neg x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_neg_alias(x_0,x_0)
}

def i_neg_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "neg x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_neg_alias(x_0,x_0_alias)
}

def i_neg_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "neg x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_neg_alias(x_0,xpr_general)
}

def i_neg_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "neg zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_neg_alias(x_0_alias,x_0)
}

def i_neg_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "neg zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_neg_alias(x_0_alias,x_0_alias)
}

def i_neg_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "neg zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_neg_alias(x_0_alias,xpr_general)
}

def i_neg_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "neg $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_neg_alias(xpr_general,x_0)
}

def i_neg_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "neg $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_neg_alias(xpr_general,x_0_alias)
}

def i_neg_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "neg $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_neg_alias(xpr_general,xpr_general)
}

def i_not_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "not x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b11111111111100000100000000010011;
// i_not_alias(x_0,x_0)
}

def i_not_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "not x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b11111111111100000100000000010011;
// i_not_alias(x_0,x_0_alias)
}

def i_not_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "not x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b111111111111;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000010011;
// i_not_alias(x_0,xpr_general)
}

def i_not_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "not zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b11111111111100000100000000010011;
// i_not_alias(x_0_alias,x_0)
}

def i_not_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "not zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b11111111111100000100000000010011;
// i_not_alias(x_0_alias,x_0_alias)
}

def i_not_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "not zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b111111111111;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000010011;
// i_not_alias(x_0_alias,xpr_general)
}

def i_not_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "not $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b11111111111100000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_not_alias(xpr_general,x_0)
}

def i_not_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "not $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b11111111111100000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_not_alias(xpr_general,x_0_alias)
}

def i_not_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "not $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b111111111111;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_not_alias(xpr_general,xpr_general)
}

def i_rtype_alu__opc_add__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_add__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_add__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_add__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_add__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_add__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_add__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_add__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_add__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_add__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "add zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_add__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_add,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_add__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_add__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_add__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "add zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_add__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_add__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_add__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_add__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "add $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_add__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "add $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_add,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_and__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_and__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_and__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_and__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_and__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_and__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_and__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_and__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_and__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_and__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "and zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_and__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000111000000110011;
// i_rtype_alu(opc_and,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_and__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_and__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_and__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_and__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_and__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_and__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_and__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_and__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_or__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_or__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_or__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_or__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_or__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_or__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_or__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_or__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_or__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_or__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "or zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_or__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000110000000110011;
// i_rtype_alu(opc_or,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_or__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_or__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_or__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "or zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_or__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_or__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_or__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_or__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "or $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_or__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "or $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b110;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_or,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_sll__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sll__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sll zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sll__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_sll__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sll__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sll zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sll__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_sll__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_sll__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sll__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sll $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sll__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sll $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_slt__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_slt__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "slt zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_slt__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_slt__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_slt__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "slt zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_slt__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_slt__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_slt__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_slt__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "slt $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_slt__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "slt $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_slt,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_sltu__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sltu__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltu zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sltu__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_sltu__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sltu__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltu zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sltu__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltu $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sltu__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltu $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_sra__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sra__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sra zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sra__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_sra__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sra__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sra zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sra__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_sra__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_sra__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sra__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sra $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sra__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sra $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_srl__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_srl__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "srl zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_srl__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_srl__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_srl__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "srl zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_srl__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_srl__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_srl__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_srl__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "srl $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_srl__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "srl $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_sub__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sub__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sub zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b01000000000000000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sub__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_sub__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_sub__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sub zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_sub__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_sub__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_sub__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b01000000000000000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_sub__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sub $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_sub__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sub $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sub,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor x0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor x0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0_alias,x_0)
}

def i_rtype_alu__opc_xor__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor x0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_xor__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor x0 ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor zero ,  x0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0,x_0)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor zero ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0,xpr_general)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor zero ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0_alias,x_0)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "xor zero ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_xor__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor zero ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,xpr_general,x_0)
}

def i_rtype_alu__opc_xor__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor zero ,  $op0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,xpr_general,x_0_alias)
}

def i_rtype_alu__opc_xor__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "xor zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0_alias,xpr_general,xpr_general)
}

def i_rtype_alu__opc_xor__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor $op0 ,  x0 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0,x_0_alias)
}

def i_rtype_alu__opc_xor__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor $op0 ,  zero ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0_alias,x_0)
}

def i_rtype_alu__opc_xor__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor $op0 ,  zero ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0_alias,x_0_alias)
}

def i_rtype_alu__opc_xor__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "xor $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,x_0_alias,xpr_general)
}

def i_rtype_alu__opc_xor__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "xor $op0 ,  $op1 ,  zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b100;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_xor,xpr_general,xpr_general,x_0_alias)
}

def i_rtype_shift__opc_slli__x_0__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "slli x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000010011;
// i_rtype_shift(opc_slli,x_0,x_0_alias,uimm5)
}

def i_rtype_shift__opc_slli__x_0_alias__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "slli zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000010011;
// i_rtype_shift(opc_slli,x_0_alias,x_0,uimm5)
}

def i_rtype_shift__opc_slli__x_0_alias__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "slli zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000010011;
// i_rtype_shift(opc_slli,x_0_alias,x_0_alias,uimm5)
}

def i_rtype_shift__opc_slli__x_0_alias__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "slli zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000010011;
// i_rtype_shift(opc_slli,x_0_alias,xpr_general,uimm5)
}

def i_rtype_shift__opc_slli__xpr_general__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "slli $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_slli,xpr_general,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srai__x_0__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srai x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srai,x_0,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srai__x_0_alias__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srai zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srai,x_0_alias,x_0,uimm5)
}

def i_rtype_shift__opc_srai__x_0_alias__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srai zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srai,x_0_alias,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srai__x_0_alias__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srai zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000010011;
// i_rtype_shift(opc_srai,x_0_alias,xpr_general,uimm5)
}

def i_rtype_shift__opc_srai__xpr_general__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srai $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srai,xpr_general,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srli__x_0__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srli x0 ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srli,x_0,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srli__x_0_alias__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srli zero ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srli,x_0_alias,x_0,uimm5)
}

def i_rtype_shift__opc_srli__x_0_alias__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srli zero ,  zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srli,x_0_alias,x_0_alias,uimm5)
}

def i_rtype_shift__opc_srli__x_0_alias__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srli zero ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000010011;
// i_rtype_shift(opc_srli,x_0_alias,xpr_general,uimm5)
}

def i_rtype_shift__opc_srli__xpr_general__x_0_alias__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srli $op0 ,  zero ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srli,xpr_general,x_0_alias,uimm5)
}

def i_seqz_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "seqz x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000100000011000000010011;
// i_seqz_alias(x_0,x_0)
}

def i_seqz_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "seqz x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000100000011000000010011;
// i_seqz_alias(x_0,x_0_alias)
}

def i_seqz_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "seqz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000001;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000010011;
// i_seqz_alias(x_0,xpr_general)
}

def i_seqz_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "seqz zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000100000011000000010011;
// i_seqz_alias(x_0_alias,x_0)
}

def i_seqz_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "seqz zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000100000011000000010011;
// i_seqz_alias(x_0_alias,x_0_alias)
}

def i_seqz_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "seqz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000001;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000010011;
// i_seqz_alias(x_0_alias,xpr_general)
}

def i_seqz_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "seqz $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000100000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_seqz_alias(xpr_general,x_0)
}

def i_seqz_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "seqz $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000100000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_seqz_alias(xpr_general,x_0_alias)
}

def i_seqz_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "seqz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000001;
let Inst{19-15} = op1;
let Inst{14-12} = 0b011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_seqz_alias(xpr_general,xpr_general)
}

def i_sgt_alias__x_0__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt x0, x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0,x_0,x_0)
}

def i_sgt_alias__x_0__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt x0, x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0,x_0,x_0_alias)
}

def i_sgt_alias__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0,x_0,xpr_general)
}

def i_sgt_alias__x_0__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt x0, zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0,x_0_alias,x_0)
}

def i_sgt_alias__x_0__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt x0, zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0,x_0_alias,x_0_alias)
}

def i_sgt_alias__x_0__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt x0, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0,x_0_alias,xpr_general)
}

def i_sgt_alias__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt x0, $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgt_alias(x_0,xpr_general,x_0)
}

def i_sgt_alias__x_0__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt x0, $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgt_alias(x_0,xpr_general,x_0_alias)
}

def i_sgt_alias__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt x0, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0,xpr_general,xpr_general)
}

def i_sgt_alias__x_0_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt zero, x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0_alias,x_0,x_0)
}

def i_sgt_alias__x_0_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt zero, x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0_alias,x_0,x_0_alias)
}

def i_sgt_alias__x_0_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt zero, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0_alias,x_0,xpr_general)
}

def i_sgt_alias__x_0_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt zero, zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0_alias,x_0_alias,x_0)
}

def i_sgt_alias__x_0_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgt zero, zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgt_alias(x_0_alias,x_0_alias,x_0_alias)
}

def i_sgt_alias__x_0_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt zero, zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0_alias,x_0_alias,xpr_general)
}

def i_sgt_alias__x_0_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt zero, $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgt_alias(x_0_alias,xpr_general,x_0)
}

def i_sgt_alias__x_0_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt zero, $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgt_alias(x_0_alias,xpr_general,x_0_alias)
}

def i_sgt_alias__x_0_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt zero, $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-15} = op1;
let Inst{14-0} = 0b010000000110011;
// i_sgt_alias(x_0_alias,xpr_general,xpr_general)
}

def i_sgt_alias__xpr_general__x_0__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt $op0, x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0,x_0)
}

def i_sgt_alias__xpr_general__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt $op0, x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0,x_0_alias)
}

def i_sgt_alias__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0,xpr_general)
}

def i_sgt_alias__xpr_general__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt $op0, zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0_alias,x_0)
}

def i_sgt_alias__xpr_general__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgt $op0, zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0_alias,x_0_alias)
}

def i_sgt_alias__xpr_general__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt $op0, zero, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,x_0_alias,xpr_general)
}

def i_sgt_alias__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt $op0, $op1, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,xpr_general,x_0)
}

def i_sgt_alias__xpr_general__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgt $op0, $op1, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,xpr_general,x_0_alias)
}

def i_sgt_alias__xpr_general__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1, xpr_general:$op2)>
{
let AsmString = "sgt $op0, $op1, $op2";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
bits<5> op2;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op2;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgt_alias(xpr_general,xpr_general,xpr_general)
}

def i_sgtz_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgtz x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgtz_alias(x_0,x_0)
}

def i_sgtz_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgtz x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgtz_alias(x_0,x_0_alias)
}

def i_sgtz_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgtz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgtz_alias(x_0,xpr_general)
}

def i_sgtz_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgtz zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgtz_alias(x_0_alias,x_0)
}

def i_sgtz_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sgtz zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sgtz_alias(x_0_alias,x_0_alias)
}

def i_sgtz_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgtz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_sgtz_alias(x_0_alias,xpr_general)
}

def i_sgtz_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgtz $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgtz_alias(xpr_general,x_0)
}

def i_sgtz_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sgtz $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgtz_alias(xpr_general,x_0_alias)
}

def i_sgtz_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sgtz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sgtz_alias(xpr_general,xpr_general)
}

def i_sltz_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltz x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sltz_alias(x_0,x_0)
}

def i_sltz_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltz x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sltz_alias(x_0,x_0_alias)
}

def i_sltz_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltz x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sltz_alias(x_0,xpr_general)
}

def i_sltz_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltz zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sltz_alias(x_0_alias,x_0)
}

def i_sltz_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "sltz zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000010000000110011;
// i_sltz_alias(x_0_alias,x_0_alias)
}

def i_sltz_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltz zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_sltz_alias(x_0_alias,xpr_general)
}

def i_sltz_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltz $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sltz_alias(xpr_general,x_0)
}

def i_sltz_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltz $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sltz_alias(xpr_general,x_0_alias)
}

def i_sltz_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltz $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_sltz_alias(xpr_general,xpr_general)
}

def i_snez_alias__x_0__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "snez x0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_snez_alias(x_0,x_0)
}

def i_snez_alias__x_0__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "snez x0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_snez_alias(x_0,x_0_alias)
}

def i_snez_alias__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "snez x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_snez_alias(x_0,xpr_general)
}

def i_snez_alias__x_0_alias__x_0__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "snez zero, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_snez_alias(x_0_alias,x_0)
}

def i_snez_alias__x_0_alias__x_0_alias__: CodasipMicroClass_<(outs), (ins)>
{
let AsmString = "snez zero, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
let Inst{31-0} = 0b00000000000000000011000000110011;
// i_snez_alias(x_0_alias,x_0_alias)
}

def i_snez_alias__x_0_alias__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "snez zero, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_snez_alias(x_0_alias,xpr_general)
}

def i_snez_alias__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "snez $op0, x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_snez_alias(xpr_general,x_0)
}

def i_snez_alias__xpr_general__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "snez $op0, zero";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
let Inst{31-12} = 0b00000000000000000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_snez_alias(xpr_general,x_0_alias)
}

def i_snez_alias__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "snez $op0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_snez_alias(xpr_general,xpr_general)
}

def i_stype_store__opc_sb__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sb x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000000;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0,simm12,x_0_alias)
}

def i_stype_store__opc_sb__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sb zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000000;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0_alias,simm12,x_0)
}

def i_stype_store__opc_sb__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sb zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000000;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0_alias,simm12,x_0_alias)
}

def i_stype_store__opc_sb__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "sb zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-25} = op0{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,x_0_alias,simm12,xpr_general)
}

def i_stype_store__opc_sb__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sb $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000000;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sb,xpr_general,simm12,x_0_alias)
}

def i_stype_store__opc_sh__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sh x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000001;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0,simm12,x_0_alias)
}

def i_stype_store__opc_sh__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sh zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000001;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0_alias,simm12,x_0)
}

def i_stype_store__opc_sh__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sh zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000001;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0_alias,simm12,x_0_alias)
}

def i_stype_store__opc_sh__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "sh zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-25} = op0{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b001;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,x_0_alias,simm12,xpr_general)
}

def i_stype_store__opc_sh__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sh $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sh,xpr_general,simm12,x_0_alias)
}

def i_stype_store__opc_sw__x_0__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sw x0 ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000010;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0,simm12,x_0_alias)
}

def i_stype_store__opc_sw__x_0_alias__simm12__x_0__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sw zero ,  $op0 ( x0 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000010;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0_alias,simm12,x_0)
}

def i_stype_store__opc_sw__x_0_alias__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sw zero ,  $op0 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
let Inst{31-25} = op0{11-5};
let Inst{24-12} = 0b0000000000010;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0_alias,simm12,x_0_alias)
}

def i_stype_store__opc_sw__x_0_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0, xpr_general:$op1)>
{
let AsmString = "sw zero ,  $op0 ( $op1 )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op0;
bits<5> op1;
let Inst{31-25} = op0{11-5};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b010;
let Inst{11-7} = op0{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,x_0_alias,simm12,xpr_general)
}

def i_stype_store__opc_sw__xpr_general__simm12__x_0_alias__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sw $op0 ,  $op1 ( zero )";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<5> op0;
bits<12> op1;
let Inst{31-25} = op1{11-5};
let Inst{24-20} = op0;
let Inst{19-12} = 0b00000010;
let Inst{11-7} = op1{4-0};
let Inst{6-0} = 0b0100011;
// i_stype_store(opc_sw,xpr_general,simm12,x_0_alias)
}

def i_utype_ops__opc_auipc__x_0_alias__uimm20__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_iAny:$op0)>
{
let AsmString = "auipc zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31-12} = op0;
let Inst{11-0} = 0b000000010111;
// i_utype_ops(opc_auipc,x_0_alias,uimm20)
}

def i_utype_ops__opc_lui__x_0_alias__uimm20__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_iAny:$op0)>
{
let AsmString = "lui zero ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<20> op0;
let Inst{31-12} = op0;
let Inst{11-0} = 0b000000110111;
// i_utype_ops(opc_lui,x_0_alias,uimm20)
}

// note: (BGN589): Has unused operands.
def i_btype_branches__opc_bgeu__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bgeu $op0, x0, $op1";
let Size = 4;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b111;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bgeu,xpr_general,x_0,relative_addr12)
}

// note: (BGN589): Has unused operands.
def i_btype_branches__opc_blt__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "blt x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000100;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_blt,x_0,x_0,relative_addr12)
}

// note: (BGN589): Has unused operands.
def i_btype_branches__opc_bltu__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bltu x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000110;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,x_0,x_0,relative_addr12)
}

// note: (BGN589): Has unused operands.
def i_btype_branches__opc_bltu__xpr_general__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op1)>
{
let AsmString = "bltu $op0, x0, $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31} = op1{11-11};
let Inst{30-25} = op1{9-4};
let Inst{24-20} = 0b00000;
let Inst{19-15} = op0;
let Inst{14-12} = 0b110;
let Inst{11-8} = op1{3-0};
let Inst{7} = op1{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bltu,xpr_general,x_0,relative_addr12)
}

// note: (BGN589): Has unused operands.
def i_btype_branches__opc_bne__x_0__x_0__relative_addr12__: CodasipMicroClass_<(outs), (ins MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12_iAny:$op0)>
{
let AsmString = "bne x0, x0, $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31} = op0{11-11};
let Inst{30-25} = op0{9-4};
let Inst{24-12} = 0b0000000000001;
let Inst{11-8} = op0{3-0};
let Inst{7} = op0{10-10};
let Inst{6-0} = 0b1100011;
// i_btype_branches(opc_bne,x_0,x_0,relative_addr12)
}

// note: (BGN511): Invalid jump address computation. Address of a jump must be computed from only one input operand.
def i_call_reg_alias__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "call_reg, $op1 ( $op0 )";
let Defs = [rf_xpr_1];
let Size = 4;
let isBranch = 1;
let isIndirectBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isAsmParserOnly = 1;
bits<12> op1;
bits<5> op0;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000011100111;
// i_call_reg_alias(simm12,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_addi__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "addi x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000000000000010011;
// i_itype_alu(opc_addi,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_addi__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "addi x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000010011;
// i_itype_alu(opc_addi,x_0,xpr_general,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_andi__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "andi x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000111000000010011;
// i_itype_alu(opc_andi,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_andi__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "andi x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000010011;
// i_itype_alu(opc_andi,x_0,xpr_general,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_andi__xpr_general__x_0__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "andi $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-12} = 0b00000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_itype_alu(opc_andi,xpr_general,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_ori__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "ori x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000110000000010011;
// i_itype_alu(opc_ori,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_ori__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "ori x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000010011;
// i_itype_alu(opc_ori,x_0,xpr_general,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_slti__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "slti x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000010000000010011;
// i_itype_alu(opc_slti,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_slti__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "slti x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000010011;
// i_itype_alu(opc_slti,x_0,xpr_general,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_sltiu__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "sltiu x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000011000000010011;
// i_itype_alu(opc_sltiu,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_sltiu__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "sltiu x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000010011;
// i_itype_alu(opc_sltiu,x_0,xpr_general,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_xori__x_0__x_0__simm12__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op0)>
{
let AsmString = "xori x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op0;
let Inst{31-20} = op0;
let Inst{19-0} = 0b00000100000000010011;
// i_itype_alu(opc_xori,x_0,x_0,simm12)
}

// note: (BGN589): Has unused operands.
def i_itype_alu__opc_xori__x_0__xpr_general__simm12__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_iAny:$op1)>
{
let AsmString = "xori x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op1;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000010011;
// i_itype_alu(opc_xori,x_0,xpr_general,simm12)
}

// note: (BGN511): Invalid jump address computation. Address of a jump must be computed from only one input operand.
def i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op1)>
{
let AsmString = "jalr x0 ,  $op1 ( $op0 )";
let Size = 4;
let isBranch = 1;
let isIndirectBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<12> op1;
bits<5> op0;
let Inst{31-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000001100111;
// i_itype_jlreg(opc_jalr,x_0,simm12,xpr_general)
}

// note: (BGN511): Invalid jump address computation. Address of a jump must be computed from only one input operand.
def i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__: CodasipMicroClass_<(outs xpr_general:$op0), (ins xpr_general:$op1, MI5valueIH1_13default_start8_6simm124simm1_6simm12_i32:$op2)>
{
let AsmString = "jalr $op0 ,  $op2 ( $op1 )";
let Size = 4;
let isBranch = 1;
let isIndirectBranch = 1;
let isTerminator = 1;
let isBarrier = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<12> op2;
bits<5> op1;
let Inst{31-20} = op2;
let Inst{19-15} = op1;
let Inst{14-12} = 0b000;
let Inst{11-7} = op0;
let Inst{6-0} = 0b1100111;
// i_itype_jlreg(opc_jalr,xpr_general,simm12,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_add__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_add,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_add__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "add x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_add__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "add x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_add,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_and__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000111000000110011;
// i_rtype_alu(opc_and,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_and__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "and x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_and__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b111000000110011;
// i_rtype_alu(opc_and,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_and__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_and__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "and $op0 ,  $op1 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b111;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_and,xpr_general,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_or__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000110000000110011;
// i_rtype_alu(opc_or,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_or__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "or x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_or__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "or x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b110000000110011;
// i_rtype_alu(opc_or,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sll__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000110011;
// i_rtype_alu(opc_sll,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sll__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sll x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sll__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sll x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000110011;
// i_rtype_alu(opc_sll,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sll__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sll $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sll,xpr_general,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_slt__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000010000000110011;
// i_rtype_alu(opc_slt,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_slt__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "slt x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_slt__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "slt x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b010000000110011;
// i_rtype_alu(opc_slt,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sltu__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000011000000110011;
// i_rtype_alu(opc_sltu,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sltu__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sltu x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sltu__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltu x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b011000000110011;
// i_rtype_alu(opc_sltu,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sltu__xpr_general__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sltu $op0 ,  $op1 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op1;
let Inst{14-12} = 0b011;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sltu,xpr_general,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sra__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_sra,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sra__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sra x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sra__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sra x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_sra,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sra__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sra $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_sra,xpr_general,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_srl__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000110011;
// i_rtype_alu(opc_srl,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_srl__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "srl x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_srl__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "srl x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000110011;
// i_rtype_alu(opc_srl,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_srl__xpr_general__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "srl $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0110011;
// i_rtype_alu(opc_srl,xpr_general,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sub__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000000000000110011;
// i_rtype_alu(opc_sub,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sub__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "sub x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b010000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_sub__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "sub x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b000000000110011;
// i_rtype_alu(opc_sub,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_xor__x_0__x_0__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000100000000110011;
// i_rtype_alu(opc_xor,x_0,x_0,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_xor__x_0__xpr_general__x_0__: CodasipMicroClass_<(outs), (ins xpr_general:$op0)>
{
let AsmString = "xor x0 ,  $op0 ,  x0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-20} = 0b000000000000;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0,xpr_general,x_0)
}

// note: (BGN589): Has unused operands.
def i_rtype_alu__opc_xor__x_0__xpr_general__xpr_general__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, xpr_general:$op1)>
{
let AsmString = "xor x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b100000000110011;
// i_rtype_alu(opc_xor,x_0,xpr_general,xpr_general)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_slli__x_0__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "slli x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000001000000010011;
// i_rtype_shift(opc_slli,x_0,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_slli__x_0__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "slli x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b001000000010011;
// i_rtype_shift(opc_slli,x_0,xpr_general,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_slli__xpr_general__x_0__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "slli $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000001;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_slli,xpr_general,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srai__x_0__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srai x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srai,x_0,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srai__x_0__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srai x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000010011;
// i_rtype_shift(opc_srai,x_0,xpr_general,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srai__xpr_general__x_0__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srai $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0100000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srai,xpr_general,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srli__x_0__x_0__uimm5__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op0)>
{
let AsmString = "srli x0 ,  x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op0;
let Inst{19-0} = 0b00000101000000010011;
// i_rtype_shift(opc_srli,x_0,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srli__x_0__xpr_general__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srli x0 ,  $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-15} = op0;
let Inst{14-0} = 0b101000000010011;
// i_rtype_shift(opc_srli,x_0,xpr_general,uimm5)
}

// note: (BGN589): Has unused operands.
def i_rtype_shift__opc_srli__xpr_general__x_0__uimm5__: CodasipMicroClass_<(outs), (ins xpr_general:$op0, MI5valueIH1_13default_start7_5uimm53imm1_5uimm5_iAny:$op1)>
{
let AsmString = "srli $op0 ,  x0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<5> op0;
bits<5> op1;
let Inst{31-25} = 0b0000000;
let Inst{24-20} = op1;
let Inst{19-12} = 0b00000101;
let Inst{11-7} = op0;
let Inst{6-0} = 0b0010011;
// i_rtype_shift(opc_srli,xpr_general,x_0,uimm5)
}

// note: (BGN589): Has unused operands.
def i_utype_ops__opc_auipc__x_0__uimm20__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_iAny:$op0)>
{
let AsmString = "auipc x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<20> op0;
let Inst{31-12} = op0;
let Inst{11-0} = 0b000000010111;
// i_utype_ops(opc_auipc,x_0,uimm20)
}

// note: (BGN589): Has unused operands.
def i_utype_ops__opc_lui__x_0__uimm20__: CodasipMicroClass_<(outs), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_iAny:$op0)>
{
let AsmString = "lui x0 ,  $op0";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
bits<20> op0;
let Inst{31-12} = op0;
let Inst{11-0} = 0b000000110111;
// i_utype_ops(opc_lui,x_0,uimm20)
}

def i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "lui $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_utype_ops(opc_lui,xpr_general,uimm20)
}

def i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "lui $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_utype_ops(opc_lui,xpr_general,uimm20)
}

def i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "lui $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_utype_ops(opc_lui,xpr_general,uimm20)
}

def i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_: CodasipMicroClass_<(outs xpr_general:$op0), (ins MI5valueIH1_13default_start8_6uimm203imm1_6uimm20_i32:$op1)>
{
let AsmString = "lui $op0 ,  $op1";
let Size = 4;
let isReMaterializable = 1;
let mayLoad = 0;
let mayStore = 0;
let hasSideEffects = 0;
let isPseudo = 1;
let isCodeGenOnly = 1;
// i_utype_ops(opc_lui,xpr_general,uimm20)
}



include "CodasipPatterns.td"
include "CodasipCustomPats.td"

// callsequence nodes, generate instructions through manual elimination


// template for auxiliary meta instructions without coding
class CodasipInstDummy<dag outs, dag ins>
: CodasipInst<outs,ins>
{
  let hasNoSchedulingInfo = 1;
  let isCodeGenOnly = 1;
  let isPseudo = 1;
}

def LSDCallSeqStart: SDCallSeqStart<[ SDTCisVT<0,i32>, SDTCisVT<1,i32> ]>;
def callseq_start: SDNode<"ISD::CALLSEQ_START", LSDCallSeqStart, [SDNPHasChain,SDNPOutGlue,SDNPSideEffect]>;
def CALLSTART: CodasipInstDummy<(outs), (ins i32imm:$InSize, i32imm:$OutSize)>
{
  let AsmString = "#CALLSEQ_START $InSize, $OutSize";
  let Pattern = [(callseq_start timm:$InSize, timm:$OutSize)];
}

def LSDCallSeqEnd: SDCallSeqEnd<[ SDTCisVT<0,i32>, SDTCisVT<1,i32> ]>;
def callseq_end: SDNode<"ISD::CALLSEQ_END", LSDCallSeqEnd, [SDNPHasChain,SDNPOptInGlue,SDNPOutGlue,SDNPSideEffect]>;
def CALLEND: CodasipInstDummy<(outs), (ins i32imm:$InSize, i32imm:$OutSize)>
{
  let AsmString = "#CALLSEQ_END $InSize, $OutSize";
  let Pattern = [(callseq_end timm:$InSize, timm:$OutSize)];
}


def CDSPeh_sjlj_setjmp  : SDNode<"CodasipISD::EH_SJLJ_SETJMP",
                                SDTypeProfile<1, 1, [SDTCisInt<0>,SDTCisPtrTy<1>]>, [SDNPHasChain, SDNPSideEffect]>;
def CDSPeh_sjlj_longjmp : SDNode<"CodasipISD::EH_SJLJ_LONGJMP",
                                SDTypeProfile<0, 1, [SDTCisPtrTy<0>]>, [SDNPHasChain, SDNPSideEffect]>;

def CDSPeh_sjlj_setup_dispatch : SDNode<"CodasipISD::EH_SJLJ_SETUP_DISPATCH",
                                SDTypeProfile<0, 1, [SDTCisPtrTy<0>]>, [SDNPHasChain, SDNPSideEffect]>;

def EH_SjLj_LongJmp : CodasipInstDummy<(outs), (ins xpr_general:$op0)>
{
  let hasSideEffects = 1;
  let isBarrier = 1;
  let usesCustomInserter = 1;
  let isTerminator = 1;
  let AsmString = "#EH_SJLJ_LONGJMP";
  let Pattern = [(CDSPeh_sjlj_longjmp xpr_general:$op0)];
}

def EH_SjLj_SetJmp : CodasipInstDummy<(outs xpr_general:$op0), (ins xpr_general:$op1)>
{
  let hasSideEffects = 1;
  let isBarrier = 1;
  let usesCustomInserter = 1;
  let AsmString = "#EH_SJLJ_SETJMP";
  let Pattern = [(set i32:$op0, (CDSPeh_sjlj_setjmp xpr_general:$op1))];
}

def EH_SjLj_Setup : CodasipInstDummy<(outs), (ins brtarg:$op1)>
{
  let isBranch = 1;
  let isTerminator = 1;
  let Size = 0;
  let AsmString = "#EH_SjLj_Setup\t$op1";
  let Pattern = [];
}

def EH_SJLJ_SETUP_DISPATCH : CodasipInstDummy<(outs), (ins xpr_general:$op0)>
{
  let isBarrier = 1;
  let hasSideEffects = 1;
  let usesCustomInserter = 1;
  let AsmString = "";
  let Pattern = [(CDSPeh_sjlj_setup_dispatch xpr_general:$op0)];
}


// ==== IR HWLoops ====

def hwloop_set_loop_iterations: CodasipInstDummy<(outs), (ins xpr_general:$op0)>
{
  let AsmString = "// HWLOOP SET LOOP ITERATIONS";
  let Pattern = [(int_set_loop_iterations (i32 xpr_general:$op0))];
  let Size = 4;
  let isBarrier = 1;
  let hasSideEffects = 1;
  let isNotDuplicable = 1;
}



def hwloop_loop_decrement_reg: CodasipInstDummy<(outs xpr_general:$op0), (ins xpr_general:$op1, i32imm:$op2)>
{
  let AsmString = "// HWLOOP LOOP DECREMENT REG";
  let Pattern = [(set xpr_general:$op0, (i32 (int_loop_decrement_reg (i32 xpr_general:$op1), (i32 imm:$op2))))];
  let Size = 4;
  let isReMaterializable = 0;
  let isNotDuplicable = 1;
}


