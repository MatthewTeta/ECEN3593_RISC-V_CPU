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


// definition of registers, groups of registers and their properties

/******** Register dedication **************************************/
// Stack pointer: rf_xpr_2
// Base pointer: rf_xpr_8

/*******************************************************************/

// convenient classes
class CodasipReg<string defSyntax, list<string> altNames, list<RegAltNameIndex> altNameInds>: Register<defSyntax,altNames>
{
  let Namespace = " Codasip";
  let RegAltNameIndices = altNameInds;
}

class CodasipRegAltNameIndex: RegAltNameIndex
{
  let Namespace = " Codasip";
}

// definition of all HW registers
def xpr_general_AltNameIndex: CodasipRegAltNameIndex;
def rf_xpr_0: CodasipReg<"", [], []>, DwarfRegNum<[0]>
{
 let HWEncoding{4-0} = 0;
}
def rf_xpr_1: CodasipReg<"x1", ["ra"], []>, DwarfRegNum<[1]>
{
 let HWEncoding{4-0} = 1;
}
def rf_xpr_2: CodasipReg<"x2", ["sp"], []>, DwarfRegNum<[2]>
{
 let HWEncoding{4-0} = 2;
}
def rf_xpr_3: CodasipReg<"x3", ["gp"], []>, DwarfRegNum<[3]>
{
 let HWEncoding{4-0} = 3;
}
def rf_xpr_4: CodasipReg<"x4", ["tp"], []>, DwarfRegNum<[4]>
{
 let HWEncoding{4-0} = 4;
}
def rf_xpr_5: CodasipReg<"x5", ["t0"], []>, DwarfRegNum<[5]>
{
 let HWEncoding{4-0} = 5;
}
def rf_xpr_6: CodasipReg<"x6", ["t1"], []>, DwarfRegNum<[6]>
{
 let HWEncoding{4-0} = 6;
}
def rf_xpr_7: CodasipReg<"x7", ["t2"], []>, DwarfRegNum<[7]>
{
 let HWEncoding{4-0} = 7;
}
def rf_xpr_8: CodasipReg<"x8", ["fp","s0"], []>, DwarfRegNum<[8]>
{
 let HWEncoding{4-0} = 8;
}
def rf_xpr_9: CodasipReg<"x9", ["s1"], []>, DwarfRegNum<[9]>
{
 let HWEncoding{4-0} = 9;
}
def rf_xpr_10: CodasipReg<"x10", ["a0"], []>, DwarfRegNum<[10]>
{
 let HWEncoding{4-0} = 10;
}
def rf_xpr_11: CodasipReg<"x11", ["a1"], []>, DwarfRegNum<[11]>
{
 let HWEncoding{4-0} = 11;
}
def rf_xpr_12: CodasipReg<"x12", ["a2"], []>, DwarfRegNum<[12]>
{
 let HWEncoding{4-0} = 12;
}
def rf_xpr_13: CodasipReg<"x13", ["a3"], []>, DwarfRegNum<[13]>
{
 let HWEncoding{4-0} = 13;
}
def rf_xpr_14: CodasipReg<"x14", ["a4"], []>, DwarfRegNum<[14]>
{
 let HWEncoding{4-0} = 14;
}
def rf_xpr_15: CodasipReg<"x15", ["a5"], []>, DwarfRegNum<[15]>
{
 let HWEncoding{4-0} = 15;
}
def rf_xpr_16: CodasipReg<"x16", ["a6"], []>, DwarfRegNum<[16]>
{
 let HWEncoding{4-0} = 16;
}
def rf_xpr_17: CodasipReg<"x17", ["a7"], []>, DwarfRegNum<[17]>
{
 let HWEncoding{4-0} = 17;
}
def rf_xpr_18: CodasipReg<"x18", ["s2"], []>, DwarfRegNum<[18]>
{
 let HWEncoding{4-0} = 18;
}
def rf_xpr_19: CodasipReg<"x19", ["s3"], []>, DwarfRegNum<[19]>
{
 let HWEncoding{4-0} = 19;
}
def rf_xpr_20: CodasipReg<"x20", ["s4"], []>, DwarfRegNum<[20]>
{
 let HWEncoding{4-0} = 20;
}
def rf_xpr_21: CodasipReg<"x21", ["s5"], []>, DwarfRegNum<[21]>
{
 let HWEncoding{4-0} = 21;
}
def rf_xpr_22: CodasipReg<"x22", ["s6"], []>, DwarfRegNum<[22]>
{
 let HWEncoding{4-0} = 22;
}
def rf_xpr_23: CodasipReg<"x23", ["s7"], []>, DwarfRegNum<[23]>
{
 let HWEncoding{4-0} = 23;
}
def rf_xpr_24: CodasipReg<"x24", ["s8"], []>, DwarfRegNum<[24]>
{
 let HWEncoding{4-0} = 24;
}
def rf_xpr_25: CodasipReg<"x25", ["s9"], []>, DwarfRegNum<[25]>
{
 let HWEncoding{4-0} = 25;
}
def rf_xpr_26: CodasipReg<"x26", ["s10"], []>, DwarfRegNum<[26]>
{
 let HWEncoding{4-0} = 26;
}
def rf_xpr_27: CodasipReg<"x27", ["s11"], []>, DwarfRegNum<[27]>
{
 let HWEncoding{4-0} = 27;
}
def rf_xpr_28: CodasipReg<"x28", ["t3"], []>, DwarfRegNum<[28]>
{
 let HWEncoding{4-0} = 28;
}
def rf_xpr_29: CodasipReg<"x29", ["t4"], []>, DwarfRegNum<[29]>
{
 let HWEncoding{4-0} = 29;
}
def rf_xpr_30: CodasipReg<"x30", ["t5"], []>, DwarfRegNum<[30]>
{
 let HWEncoding{4-0} = 30;
}
def rf_xpr_31: CodasipReg<"x31", ["t6"], []>, DwarfRegNum<[31]>
{
 let HWEncoding{4-0} = 31;
}




