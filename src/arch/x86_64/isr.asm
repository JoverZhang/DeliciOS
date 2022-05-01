; SPDX-License-Identifier: GPL-2.0-only

section .text

_isr_handler:
  ; ========== push all registers ==========
  push rax
  push rcx
  push rdx
  push rbx
  push rsi
  push rdi
  push rsp
  push rbp
  push r8
  push r9
  push r10
  push r11
  push r12
  push r13
  push r14
  push r15
  ; ========== push all registers ==========

  mov ax, ds
  push rax                ; save ds

  mov ax, 0x10            ; load kernel data segment
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  extern isr_handler      ; defined in kernel/isr.c
  call isr_handler

  pop rbx                 ; restore kernel data segment
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx

  ; ========== restore all registers ==========
  pop r15
  pop r14
  pop r13
  pop r12
  pop r11
  pop r10
  pop r9
  pop r8
  pop rbp
  pop rsp
  pop rdi
  pop rsi
  pop rbx
  pop rdx
  pop rcx
  pop rax
  ; ========== restore all registers ==========

  add rsp, 16             ; restore stack for erro no been pushed

  sti                     ; re-enable interrupts
  iretq

; arg1: function name
; arg2: interrupt number
%macro ISR_HANDLER 2
global %1
%1:
  cli
  push qword 0
  push qword %2
  jmp _isr_handler
%endmacro

; exceptions
ISR_HANDLER exception_0, 0
ISR_HANDLER exception_1, 1
ISR_HANDLER exception_2, 2
ISR_HANDLER exception_3, 3
ISR_HANDLER exception_4, 4
ISR_HANDLER exception_5, 5
ISR_HANDLER exception_6, 6
ISR_HANDLER exception_7, 7
ISR_HANDLER exception_8, 8
ISR_HANDLER exception_9, 9
ISR_HANDLER exception_10, 10
ISR_HANDLER exception_11, 11
ISR_HANDLER exception_12, 12
ISR_HANDLER exception_13, 13
ISR_HANDLER exception_14, 14
ISR_HANDLER exception_15, 15
ISR_HANDLER exception_16, 16
ISR_HANDLER exception_17, 17
ISR_HANDLER exception_18, 18
ISR_HANDLER exception_19, 19
ISR_HANDLER exception_20, 20
ISR_HANDLER exception_21, 21
ISR_HANDLER exception_22, 22
ISR_HANDLER exception_23, 23
ISR_HANDLER exception_24, 24
ISR_HANDLER exception_25, 25
ISR_HANDLER exception_26, 26
ISR_HANDLER exception_27, 27
ISR_HANDLER exception_28, 28
ISR_HANDLER exception_29, 29
ISR_HANDLER exception_30, 30
ISR_HANDLER exception_31, 31

; interrupt requests
ISR_HANDLER irq_0, 32
ISR_HANDLER irq_1, 33
ISR_HANDLER irq_2, 34
ISR_HANDLER irq_3, 35
ISR_HANDLER irq_4, 36
ISR_HANDLER irq_5, 37
ISR_HANDLER irq_6, 38
ISR_HANDLER irq_7, 39
ISR_HANDLER irq_8, 40
ISR_HANDLER irq_9, 41
ISR_HANDLER irq_10, 42
ISR_HANDLER irq_11, 43
ISR_HANDLER irq_12, 44
ISR_HANDLER irq_13, 45
ISR_HANDLER irq_14, 46
ISR_HANDLER irq_15, 47

; soft interrupts
ISR_HANDLER exception_128, 0x80
