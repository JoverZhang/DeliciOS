// SPDX-License-Identifier: GPL-2.0-only

#include "user/shell.h"
#include "arch/console.h"
#include "arch/printf.h"
#include "kernel/system_call.h"
#include "kernel/timer.h"

// load banner of screen
// Be careful. this banner contains multiple "msleep()".
static void load_banner() {
  console_set_foreground_color(CONSOLE_YELLOW);
  printf("\nmoving to user mode");
  for (i32 i = 0; i < 3; i++) {
    printf(".");
    msleep(1000);
  }
  printf("\n");
  console_set_foreground_color(CONSOLE_WHITE);

  printf("========================================");
  printf("========================================\n\n\n\n\n\n");
  console_set_foreground_color(CONSOLE_LIGHT_CYAN);
  printf("                                  Welcome to\n\n\n");
  console_set_foreground_color(CONSOLE_WHITE);
  printf("                             __     ___      _ ____  _____    \n"
         "                        ____/ /__  / (_)____(_) __ \\/ ___/   \n"
         "                       / __  / _ \\/ / / ___/ / / / /\\__ \\  \n"
         "                      / /_/ /  __/ / / /__/ / /_/ /___/ /     \n"
         "                      \\__,_/\\___/_/_/\\___/_/\\____//____/  \n");
  printf("\n\n\n\n\n\n\n\n\n\n");

  for (i32 i = 0; i < 80; i++) {
    printf("#");
    msleep(25);
  }
  console_clear();
}

// mock user program, it's written like the program on Linux.
//
// this is an example of multiprocess program.
// ps: the "fork()" is "system call" of create a child process in kernel.
static noreturn void mock_user_program() {
  if (!fork()) {
    if (!fork()) {
      if (!fork()) {
        while (1) {
          console_set_foreground_color(CONSOLE_LIGHT_GREEN);
          printf("[p4]: print d\n");
          msleep(250);
        }
      }
      while (1) {
        console_set_foreground_color(CONSOLE_LIGHT_GRAY);
        printf("[p3]: print c\n");
        msleep(500);
      }
    }
    while (1) {
      console_set_foreground_color(CONSOLE_LIGHT_BLUE);
      printf("[p2]: print b\n");
      msleep(750);
    }
  }
  while (1) {
    console_set_foreground_color(CONSOLE_LIGHT_RED);
    printf("[p1]: print a\n");
    msleep(1000);
  }
}

// TODO: implement the shell
public void run_shell() {
  load_banner();
  mock_user_program();
}
