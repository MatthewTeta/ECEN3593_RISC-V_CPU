# 1 "/home/project/ia_riscv32i/libs/newlib/libgloss/crt1.S"
# 1 "<built-in>" 1
# 330 "<built-in>"
# 1 "/home/project/ia_riscv32i/work/ia_riscv32i_options.hcodal" 1
# 331 "<built-in>" 2
# 1 "/home/project/ia_riscv32i/libs/newlib/libgloss/crt1.S" 2
# 26 "/home/project/ia_riscv32i/libs/newlib/libgloss/crt1.S"
 .section .crt0, "ax"


_start:
 .global _start

 j _reset_handler
 nop
 nop
 nop


codasip_syscall:
    .global codasip_syscall
    .dword 0

_reset_handler:
    .global _reset_handler



 lui sp, (_stack & 0xfffff000) >> 12
 lui x30, (_stack & 0x00000fff)
 srli x30, x30, 12
 or sp, sp, x30


 j ctors_init

ctors_initialized:
    j dtors_init

dtors_initialized:

 lui x10, (_codasip_argc_address & 0xfffff000) >> 12
 lui x30, (_codasip_argc_address & 0x00000fff)
 srli x30, x30, 12
 or x10, x10, x30
    lw x10, 0(x10)

 lui x11, (_codasip_argv_pointers & 0xfffff000) >> 12
 lui x30, (_codasip_argv_pointers & 0x00000fff)
 srli x30, x30, 12
 or x11, x11, x30


    call main
    call exit
    addi x31, x0, 1; lui t0, (codasip_syscall & 0xfffff000) >> 12; lui x30, (codasip_syscall & 0x00000fff); srli x30, x30, 12; or t0, t0, x30; sw x31, 0 (t0); 1: jal x0, 1b

ctors_init:


 lui x13, (__CTOR_LIST__ & 0xfffff000) >> 12
 lui x30, (__CTOR_LIST__ & 0x00000fff)
 srli x30, x30, 12
 or x13, x13, x30


 addi sp, sp, -(8)

ctors_loop:

 lui x14, (__CTOR_END__ & 0xfffff000) >> 12
 lui x30, (__CTOR_END__ & 0x00000fff)
 srli x30, x30, 12
 or x14, x14, x30
 beq x14, x13, ctors_end


    sw x13, 0(sp)

    lw x13, 0(x13)

    nop
    jalr x1, 0(x13)

    lw x13, 0(sp)

    nop

    addi x13, x13, 4
    j ctors_loop

ctors_end:
    mv x13, x0
    mv x14, x0

    addi sp, sp, +8
    j ctors_initialized

dtors_init:

 lui x13, (__DTOR_LIST__ & 0xfffff000) >> 12
 lui x30, (__DTOR_LIST__ & 0x00000fff)
 srli x30, x30, 12
 or x13, x13, x30


    addi sp, sp, -(8)

dtors_loop:

 lui x14, (__DTOR_END__ & 0xfffff000) >> 12
 lui x30, (__DTOR_END__ & 0x00000fff)
 srli x30, x30, 12
 or x14, x14, x30
    beq x14, x13, dtors_end

    sw x13, 0(sp)

    lw x10, 0(x13)

    nop
    call atexit

    lw x13, 0(sp)

    nop

    addi x13, x13, 4
    j dtors_loop

dtors_end:
    mv x13, x0
    mv x14, x0

    addi sp, sp, +8
    j dtors_initialized

abort:
    .global abort

    addi x10, x0, 134
    addi x31, x0, 1; lui t0, (codasip_syscall & 0xfffff000) >> 12; lui x30, (codasip_syscall & 0x00000fff); srli x30, x30, 12; or t0, t0, x30; sw x31, 0 (t0); 1: jal x0, 1b

_exit:
    .global _exit

    addi x31, x0, 1; lui t0, (codasip_syscall & 0xfffff000) >> 12; lui x30, (codasip_syscall & 0x00000fff); srli x30, x30, 12; or t0, t0, x30; sw x31, 0 (t0); 1: jal x0, 1b




    .section .progargs, "aw"
    .align 8
_codasip_argc_address:
    .global _codasip_argc_address
    .word 0

_codasip_argv_pointers:
    .global _codasip_argv_pointers
    .fill 32, 4, 0

_codasip_argv_strings:
    .global _codasip_argv_strings
    .fill 512, 1, 0



    .section .text_jump_padding, "ax"
    .word 0
    .word 0
    .word 0



    .section .data
    .global __dso_handle
    .weak __dso_handle
__dso_handle:
    .long 0