// definition of HW banks


// definition of register class rf_xpr
def rf_xpr: RegisterClass<"Codasip", [i32], 32, (add rf_xpr_0, rf_xpr_1, rf_xpr_2, rf_xpr_3, rf_xpr_4, rf_xpr_5, rf_xpr_6, rf_xpr_7, rf_xpr_8, rf_xpr_9, rf_xpr_10, rf_xpr_11, rf_xpr_12, rf_xpr_13, rf_xpr_14, rf_xpr_15, rf_xpr_16, rf_xpr_17, rf_xpr_18, rf_xpr_19, rf_xpr_20, rf_xpr_21, rf_xpr_22, rf_xpr_23, rf_xpr_24, rf_xpr_25, rf_xpr_26, rf_xpr_27, rf_xpr_28, rf_xpr_29, rf_xpr_30, rf_xpr_31)>
{
  let isAllocatable = 0;
  let Size = 32;
}


// dummy classes for FI hack



// definition of logical classes


// definition of register class xpr_general
def xpr_general: RegisterClass<"Codasip", [i32], 32, (add rf_xpr_1, rf_xpr_2, rf_xpr_3, rf_xpr_4, rf_xpr_5, rf_xpr_6, rf_xpr_7, rf_xpr_8, rf_xpr_9, rf_xpr_10, rf_xpr_11, rf_xpr_12, rf_xpr_13, rf_xpr_14, rf_xpr_15, rf_xpr_16, rf_xpr_17, rf_xpr_18, rf_xpr_19, rf_xpr_20, rf_xpr_21, rf_xpr_22, rf_xpr_23, rf_xpr_24, rf_xpr_25, rf_xpr_26, rf_xpr_27, rf_xpr_28, rf_xpr_29, rf_xpr_30, rf_xpr_31)>
{
  let AltOrders = [ (add rf_xpr_8, rf_xpr_9, rf_xpr_15, rf_xpr_14, rf_xpr_13, rf_xpr_12, rf_xpr_11, rf_xpr_10, rf_xpr_1, rf_xpr_3, rf_xpr_4, rf_xpr_5, rf_xpr_6, rf_xpr_7, rf_xpr_16, rf_xpr_17, rf_xpr_18, rf_xpr_19, rf_xpr_20, rf_xpr_21, rf_xpr_22, rf_xpr_23, rf_xpr_24, rf_xpr_25, rf_xpr_26, rf_xpr_27, rf_xpr_29),
     (add ) ];
  let AltOrderSelect = [{ if(true) return 1; else  return 0;}];
  let Size = 32;
  let CopyCost = 1;
}


// definition of discarded classes


