// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "../arch/types.h"

// Priority queue implemented using heap.
// this macro is usage similar the c++ template.
//
// CLASS: custom queue name
// T    : node type
// SIZE : max size of queue
// CMP  : comparator
#define CREATE_PRIORITY_QUEUE(CLASS, T, SIZE, CMP)              \
typedef struct {                                                \
  i32 size;                                                     \
  T *queue[SIZE];                                               \
} CLASS;                                                        \
                                                                \
static void sift_up(CLASS *q, i32 k, T *x) {                    \
  while (k > 0) {                                               \
    i32 parent_i = (k - 1) >> 1;                                \
    T *parent = q->queue[parent_i];                             \
                                                                \
    if (CMP(x, parent) >= 0) {                                  \
      break;                                                    \
    }                                                           \
                                                                \
    q->queue[k] = parent;                                       \
    parent->index = k;                                          \
                                                                \
    k = parent_i;                                               \
  }                                                             \
  q->queue[k] = x;                                              \
  x->index = k;                                                 \
}                                                               \
                                                                \
static void sift_down(CLASS *q, i32 k, T *x) {                  \
  i32 half = q->size >> 1;                                      \
  while (k < half) {                                            \
    i32 child_i = (k << 1) + 1;                                 \
    T *child = q->queue[child_i];                               \
                                                                \
    i32 r = child_i + 1;                                        \
    if (r < q->size &&                                          \
        CMP(child, q->queue[r]) > 0) {                          \
      child = q->queue[child_i = r];                            \
    }                                                           \
    if (CMP(x, child) <= 0)                                     \
      break;                                                    \
                                                                \
    q->queue[k] = child;                                        \
    child->index = k;                                           \
    k = child_i;                                                \
  }                                                             \
  q->queue[k] = x;                                              \
  x->index = k;                                                 \
}                                                               \
                                                                \
static bool offer(CLASS *q, T *x) {                             \
  if (q->size >= SIZE) return false;                            \
  sift_up(q, q->size++, x);                                     \
  return true;                                                  \
}                                                               \
                                                                \
static T *poll(CLASS *q) {                                      \
  if (q->size == 0) return NULL;                                \
                                                                \
  T *result = q->queue[0];                                      \
  result->index = -1;                                           \
                                                                \
  i32 size = --q->size;                                         \
  T *last = q->queue[size];                                     \
  q->queue[size] = NULL;                                        \
                                                                \
  if (size != 0)                                                \
    sift_down(q, 0, last);                                      \
  return result;                                                \
}                                                               \
                                                                \
static T *remove_at(CLASS *q, i32 i) {                          \
  i32 s = --q->size;                                            \
  if (s == i) {                                                 \
    q->queue[i] = NULL;                                         \
    return NULL;                                                \
  }                                                             \
                                                                \
  T *moved = q->queue[s];                                       \
  q->queue[s] = NULL;                                           \
  sift_down(q, i, moved);                                       \
  if (q->queue[i] == moved) {                                   \
    sift_up(q, i, moved);                                       \
    if (q->queue[i] != moved)                                   \
      return moved;                                             \
  }                                                             \
  return NULL;                                                  \
}                                                               \
                                                                \
static T *peek(CLASS *q) {                                      \
  return (q->size == 0) ? NULL : q->queue[0];                   \
}

#define PRIORITY_QUEUE(CLASS, T, SIZE, CMP)   \
  CREATE_PRIORITY_QUEUE(CLASS, T, SIZE, CMP)  \
  CLASS
