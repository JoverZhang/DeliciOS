// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include <stdarg.h>

int printf(const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
