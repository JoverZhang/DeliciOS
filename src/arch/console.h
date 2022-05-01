// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"

typedef enum {
  CONSOLE_BLACK = 0,
  CONSOLE_BLUE = 1,
  CONSOLE_GREEN = 2,
  CONSOLE_CYAN = 3,
  CONSOLE_RED = 4,
  CONSOLE_MAGENTA = 5,
  CONSOLE_BROWN = 6,
  CONSOLE_LIGHT_GRAY = 7,
  CONSOLE_DARK_GRAY = 8,
  CONSOLE_LIGHT_BLUE = 9,
  CONSOLE_LIGHT_GREEN = 10,
  CONSOLE_LIGHT_CYAN = 11,
  CONSOLE_LIGHT_RED = 12,
  CONSOLE_PINK = 13,
  CONSOLE_YELLOW = 14,
  CONSOLE_WHITE = 15,
} ConsoleColor;

void console_clear(void);
void console_set_color(ConsoleColor foreground, ConsoleColor background);
void console_set_foreground_color(ConsoleColor foreground);

void puts(const char *s);

void console_init();
