/*
 *  regression.s
 *
 *  Author: Matthew Teta
 *  Date: 10/1/22
 *  
 */

 // Section .crt0 is always placed from address 0
	.section .crt0, "ax"

_start:
	.global _start

 /*
 	Immediate (i-type) ALU operations
 */
 	addi x2, x0, 2				// load 2 into register x2
 	nop
 	nop
 	nop
 	addi x2, x2, (-1 & 0xfff)	// add imm (2 + -1) sign extended
 	nop					// x2 = 2
 	nop
 	nop
 	slti x3, x2, 2				// compare 1 to 2, less than so x3 = 1
 	nop					// x2 = 1
 	nop
 	nop
 	slti x3, x2, 1				// compare 1 to 1, not less than, so x3 = 0
 	nop					// x3 = 1
    nop
    nop
    nop
    nop                 // x3 = 0
    // Test sltiu
    sltiu x2, x2, 1             // compare 1 to 1, x2 = 0
    nop
    nop
    nop
    addi x3, x2, -3             // add -4 to get a negative number in a reg (x3)
    nop                 // x2 = 0
    nop
    nop
    sltiu x2, x0, 0xfff         // compare 0 to -1 unsigned (sign extended), 0 is less than 2^32-1 so x2 = 1
    nop                 // x3 = -3
    nop
    nop
    sltiu x2, x3, 10            // compare large unsigned to small unsigned, not less than so x2 = 0
    nop                 // x2 = 1
    nop
    nop
    nop
    nop                 // x2 = 0
    // Test xori
    xori x4, x0, 0xfff          // xor 0x00 with 0xFFFFFFFF, should get x4 = 2^32-1 = 0xFFFFFFFF = 4,294,967,295
    nop
    nop
    nop
    xori x5, x4, 0              // xor 0xFFFFFFFF with 0x00000000, should get x5 = 2^32-1 = 0xFFFFFFFF = 4,294,967,295
    nop                 // x4 = 0xFFFFFFFF
    nop
    nop
    xori x4, x5, 0xfff          // xor 0xFFFFFFFF with 0xFFFFFFFF, x4 = 0
    nop                 // x5 = 0xFFFFFFFF
    nop
    nop
    nop
    nop                 // x4 = 0
    // Test ori
    ori x4, x5, 0xfff           // or 0xFFFFFFFF with 0xFFFFFFFF, x4 = 0xFFFFFFFF
    nop
    nop
    nop
    ori x4, x0, 0               // or 0x00 with 0x00, x4 = 0x00
    nop                 // x4 = 0xFFFFFFFF
    nop
    nop
    ori x2, x4, 0xfff           // or 0x00 with 0xFFFFFFFF, x2 = 0xFFFFFFFF
    nop                 // x4 = 0x00
    nop
    nop
    ori x4, x2, 0               // or 0xFFFFFFFF with 0x00, x4 = 0xFFFFFFFF
    nop                 // x2 = 0xFFFFFFFF
    nop
    nop
    nop
    nop                 // x4 = 0xFFFFFFFF
    // andi
    andi x2, x4, 0              // and 0xFF.. with 0x00, x2 = 0x00
    nop
    nop
    nop
    andi x2, x4, 0xfff          // and 0xFF.. with 0xFF.., x2 = 0xFF...
    nop                 // x2 = 0x00
    nop
    nop
    andi x4, x0, 0              // and 0 with 0, x4 = 0
    nop                 // x2 = 0xFFFFFFFF
    nop
    nop
    andi x5, x0, 0xfff          // and 0 with 0xFF.., x5 = 0x00
    nop                 // x4 = 0x00
    nop
    nop
    nop
    nop                 // x5 = 0x00
    // End I-Type ALU Instruction Tests (1)
    nop
 	nop
 	nop
    nop
  	halt
 	nop
 	nop
 	nop
 	nop
 /*
 	Immediate (r-type) ALU operations
 */
    // Create numbers for testing instructions
    addi x1, x0, 1
    addi x2, x0, 8
    addi x3, x0, -1
    addi x4, x0, -8
    addi x5, x0, 0xFFF // This is the same as -1
    srli x6, x5, 1
    nop
    nop
    nop
    // Test add
    add x10, x0, x0             // add 0+0,     x10 = 0
    nop
    nop
    nop
    add x10, x1, x1             // add 1+1,     x10 = 2
    nop                 // x10 = 0
    nop
    nop
    add x10, x3, x3             // add -1+-1,   x10 = -2 = 0xFFFFFFFE
    nop                 // x10 = 2
    nop
    nop
    add x10, x1, x3             // add 1+-1,    x10 = 0
    nop                 // x10 = -2 = 0xFFFFFFFE
    nop
    nop
    add x10, x5, x0             // add -1+0,    x10 = -1 = 0xFFFFFFFF
    nop                 // x10 = 0
    nop
    nop
    add x10, x6, x1             // add 0x7FFFFFFF + 1,  x10 = 0x80000000 (overflow to negative)
    nop                 // x10 = -1 = 0xFFFFFFFF
    nop
    nop
    nop
    nop                 // x10 = 0x80000000
    // Test sub
    sub x10, x0, x0             // 0-0,     x10 = 0
    nop
    nop
    nop
    sub x10, x1, x0             // 1-0,     x10 = 1
    nop                 // x10 = 0
    nop
    nop
    sub x10, x1, x1             // 1-1,     x10 = 0
    nop                 // x10 = 1
    nop
    nop
    sub x10, x2, x4             // 8-(-8),  x10 = 16
    nop                 // x10 = 0
    nop
    nop
    sub x10, x4, x2             //(-8)-8,   x10 = -16 = 0xFFFFFFF0
    nop                 // x10 = 16
    nop
    nop
    sub x10, x4, x4             //(-8)-(-8) x10 = 0
    nop                 // x10 = -16 = 0xFFFFFFF0
    nop
    nop
    nop
    nop                 // x10 = 0
    // Test sll
    // Initialize more test values
    addi x7, x0, 2              // x7 = 2
    nop
    nop
    nop
    addi x8, x0, 31             // x8 = 31
    nop                 // x7 = 2
    nop
    nop
    addi x9, x0, 32             // x9 = 32
    nop                 // x8 = 31
    nop
    nop
    sll x10, x0, x0             // 0<<0,    x10 = 0
    nop                 // x9 = 32
    nop
    nop
    sll x10, x1, x0             // 1<<0,    x10 = 0
    nop                 // x10 = 0
    nop
    nop
    sll x10, x1, x1             // 1<<1,    x10 = 2
    nop                 // x10 = 0
    nop
    nop
    sll x10, x2, x7             // 8<<2,    x10 = 32
    nop                 // x10 = 2
    nop
    nop
    sll x10, x1, x8             // 1<<31,   x10 = 0x80000000
    nop                 // x10 = 32
    nop
    nop
    sll x10, x1, x9             // 1<<32,   x10 = 0
    nop                 // x10 = 0x80000000
    nop
    nop
    nop
    nop                 // x10 = 0
    // Test slt
    addi x10, x0, 1             // Initialize to see difference
    nop
    nop
    nop
    slt x10, x2, x1             // 8<1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    slt x10, x1, x2             // 1<8,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    slt x10, x1, x1             // 1<1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    slt x10, x3, x1             // (-1)<1,      x10 = 1
    nop                 // x10 = 0
    nop
    nop
    slt x10, x3, x4             // (-1)<(-8),   x10 = 0
    nop                 // x10 = 1
    nop
    nop
    slt x10, x4, x3             // (-8)<(-1),   x10 = 1
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = 1
    // Test sltu
    addi x10, x0, 1             // Initialize   x10 = 1
    nop
    nop
    nop
    sltu x10, x0, x0            // 0<0,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    sltu x10, x1, x2            // 1<8,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    sltu x10, x2, x1            // 8<1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    sltu x10, x1, x3            // 0<-1,        x10 = 1
    nop                 // x10 = 0
    nop
    nop
    sltu x10, x1, x1            // 1<1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    nop
    nop                 // x10 = 0
    // Test xor
    addi x10, x0, 1             // Initialize   x10 = 1
    nop
    nop
    nop
    xor x10, x0, x0             // 0^0,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    xor x10, x0, x1             // 0^1,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    xor x10, x1, x1             // 1^1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    nop
    nop                 // x10 = 0
    // Test srl
    addi x10, x0, 0             // Initialize   x10 = 0
    nop
    nop
    nop
    srl x10, x1, x0             // 1>>0,        x10 = 1
    nop                 // x10 = 0
    nop
    nop
    srl x10, x1, x1             // 1>>1,        x10 = 0
    nop                 // x10 = 1
    nop
    nop
    srl x10, x3, x1             // -1>>1,       x10 = 0x7FFFFFFF
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = 0x7FFFFFFF
    // Test sra
    addi x10, x0, 0             // Initialize   x10 = 0
    nop
    nop
    nop
    sra x10, x1, x0             // 1>>0,        x10 = 1
    nop                 // x10 = 0
    nop
    nop
    sra x10, x1, x1             // 1>>1,        x10 = 0
    nop                 // x10 = 1
    nop
    nop
    sra x10, x3, x1             // -1>>1,       x10 = -1 = 0xFFFFFFFF
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = -1 = 0xFFFFFFFF
    // Test or
    addi x10, x0, 0             // Initialize   x10 = 0
    nop
    nop
    nop
    or x10, x1, x0              // 1|0,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    or x10, x0, x0              // 0|0,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    or x10, x1, x1              // 1|1,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    or x10, x2, x0              // 8|0,         x10 = 8
    nop                 // x10 = 1
    nop
    nop
    or x10, x2, x1              // 8|1,         x10 = 9
    nop                 // x10 = 8
    nop
    nop
    or x10, x3, x4              // -1|-8,       x10 = 0xFFFFFFFF
    nop                 // x10 = 9
    nop
    nop
    nop
    nop                 // x10 = 0xFFFFFFFF
    // Test and
    addi x10, x0, 1             // Initialize   x10 = 1
    nop
    nop
    nop
    and x10, x0, x0             // 0&0,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    and x10, x1, x1             // 1&1,         x10 = 1
    nop                 // x10 = 0
    nop
    nop
    and x10, x0, x1             // 0&1,         x10 = 0
    nop                 // x10 = 1
    nop
    nop
    and x10, x3, x3             // -1&-1,       x10 = 0xFFFFFFFF
    nop                 // x10 = 0
    nop
    nop
    and x10, x1, x0             // 1&0,         x10 = 0
    nop                 // x10 = 0xFFFFFFFF
    nop
    nop
    and x10, x3, x4             // -1&-8,       x10 = -8 = 0xFFFFFFF8
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = -8 = 0xFFFFFFF8
    /* End Immediate (r-type) ALU operations */
	nop
	nop
	nop
	nop
 	halt
 	nop
 	nop
 	nop
 	nop
 /*
    Immediate (r-type immediate) ALU operations
    - slli
    - srli
    - srai
 */
    // Test slli
    // Initialize test values
    addi x7, x0, 2              // x7 = 2
    nop
    nop
    nop
    addi x8, x0, 31             // x8 = 31
    nop                 // x7 = 2
    nop
    nop
    addi x9, x0, 32             // x9 = 32
    nop                 // x8 = 31
    nop
    nop
    slli x10, x0, 0            // 0<<0,    x10 = 0
    nop                 // x9 = 32
    nop
    nop
    slli x10, x1, 0            // 1<<0,    x10 = 0
    nop                 // x10 = 0
    nop
    nop
    slli x10, x1, 1            // 1<<1,    x10 = 2
    nop                 // x10 = 0
    nop
    nop
    slli x10, x2, 2            // 8<<2,    x10 = 32
    nop                 // x10 = 2
    nop
    nop
    slli x10, x1, 31           // 1<<31,   x10 = 0x80000000
    nop                 // x10 = 32
    nop
    nop
    slli x10, x1, 32           // 1<<32,   x10 = 0
    nop                 // x10 = 0x80000000
    nop
    nop
    nop
    nop                 // x10 = 0
    // Test srli
    addi x10, x0, 0             // Initialize   x10 = 0
    nop
    nop
    nop
    srli x10, x1, 0             // 1>>0,        x10 = 1
    nop                 // x10 = 0
    nop
    nop
    srli x10, x1, 1             // 1>>1,        x10 = 0
    nop                 // x10 = 1
    nop
    nop
    srli x10, x3, 1             // -1>>1,       x10 = 0x7FFFFFFF
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = 0x7FFFFFFF
    // Test srai
    addi x10, x0, 0             // Initialize   x10 = 0
    nop
    nop
    nop
    srai x10, x1, 0             // 1>>0,        x10 = 1
    nop                 // x10 = 0
    nop
    nop
    srai x10, x1, 1             // 1>>1,        x10 = 0
    nop                 // x10 = 1
    nop
    nop
    srai x10, x3, 1             // -1>>1,       x10 = -1 = 0xFFFFFFFF
    nop                 // x10 = 0
    nop
    nop
    nop
    nop                 // x10 = -1 = 0xFFFFFFFF
    /* End Immediate (r-type immediate) ALU operations */
	nop
	nop
	nop
	nop
 	halt
 	nop
 	nop
 	nop
 	nop
 /*
 	Data hazard detection and forwarding test sequences
 */
 	addi x2, x0, 1				// load x2 register with 1
 	addi x3, x0, 2				// load x3 register with 2
 	addi x4, x0, 3				// load x4 register with 3
 	addi x5, x0, -1				// load x5 register with -1
    addi x10, x0, 1             // Initialize   x10 = 1
    nop
    nop
    nop
    nop
    nop                 // x10 = 1

    // Read after Write 1
    add x10, x2, x5             // -1+1,        x10 = 0
    add x10, x10, x2            // 0+1,         x10 = 1
    nop
    nop
    nop
    nop
    nop
    // Read after Write 2
    add x10, x2, x5             // -1+1,        x10 = 0
    nop
    add x10, x10, x2            // 0+1,         x10 = 1
    nop
    nop
    nop
    nop
    // Read after Write 3
    add x10, x2, x5             // -1+1,        x10 = 0
    nop
    nop
    add x10, x10, x2            // 0+1,         x10 = 1
    nop
    nop
    nop

	nop
	nop
	nop
	nop
  	halt
 	nop
 	nop
 	nop
 	nop
 /*
 	Branch (b-type) operations
    - beq
    - bne
    - blt
    - bge
    - bltu
    - bgeu
 */
    addi x1, x0, 1
    addi x3, x0, -1
    # // Initialize Loop iterator
    # addi x11, x0, N
	nop
	nop
	nop
	nop
