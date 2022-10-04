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
 * \author  Codasip (c) Assembler generator
 * \version 9.1.1-1255
 * \brief   Source for assembler
 */

%type <assemblerNode> MI5start
%type <assemblerNode> MI13default_start_broken
%type <assemblerNode> MI13default_start_identifier_identifier
%type <assemblerNode> MI19roots_default_start_identifier_identifier
%type <assemblerNode> MI3isaIH1_13default_start_identifier_identifier
%type <assemblerNode> MI11i_rtype_aluIH1_13default_start
%type <assemblerNode> MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc
%type <assemblerNode> MI7xpr_allIH1_13default_start9_7xpr_all2rd
%type <assemblerNode> MI11xpr_generalIH1_13default_start9_7xpr_all2rd
%type <assemblerNode> MI7xpr_allIH1_13default_start9_7xpr_all3rs1
%type <assemblerNode> MI11xpr_generalIH1_13default_start9_7xpr_all3rs1
%type <assemblerNode> MI7xpr_allIH1_13default_start9_7xpr_all3rs2
%type <assemblerNode> MI11xpr_generalIH1_13default_start9_7xpr_all3rs2
%type <assemblerNode> MI13i_rtype_shiftIH1_13default_start
%type <assemblerNode> MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc
%type <assemblerNode> MI11i_itype_aluIH1_13default_start
%type <assemblerNode> MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc
%type <assemblerNode> MI11i_utype_opsIH1_13default_start
%type <assemblerNode> MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc
%type <assemblerNode> MI13i_jtype_jlinkIH1_13default_start
%type <assemblerNode> MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc
%type <assemblerNode> MI16i_btype_branchesIH1_13default_start
%type <assemblerNode> MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc
%type <assemblerNode> MI10i_li_aliasIH1_13default_start
%type <assemblerNode> MI10i_mv_aliasIH1_13default_start
%type <assemblerNode> MI11i_not_aliasIH1_13default_start
%type <assemblerNode> MI11i_neg_aliasIH1_13default_start
%type <assemblerNode> MI12i_seqz_aliasIH1_13default_start
%type <assemblerNode> MI12i_snez_aliasIH1_13default_start
%type <assemblerNode> MI12i_sltz_aliasIH1_13default_start
%type <assemblerNode> MI12i_sgtz_aliasIH1_13default_start
%type <assemblerNode> MI11i_sgt_aliasIH1_13default_start
%type <assemblerNode> MI12i_beqz_aliasIH1_13default_start
%type <assemblerNode> MI12i_bnez_aliasIH1_13default_start
%type <assemblerNode> MI12i_blez_aliasIH1_13default_start
%type <assemblerNode> MI12i_bltz_aliasIH1_13default_start
%type <assemblerNode> MI12i_bgez_aliasIH1_13default_start
%type <assemblerNode> MI12i_bgtz_aliasIH1_13default_start
%type <assemblerNode> MI11i_bgt_aliasIH1_13default_start
%type <assemblerNode> MI11i_ble_aliasIH1_13default_start
%type <assemblerNode> MI12i_bgtu_aliasIH1_13default_start
%type <assemblerNode> MI12i_bleu_aliasIH1_13default_start
%type <assemblerNode> MI10i_jr_aliasIH1_13default_start
%type <assemblerNode> MI13default_start_identifier_non_identifier
%type <assemblerNode> MI19roots_default_start_identifier_non_identifier
%type <assemblerNode> MI3isaIH1_13default_start_identifier_non_identifier
%type <assemblerNode> MI13i_itype_loadsIH1_13default_start
%type <assemblerNode> MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc
%type <assemblerNode> MI13i_stype_storeIH1_13default_start
%type <assemblerNode> MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc
%type <assemblerNode> MI13i_itype_jlregIH1_13default_start
%type <assemblerNode> MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc
%type <assemblerNode> MI16i_call_reg_aliasIH1_13default_start
%type <assemblerNode> Instructions

%code {
}

%%

Newline
    : ';'
    ;

Code
    : Instructions %merge <MergeCode>
    {
        $$ = $1;
    }
    ;

Instructions
    : MI5start
    {
        $$ = &ast::assembler::Builder::CreateGenerateInstructionCommand(GetLocation(@1), *$1, 0);
    }
    ;

MI5start
    : MI13default_start_broken %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI5start", "", 0);
        $$->AddChild(*$1);
    }
    ;

MI13default_start_broken
    : MI13default_start_identifier_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13default_start_broken", "", 0);
        $$->AddChild(*$1);
    }
    | MI13default_start_identifier_non_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13default_start_broken", "", 0);
        $$->AddChild(*$1);
    }
    ;

MI13default_start_identifier_identifier
    : MI19roots_default_start_identifier_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13default_start_identifier_identifier", "", 0, 0);
        $$->AddChild(*$1);
    }
    ;

MI19roots_default_start_identifier_identifier
    : MI3isaIH1_13default_start_identifier_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI19roots_default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    ;

MI3isaIH1_13default_start_identifier_identifier
    : MI11i_rtype_aluIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI13i_rtype_shiftIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_itype_aluIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_utype_opsIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI13i_jtype_jlinkIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI16i_btype_branchesIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | N O P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_nop_aliasIH1_13default_start", "i_nop_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "nop"));
        $$->AddChild(*x1);
    }
    | MI10i_li_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI10i_mv_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_not_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_neg_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_seqz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_snez_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_sltz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_sgtz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_sgt_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_beqz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bnez_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_blez_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bltz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bgez_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bgtz_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_bgt_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI11i_ble_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bgtu_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI12i_bleu_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | J WS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9i_j_aliasIH1_13default_start", "i_j_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "j"));
        x1->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@3), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *$3, 20, 1));
        x1->AddChild(*x2);
        $$->AddChild(*x1);
    }
    | MI10i_jr_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | R E T %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_ret_aliasIH1_13default_start", "i_ret_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ret"));
        $$->AddChild(*x1);
    }
    | C A L L WS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_call_aliasIH1_13default_start", "i_call_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "call"));
        x1->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@6), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *$6, 20, 1));
        x1->AddChild(*x2);
        $$->AddChild(*x1);
    }
    | H A L T %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6i_haltIH1_13default_start", "i_halt", 0, 0);
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_haltIH1_13default_start10_8opc_halt3opc", "opc_halt", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "halt"));
        x1->AddChild(*x2);
        $$->AddChild(*x1);
    }
    ;

