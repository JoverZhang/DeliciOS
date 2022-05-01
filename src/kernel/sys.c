// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/sys.h"
#include "kernel/isr.h"

typedef int (*SysCallHandler)(Registers *);
static SysCallHandler syscall_table[] = {
    [2] = sys_fork,
    [29] = sys_pause,
};

// entrance of system call
void syscall_handler(Registers *reg) {
  reg->rax = syscall_table[reg->rax](reg);
}

public void syscall_init(void) {
  isr_register_interrupt_handler(ISR_SYSCALL, syscall_handler);
}