TEST0:
	beq x0, x0, PASS0           // beq+,        ->PASS0
BRANCH_FAIL0:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
PASS2:
    beq x3, x3, PASS3           // beq+,        ->PASS3
    beq x0, x0, BRANCH_FAIL1    // beq+,        ->BRANCH_FAIL1
PASS1:
    beq x0, x0, PASS2           // beq-,        ->PASS2
    beq x0, x0, BRANCH_FAIL1    // beq+,        ->BRANCH_FAIL1
PASS0:
    beq x0, x1, BRANCH_FAIL0    // ~beq-,       (NOP)
    beq x0, x1, BRANCH_FAIL1    // ~beq+,       (NOP)
    beq x0, x1, BRANCH_FAIL0    // ~beq-,       (NOP)
    beq x1, x0, BRANCH_FAIL1    // ~beq+,       (NOP)
    beq x1, x1, PASS1           // beq-,        ->PASS1
BRANCH_FAIL1:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
    // Test bne
PASS6:
    bne x0, x3, PASS7           // bne+,        ->PASS7
    bne x0, x1, BRANCH_FAIL2    // bne+,        ->BRANCH_FAIL1
PASS5:
    bne x3, x0, PASS6           // bne-,        ->PASS6
    bne x0, x1, BRANCH_FAIL2    // bne+,        ->BRANCH_FAIL1
