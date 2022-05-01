/* SPDX-License-Identifier: GPL-2.0-only */

OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(start)

SECTIONS
{
  .boot 10M : {
    KEEP(*(.multiboot_header))
  }

  . = ALIGN(4096);
  .text : {
    *(.text)
  }

  . = ALIGN(4096);
  .init.text : {
    *(.init.text)
  }

  . = ALIGN(4096);
  .rodata : {
    *(.rodata)
  }

  . = ALIGN(4096);
  .data : {
    *(.data..page_aligned)
    *(.data)
  }

  . = ALIGN(4096);
  .bss : {
    *(.bss..page_aligned)
    *(.bss)
  }

  . = ALIGN(4096);
  .physical : {
    *(.physical)
  }
}
