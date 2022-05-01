// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"
#include "kernel/isr.h"

#define NR_TASKS        10

#define TASK_RUNNING    0
#define TASK_STOPPED    4

typedef struct Task {
  i32 pid;
  i32 state;    // -1 unrunnable, 0 runnable, >0 stopped
  i32 counter;
  i32 priority;
// mm
  u64 stack;
// context
  struct {
    u64 r15, r14, r13, r12, r11, r10, r9, r8,
        rdi, rsi, rbx, rdx, rcx, rax;
    u64 rbp, rsp;
    u64 rip;
  } ts;
} Task;

typedef struct {
  Task *task; // pointer to task
  i32 index;  // index of tasks
} TaskNode;

void schedule(Registers *reg);

Task *find_empty_process(void);

void wakeup_process(Task *task);

void task_print(Task *t);

void sched_init(void);