MI11i_rtype_aluIH1_13default_start
    : MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_rtype_aluIH1_13default_start", "i_rtype_alu", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(*$8);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        $$->AddChild(*$13);
    }
    ;

MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc
    : A D D %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_addIH1_13default_start16_13opc_rtype_alu3opc", "opc_add", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "add"));
        $$->AddChild(*x1);
    }
    | S U B %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_subIH1_13default_start16_13opc_rtype_alu3opc", "opc_sub", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sub"));
        $$->AddChild(*x1);
    }
    | S L L %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_sllIH1_13default_start16_13opc_rtype_alu3opc", "opc_sll", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sll"));
        $$->AddChild(*x1);
    }
    | S L T %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_sltIH1_13default_start16_13opc_rtype_alu3opc", "opc_slt", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "slt"));
        $$->AddChild(*x1);
    }
    | S L T U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_sltuIH1_13default_start16_13opc_rtype_alu3opc", "opc_sltu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sltu"));
        $$->AddChild(*x1);
    }
    | X O R %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_xorIH1_13default_start16_13opc_rtype_alu3opc", "opc_xor", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "xor"));
        $$->AddChild(*x1);
    }
    | S R L %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_srlIH1_13default_start16_13opc_rtype_alu3opc", "opc_srl", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "srl"));
        $$->AddChild(*x1);
    }
    | S R A %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_sraIH1_13default_start16_13opc_rtype_alu3opc", "opc_sra", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sra"));
        $$->AddChild(*x1);
    }
    | O R %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_orIH1_13default_start16_13opc_rtype_alu3opc", "opc_or", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "or"));
        $$->AddChild(*x1);
    }
    | A N D %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_andIH1_13default_start16_13opc_rtype_alu3opc", "opc_and", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "and"));
        $$->AddChild(*x1);
    }
    ;

MI7xpr_allIH1_13default_start9_7xpr_all2rd
    : MI11xpr_generalIH1_13default_start9_7xpr_all2rd %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        $$->AddChild(*$1);
    }
    | X '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_0IH1_13default_start9_7xpr_all2rd", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x0"));
        $$->AddChild(*x1);
    }
    | Z E R O %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9x_0_aliasIH1_13default_start9_7xpr_all2rd", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "zero"));
        $$->AddChild(*x1);
    }
    ;

