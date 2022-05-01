// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"
#include "arch/dbg.h"

struct Task;

struct Task *get_current();

#define current get_current()

i32 printk(const char *fmt, ...);