PASS3:
    bne x0, x0, BRANCH_FAIL1    // ~bne-,       (NOP)
    bne x0, x0, BRANCH_FAIL2    // ~bne+,       (NOP)
    bne x1, x1, BRANCH_FAIL1    // ~bne-,       (NOP)
    bne x1, x1, BRANCH_FAIL2    // ~bne+,       (NOP)
    bne x0, x1, PASS4           // bne+,        ->PASS4
BRANCH_FAIL2:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
PASS4:
    bne x1, x0, PASS5           // bne-,        ->PASS5
BRANCH_FAIL3:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
    // Test blt
PASS10:
    blt x0, x3, PASS11          // blt+,        ->PASS11
    blt x0, x1, BRANCH_FAIL4    // blt+,        ->BRANCH_FAIL1
PASS9:
    blt x3, x1, PASS10          // blt-,        ->PASS10
    blt x0, x1, BRANCH_FAIL4    // blt+,        ->BRANCH_FAIL1
PASS7:
    blt x0, x0, BRANCH_FAIL3    // ~blt-,       (NOP)
    blt x0, x0, BRANCH_FAIL4    // ~blt+,       (NOP)
    blt x1, x1, BRANCH_FAIL3    // ~blt-,       (NOP)
    blt x1, x1, BRANCH_FAIL4    // ~blt+,       (NOP)
    blt x0, x1, PASS8           // blt+,        ->PASS8
