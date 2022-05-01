// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"

#define __NR_fork       2
#define __NR_pause      29
#define __NR_nanosleep  35

#define _syscall0(type, name) \
  static inline type name() { \
    type res; \
    asm volatile ("int $0x80": "=a"(res): "a"(__NR_##name)); \
    return res >= 0 ? res : -1; \
  }

_syscall0(int, fork)
_syscall0(int, pause)
