// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/kernel.h"
#include "arch/boot.h"
#include "arch/console.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "kernel/keyboard.h"
#include "kernel/sched.h"
#include "kernel/sys.h"
#include "kernel/system_call.h"
#include "kernel/timer.h"
#include "mm/page.h"
#include "mm/mm.h"
#include "user/shell.h"

void init(void) {
  run_shell();
}

/**
 * Enter user mode
 */
#define move_to_user_mode() do {  \
  asm volatile(                   \
    "pushq $0x20\n\t"             \
    "pushq %%rax\n\t"             \
    "pushfq\n\t"                  \
    "pushq $0x18\n\t"             \
    "pushq $1f\n\t"               \
    "iretq\n\t"                   \
    "1:\n\t"                      \
    "movq $0x20, %%rax\n\t"       \
    "movw %%ax, %%ds\n\t"         \
    "movw %%ax, %%es\n\t"         \
    "movw %%ax, %%fs\n\t"         \
    "movw %%ax, %%gs\n\t"         \
    :: "a"(current->ts.rsp)       \
  );                              \
} while (0)

public asmlinkage void __init start_kernel(void) {
  // for kernel debug
  console_init();

  gdt_init();
  page_init();
  idt_init();
  mm_init();

  timer_init();
  sched_init();
  keyboard_init();
  syscall_init();

  sti();

  printk("started kernel\n");

  move_to_user_mode();

  if (!fork()) {
    init();
  }

  while (1) pause();
}