BRANCH_FAIL4:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
PASS8:
    blt x3, x0, PASS9           // blt-,        ->PASS9
BRANCH_FAIL5:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
    // Test bge
PASS14:
    bge x3, x0, PASS15          // bge+,        ->PASS11
    bge x1, x0, BRANCH_FAIL6    // bge+,        ->BRANCH_FAIL1
PASS13:
    bge x1, x3, PASS14          // bge-,        ->PASS10
    bge x1, x0, BRANCH_FAIL6    // bge+,        ->BRANCH_FAIL1
PASS11:
    bge x0, x0, BRANCH_FAIL5    // ~bge-,       (NOP)
    bge x0, x0, BRANCH_FAIL6    // ~bge+,       (NOP)
    bge x1, x1, BRANCH_FAIL5    // ~bge-,       (NOP)
    bge x1, x1, BRANCH_FAIL6    // ~bge+,       (NOP)
    bge x1, x0, PASS12          // bge+,        ->PASS8
BRANCH_FAIL6:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
PASS12:
    bge x0, x3, PASS13          // bge-,        ->PASS9
BRANCH_FAIL7:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
	nop
    // Test bltu
PASS16:
    bltu x0, x3, PASS17             // bltu+,       ->PASS17
PASS15:
    bltu x0, x0, BRANCH_FAIL7       // ~bltu-,      (NOP)
    bltu x0, x0, BRANCH_FAIL8       // ~bltu+,      (NOP)
    bltu x1, x1, BRANCH_FAIL7       // ~bltu-,      (NOP)
    bltu x1, x1, BRANCH_FAIL8       // ~bltu+,      (NOP)
    bltu x3, x1, BRANCH_FAIL8       // ~bltu+,      (NOP)
    bltu x0, x1, PASS16             // bltu-,       ->PASS16 
