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

// Nice levels
// (copy from Linux)
static const i32 sched_prio_to_weight[40] = {
    /* -20 */ 88761,    /* -19 */ 71755,    /* -18 */ 56483,    /* -17 */ 46273,
    /* -16 */ 36291,    /* -15 */ 29154,    /* -14 */ 23254,    /* -13 */ 18705,
    /* -12 */ 14949,    /* -11 */ 11916,    /* -10 */  9548,    /*  -9 */  7620,
    /*  -8 */  6100,    /*  -7 */  4904,    /*  -6 */  3906,    /*  -5 */  3121,
    /*  -4 */  2501,    /*  -3 */  1991,    /*  -2 */  1586,    /*  -1 */  1277,
    /*   0 */  1024,    /*   1 */   820,    /*   2 */   655,    /*   3 */   526,
    /*   4 */   423,    /*   5 */   335,    /*   6 */   272,    /*   7 */   215,
    /*   8 */   172,    /*   9 */   137,    /*  10 */   110,    /*  11 */    87,
    /*  12 */    70,    /*  13 */    56,    /*  14 */    45,    /*  15 */    36,
    /*  16 */    29,    /*  17 */    23,    /*  18 */    18,    /*  19 */    15,
};

void schedule(Registers *reg);

Task *find_empty_process(void);

void wakeup_process(Task *task);

void task_print(Task *t);

void sched_init(void);
