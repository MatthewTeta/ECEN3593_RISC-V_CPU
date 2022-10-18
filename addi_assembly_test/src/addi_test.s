/*
 * addi_test.s
 *
 *  Created on: April 1st, 2022
 *      Author: kgraham
 */

 // Section .crt0 is always placed from address 0
	.section .crt0, "ax"

_start:
	.global _start

 /*
 	Immediate (itype) ALU operations
 */

/**************************************************************************
 * Simple add immediate, addi, functionality test to validate data-path
 **************************************************************************/
	addi x2, x0, 2			// Load 2 into x2 reg, 2 + 0 = 2
	nop
	nop
	nop
	addi x2, x2, -1			// value of x2 which will become 2 + -1 resulting in 1
	nop					// check that x2 has been updated with the value 2
	nop
	nop
	nop
	nop					// check to validate x2: 2 + (-1) resulting in the value 1
	halt
/**************************************************************************
 * Simple add rtype, add, functionality test to validate data-path
 **************************************************************************/
	nop
	nop
	nop
	nop
	addi x1, x0, -1
	nop
	nop
	nop
	add x2, x2, x2			// from previous test, x2 = 1, 1 + 1 = 2
	nop					// x1 = -1, 0xffffffff
	nop
	nop
	nop
	nop					// x2 = 2
	add	x3, x1, x2			// -1 + 2 = 1
	nop
	nop
	nop
	nop
	nop					// x3 = 1
	add x2, x1, x3			// 1 + (-1) = 0
	nop
	nop
	nop
	nop
	nop					// x2 should change from 2 to 0
	halt
	nop
	nop
	nop
	nop
	nop
	nop
