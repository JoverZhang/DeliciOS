OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(start)

SECTIONS
{
  .boot 10M : {
    KEEP(*(.multiboot_header))
  }

  .text : {
    *(.text)
    . = ALIGN(4096);
  }

  .rodata : {
    *(.rodata)
    . = ALIGN(4096);
  }

  .data : {
    *(.data)
    . = ALIGN(4096);
  }

  .bss : {
    *(.bss..page_aligned)
    *(.bss)
    . = ALIGN(4096);
  }
}