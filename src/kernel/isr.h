// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"

// IRQ default constants
#define IRQ_BASE            0x20
#define IRQ0_TIMER          (IRQ_BASE + 0x00)
#define IRQ1_KEYBOARD       (IRQ_BASE + 0x01)
#define IRQ2_CASCADE        (IRQ_BASE + 0x02)
#define IRQ3_SERIAL_PORT2   (IRQ_BASE + 0x03)
#define IRQ4_SERIAL_PORT1   (IRQ_BASE + 0x04)
#define IRQ5_RESERVED       (IRQ_BASE + 0x05)
#define IRQ6_DISKETTE_DRIVE (IRQ_BASE + 0x06)
#define IRQ7_PARALLEL_PORT  (IRQ_BASE + 0x07)
#define IRQ8_CMOS_CLOCK     (IRQ_BASE + 0x08)
#define IRQ9_CGA            (IRQ_BASE + 0x09)
#define IRQ10_RESERVED      (IRQ_BASE + 0x0A)
#define IRQ11_RESERVED      (IRQ_BASE + 0x0B)
#define IRQ12_AUXILIARY     (IRQ_BASE + 0x0C)
#define IRQ13_FPU           (IRQ_BASE + 0x0D)
#define IRQ14_HARD_DISK     (IRQ_BASE + 0x0E)
#define IRQ15_RESERVED      (IRQ_BASE + 0x0F)

#define ISR_SYSCALL         0x80

#define NUM_INTERRUPT_HANDLERS  256

typedef struct {
  u64 ds;
  u64 r15, r14, r13, r12,
      r11, r10, r9, r8,
      rbp, rsp, rdi, rsi,
      rbx, rdx, rcx, rax;             // pushed by "save context"
  u64 int_no, err_code;               // interrupt number and error code
  u64 rip, cs, rflags, user_rsp, ss;  // pushed by the processor automatically
} Registers;

// ISR function prototype
typedef void (*IsrHandler)(Registers *);

/**
 * register given handler to interrupt handlers at given num
 */
void isr_register_interrupt_handler(i32 num, IsrHandler handler);

/**
 * turn off current interrupt
 */
void isr_end_interrupt(i32 num);

/**
 * invoke isr routine and send eoi to pic,
 * being called in isr.asm
 */
asmlinkage void isr_handler(Registers reg);

// defined in isr.asm
extern void exception_0();
extern void exception_1();
extern void exception_2();
extern void exception_3();
extern void exception_4();
extern void exception_5();
extern void exception_6();
extern void exception_7();
extern void exception_8();
extern void exception_9();
extern void exception_10();
extern void exception_11();
extern void exception_12();
extern void exception_13();
extern void exception_14();
extern void exception_15();
extern void exception_16();
extern void exception_17();
extern void exception_18();
extern void exception_19();
extern void exception_20();
extern void exception_21();
extern void exception_22();
extern void exception_23();
extern void exception_24();
extern void exception_25();
extern void exception_26();
extern void exception_27();
extern void exception_28();
extern void exception_29();
extern void exception_30();
extern void exception_31();
extern void exception_128();

// defined in isr.asm
extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();
