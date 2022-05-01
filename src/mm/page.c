// SPDX-License-Identifier: GPL-2.0-only

#include "page.h"

// page global directory
static __page_aligned_data Pgd pgd[512];

extern u8 pa_start[0];
static i64 pa_offset = 0;

static inline void load_cr3(const Pgd *p) {
  asm volatile("movq %0, %%cr3"::"r" (*p));
}

void *obtain_physical_page() {
  void *result = &pa_start[pa_offset];
  pa_offset += PAGE_SIZE;
  return result;
}

public void page_init(void) {
  Pud *pud = (Pud *) obtain_physical_page();
  Pte *pte = (Pte *) obtain_physical_page();

  for (i32 i = 0; i < 512; i++) {
    pte[i] = (Pte) (0x200000 * i) | 0b10000011;
  }

  pgd[0] = (Pgd) pud | 0b11;
  pud[0] = (Pud) pte | 0b11;
  load_cr3(pgd);
}
