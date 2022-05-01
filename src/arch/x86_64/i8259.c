// SPDX-License-Identifier: GPL-2.0-only

#include "arch/i8259.h"

#define PIC1          0x0020  /* IO base address for master PIC */
#define PIC2          0x00A0  /* IO base address for slave PIC */
#define PIC1_COMMAND  PIC1
#define PIC1_DATA     (PIC1 + 1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA     (PIC2 + 1)

#define ICW1_INIT     0x10
#define ICW1_ICW4     0x01
#define ICW4_8086     0x01

#define PIC_READ_IRR  0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR  0x0b    /* OCW3 irq service next CMD read */

#define PIC_EOI       0x20    /* End-of-interrupt command code */

public void pic_eoi(u8 irq) {
  if (irq >= 0x28)
    outb(PIC_EOI, PIC2_COMMAND);
  outb(PIC_EOI, PIC1_COMMAND);
}

static inline u16 pic_get_irq_reg(i32 ocw3) {
  /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
   * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
  outb(ocw3, PIC1_COMMAND);
  outb(ocw3, PIC2_COMMAND);
  return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

/* Returns the combined value of the cascaded PICs irq request register */
public u16 pic_get_irr(void) {
  return pic_get_irq_reg(PIC_READ_IRR);
}

/* Returns the combined value of the cascaded PICs in-service register */
public u16 pic_get_isr(void) {
  return pic_get_irq_reg(PIC_READ_ISR);
}

void init_ISA_irqs() {
  // save masks
  u8 a1 = inb(PIC1_DATA);
  u8 a2 = inb(PIC2_DATA);

  // starts the initialization sequence (in cascade mode)
  outb(ICW1_INIT | ICW1_ICW4, PIC1_COMMAND);
  outb(ICW1_INIT | ICW1_ICW4, PIC2_COMMAND);

  outb(0x20, PIC1_DATA); // ICW2: Master PIC vector offset
  outb(0x28, PIC2_DATA); // ICW2: Slave PIC vector offset
  outb(4,
       PIC1_DATA);    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  outb(2,
       PIC2_DATA);    // ICW3: tell Slave PIC its cascade identity (0000 0010)

  outb(ICW4_8086, PIC1_DATA);
  outb(ICW4_8086, PIC2_DATA);
  // restore saved masks.
  outb(a1, PIC1_DATA);
  outb(a2, PIC2_DATA);
}

public void irq_init(void) {
  init_ISA_irqs();
}