MI11xpr_generalIH1_13default_start9_7xpr_all2rd
    : X '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_1IH1_13default_start9_7xpr_all2rd", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x1"));
        $$->AddChild(*x1);
    }
    | R A %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_1_alias0IH1_13default_start9_7xpr_all2rd", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ra"));
        $$->AddChild(*x1);
    }
    | X '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_2IH1_13default_start9_7xpr_all2rd", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x2"));
        $$->AddChild(*x1);
    }
    | S P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_2_alias0IH1_13default_start9_7xpr_all2rd", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sp"));
        $$->AddChild(*x1);
    }
    | X '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_3IH1_13default_start9_7xpr_all2rd", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x3"));
        $$->AddChild(*x1);
    }
    | G P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_3_alias0IH1_13default_start9_7xpr_all2rd", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "gp"));
        $$->AddChild(*x1);
    }
    | X '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_4IH1_13default_start9_7xpr_all2rd", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x4"));
        $$->AddChild(*x1);
    }
    | T P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_4_alias0IH1_13default_start9_7xpr_all2rd", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "tp"));
        $$->AddChild(*x1);
    }
    | X '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_5IH1_13default_start9_7xpr_all2rd", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x5"));
        $$->AddChild(*x1);
    }
    | T '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_5_alias0IH1_13default_start9_7xpr_all2rd", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t0"));
        $$->AddChild(*x1);
    }
    | X '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_6IH1_13default_start9_7xpr_all2rd", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x6"));
        $$->AddChild(*x1);
    }
    | T '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_6_alias0IH1_13default_start9_7xpr_all2rd", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t1"));
        $$->AddChild(*x1);
    }
    | X '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_7IH1_13default_start9_7xpr_all2rd", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x7"));
        $$->AddChild(*x1);
    }
    | T '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_7_alias0IH1_13default_start9_7xpr_all2rd", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t2"));
        $$->AddChild(*x1);
    }
    | X '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_8IH1_13default_start9_7xpr_all2rd", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x8"));
        $$->AddChild(*x1);
    }
    | F P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias0IH1_13default_start9_7xpr_all2rd", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "fp"));
        $$->AddChild(*x1);
    }
    | S '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias1IH1_13default_start9_7xpr_all2rd", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s0"));
        $$->AddChild(*x1);
    }
    | X '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_9IH1_13default_start9_7xpr_all2rd", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x9"));
        $$->AddChild(*x1);
    }
    | S '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_9_alias0IH1_13default_start9_7xpr_all2rd", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s1"));
        $$->AddChild(*x1);
    }
    | X '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_10IH1_13default_start9_7xpr_all2rd", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x10"));
        $$->AddChild(*x1);
    }
    | A '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_10_alias0IH1_13default_start9_7xpr_all2rd", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a0"));
        $$->AddChild(*x1);
    }
    | X '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_11IH1_13default_start9_7xpr_all2rd", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x11"));
        $$->AddChild(*x1);
    }
    | A '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_11_alias0IH1_13default_start9_7xpr_all2rd", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a1"));
        $$->AddChild(*x1);
    }
    | X '1' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_12IH1_13default_start9_7xpr_all2rd", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x12"));
        $$->AddChild(*x1);
    }
    | A '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_12_alias0IH1_13default_start9_7xpr_all2rd", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a2"));
        $$->AddChild(*x1);
    }
    | X '1' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_13IH1_13default_start9_7xpr_all2rd", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x13"));
        $$->AddChild(*x1);
    }
    | A '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_13_alias0IH1_13default_start9_7xpr_all2rd", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a3"));
        $$->AddChild(*x1);
    }
    | X '1' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_14IH1_13default_start9_7xpr_all2rd", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x14"));
        $$->AddChild(*x1);
    }
    | A '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_14_alias0IH1_13default_start9_7xpr_all2rd", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a4"));
        $$->AddChild(*x1);
    }
    | X '1' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_15IH1_13default_start9_7xpr_all2rd", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x15"));
        $$->AddChild(*x1);
    }
    | A '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_15_alias0IH1_13default_start9_7xpr_all2rd", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a5"));
        $$->AddChild(*x1);
    }
    | X '1' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_16IH1_13default_start9_7xpr_all2rd", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x16"));
        $$->AddChild(*x1);
    }
    | A '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_16_alias0IH1_13default_start9_7xpr_all2rd", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a6"));
        $$->AddChild(*x1);
    }
    | X '1' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_17IH1_13default_start9_7xpr_all2rd", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x17"));
        $$->AddChild(*x1);
    }
    | A '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_17_alias0IH1_13default_start9_7xpr_all2rd", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a7"));
        $$->AddChild(*x1);
    }
    | X '1' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_18IH1_13default_start9_7xpr_all2rd", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x18"));
        $$->AddChild(*x1);
    }
    | S '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_18_alias0IH1_13default_start9_7xpr_all2rd", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s2"));
        $$->AddChild(*x1);
    }
    | X '1' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_19IH1_13default_start9_7xpr_all2rd", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x19"));
        $$->AddChild(*x1);
    }
    | S '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_19_alias0IH1_13default_start9_7xpr_all2rd", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s3"));
        $$->AddChild(*x1);
    }
    | X '2' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_20IH1_13default_start9_7xpr_all2rd", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x20"));
        $$->AddChild(*x1);
    }
    | S '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_20_alias0IH1_13default_start9_7xpr_all2rd", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s4"));
        $$->AddChild(*x1);
    }
    | X '2' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_21IH1_13default_start9_7xpr_all2rd", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x21"));
        $$->AddChild(*x1);
    }
    | S '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_21_alias0IH1_13default_start9_7xpr_all2rd", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s5"));
        $$->AddChild(*x1);
    }
    | X '2' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_22IH1_13default_start9_7xpr_all2rd", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x22"));
        $$->AddChild(*x1);
    }
    | S '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_22_alias0IH1_13default_start9_7xpr_all2rd", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s6"));
        $$->AddChild(*x1);
    }
    | X '2' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_23IH1_13default_start9_7xpr_all2rd", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x23"));
        $$->AddChild(*x1);
    }
    | S '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_23_alias0IH1_13default_start9_7xpr_all2rd", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s7"));
        $$->AddChild(*x1);
    }
    | X '2' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_24IH1_13default_start9_7xpr_all2rd", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x24"));
        $$->AddChild(*x1);
    }
    | S '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_24_alias0IH1_13default_start9_7xpr_all2rd", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s8"));
        $$->AddChild(*x1);
    }
    | X '2' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_25IH1_13default_start9_7xpr_all2rd", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x25"));
        $$->AddChild(*x1);
    }
    | S '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_25_alias0IH1_13default_start9_7xpr_all2rd", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s9"));
        $$->AddChild(*x1);
    }
    | X '2' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_26IH1_13default_start9_7xpr_all2rd", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x26"));
        $$->AddChild(*x1);
    }
    | S '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_26_alias0IH1_13default_start9_7xpr_all2rd", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s10"));
        $$->AddChild(*x1);
    }
    | X '2' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_27IH1_13default_start9_7xpr_all2rd", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x27"));
        $$->AddChild(*x1);
    }
    | S '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_27_alias0IH1_13default_start9_7xpr_all2rd", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s11"));
        $$->AddChild(*x1);
    }
    | X '2' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_28IH1_13default_start9_7xpr_all2rd", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x28"));
        $$->AddChild(*x1);
    }
    | T '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_28_alias0IH1_13default_start9_7xpr_all2rd", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t3"));
        $$->AddChild(*x1);
    }
    | X '2' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_29IH1_13default_start9_7xpr_all2rd", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x29"));
        $$->AddChild(*x1);
    }
    | T '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_29_alias0IH1_13default_start9_7xpr_all2rd", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t4"));
        $$->AddChild(*x1);
    }
    | X '3' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_30IH1_13default_start9_7xpr_all2rd", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x30"));
        $$->AddChild(*x1);
    }
    | T '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_30_alias0IH1_13default_start9_7xpr_all2rd", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t5"));
        $$->AddChild(*x1);
    }
    | X '3' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_31IH1_13default_start9_7xpr_all2rd", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x31"));
        $$->AddChild(*x1);
    }
    | T '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_31_alias0IH1_13default_start9_7xpr_all2rd", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t6"));
        $$->AddChild(*x1);
    }
    ;

MI7xpr_allIH1_13default_start9_7xpr_all3rs1
    : MI11xpr_generalIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        $$->AddChild(*$1);
    }
    | X '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_0IH1_13default_start9_7xpr_all3rs1", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x0"));
        $$->AddChild(*x1);
    }
    | Z E R O %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9x_0_aliasIH1_13default_start9_7xpr_all3rs1", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "zero"));
        $$->AddChild(*x1);
    }
    ;

