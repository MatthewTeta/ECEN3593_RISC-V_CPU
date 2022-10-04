//===-- windows/PosixApi.h --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_Host_windows_PosixApi_h
#define liblldb_Host_windows_PosixApi_h

#include "llvm/Support/Compiler.h"
#if !defined(_WIN32)
#error "windows/PosixApi.h being #included on non Windows system!"
#endif

// va_start, va_end, etc macros.
#include <stdarg.h>

// time_t, timespec, etc.
#include <time.h>

#ifndef PATH_MAX
#define PATH_MAX 32768
#endif

#define O_NOCTTY 0
#define O_NONBLOCK 0
#define SIGTRAP 5
#define SIGKILL 9
#define SIGSTOP 20

/// ==== CODASIP ====
#include <stdint.h>

// pyconfig.h typedefs this.  We require python headers to be included before
// any LLDB headers, but there's no way to prevent python's pid_t definition
// from leaking, so this is the best option.

#if defined(__MINGW32__)
#include <sys/types.h>
#include <sys/stat.h>
#else
#ifndef NO_PID_T
typedef uint32_t pid_t;
#endif
#endif
/// =================

#if defined(_MSC_VER)
#define S_IRUSR S_IREAD  /* read, user */
#define S_IWUSR S_IWRITE /* write, user */
#define S_IXUSR 0        /* execute, user */
#endif
/// ==== CODASIP ====
#ifndef S_IRGRP
/// =================
#define S_IRGRP 0 /* read, group */
#define S_IWGRP 0 /* write, group */
#define S_IXGRP 0 /* execute, group */
#define S_IROTH 0 /* read, others */
#define S_IWOTH 0 /* write, others */
#define S_IXOTH 0 /* execute, others */
#define S_IRWXU 0
#define S_IRWXG 0
#define S_IRWXO 0

/// ==== CODASIP ====
#endif
#ifdef _WIN32
/// =================

// PRIxxx format macros for printf()
#include <inttypes.h>

// open(), close(), creat(), etc.
#include <io.h>

typedef unsigned short mode_t;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define S_IFDIR _S_IFDIR

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode)&S_IFMT) == S_IFDIR)
#endif

/// ==== CODASIP ====
#endif // _WIN32
/// =================

// Various useful posix functions that are not present in Windows.  We provide
// custom implementations.
int vasprintf(char **ret, const char *fmt, va_list ap);
char *strcasestr(const char *s, const char *find);
char *realpath(const char *name, char *resolved);

int usleep(uint32_t useconds);
char *basename(char *path);
char *dirname(char *path);

/// ==== CODASIP ====
#ifndef __MINGW32__
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
#endif
/// =================

// empty functions
inline int posix_openpt(int flag) { LLVM_BUILTIN_UNREACHABLE; }

inline int strerror_r(int errnum, char *buf, size_t buflen) {
  LLVM_BUILTIN_UNREACHABLE;
}

inline int unlockpt(int fd) { LLVM_BUILTIN_UNREACHABLE; }
inline int grantpt(int fd) { LLVM_BUILTIN_UNREACHABLE; }
inline char *ptsname(int fd) { LLVM_BUILTIN_UNREACHABLE; }

inline pid_t fork(void) { LLVM_BUILTIN_UNREACHABLE; }
inline pid_t setsid(void) { LLVM_BUILTIN_UNREACHABLE; }

#endif
