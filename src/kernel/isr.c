// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/isr.h"
#include "arch/i8259.h"
#include "arch/traps.h"
#include "kernel/kernel.h"

// For both exceptions and irq interrupt
IsrHandler interrupt_handlers[NUM_INTERRUPT_HANDLERS];

/**
 * print given registers
 */
static inline void registers_print(Registers *reg) {
  printk("===REGISTERS===\n");
  printk("int_no 0x%08x, err_code: 0x%08x\n", reg->int_no, reg->err_code);
  printk("ds: 0x%08x\n", reg->ds);
  printk("rdi: 0x%08x, rsi: 0x%08x, rbp: 0x%08x, rsp: 0x%08x\n",
         reg->rdi, reg->rsi, reg->rbp, reg->rsp);
  printk("rbx: 0x%08x, rdx: 0x%08x, rcx: 0x%08x, rax: 0x%08x\n",
         reg->rbx, reg->rdx, reg->rcx, reg->rax);
  printk("=AUTO=:\n");
  printk("rip: 0x%08x, cs: 0x%08x\n", reg->rip, reg->cs);
  printk("rflags: 0x%08x\n", reg->rflags);
  printk("rsp: 0x%08x, ss: 0x%08x\n", reg->user_rsp, reg->ss);
  printk("===============\n");
}

/**
 * register given handler to interrupt handlers at given num
 */
public void isr_register_interrupt_handler(i32 num, IsrHandler handler) {
  printk("IRQ %d registered\n", num);
  if (num < NUM_INTERRUPT_HANDLERS)
    interrupt_handlers[num] = handler;
}

/**
 * turn off current interrupt
 */
public void isr_end_interrupt(i32 num) {
  pic_eoi(num);
}

/**
 * invoke isr routine and send eoi to pic,
 * being called in isr.asm
 */
public asmlinkage void isr_handler(Registers reg) {
  // exceptions
  if (reg.int_no < IRQ_BASE) {
    PANIC("exception: %s", exception_messages[reg.int_no]);
  }
  // interrupt quests
  interrupt_handlers[reg.int_no](&reg);
  isr_end_interrupt((i32) reg.int_no);
}
