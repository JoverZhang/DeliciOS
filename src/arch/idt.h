// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "types.h"
#include "../kernel/isr.h"

#define IDT_ENTRIES 256

typedef struct {
  u16 offset_low;    // offset bits 0..15
  u16 segment;       // a code segment selector in GDT or LDT
  struct {
    u16 ist: 3,      // holds Interrupt Stack Table offset
    zero: 5,         // reserved
    type: 5,         // gate type
    dpl: 2,          // defines privilege levels
    p: 1;            // present bit
  } bits;
  u16 offset_middle; // offset bits 16..31
  u32 offset_high;   // offset bits 32..63
  u32 zero;          // reserved
} __attribute__((packed)) Idt;

typedef struct {
  u16 size;
  Idt *address;
} __attribute__((packed)) IdtDescr;

void idt_init(void);
