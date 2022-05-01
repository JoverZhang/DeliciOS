; SPDX-License-Identifier: GPL-2.0-only

section .text
bits 64

global long_mode_entry
long_mode_entry:
  mov ax, 0x10
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  extern start_kernel
  call start_kernel
  hlt

section .physical
  align 4096
global pa_start
pa_start:
