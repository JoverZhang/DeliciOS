// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "types.h"

#define GDT_ENTRIES 16

typedef struct {
  u16 limit0;
  u16 base0;
  u8 base1;
  // access byte
  u8 a: 1,      // accessed bit
  rw: 1,        // readable / writeable
  dc: 1,        // direction / conforming
  e: 1,         // executable
  s: 1,         // (1) is tss
  dpl: 2,       // descriptor privilege level
  p: 1;         // present
  u8 limit1: 4, // limit1
  // flags
  zero: 1,      // reserved
  l: 1,         // long mode
  db: 1,        // size flag
  g: 1;         // granularity
  u8 base2;
} __attribute__((packed)) Gdt;

typedef struct {
  u16 size;
  Gdt *address;
} __attribute__((packed)) GdtDescr;

void gdt_init(void);