BRANCH_FAIL8:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
    // Test bgeu
PASS18:
    bgeu x3, x0, PASS19             // bgeu+,       ->PASS19
PASS17:
    bgeu x0, x0, BRANCH_FAIL8       // ~bgeu-,      (NOP)
    bgeu x0, x0, BRANCH_FAIL9       // ~bgeu+,      (NOP)
    bgeu x1, x1, BRANCH_FAIL8       // ~bgeu-,      (NOP)
    bgeu x1, x1, BRANCH_FAIL9       // ~bgeu+,      (NOP)
    bgeu x1, x3, BRANCH_FAIL9       // ~bgeu+,      (NOP)
    bgeu x1, x0, PASS18             // bgeu-,       ->PASS18
BRANCH_FAIL9:
	nop
	nop
	nop
	nop
	halt		// Branch test has failed, time to debug
	nop
	nop
	nop
PASS19:
    /* All Branch Tests have passed */
	nop
	nop
	nop
  	halt
 	nop
 	nop
 	nop
 	nop
 /*
 	jump instruction operations
    - jalr
    - jal
 */
JTEST0:
    jal x12, 4                      // x12 = JTEST0+4,          ->JTEST1
    jal x0, JFAIL
JTEST1:
    jalr x12, 12(x12)               // x12 = JTEST1+4,          ->JTEST2
    jal x0, JFAIL