MI11xpr_generalIH1_13default_start9_7xpr_all3rs1
    : X '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_1IH1_13default_start9_7xpr_all3rs1", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x1"));
        $$->AddChild(*x1);
    }
    | R A %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_1_alias0IH1_13default_start9_7xpr_all3rs1", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ra"));
        $$->AddChild(*x1);
    }
    | X '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_2IH1_13default_start9_7xpr_all3rs1", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x2"));
        $$->AddChild(*x1);
    }
    | S P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_2_alias0IH1_13default_start9_7xpr_all3rs1", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sp"));
        $$->AddChild(*x1);
    }
    | X '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_3IH1_13default_start9_7xpr_all3rs1", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x3"));
        $$->AddChild(*x1);
    }
    | G P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_3_alias0IH1_13default_start9_7xpr_all3rs1", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "gp"));
        $$->AddChild(*x1);
    }
    | X '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_4IH1_13default_start9_7xpr_all3rs1", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x4"));
        $$->AddChild(*x1);
    }
    | T P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_4_alias0IH1_13default_start9_7xpr_all3rs1", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "tp"));
        $$->AddChild(*x1);
    }
    | X '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_5IH1_13default_start9_7xpr_all3rs1", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x5"));
        $$->AddChild(*x1);
    }
    | T '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_5_alias0IH1_13default_start9_7xpr_all3rs1", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t0"));
        $$->AddChild(*x1);
    }
    | X '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_6IH1_13default_start9_7xpr_all3rs1", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x6"));
        $$->AddChild(*x1);
    }
    | T '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_6_alias0IH1_13default_start9_7xpr_all3rs1", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t1"));
        $$->AddChild(*x1);
    }
    | X '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_7IH1_13default_start9_7xpr_all3rs1", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x7"));
        $$->AddChild(*x1);
    }
    | T '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_7_alias0IH1_13default_start9_7xpr_all3rs1", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t2"));
        $$->AddChild(*x1);
    }
    | X '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_8IH1_13default_start9_7xpr_all3rs1", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x8"));
        $$->AddChild(*x1);
    }
    | F P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias0IH1_13default_start9_7xpr_all3rs1", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "fp"));
        $$->AddChild(*x1);
    }
    | S '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias1IH1_13default_start9_7xpr_all3rs1", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s0"));
        $$->AddChild(*x1);
    }
    | X '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_9IH1_13default_start9_7xpr_all3rs1", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x9"));
        $$->AddChild(*x1);
    }
    | S '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_9_alias0IH1_13default_start9_7xpr_all3rs1", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s1"));
        $$->AddChild(*x1);
    }
    | X '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_10IH1_13default_start9_7xpr_all3rs1", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x10"));
        $$->AddChild(*x1);
    }
    | A '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_10_alias0IH1_13default_start9_7xpr_all3rs1", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a0"));
        $$->AddChild(*x1);
    }
    | X '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_11IH1_13default_start9_7xpr_all3rs1", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x11"));
        $$->AddChild(*x1);
    }
    | A '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_11_alias0IH1_13default_start9_7xpr_all3rs1", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a1"));
        $$->AddChild(*x1);
    }
    | X '1' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_12IH1_13default_start9_7xpr_all3rs1", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x12"));
        $$->AddChild(*x1);
    }
    | A '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_12_alias0IH1_13default_start9_7xpr_all3rs1", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a2"));
        $$->AddChild(*x1);
    }
    | X '1' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_13IH1_13default_start9_7xpr_all3rs1", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x13"));
        $$->AddChild(*x1);
    }
    | A '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_13_alias0IH1_13default_start9_7xpr_all3rs1", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a3"));
        $$->AddChild(*x1);
    }
    | X '1' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_14IH1_13default_start9_7xpr_all3rs1", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x14"));
        $$->AddChild(*x1);
    }
    | A '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_14_alias0IH1_13default_start9_7xpr_all3rs1", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a4"));
        $$->AddChild(*x1);
    }
    | X '1' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_15IH1_13default_start9_7xpr_all3rs1", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x15"));
        $$->AddChild(*x1);
    }
    | A '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_15_alias0IH1_13default_start9_7xpr_all3rs1", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a5"));
        $$->AddChild(*x1);
    }
    | X '1' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_16IH1_13default_start9_7xpr_all3rs1", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x16"));
        $$->AddChild(*x1);
    }
    | A '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_16_alias0IH1_13default_start9_7xpr_all3rs1", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a6"));
        $$->AddChild(*x1);
    }
    | X '1' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_17IH1_13default_start9_7xpr_all3rs1", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x17"));
        $$->AddChild(*x1);
    }
    | A '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_17_alias0IH1_13default_start9_7xpr_all3rs1", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a7"));
        $$->AddChild(*x1);
    }
    | X '1' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_18IH1_13default_start9_7xpr_all3rs1", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x18"));
        $$->AddChild(*x1);
    }
    | S '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_18_alias0IH1_13default_start9_7xpr_all3rs1", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s2"));
        $$->AddChild(*x1);
    }
    | X '1' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_19IH1_13default_start9_7xpr_all3rs1", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x19"));
        $$->AddChild(*x1);
    }
    | S '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_19_alias0IH1_13default_start9_7xpr_all3rs1", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s3"));
        $$->AddChild(*x1);
    }
    | X '2' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_20IH1_13default_start9_7xpr_all3rs1", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x20"));
        $$->AddChild(*x1);
    }
    | S '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_20_alias0IH1_13default_start9_7xpr_all3rs1", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s4"));
        $$->AddChild(*x1);
    }
    | X '2' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_21IH1_13default_start9_7xpr_all3rs1", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x21"));
        $$->AddChild(*x1);
    }
    | S '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_21_alias0IH1_13default_start9_7xpr_all3rs1", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s5"));
        $$->AddChild(*x1);
    }
    | X '2' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_22IH1_13default_start9_7xpr_all3rs1", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x22"));
        $$->AddChild(*x1);
    }
    | S '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_22_alias0IH1_13default_start9_7xpr_all3rs1", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s6"));
        $$->AddChild(*x1);
    }
    | X '2' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_23IH1_13default_start9_7xpr_all3rs1", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x23"));
        $$->AddChild(*x1);
    }
    | S '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_23_alias0IH1_13default_start9_7xpr_all3rs1", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s7"));
        $$->AddChild(*x1);
    }
    | X '2' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_24IH1_13default_start9_7xpr_all3rs1", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x24"));
        $$->AddChild(*x1);
    }
    | S '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_24_alias0IH1_13default_start9_7xpr_all3rs1", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s8"));
        $$->AddChild(*x1);
    }
    | X '2' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_25IH1_13default_start9_7xpr_all3rs1", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x25"));
        $$->AddChild(*x1);
    }
    | S '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_25_alias0IH1_13default_start9_7xpr_all3rs1", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s9"));
        $$->AddChild(*x1);
    }
    | X '2' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_26IH1_13default_start9_7xpr_all3rs1", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x26"));
        $$->AddChild(*x1);
    }
    | S '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_26_alias0IH1_13default_start9_7xpr_all3rs1", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s10"));
        $$->AddChild(*x1);
    }
    | X '2' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_27IH1_13default_start9_7xpr_all3rs1", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x27"));
        $$->AddChild(*x1);
    }
    | S '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_27_alias0IH1_13default_start9_7xpr_all3rs1", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s11"));
        $$->AddChild(*x1);
    }
    | X '2' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_28IH1_13default_start9_7xpr_all3rs1", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x28"));
        $$->AddChild(*x1);
    }
    | T '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_28_alias0IH1_13default_start9_7xpr_all3rs1", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t3"));
        $$->AddChild(*x1);
    }
    | X '2' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_29IH1_13default_start9_7xpr_all3rs1", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x29"));
        $$->AddChild(*x1);
    }
    | T '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_29_alias0IH1_13default_start9_7xpr_all3rs1", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t4"));
        $$->AddChild(*x1);
    }
    | X '3' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_30IH1_13default_start9_7xpr_all3rs1", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x30"));
        $$->AddChild(*x1);
    }
    | T '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_30_alias0IH1_13default_start9_7xpr_all3rs1", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t5"));
        $$->AddChild(*x1);
    }
    | X '3' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_31IH1_13default_start9_7xpr_all3rs1", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x31"));
        $$->AddChild(*x1);
    }
    | T '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_31_alias0IH1_13default_start9_7xpr_all3rs1", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t6"));
        $$->AddChild(*x1);
    }
    ;

