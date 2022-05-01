// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"

void *memset(void *s, char c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

i32 strcmp(const char *str1, const char *str2);
i32 strncmp(const char *cs, const char *ct, size_t count);
size_t strnlen(const char *s, size_t maxlen);
char atou(const char *s);