JTEST2:
    jal x0, JTESTNEG0
JTESTNEG3:
    jal x0, JSUCCESS                //                          ->JSUCCESS
    jal x0, JFAIL
JTESTNEG2:
    jalr x0, -16(x12)               //                          ->JTESTNEG3
JTESTNEG1:
    jalr x12, -20(x12)              // x12 = JTESTNEG1+4,       ->JTESTNEG2
    jal x0, JFAIL
JTESTNEG0:
    jal x12, -8                     // x12 = JTESTNEG0+4,       ->JTESTNEG1
    jal x0, JFAIL
JFAIL:
    nop
    nop
    nop
    halt            // Jump test failed
    nop
    nop
    nop
JSUCCESS:
    // All jump tests successful
	nop
	nop
	nop
	nop
  	halt
 	nop
 	nop
 	nop
 	nop
 /*
 	Store (s-type)  operations
 */
 	// Loading test data into registers for Store / Load tests
 	addi x20, x0, 0x765
 	slli x20, x20, 12
 	ori	x20, x20, 0x432
 	slli x20, x20, 8
 	ori x20, x20, 0x10				// x20 = 0x76543210
 	xori x21, x20, 0xfff			// x21 = 0x89abcdef
 	// Load register x10 with base DATA memory location
 	addi x10, x0, (DATA >> 12)		// Assume DATA memory address less than 24-bits
 	slli x10, x10, 12				// Move the upper 12-bits to locations 12..23
 	ori x10, x10, (DATA & 0xfff)	// OR in the lower 12-bits to create all 24-bits
 	// Load register x11 with base DATA_MINU location
 	addi x11, x0, (DATA_MINUS >> 12)	// Assume DATA memory address less than 24-bits
 	slli x11, x11, 12					// Move the upper 12-bits to locations 12..23
 	ori x11, x11, (DATA_MINUS & 0xfff)	// OR in the lower 12-bits to create all 24-bits
 	// start of Store Instruction test
	nop
	nop
	nop
	nop
  	halt
  	nop
  	beq x0, x0, LOAD_TEST
  	nop
  	nop
 /*
 	Data Memory Space for regression test
 	- There are 8 NOP locations which are available
 		to be overwritten for test
 	- Accessing the first data location by 0 offset of x10 => 0(x10)
 	- Accessing the 1st byte in data space is 1 offset of x10 => 1(x10)
 	- Accessing the 2nd half-word in data space is 2 offset of x10 => 2(x10)
 	- Accessing the 2nd word in data space is 4 offset of x10 => 4(x10)
 */
DATA:
 	nop
 	nop
 	nop
 	nop
 	nop
 	nop
 	nop
 	nop
 DATA_MINUS:

 /*
 	Load (l-type)  operations
 */
LOAD_TEST:
	nop
	nop
	nop
	nop
  	halt
 	nop
 	nop
 	nop
 	nop
 LOAD_FAIL:							// Using branch statements, if load does not
 	nop								// return result expected, branch to LOAD_FAIL label
 	nop
 	nop
 	halt
 	nop
 	nop
 	nop
 	nop


