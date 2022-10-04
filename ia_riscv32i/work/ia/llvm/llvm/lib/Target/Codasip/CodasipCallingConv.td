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


// definition of calling conventions
// should be backed by abi def, but can be done automatically as well

def CC_Codasip_Gen: CallingConv<[
  CCIfType<[i16,i8,i1], CCPromoteToType<i32>>,
  CCIfNotVarArg<CCIfType<[i32], CCAssignToReg<[rf_xpr_10, rf_xpr_11, rf_xpr_12, rf_xpr_13, rf_xpr_14, rf_xpr_15, rf_xpr_16, rf_xpr_17]>>>,
  CCIfType<[i32], CCAssignToStack<4,4>>
]>;

def RetCC_Codasip_Gen: CallingConv<[
  CCIfType<[i16,i8,i1], CCPromoteToType<i32>>,
  CCIfType<[i32], CCAssignToReg<[rf_xpr_10, rf_xpr_11, rf_xpr_12, rf_xpr_13, rf_xpr_14, rf_xpr_15, rf_xpr_16, rf_xpr_17]>>
]>;

def CSR_NoRar_Codasip: CalleeSavedRegs<
  (add rf_xpr_9, rf_xpr_18, rf_xpr_19, rf_xpr_20, rf_xpr_21, rf_xpr_22, rf_xpr_23, rf_xpr_24, rf_xpr_25, rf_xpr_26, rf_xpr_27, rf_xpr_8)
>;

// rar must come first
def CSR_Codasip: CalleeSavedRegs<
  (add rf_xpr_1, CSR_NoRar_Codasip)
>;

// all registers (no-rar variant not needed)
def CSR_All_Codasip: CalleeSavedRegs<
  (add rf_xpr_1, rf_xpr_3, rf_xpr_4, rf_xpr_5, rf_xpr_6, rf_xpr_7, rf_xpr_8, rf_xpr_9, rf_xpr_10, rf_xpr_11, rf_xpr_12, rf_xpr_13, rf_xpr_14, rf_xpr_15, rf_xpr_16, rf_xpr_17, rf_xpr_18, rf_xpr_19, rf_xpr_20, rf_xpr_21, rf_xpr_22, rf_xpr_23, rf_xpr_24, rf_xpr_25, rf_xpr_26, rf_xpr_27, rf_xpr_28, rf_xpr_29, rf_xpr_30, rf_xpr_31 )
>;

def CSR_NoRegs: CalleeSavedRegs<(add)>;

include "CodasipCustomCallC.td"
