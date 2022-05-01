// SPDX-License-Identifier: GPL-2.0-only

#include "arch/boot.h"

extern void setup_page_tables();
extern void enable_paging();
extern void go_to_long_mode();

void main() {
  setup_page_tables();
  enable_paging();

  // go to long mode (64bit)
  go_to_long_mode();
}
