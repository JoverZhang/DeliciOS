// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/timer.h"
#include "arch/boot.h"
#include "kernel/isr.h"
#include "kernel/system_call.h"
#include "lib/priority_queue.h"
#include "mm/mm.h"

#define TIMER_TICK_RATE             1193182ul
#define TIMER_CHANNEL_0_DATA_PORT   0x40
#define TIMER_CHANNEL_1_DATA_PORT   0x41
#define TIMER_CHANNEL_2_DATA_PORT   0x42
#define TIMER_COMMAND_PORT          0x43

#define NR_TIMER_TASKS 1 << 8

// TimerTask comparator
static i32 timer_task_cmp(TimerTask *a, TimerTask *b);
// timer task queue
PRIORITY_QUEUE(TimerTaskQueue, TimerTask,
               NR_TIMER_TASKS, timer_task_cmp) timer_tasks;

// record times of time interrupts
static volatile u64 jiffies = 0;
// times of time interrupts per second
static u16 frequency = 0;

public void msleep(i32 ms) {
  u32 end = jiffies +  frequency * ms / 1000;

  // TODO(jover): to be fix.
  //  The time interrupt needs to occurs before the pause().
  //  I guess this bug will disappear when "switch_to()" is fixed.
  while (jiffies < end);

  TimerTask *node = (TimerTask *) kmalloc(sizeof(TimerTask));
  BUG_ON(!node);
  node->pri = end;
  node->arg0 = current;
  node->fn = wakeup_process;
  offer(&timer_tasks, node);

  pause();
}

static i32 timer_task_cmp(TimerTask *a, TimerTask *b) {
  if (a->pri < b->pri) return -1;
  else if (a->pri > b->pri) return 1;
  return 0;
}

// timer interrupt service routine
void timer_handler(Registers *reg) {
  jiffies++;

  // handle timer tasks
  TimerTask *task;
  while ((task = peek(&timer_tasks)) && task->pri < jiffies) {
    task = poll(&timer_tasks);
    task->fn(task->arg0);
    kfree(task);
  }

  // do schedule
  schedule(reg);
}

// enable time interrupt of cpu
void timer_set_frequency(u16 f) {
  frequency = f;
  u16 divisor = TIMER_TICK_RATE / f;
  // set Mode 3 - Square Wave Mode
  outb(0b00110110, TIMER_COMMAND_PORT);
  // set low byte
  outb(divisor & 0xFF, TIMER_CHANNEL_0_DATA_PORT);
  // set high byte
  outb((divisor >> 8) & 0xFF, TIMER_CHANNEL_0_DATA_PORT);
}

public void timer_init(void) {
  // The 100 is copy from linux
  timer_set_frequency(100);

  isr_register_interrupt_handler(IRQ0_TIMER, timer_handler);
}