MI7xpr_allIH1_13default_start9_7xpr_all3rs2
    : MI11xpr_generalIH1_13default_start9_7xpr_all3rs2 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        $$->AddChild(*$1);
    }
    | X '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_0IH1_13default_start9_7xpr_all3rs2", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x0"));
        $$->AddChild(*x1);
    }
    | Z E R O %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9x_0_aliasIH1_13default_start9_7xpr_all3rs2", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "zero"));
        $$->AddChild(*x1);
    }
    ;

MI11xpr_generalIH1_13default_start9_7xpr_all3rs2
    : X '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_1IH1_13default_start9_7xpr_all3rs2", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x1"));
        $$->AddChild(*x1);
    }
    | R A %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_1_alias0IH1_13default_start9_7xpr_all3rs2", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ra"));
        $$->AddChild(*x1);
    }
    | X '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_2IH1_13default_start9_7xpr_all3rs2", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x2"));
        $$->AddChild(*x1);
    }
    | S P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_2_alias0IH1_13default_start9_7xpr_all3rs2", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sp"));
        $$->AddChild(*x1);
    }
    | X '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_3IH1_13default_start9_7xpr_all3rs2", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x3"));
        $$->AddChild(*x1);
    }
    | G P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_3_alias0IH1_13default_start9_7xpr_all3rs2", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "gp"));
        $$->AddChild(*x1);
    }
    | X '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_4IH1_13default_start9_7xpr_all3rs2", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x4"));
        $$->AddChild(*x1);
    }
    | T P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_4_alias0IH1_13default_start9_7xpr_all3rs2", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "tp"));
        $$->AddChild(*x1);
    }
    | X '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_5IH1_13default_start9_7xpr_all3rs2", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x5"));
        $$->AddChild(*x1);
    }
    | T '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_5_alias0IH1_13default_start9_7xpr_all3rs2", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t0"));
        $$->AddChild(*x1);
    }
    | X '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_6IH1_13default_start9_7xpr_all3rs2", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x6"));
        $$->AddChild(*x1);
    }
    | T '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_6_alias0IH1_13default_start9_7xpr_all3rs2", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t1"));
        $$->AddChild(*x1);
    }
    | X '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_7IH1_13default_start9_7xpr_all3rs2", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x7"));
        $$->AddChild(*x1);
    }
    | T '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_7_alias0IH1_13default_start9_7xpr_all3rs2", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t2"));
        $$->AddChild(*x1);
    }
    | X '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_8IH1_13default_start9_7xpr_all3rs2", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x8"));
        $$->AddChild(*x1);
    }
    | F P %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias0IH1_13default_start9_7xpr_all3rs2", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "fp"));
        $$->AddChild(*x1);
    }
    | S '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_8_alias1IH1_13default_start9_7xpr_all3rs2", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s0"));
        $$->AddChild(*x1);
    }
    | X '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI3x_9IH1_13default_start9_7xpr_all3rs2", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x9"));
        $$->AddChild(*x1);
    }
    | S '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10x_9_alias0IH1_13default_start9_7xpr_all3rs2", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s1"));
        $$->AddChild(*x1);
    }
    | X '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_10IH1_13default_start9_7xpr_all3rs2", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x10"));
        $$->AddChild(*x1);
    }
    | A '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_10_alias0IH1_13default_start9_7xpr_all3rs2", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a0"));
        $$->AddChild(*x1);
    }
    | X '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_11IH1_13default_start9_7xpr_all3rs2", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x11"));
        $$->AddChild(*x1);
    }
    | A '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_11_alias0IH1_13default_start9_7xpr_all3rs2", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a1"));
        $$->AddChild(*x1);
    }
    | X '1' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_12IH1_13default_start9_7xpr_all3rs2", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x12"));
        $$->AddChild(*x1);
    }
    | A '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_12_alias0IH1_13default_start9_7xpr_all3rs2", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a2"));
        $$->AddChild(*x1);
    }
    | X '1' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_13IH1_13default_start9_7xpr_all3rs2", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x13"));
        $$->AddChild(*x1);
    }
    | A '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_13_alias0IH1_13default_start9_7xpr_all3rs2", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a3"));
        $$->AddChild(*x1);
    }
    | X '1' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_14IH1_13default_start9_7xpr_all3rs2", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x14"));
        $$->AddChild(*x1);
    }
    | A '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_14_alias0IH1_13default_start9_7xpr_all3rs2", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a4"));
        $$->AddChild(*x1);
    }
    | X '1' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_15IH1_13default_start9_7xpr_all3rs2", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x15"));
        $$->AddChild(*x1);
    }
    | A '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_15_alias0IH1_13default_start9_7xpr_all3rs2", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a5"));
        $$->AddChild(*x1);
    }
    | X '1' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_16IH1_13default_start9_7xpr_all3rs2", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x16"));
        $$->AddChild(*x1);
    }
    | A '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_16_alias0IH1_13default_start9_7xpr_all3rs2", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a6"));
        $$->AddChild(*x1);
    }
    | X '1' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_17IH1_13default_start9_7xpr_all3rs2", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x17"));
        $$->AddChild(*x1);
    }
    | A '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_17_alias0IH1_13default_start9_7xpr_all3rs2", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "a7"));
        $$->AddChild(*x1);
    }
    | X '1' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_18IH1_13default_start9_7xpr_all3rs2", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x18"));
        $$->AddChild(*x1);
    }
    | S '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_18_alias0IH1_13default_start9_7xpr_all3rs2", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s2"));
        $$->AddChild(*x1);
    }
    | X '1' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_19IH1_13default_start9_7xpr_all3rs2", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x19"));
        $$->AddChild(*x1);
    }
    | S '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_19_alias0IH1_13default_start9_7xpr_all3rs2", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s3"));
        $$->AddChild(*x1);
    }
    | X '2' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_20IH1_13default_start9_7xpr_all3rs2", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x20"));
        $$->AddChild(*x1);
    }
    | S '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_20_alias0IH1_13default_start9_7xpr_all3rs2", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s4"));
        $$->AddChild(*x1);
    }
    | X '2' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_21IH1_13default_start9_7xpr_all3rs2", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x21"));
        $$->AddChild(*x1);
    }
    | S '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_21_alias0IH1_13default_start9_7xpr_all3rs2", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s5"));
        $$->AddChild(*x1);
    }
    | X '2' '2' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_22IH1_13default_start9_7xpr_all3rs2", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x22"));
        $$->AddChild(*x1);
    }
    | S '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_22_alias0IH1_13default_start9_7xpr_all3rs2", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s6"));
        $$->AddChild(*x1);
    }
    | X '2' '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_23IH1_13default_start9_7xpr_all3rs2", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x23"));
        $$->AddChild(*x1);
    }
    | S '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_23_alias0IH1_13default_start9_7xpr_all3rs2", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s7"));
        $$->AddChild(*x1);
    }
    | X '2' '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_24IH1_13default_start9_7xpr_all3rs2", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x24"));
        $$->AddChild(*x1);
    }
    | S '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_24_alias0IH1_13default_start9_7xpr_all3rs2", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s8"));
        $$->AddChild(*x1);
    }
    | X '2' '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_25IH1_13default_start9_7xpr_all3rs2", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x25"));
        $$->AddChild(*x1);
    }
    | S '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_25_alias0IH1_13default_start9_7xpr_all3rs2", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s9"));
        $$->AddChild(*x1);
    }
    | X '2' '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_26IH1_13default_start9_7xpr_all3rs2", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x26"));
        $$->AddChild(*x1);
    }
    | S '1' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_26_alias0IH1_13default_start9_7xpr_all3rs2", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s10"));
        $$->AddChild(*x1);
    }
    | X '2' '7' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_27IH1_13default_start9_7xpr_all3rs2", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x27"));
        $$->AddChild(*x1);
    }
    | S '1' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_27_alias0IH1_13default_start9_7xpr_all3rs2", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "s11"));
        $$->AddChild(*x1);
    }
    | X '2' '8' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_28IH1_13default_start9_7xpr_all3rs2", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x28"));
        $$->AddChild(*x1);
    }
    | T '3' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_28_alias0IH1_13default_start9_7xpr_all3rs2", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t3"));
        $$->AddChild(*x1);
    }
    | X '2' '9' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_29IH1_13default_start9_7xpr_all3rs2", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x29"));
        $$->AddChild(*x1);
    }
    | T '4' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_29_alias0IH1_13default_start9_7xpr_all3rs2", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t4"));
        $$->AddChild(*x1);
    }
    | X '3' '0' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_30IH1_13default_start9_7xpr_all3rs2", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x30"));
        $$->AddChild(*x1);
    }
    | T '5' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_30_alias0IH1_13default_start9_7xpr_all3rs2", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t5"));
        $$->AddChild(*x1);
    }
    | X '3' '1' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI4x_31IH1_13default_start9_7xpr_all3rs2", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "x31"));
        $$->AddChild(*x1);
    }
    | T '6' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11x_31_alias0IH1_13default_start9_7xpr_all3rs2", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "t6"));
        $$->AddChild(*x1);
    }
    ;

