// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/kernel.h"
#include "arch/console.h"
#include "arch/printf.h"

public i32 printk(const char *fmt, ...) {
  va_list args;
  char buf[1024];
  int n;

  va_start(args, fmt);
  n = vsprintf(buf, fmt, args);
  va_end(args);

  puts(buf);
  return n;
}
