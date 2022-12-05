/*
 * control_test.s
 *
 *  Created on: April 1st, 2022
 *      Author: kgraham
 */

 // Section .crt0 is always placed from address 0
	.section .crt0, "ax"

_start:
	.global _start


/*********************************************************************************
 * Simple branch test including tests of clearing instruction after branch taken
 *********************************************************************************/
	addi x2, x0, 2			        // Load 2 into x2 reg, 2 + 0 = 2
	nop
	nop
	nop
	beq x0, x2, FAIL		        // x0=0, x2=2, so it should not branch
    nop
    nop
    nop
	addi x3, x0, 1		    // check that x2 has been updated with the value 2 //x3 should be set to 1
	nop
	nop
	nop
	beq x0, x0, PASS1		        // x=0, x=0, so branch to PASS1
	addi x4, x0, 1			// x3 = 1 
	nop
	nop
	nop
    nop
    nop                     // if x4 gets set to 1, the EX instruction was not cleared (NOP)
    nop
	halt					// If halt reached, branch instruction failed
/**************************************************************************
 * If reached this halt statement, test failure
 **************************************************************************/
 	nop
	nop
	nop
	nop
	nop
	nop
PASS2:
	nop                     // x3 should equal to 1 since the branch beforehand was not taken
 	nop						// check here to ensure that x4 and x5 are not set, if set,
	nop						//      instruction in ID or EX stage was not cleared (NOP)
	nop						//      if x4 = 1, IDEX was not cleared to make a NOP bubble in EX stage
	nop                     //      if X5 = 1, EXMEM was not cleared to make a NOP bubble in MEM stage
	nop                     // If halts here, both positive and negative offset branches successful
	# halt
/**************************************************************************
 * Simple Jump instruction tests
 **************************************************************************/
 	nop						
 	nop						
	nop						
	nop						
	nop
	nop
	addi x2, x0, (RETURN1 & 0xff)		// Save lower 16-bit address.  Small program less than 16-bits address
    addi x30, x0, ((RETURN1 & 0xff00) >> 8)
    slli x30, x30, 8
    or x2, x2, x30
    nop
	nop
	nop
	nop
    nop                     // x2 = RETURN1 address
	jal x1, JUMP1			// jump to positive offset and save return address, RETURN1 label into x1
RETURN1:
	nop
	nop
	nop
	nop
	jal x1, JUMP2
	nop
	nop
	nop
	nop
JUMP3:
	nop
	nop
	nop
	halt					// if code reaches this halt statement, and x10 = 1, your project has passed this test
/**************************************************************************
 * All tests for the control instruction tests have been completed
 **************************************************************************/
 	nop
	nop
	nop
	nop
	nop
JUMP2:
	nop
	nop
	jal x1, JUMP3			// testing negative offset jump
	nop
	nop
	nop
	nop
	nop                 
	halt					// if this halt is reached, there is an error in your jump routine
/**************************************************************************
 * If reached this halt statement, test failure
 **************************************************************************/
 	nop
	nop

PASS1:
	nop
	nop
	beq x0, x0, PASS2		// Testing negative offset branch
	nop
	addi x5, x0, 1			//if x5 gets set to 1, the ID instruction was not cleared (NOP)
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	halt					// reaching this break indicates a failure to branch proceeding this halt
/**************************************************************************
 * Extra-credit Load test to validate structural hazard detected and stall
 **************************************************************************/
 	nop
	nop
	nop
	nop
	nop
	nop
JUMP1:
	addi x10, x0, 1			// Set x10 to 1 to validate jump to address is executed
	nop
	addi x3, x0, 0xff
    slli x30, x3, 8
	or x3, x3, x30      // Save lower 16-bits of return address to compare with lower 16-bits of label
	and x3, x3, x1		
	nop                 // if x10 does not equal 1, the target jump instruction is not executed
    nop                 //     - possible error could be jumping to PC + 4 + jump offset instead of
	nop                 //     - PC + jump offset
	nop
	nop                 // x3 = return address saved
	nop
	bne	x3, x2, FAIL		// x2 = RETURN1.  Validates proper return address saved in x1
	nop
	nop
	nop
	nop
	nop
	jalr x1, 0(x1)			// Use return address saved from the jump to JUMP1

FAIL:
	nop
	nop
	nop
	nop
	nop
	halt
/**************************************************************************
 * If reached this halt statement, test failure
 **************************************************************************/
 	nop
	nop
	nop
	nop
	nop