MI13i_rtype_shiftIH1_13default_start
    : MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13i_rtype_shiftIH1_13default_start", "i_rtype_shift", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(*$8);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI5uimm5IH1_13default_start7_5uimm53imm", "uimm5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@13), "MI5valueIH1_13default_start7_5uimm53imm1_5uimm5", "value", *$13, 5, 0));
        $$->AddChild(*x1);
    }
    ;

MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc
    : S L L I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_slliIH1_13default_start18_15opc_rtype_shift3opc", "opc_slli", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "slli"));
        $$->AddChild(*x1);
    }
    | S R L I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_srliIH1_13default_start18_15opc_rtype_shift3opc", "opc_srli", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "srli"));
        $$->AddChild(*x1);
    }
    | S R A I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_sraiIH1_13default_start18_15opc_rtype_shift3opc", "opc_srai", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "srai"));
        $$->AddChild(*x1);
    }
    ;

MI11i_itype_aluIH1_13default_start
    : MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_itype_aluIH1_13default_start", "i_itype_alu", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(*$8);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@13), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$13, 12, 0));
        $$->AddChild(*x1);
    }
    ;

MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc
    : A D D I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_addiIH1_13default_start16_13opc_itype_alu3opc", "opc_addi", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "addi"));
        $$->AddChild(*x1);
    }
    | S L T I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_sltiIH1_13default_start16_13opc_itype_alu3opc", "opc_slti", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "slti"));
        $$->AddChild(*x1);
    }
    | S L T I U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9opc_sltiuIH1_13default_start16_13opc_itype_alu3opc", "opc_sltiu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sltiu"));
        $$->AddChild(*x1);
    }
    | X O R I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_xoriIH1_13default_start16_13opc_itype_alu3opc", "opc_xori", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "xori"));
        $$->AddChild(*x1);
    }
    | O R I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_oriIH1_13default_start16_13opc_itype_alu3opc", "opc_ori", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ori"));
        $$->AddChild(*x1);
    }
    | A N D I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_andiIH1_13default_start16_13opc_itype_alu3opc", "opc_andi", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "andi"));
        $$->AddChild(*x1);
    }
    ;

