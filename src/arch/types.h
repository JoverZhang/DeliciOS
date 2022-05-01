// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "lib/compiler.h"

#define PAGE_SIZE 4096
#define __section(section)  __attribute__((__section__(section)))
#define __aligned(x)        __attribute__((__aligned__(x)))
#define __aligned_page      __aligned(PAGE_SIZE)

#define __init              __section(".init.text")
#define __page_aligned_data __section(".data..page_aligned")  __aligned(PAGE_SIZE)
#define __page_aligned_bss  __section(".bss..page_aligned")   __aligned(PAGE_SIZE)

#define asmlinkage          __attribute__((regparm(0)))
#define inline              __inline__
#define asm                 __asm__

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

typedef i32 bool;
static const bool true = 1;
static const bool false = 0;

static inline u32 isdigit(char ch) {
  return (ch >= '0') && (ch <= '9');
}
