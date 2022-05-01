// SPDX-License-Identifier: GPL-2.0-only

#include "arch/idt.h"
#include "kernel/keyboard.h"
#include "arch/i8259.h"

#define IDT_TABLE_SIZE (IDT_ENTRIES * sizeof(Idt)) - 1

static Idt idt[IDT_ENTRIES];
static IdtDescr idt_ptr = {
    .size = IDT_TABLE_SIZE,
    .address = idt,
};

static inline void load_idt(const IdtDescr *p) {
  asm volatile("lidt %0"::"m" (*p));
}

void idt_set_entry(u8 idx, IsrHandler isr_handler, u16 seg, u8 flags) {
  Idt *entry = &idt[idx];
  u64 base = (u64) isr_handler;
  entry->offset_low = base & 0xffff;
  entry->segment = seg;
  entry->bits.ist = 0;
  entry->bits.zero = 0;
  entry->bits.type = 0xe;
  entry->bits.dpl = 0;
  entry->bits.p = 1;
  entry->offset_middle = (base & 0xffff0000) >> 16;
  entry->offset_high = (base & 0xffffffff00000000) >> 32;
  entry->zero = 0;
}

public void idt_init(void) {
  irq_init();

  // exceptions
  idt_set_entry(0, exception_0, 0x08, 0x8E);
  idt_set_entry(1, exception_1, 0x08, 0x8E);
  idt_set_entry(2, exception_2, 0x08, 0x8E);
  idt_set_entry(3, exception_3, 0x08, 0x8E);
  idt_set_entry(4, exception_4, 0x08, 0x8E);
  idt_set_entry(5, exception_5, 0x08, 0x8E);
  idt_set_entry(6, exception_6, 0x08, 0x8E);
  idt_set_entry(7, exception_7, 0x08, 0x8E);
  idt_set_entry(8, exception_8, 0x08, 0x8E);
  idt_set_entry(9, exception_9, 0x08, 0x8E);
  idt_set_entry(10, exception_10, 0x08, 0x8E);
  idt_set_entry(11, exception_11, 0x08, 0x8E);
  idt_set_entry(12, exception_12, 0x08, 0x8E);
  idt_set_entry(13, exception_13, 0x08, 0x8E);
  idt_set_entry(14, exception_14, 0x08, 0x8E);
  idt_set_entry(15, exception_15, 0x08, 0x8E);
  idt_set_entry(16, exception_16, 0x08, 0x8E);
  idt_set_entry(17, exception_17, 0x08, 0x8E);
  idt_set_entry(18, exception_18, 0x08, 0x8E);
  idt_set_entry(19, exception_19, 0x08, 0x8E);
  idt_set_entry(20, exception_20, 0x08, 0x8E);
  idt_set_entry(21, exception_21, 0x08, 0x8E);
  idt_set_entry(22, exception_22, 0x08, 0x8E);
  idt_set_entry(23, exception_23, 0x08, 0x8E);
  idt_set_entry(24, exception_24, 0x08, 0x8E);
  idt_set_entry(25, exception_25, 0x08, 0x8E);
  idt_set_entry(26, exception_26, 0x08, 0x8E);
  idt_set_entry(27, exception_27, 0x08, 0x8E);
  idt_set_entry(28, exception_28, 0x08, 0x8E);
  idt_set_entry(29, exception_29, 0x08, 0x8E);
  idt_set_entry(30, exception_30, 0x08, 0x8E);
  idt_set_entry(31, exception_31, 0x08, 0x8E);

  idt_set_entry(IRQ0_TIMER, irq_0, 0x8, 0);
  idt_set_entry(IRQ1_KEYBOARD, irq_1, 0x8, 0);

  idt_set_entry(ISR_SYSCALL, exception_128, 0x8, 0);

  load_idt(&idt_ptr);
}