MI11i_utype_opsIH1_13default_start
    : MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_utype_opsIH1_13default_start", "i_utype_ops", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6uimm20IH1_13default_start8_6uimm203imm", "uimm20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI5valueIH1_13default_start8_6uimm203imm1_6uimm20", "value", *$8, 20, 0));
        $$->AddChild(*x1);
    }
    ;

MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc
    : L U I %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_luiIH1_13default_start16_13opc_utype_ops3opc", "opc_lui", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lui"));
        $$->AddChild(*x1);
    }
    | A U I P C %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI9opc_auipcIH1_13default_start16_13opc_utype_ops3opc", "opc_auipc", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "auipc"));
        $$->AddChild(*x1);
    }
    ;

MI13i_jtype_jlinkIH1_13default_start
    : MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13i_jtype_jlinkIH1_13default_start", "i_jtype_jlink", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *$8, 20, 1));
        $$->AddChild(*x1);
    }
    ;

MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc
    : J A L %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_jalIH1_13default_start18_15opc_jtype_jlink3opc", "opc_jal", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "jal"));
        $$->AddChild(*x1);
    }
    ;

MI16i_btype_branchesIH1_13default_start
    : MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI16i_btype_branchesIH1_13default_start", "i_btype_branches", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(*$7);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@9), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@10), $10)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr123imm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@11), "MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12", "addr12", *$11, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc
    : B E Q %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_beqIH1_13default_start21_18opc_btype_branches3opc", "opc_beq", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "beq"));
        $$->AddChild(*x1);
    }
    | B N E %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_bneIH1_13default_start21_18opc_btype_branches3opc", "opc_bne", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bne"));
        $$->AddChild(*x1);
    }
    | B L T %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_bltIH1_13default_start21_18opc_btype_branches3opc", "opc_blt", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "blt"));
        $$->AddChild(*x1);
    }
    | B G E %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_bgeIH1_13default_start21_18opc_btype_branches3opc", "opc_bge", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bge"));
        $$->AddChild(*x1);
    }
    | B L T U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_bltuIH1_13default_start21_18opc_btype_branches3opc", "opc_bltu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bltu"));
        $$->AddChild(*x1);
    }
    | B G E U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_bgeuIH1_13default_start21_18opc_btype_branches3opc", "opc_bgeu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bgeu"));
        $$->AddChild(*x1);
    }
    ;

MI10i_li_aliasIH1_13default_start
    : L I WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10i_li_aliasIH1_13default_start", "i_li_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "li"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@3), $3)); // WS
        $$->AddChild(*$4);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@6), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$8, 12, 0));
        $$->AddChild(*x1);
    }
    ;

MI10i_mv_aliasIH1_13default_start
    : M V WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10i_mv_aliasIH1_13default_start", "i_mv_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "mv"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@3), $3)); // WS
        $$->AddChild(*$4);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@6), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(*$8);
    }
    ;

MI11i_not_aliasIH1_13default_start
    : N O T WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_not_aliasIH1_13default_start", "i_not_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "not"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // WS
        $$->AddChild(*$5);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@7), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(*$9);
    }
    ;

MI11i_neg_aliasIH1_13default_start
    : N E G WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_neg_aliasIH1_13default_start", "i_neg_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "neg"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // WS
        $$->AddChild(*$5);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@7), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(*$9);
    }
    ;

MI12i_seqz_aliasIH1_13default_start
    : S E Q Z WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_seqz_aliasIH1_13default_start", "i_seqz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "seqz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
    }
    ;

MI12i_snez_aliasIH1_13default_start
    : S N E Z WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_snez_aliasIH1_13default_start", "i_snez_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "snez"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
    }
    ;

MI12i_sltz_aliasIH1_13default_start
    : S L T Z WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_sltz_aliasIH1_13default_start", "i_sltz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sltz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
    }
    ;

MI12i_sgtz_aliasIH1_13default_start
    : S G T Z WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_sgtz_aliasIH1_13default_start", "i_sgtz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sgtz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
    }
    ;

MI11i_sgt_aliasIH1_13default_start
    : S G T WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_sgt_aliasIH1_13default_start", "i_sgt_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sgt"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // WS
        $$->AddChild(*$5);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@7), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(*$9);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@10), $10)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@11), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        $$->AddChild(*$13);
    }
    ;

