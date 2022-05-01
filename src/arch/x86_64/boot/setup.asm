; SPDX-License-Identifier: GPL-2.0-only

section .text
bits 32

; entrypoint of multiboot
global start
start:
  ; check machine environment
  call check_multiboot
  call check_cpuid
  call check_long_mode

  ; load gdt for enable long mode
  lgdt [gdt_descr_address]

  ; jmp to C code
  extern main
  mov esp, stack_top  ; init stack for C language
  jmp main            ; main32.c
  hlt

global go_to_long_mode
go_to_long_mode:
  extern long_mode_entry
  jmp 0x08:long_mode_entry

check_multiboot:
  cmp eax, 0x36d76289
  jne .no_multiboot
  ret

.no_multiboot:
  mov al, "M"
  jmp error

check_cpuid:
  pushfd
  pop eax
  mov ecx, eax
  xor eax, 1 << 21
  push eax
  popfd
  pushfd
  pop eax
  push ecx
  popfd
  cmp eax, ecx
  je .no_cpuid
  ret

.no_cpuid:
  mov al, "C"
  jne error

check_long_mode:
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000001
  jb .no_long_mode

  mov eax, 0x80000001
  cpuid
  test edx, 1 << 29
  jz .no_long_mode

  ret

.no_long_mode:
  mov al, "L"
  jmp error
  hlt

global setup_page_tables
setup_page_tables:
  mov eax, page_table_l3
  or eax, 0b11 ; present, writable
  mov [page_table_l4], eax

  mov eax, page_table_l2
  or eax, 0b11 ; present, writable
  mov [page_table_l3], eax

  mov ecx, 0 ; counter
.loop:
  mov eax, 0x200000 ; 2MiB
  mul ecx
  or eax, 0b10000011 ; present, writable, huge page
  mov [page_table_l2 + ecx * 8], eax

  inc ecx ; increment count
  cmp ecx, 512 ; checks if the whole table is mapped
  jne .loop
  ret

global enable_paging
enable_paging:
  ; pass page table location to cpu
  mov eax, page_table_l4
  mov cr3, eax

  ; enable PAE
  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  ; enable long mode
  mov ecx, 0xc0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  ; enable paging
  mov eax, cr0
  or eax, 1 << 31
  mov cr0, eax

  ret

; debug
error:
  mov dword [0xb8000], 0x4f524f45
  mov dword [0xb8004], 0x4f3a4f52
  mov dword [0xb8008], 0x4f204f20
  mov byte [0xb800a], al
  hlt


section .bss
align 4096
; page tables
page_table_l4:
  resb 4096
page_table_l3:
  resb 4096
page_table_l2:
  resb 4096


; initial stack
section .bss
  align 4
stack_bottom:
  ; 1 MB of uninitialized data for stack
  resb  1 << 20
stack_top:


; Flags
G     EQU 1       << 55 ; page 4k
L     EQU 1       << 53 ; long mode
; Access byte
P     EQU 1       << 47 ; present
S     EQU 1       << 44 ; no tss
E     EQU 1       << 43 ; executable
RW    EQU 1       << 41
BASE  EQU 0x00    << 16
LIMIT EQU 0xFFFF  << 0

; global gdt_descr
section .text
gdt_descr:
  dq 0 ; zero entry
  dq G | L | P | S | E | RW | BASE | LIMIT ; code segment ; 0x08 kernel code
  dq G | L | P | S |     RW | BASE | LIMIT ; code segment ; 0x10 kernel data
gdt_descr_address:
  dw $ - gdt_descr - 1
  dq gdt_descr
