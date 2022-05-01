// SPDX-License-Identifier: GPL-2.0-only

#include "mm.h"
#include "kernel/intlock.h"

#define MAX_HEAP ((u64) (1 << 20)) // 1MB

// heap start address
static u8 heap_start[MAX_HEAP];
static i64 heap_brk = 0;

// increase or decrease the end of heap space
// and return computed heap address
static void *sbrk(i64 incr) {
  i64 n = heap_brk + incr;
  if (n < 0 || MAX_HEAP <= n) return (void *) -1;
  void *address = &heap_start[heap_brk];
  heap_brk = n;
  return address;
}

// heap block header
// notice: this is linked list
typedef u8 Align_16[16];
typedef union Header {
  struct {
    i64 size;
    u8 is_free;
    union Header *next;
  };
  Align_16 _;
} Header;

// define linked list
static Header *head, *tail;
static IntLock g_malloc_lock;

// get a free block from block list
Header *get_free_block(u64 size) {
  Header *cur = head;
  while (cur) {
    if (cur->is_free && cur->size >= size)
      return cur;
    cur = cur->next;
  }
  return NULL;
}

public void *kmalloc(u64 size) {
  int_lock(&g_malloc_lock);

  Header *header = get_free_block(size);
  if (header) {
    header->is_free = false;
    int_unlock(&g_malloc_lock);
    return (void *) (header + 1);
  }
  // new block
  u64 total_size = sizeof(Header) + size;
  void *block = sbrk((i64) total_size);
  if (block == (void *) -1) {
    int_unlock(&g_malloc_lock);
    return NULL;
  }
  header = block;
  header->size = (i64) size;
  header->is_free = false;
  header->next = NULL;

  if (!head)
    head = header;
  if (tail)
    tail->next = header;
  tail = header;

  int_unlock(&g_malloc_lock);
  return (void *) (header + 1);
}

public void kfree(void *block) {
  if (!block) return;
  Header *header = (Header *) block - 1;
  if ((u8 *) block + header->size == sbrk(0)) {
    if (head == tail) {
      head = tail = NULL;
    } else {
      Header *tmp = head;
      while (tmp) {
        if (tmp->next == tail) {
          tmp->next = NULL;
          tail = tmp;
        }
        tmp = tmp->next;
      }
    }
    sbrk(0 - (i64) sizeof(Header) - header->size);
    int_unlock(&g_malloc_lock);
    return;
  }
  header->is_free = 1;
  int_unlock(&g_malloc_lock);
}

public void mm_init(void) {
  // nothing to do
}
