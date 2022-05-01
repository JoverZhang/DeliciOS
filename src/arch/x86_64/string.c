// SPDX-License-Identifier: GPL-2.0-only
/*
 *  Copyright (C) 1991, 1992 Linus Torvalds
 *  Copyright 2007 rPath, Inc. - All Rights Reserved
 */

/*
 * Very basic string functions
 */

#include "arch/string.h"

public void *memset(void *s, char c, size_t n) {
  char *ss = s;
  for (int i = 0; i < n; i++)
    ss[i] = c;
  return s;
}

public void *memcpy(void *dest, const void *src, size_t n) {
  u64 d0, d1, d2;
  asm volatile(
    "rep ; movsq\n\t"
    "movq %4,%%rcx\n\t"
    "rep ; movsb\n\t"
    : "=&c" (d0), "=&D" (d1), "=&S" (d2)
    : "0" (n >> 3), "g" (n & 7), "1" (dest), "2" (src)
    : "memory");

  return dest;
}


public i32 strcmp(const char *str1, const char *str2) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  i32 delta = 0;

  while (*s1 || *s2) {
    delta = *s1 - *s2;
    if (delta)
      return delta;
    s1++;
    s2++;
  }
  return 0;
}

public i32 strncmp(const char *cs, const char *ct, size_t count) {
  unsigned char c1, c2;

  while (count) {
    c1 = *cs++;
    c2 = *ct++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (!c1)
      break;
    count--;
  }
  return 0;
}

public size_t strnlen(const char *s, size_t maxlen) {
  const char *es = s;
  while (*es && maxlen) {
    es++;
    maxlen--;
  }

  return (es - s);
}

public char atou(const char *s) {
  unsigned int i = 0;
  while (isdigit(*s))
    i = i * 10 + (*s++ - '0');
  return i;
}
