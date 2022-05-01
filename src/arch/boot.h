// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"

static inline void outb(u8 v, u16 port) {
  asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline u8 inb(u16 port) {
  u8 v;
  asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
  return v;
}

static inline void outw(u16 v, u16 port) {
  asm volatile("outw %0,%1" : : "a" (v), "dN" (port));
}
static inline u16 inw(u16 port) {
  u16 v;
  asm volatile("inw %1,%0" : "=a" (v) : "dN" (port));
  return v;
}

static inline void outl(u32 v, u16 port) {
  asm volatile("outl %0,%1" : : "a" (v), "dN" (port));
}
static inline u32 inl(u16 port) {
  u32 v;
  asm volatile("inl %1,%0" : "=a" (v) : "dN" (port));
  return v;
}

static inline u64 get_cs(void) {
  u64 v;
  asm volatile("mov %%cs, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_ss(void) {
  u64 v;
  asm volatile("mov %%ss, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_ds(void) {
  u64 v;
  asm volatile("mov %%ds, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_es(void) {
  u64 v;
  asm volatile("mov %%es, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_fs(void) {
  u64 v;
  asm volatile("mov %%fs, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_gs(void) {
  u64 v;
  asm volatile("mov %%gs, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_sp(void) {
  u64 v;
  asm volatile("movq %%rsp, %%rax":"=a" (v):);
  return v;
}
static inline u64 get_bp(void) {
  u64 v;
  asm volatile("movq %%rbp, %%rax":"=a" (v):);
  return v;
}
static inline void set_sp(u64 v) {
  asm volatile("movq %0, %%rsp"::"a"(v));
}
static inline void set_bp(u64 v) {
  asm volatile("movq %0, %%rbp"::"a"(v));
}

static inline void sti(void) {
  asm volatile("sti");
}
