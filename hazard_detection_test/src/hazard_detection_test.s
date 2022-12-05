/*
 * hazard_detection_test.s
 *
 */

 // Section .crt0 is always placed from address 0
	.section .crt0, "ax"

_start:
	.global _start

// I-type Test (rs1 data hazard detection and forwarding)
// Testing data forward from the EXMEM and MEMWB pipeline registers and the WB pipeline stage
     addi  x2, x0, 1                        // x2=1
     addi  x2, x2, 2                        // EXMEM data hazard, x2=3
     addi  x2, x2, 3                        // validates EXMEM over MEMWB or MEM stage data hazard, x2=6
     addi  x2, x2, 4                        // validates EXMEM over WB or WB data hazard, x2=10 (0xa)
     nop
     nop                    // x2 = 1
     nop                    // x2 = 3
     nop                    // x2 = 6
     nop                    // x2 = 10 (0xa)
     addi x2, x0, 1                         // x2=1
     nop
     addi x2, x2, 2                         // MEMWB (MEM Stage) data hazard, x2=3
     addi x2, x2, 3                         // x2=6
     nop
     addi x2, x2, 4         // x2 = 1       // valdates MEMWB over WB data hazard, x2=10 (0xa)
     nop
     nop                    // x2 = 3
     addi x2, x2, 5         // x2 = 6       // validates WB stage data hazard, x2=5
     nop
     nop                    // x2 = 10 (0xa)
     nop
     nop
     nop                    // x2 = 15 (0xf)
     nop
     nop
     nop
     nop
     nop
     nop
     nop
// R-Type Test
// Testing rs1 is properly forwarded
// Assuming that the data forwarding from the different locations will work if passing the 
// first set of tests since the data forwarding logic is agnostic to the instruction type,
// just comparing the different rd register values and regwrite bits
     addi x2, x0, 10
     nop
     nop
     addi x3, x0, 1		                    // x3 = 1
     add x3, x3, x2		                    // EXMEM data hazard, x3 = 1 + 10 = 11 (0xb)
     add x3, x3, x2		    // x2 = 10 (0xa)// EXMEM over MEMWB or MEM stage data hazard, x3 = 11 + 10 = 21 (0x15)
     add x3, x3, x2		                    // EXMEM over WB or WB data hazard, x3 = 21 + 10 = 31 (0x1f)
     nop
     nop                    // x3 = 1
     nop                    // x3 = 11 (0xb)
     nop                    // x3 = 21 (0x15)
     nop                    // x3 = 31 (0x1f)
     nop
     nop
     nop
     nop
     nop
     nop
     nop
// Testing rs2 is properly forwarded
// rs2 is a new set of logic, so all test conditions are required as in the rs1 I-TYPE tests
     addi x4, x0, 1		                    // x4 = 1
     add x4, x2, x4		                    // EXMEM data hazard, x4 = 10 + 1 = 11 (0xb)
     add x4, x2, x4		                    // EXMEM over MEMWB or MEM stage data hazard, x4 = 11 + 10 = 21 (0x15)
     add x4, x2, x4		                    // EXMEM over WB or WB data hazard, x4 = 21 + 10 = 31 (0x1f)
     nop
     nop                   // x4 = 1
     nop                   // x4 = 11 (0xb)
     nop                   // x4 = 21 (0x15)
     nop                   // x4 = 31 (0x1f)
     addi x1, x0, 1                         // x1=1
     nop
     nop
     nop
     nop
     nop                    // x1 = 1
     add x2, x0, x1                         // x2=1
     nop
     add x2, x1, x2                         // MEMWB (MEM stage) data hazard, x2=2
     add x2, x1, x2                         // x2=3
     nop                    
     add x2, x1, x2         // x2 = 1       // valdates MEMWB over WB data hazard, x2=4
     nop
     nop                    // x2 = 2
     add x2, x1, x2         // x2 = 3       // validates WB stage data hazard, x2=5
     nop
     nop                    // x2 = 4
     nop
     nop
     nop                    // x2 = 5
     nop
     nop
     nop
     halt
     nop
     nop
     nop
