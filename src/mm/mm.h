// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"
#include "arch/dbg.h"

// kernel malloc
void *kmalloc(u64 size);
// kernel free
void kfree(void *block);

void mm_init(void);
