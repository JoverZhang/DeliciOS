// SPDX-License-Identifier: GPL-2.0-only

#include "kernel/keyboard.h"
#include "arch/boot.h"
#include "kernel/isr.h"
#include "kernel/kernel.h"

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_STATUS_PORT    0x64

/*
 * released key
 *
 * scan codes in alphabetical order for QWERTY keyboard
 * see https://wiki.osdev.org/PS/2_Keyboard
 */
typedef enum {
  KEY_R_LEFT_SHIFT = 0xAA,
  KEY_R_RIGHT_SHIFT = 0xB6,
} KeyReleased;

const static char KEYBOARD_MAP[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,  /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    '`', 0,  /* Left shift */
    '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* Right shift */
    '*', 0, /* Alt */
    ' ', /* Space bar */
    0, /* Caps lock */
    /* F1 key ...> */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* <... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

static inline bool is_upper(char c) {
  return c >= 'A' && c <= 'Z';
}

static inline bool is_lower(char c) {
  return c >= 'a' && c <= 'z';
}

static inline char upper(char c) {
  if (is_lower(c))
    return (char) (c - 32);
  return c;
}

static inline char lower(char c) {
  if (is_upper(c))
    return (char) (c + 32);
  return c;
}

static inline bool is_alpha(char c) {
  return is_upper(c) || is_lower(c);
}

static inline char alternate_char(char c) {
  switch (c) {
    case '`': return '~';
    case '1': return '!';
    case '2': return '@';
    case '3': return '#';
    case '4': return '$';
    case '5': return '%';
    case '6': return '^';
    case '7': return '&';
    case '8': return '*';
    case '9': return '(';
    case '0': return ')';
    case '-': return '_';
    case '=': return '+';
    case '[': return '{';
    case ']': return '}';
    case '\\': return '|';
    case ';': return ':';
    case '\'': return '\"';
    case ',': return '<';
    case '.': return '>';
    case '/': return '?';
    default: return c;
  }
}

static u8 g_key;
static char g_char = 0;
static bool g_caps_lock = false;
static bool g_shift = false;

void console_output() {
  printk("%c", g_char);
}

// keyboard interrupt service routine
void keyboard_handler(Registers *reg) {
  if (~inb(KEYBOARD_STATUS_PORT) & 1)
    return;

  if ((g_key = inb(KEYBOARD_DATA_PORT)) < 0) return;

  // key released
  if (g_key & 0x80) {
    if (g_key == KEY_R_LEFT_SHIFT || g_key == KEY_R_RIGHT_SHIFT) {
      g_shift = false;
    }
    return;
  }
  // key pressed
  if (g_key == KEY_CAPS_LOCK) {
    g_caps_lock = !g_caps_lock;
    return;
  } else if (g_key == KEY_LEFT_SHIFT || g_key == KEY_RIGHT_SHIFT) {
    g_shift = true;
    return;
  } else if (g_key == KEY_ENTER) {
    g_char = '\n';
  } else if (g_key == KEY_TAB) {
    g_char = '\t';
  } else {
    g_char = KEYBOARD_MAP[g_key];
    // when caps in on
    if (g_caps_lock) {
      // if shift is pressed before
      if (g_shift) {
        if (!is_alpha(g_char)) {
          g_char = alternate_char(g_char);
        }
      } else {
        g_char = upper(g_char);
      }
    } else {
      // if shift is pressed before
      if (g_shift) {
        if (is_alpha(g_char)) {
          g_char = upper(g_char);
        } else {
          g_char = alternate_char(g_char);
        }
      }
    }
  }

  // TODO: async in daemon process
  console_output();
}

public void keyboard_init(void) {
  isr_register_interrupt_handler(IRQ1_KEYBOARD, keyboard_handler);
}
