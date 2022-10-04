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


// schedule itineraries, this can be edited
// Note: if VLIW, we don't care about actual unit IDs
// - the only thing that matters is how many slots does something consume

def FU0_S0: FuncUnit;
def FU1_S0: FuncUnit;
def W_rf_xpr_S0: FuncUnit;
def Itin_sc_load: InstrItinClass;

def CodasipItineraries: ProcessorItineraries<[FU0_S0,FU1_S0,W_rf_xpr_S0], [], [
InstrItinData<Itin_sc_load, [InstrStage< 1, [FU0_S0]>, InstrStage<0,[W_rf_xpr_S0],0>, InstrStage< 1, [FU1_S0]>]>
]>;


// an empty file, unless edited
include "CodasipCustomSchedule.td"
// an empty file, unless vliw
include "CodasipVliwSchedule.td"

