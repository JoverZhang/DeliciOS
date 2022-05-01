// SPDX-License-Identifier: GPL-2.0-only

#include "arch/gdt.h"

#define GDT_TABLE_SIZE (GDT_ENTRIES * sizeof(Gdt)) - 1

static Gdt gdt[GDT_ENTRIES];
static GdtDescr gdt_ptr = {
    .size = GDT_TABLE_SIZE,
    .address = gdt,
};

static inline void load_gdt(const GdtDescr *p) {
  asm volatile("lgdt %0"::"m" (*p));
}

public void gdt_init(void) {
  // kernel cs
  gdt[1] = (Gdt) {
      .base2 = 0,
      // flags
      .g = 1, .l = 1, .p = 1, .dpl = 0,
      .limit1 = 0xF,
      // access byte
      .s = 1, .e = 1, .rw = 1,
      .base1 = 0,
      .base0 = 0, .limit0 = 0xFFFF
  };
  // kernel ds
  gdt[2] = (Gdt) {
      .base2 = 0,
      // flags
      .g = 1, .l = 1, .p = 1, .dpl = 0,
      .limit1 = 0xF,
      // access byte
      .s = 1, .rw = 1,
      .base1 = 0,
      .base0 = 0, .limit0 = 0xFFFF
  };
  // user cs
  gdt[3] = (Gdt) {
      .base2 = 0,
      // flags
      .g = 1, .l = 1, .p = 1, .dpl = 0, // TODO: update it to 3, and fix those problems.
      .limit1 = 0xF,
      // access byte
      .s = 1, .e = 1, .rw = 1,
      .base1 = 0,
      .base0 = 0, .limit0 = 0xFFFF
  };
  // user ds
  gdt[4] = (Gdt) {
      .base2 = 0,
      // flags
      .g = 1, .l = 1, .p = 1, .dpl = 0, // TODO: update it to 3, and fix those problems.
      .limit1 = 0xF,
      // access byte
      .s = 1, .rw = 1,
      .base1 = 0,
      .base0 = 0, .limit0 = 0xFFFF
  };

  load_gdt(&gdt_ptr);
}