MI12i_beqz_aliasIH1_13default_start
    : B E Q Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_beqz_aliasIH1_13default_start", "i_beqz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "beqz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bnez_aliasIH1_13default_start
    : B N E Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bnez_aliasIH1_13default_start", "i_bnez_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bnez"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_blez_aliasIH1_13default_start
    : B L E Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_blez_aliasIH1_13default_start", "i_blez_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "blez"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bltz_aliasIH1_13default_start
    : B L T Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bltz_aliasIH1_13default_start", "i_bltz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bltz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bgez_aliasIH1_13default_start
    : B G E Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bgez_aliasIH1_13default_start", "i_bgez_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bgez"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bgtz_aliasIH1_13default_start
    : B G T Z WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bgtz_aliasIH1_13default_start", "i_bgtz_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bgtz"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@10), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$10, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI11i_bgt_aliasIH1_13default_start
    : B G T WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_bgt_aliasIH1_13default_start", "i_bgt_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bgt"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // WS
        $$->AddChild(*$5);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@7), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(*$9);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@10), $10)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@11), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@13), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$13, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI11i_ble_aliasIH1_13default_start
    : B L E WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI11i_ble_aliasIH1_13default_start", "i_ble_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "ble"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // WS
        $$->AddChild(*$5);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@6), $6)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@7), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@8), $8)); // MWS
        $$->AddChild(*$9);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@10), $10)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@11), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@12), $12)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@13), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$13, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bgtu_aliasIH1_13default_start
    : B G T U WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bgtu_aliasIH1_13default_start", "i_bgtu_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bgtu"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@12), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@14), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$14, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI12i_bleu_aliasIH1_13default_start
    : B L E U WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI12i_bleu_aliasIH1_13default_start", "i_bleu_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "bleu"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@5), $5)); // WS
        $$->AddChild(*$6);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@8), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(*$10);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@12), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@14), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *$14, 12, 1));
        $$->AddChild(*x1);
    }
    ;

MI10i_jr_aliasIH1_13default_start
    : J R WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI10i_jr_aliasIH1_13default_start", "i_jr_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "jr"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@3), $3)); // WS
        $$->AddChild(*$4);
    }
    ;

MI13default_start_identifier_non_identifier
    : MI19roots_default_start_identifier_non_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13default_start_identifier_non_identifier", "", 0, 0);
        $$->AddChild(*$1);
    }
    ;

MI19roots_default_start_identifier_non_identifier
    : MI3isaIH1_13default_start_identifier_non_identifier %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI19roots_default_start_identifier_non_identifier", "", 0);
        $$->AddChild(*$1);
    }
    ;

MI3isaIH1_13default_start_identifier_non_identifier
    : MI13i_itype_loadsIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI13i_stype_storeIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI13i_itype_jlregIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        $$->AddChild(*$1);
    }
    | MI16i_call_reg_aliasIH1_13default_start %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        $$->AddChild(*$1);
    }
    ;

MI13i_itype_loadsIH1_13default_start
    : MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13i_itype_loadsIH1_13default_start", "i_itype_loads", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$8, 12, 0));
        $$->AddChild(*x1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), "("));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        $$->AddChild(*$12);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@14), ")"));
    }
    ;

MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc
    : L B %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_lbIH1_13default_start18_15opc_itype_loads3opc", "opc_lb", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lb"));
        $$->AddChild(*x1);
    }
    | L H %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_lhIH1_13default_start18_15opc_itype_loads3opc", "opc_lh", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lh"));
        $$->AddChild(*x1);
    }
    | L W %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_lwIH1_13default_start18_15opc_itype_loads3opc", "opc_lw", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lw"));
        $$->AddChild(*x1);
    }
    | L B U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_lbuIH1_13default_start18_15opc_itype_loads3opc", "opc_lbu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lbu"));
        $$->AddChild(*x1);
    }
    | L H U %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI7opc_lhuIH1_13default_start18_15opc_itype_loads3opc", "opc_lhu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "lhu"));
        $$->AddChild(*x1);
    }
    ;

MI13i_stype_storeIH1_13default_start
    : MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13i_stype_storeIH1_13default_start", "i_stype_store", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$8, 12, 0));
        $$->AddChild(*x1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), "("));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        $$->AddChild(*$12);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@14), ")"));
    }
    ;

MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc
    : S B %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_sbIH1_13default_start18_15opc_stype_store3opc", "opc_sb", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sb"));
        $$->AddChild(*x1);
    }
    | S H %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_shIH1_13default_start18_15opc_stype_store3opc", "opc_sh", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sh"));
        $$->AddChild(*x1);
    }
    | S W %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6opc_swIH1_13default_start18_15opc_stype_store3opc", "opc_sw", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "sw"));
        $$->AddChild(*x1);
    }
    ;

MI13i_itype_jlregIH1_13default_start
    : MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI13i_itype_jlregIH1_13default_start", "i_itype_jlreg", 0, 0);
        $$->AddChild(*$1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@2), $2)); // WS
        $$->AddChild(*$3);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@4), $4)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@5), ", "));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@7), $7)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@8), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$8, 12, 0));
        $$->AddChild(*x1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), "("));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        $$->AddChild(*$12);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@14), ")"));
    }
    ;

MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc
    : J A L R %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateSet(GetLocation(@$), "MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI8opc_jalrIH1_13default_start18_15opc_itype_jlreg3opc", "opc_jalr", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "jalr"));
        $$->AddChild(*x1);
    }
    ;

MI16i_call_reg_aliasIH1_13default_start
    : C A L L '_' R E G MWS ',' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')' %merge <MergeNode>
    {
        $$ = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI16i_call_reg_aliasIH1_13default_start", "i_call_reg_alias", 0, 0);
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@1), "call_reg"));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@9), $9)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@10), ","));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@11), $11)); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation(@$), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation(@12), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *$12, 12, 0));
        $$->AddChild(*x1);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@13), $13)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@14), "("));
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@15), $15)); // MWS
        $$->AddChild(*$16);
        $$->AddChild(ast::assembler::Builder::CreateSpace(GetLocation(@17), $17)); // MWS
        $$->AddChild(ast::assembler::Builder::CreateConstant(GetLocation(@18), ")"));
    }
    ;

%%
