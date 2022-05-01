// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"

/**
 * lock by interrupt
 */
typedef struct {
  u64 _rflags;
} IntLock;

static inline void int_lock(IntLock *ctx) {
  asm volatile(
    "pushfq\n\t"
    "cli\n\t"
    "popq %0\n\t"
    : "=m"(ctx->_rflags) : : "memory");
}

static inline void int_unlock(IntLock *ctx) {
  asm volatile(
    "pushq %0\n\t"
    "popfq\n\t"
    : : "m"(ctx->_rflags) : "memory");
}
