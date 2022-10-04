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


#ifndef _CODASIP_INLINES_H_
#define _CODASIP_INLINES_H_

//#include <inttypes.h>
#if   __SIZEOF_POINTER__ == 2
#define int32_t            long
#define uint32_t  unsigned long
#define OPCODE_TYPE_STR "i16"
#elif __SIZEOF_POINTER__ == 4
#define int32_t            long
#define uint32_t  unsigned long
#define OPCODE_TYPE_STR "i32"
#elif __SIZEOF_POINTER__ == 8
#define int32_t            int
#define uint32_t  unsigned int
#define OPCODE_TYPE_STR "i32"
#else
// for other pointer sizes assume long is 32-bit
// that's how it is in clang
#define int32_t            long
#define uint32_t  unsigned long
#endif

#define int8_t      signed char 
#define uint8_t   unsigned char
#define int16_t            short
#define uint16_t  unsigned short
#define int64_t            long long
#define uint64_t  unsigned long long

// helper types
typedef union {int32_t i; float f;} __codasip_builtin_bitcast_i32_f32_ty;

// non-standard ints
#define DEFINE_CUSTOM_INT(width) \
typedef          int  int##width##_t __attribute__((bit_width( width ))); \
typedef unsigned int uint##width##_t __attribute__((bit_width( width )))
DEFINE_CUSTOM_INT(1);
DEFINE_CUSTOM_INT(128);
DEFINE_CUSTOM_INT(256);
DEFINE_CUSTOM_INT(512);
DEFINE_CUSTOM_INT(1024);
DEFINE_CUSTOM_INT(2048);
#undef DEFINE_CUSTOM_INT

// Structures and types in which the wrappers return their results.




// builtin template functions -- don't use directly

extern void   __codasip_builtin_void(int,...)    __asm__("llvm.codasip.builtin." OPCODE_TYPE_STR);
extern float  __codasip_builtin_float(int,...)   __asm__("llvm.codasip.builtin.anyfloat.f32." OPCODE_TYPE_STR);
extern double __codasip_builtin_double(int,...)  __asm__("llvm.codasip.builtin.anyfloat.f64." OPCODE_TYPE_STR);
extern void   __codasip_builtin_nomem_void(int,...)    __asm__("llvm.codasip.builtin." OPCODE_TYPE_STR); //must not be void and nomem at the same time
extern float  __codasip_builtin_nomem_float(int,...)   __asm__("llvm.codasip.builtin.nomem.anyfloat.f32." OPCODE_TYPE_STR);
extern double __codasip_builtin_nomem_double(int,...)  __asm__("llvm.codasip.builtin.nomem.anyfloat.f64." OPCODE_TYPE_STR);



/// Internal subcodes for intrinsic calls
enum IntrinsicsSubcodes
{
  
  IntrinsicsSubcodes_stopper
};

// Wrappers for intrinsic calls 



#undef int8_t
#undef uint8_t
#undef int16_t
#undef uint16_t
#undef int32_t
#undef uint32_t
#undef int64_t
#undef uint64_t

#endif // _CODASIP_INLINES_H_
