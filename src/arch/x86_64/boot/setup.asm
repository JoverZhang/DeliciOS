bits 32
section .text

global start
start:
  mov esp, stack_top
  extern setup
  call setup
loop:
  jmp loop


section .bss
stack_bottom:
  ; 1 MB of uninitialized data for stack
  resb  1 << 20
stack_top:
