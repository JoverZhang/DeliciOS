// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "kernel/kernel.h"
#include "kernel/isr.h"

int sys_fork(Registers *reg);
int sys_pause(Registers *reg);

void syscall_init(void);
