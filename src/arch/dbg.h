// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"

#define PANIC(fmt...) \
do { panic(__FILE__, __LINE__, __func__, fmt); } while (0)

#define BUG_ON(condition) \
do { if (unlikely(condition)) PANIC("BUG!"); } while (0)

void panic(const char *file, i32 line, const char *fun, const char *fmt, ...);
