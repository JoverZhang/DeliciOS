// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "arch/boot.h"

void pic_eoi(u8 irq);
u16 pic_get_irr(void);
u16 pic_get_isr(void);
void irq_init(void);
