// SPDX-License-Identifier: GPL-2.0-only

#include "arch/console.h"
#include "arch/boot.h"

#define VGA_REGISTER_CRT_ADDR 0x3d4
#define VGA_REGISTER_CRT_DATA 0x3d5

const static i32 MAX_COLS = 80;
const static i32 MAX_ROWS = 25;

typedef struct {
  char c;   // output character
  u8 color; // output color
} Char;

Char *buf = (Char *) 0xb8000;
i32 g_col = 0;
i32 g_row = 0;
char color = CONSOLE_BLACK << 4 | CONSOLE_WHITE;

public void update_cursor() {
  u16 cursor = g_row * MAX_COLS + g_col;
  outb(0x0e, VGA_REGISTER_CRT_ADDR);
  outb(cursor >> 8, VGA_REGISTER_CRT_DATA);
  outb(0x0f, VGA_REGISTER_CRT_ADDR);
  outb(cursor, VGA_REGISTER_CRT_DATA);
}

void clear_row(i32 row) {
  Char empty = (Char) {.c =  ' ', .color =  color};

  for (i32 col = 0; col < MAX_COLS; col++) {
    buf[col + MAX_COLS * row] = empty;
  }
}

void print_newline(void) {
  g_col = 0;
  if (g_row < MAX_ROWS - 1) {
    g_row++;
    return;
  }
  for (i32 row = 0; row < MAX_ROWS; row++) {
    for (i32 col = 0; col < MAX_COLS; col++) {
      buf[col + MAX_COLS * (row - 1)] = buf[col + MAX_COLS * row];
    }
  }
  clear_row(MAX_ROWS - 1);
}

public void console_clear(void) {
  for (i32 i = 0; i < MAX_ROWS; i++) {
    clear_row(i);
  }
  g_col = 0;
  g_row = 0;
}

void putchar(char c) {
  if (c == '\n') {
    print_newline();
    update_cursor();
    return;
  }

  if (g_col > MAX_COLS) {
    print_newline();
  }

  buf[g_col + MAX_COLS * g_row] = (Char) {.c = c, .color = color};
  g_col++;
  update_cursor();
}

public void puts(const char *str) {
  while (*str != '\0') {
    putchar(*str++);
  }
}

public void console_set_color(ConsoleColor foreground,
                              ConsoleColor background) {
  color = (char) ((background << 4) | foreground);
}

public void console_set_foreground_color(ConsoleColor foreground) {
  console_set_color(foreground, color & 0xf0);
}

public void console_init() {
  // enable cursor
  outb(0x0a, VGA_REGISTER_CRT_ADDR);
  u8 temp = inb(VGA_REGISTER_CRT_DATA);
  temp &= ~(1 << 5); // Clear cursor disable bit
  outb(temp, VGA_REGISTER_CRT_DATA);

  console_clear();
  console_set_color(CONSOLE_WHITE, CONSOLE_BLACK);
}
