// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/types.h"

typedef u64 Pgd;
typedef u64 Pud;
typedef u64 Pmd;
typedef u64 Pte;

void page_init(void);
