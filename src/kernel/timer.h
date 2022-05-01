// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"
#include "kernel/sched.h"

typedef struct {
  u64 pri;    // expire
  i32 index;  // index
  Task *arg0;
  void (*fn)(Task *);
} TimerTask;

void msleep(i32 ms);
void timer_init(void);
