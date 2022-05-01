// SPDX-License-Identifier: GPL-2.0-only

#include "arch/dbg.h"
#include "arch/console.h"
#include "arch/printf.h"

public
void panic(const char *file, i32 line, const char *fun, const char *fmt, ...) {
  va_list args;
  char buf[1024];

  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);

  console_set_color(CONSOLE_YELLOW, CONSOLE_DARK_GRAY);
  printf("\n%s\n"
         " in %s:%d/%s()\n\n"
         " -- System halted",
         buf, file, line, fun);

  asm volatile("cli\n\thlt\n\t");
}
