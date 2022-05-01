// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/sys.h"
#include "kernel/isr.h"
#include "kernel/sched.h"
#include "arch/string.h"

#define TASK_STACK (1 << 20) // 1m

i32 last_pid = 2;

public int sys_fork(Registers *reg) {
  Task *p = find_empty_process();

  *p = *current; // NOTE! this doesn't copy the supervisor stack

  // copy stack
  memcpy((void *) (p->stack),
         (void *) (current->stack - TASK_STACK),
         TASK_STACK);
  p->stack += TASK_STACK;

  p->pid = last_pid++;
  p->counter = p->priority;
  p->state = TASK_RUNNING;
  p->ts.rip = reg->rip;
  p->ts.rax = 0;            // return 0 in child process
  p->ts.rcx = reg->rcx;
  p->ts.rdx = reg->rdx;
  p->ts.rbx = reg->rbx;
  p->ts.rsi = reg->rsi;
  p->ts.rdi = reg->rdi;
  p->ts.rsp = reg->user_rsp + TASK_STACK;
  p->ts.rbp = reg->rbp + TASK_STACK;
  p->ts.r8 = reg->r8;
  p->ts.r9 = reg->r9;
  p->ts.r10 = reg->r10;
  p->ts.r11 = reg->r11;
  p->ts.r12 = reg->r12;
  p->ts.r13 = reg->r13;
  p->ts.r14 = reg->r14;
  p->ts.r15 = reg->r15;

  return p->pid; // return child pid in parent process
}
