# SPDX-License-Identifier: GPL-2.0-only
ARCH	= arch/x86_64

AS	 	= nasm 					# TODO: change to gas
CC 		= x86_64-pc-linux-gnu-gcc
LD 		= x86_64-elf-ld
GRUB 	= grub-mkrescue

SRC 		= ./src
OUT 		= ./dist
CONFIG		= ./config
ISO_DIR		= $(OUT)/release/x86_64/iso
TARGET		= $(OUT)/release/x86_64/kernel
TARGET_ISO 	= $(TARGET).iso

AS_FLAGS	= -f elf64
CC_FLAGS 	= -Wall -ffreestanding -fwhole-program -m64 -std=c11 -O0
LD_FLAGS	= -n -m elf_x86_64 -T $(CONFIG)/x86_64/linker.ld -nostdlib


# config target objects
ARCH_ASM_OBJ	:= $(patsubst $(SRC)/$(ARCH)/%.asm, $(OUT)/$(ARCH)/%.o, $(shell find $(SRC)/$(ARCH) -name *.asm))
ARCH_C_OBJ		:= $(patsubst $(SRC)/$(ARCH)/%.c, $(OUT)/$(ARCH)/%.o, $(shell find $(SRC)/$(ARCH) -name *.c))
ARCH_OBJ		:= $(ARCH_ASM_OBJ) $(ARCH_C_OBJ)

KERNEL_OBJ		:= $(patsubst $(SRC)/kernel/%.c, $(OUT)/kernel/%.o, $(shell find $(SRC)/kernel -name *.c))
LIB_OBJ			:= $(patsubst $(SRC)/lib/%.c, $(OUT)/lib/%.o, $(shell find $(SRC)/lib -name *.c))
MM_OBJ			:= $(patsubst $(SRC)/mm/%.c, $(OUT)/mm/%.o, $(shell find $(SRC)/mm -name *.c))
USER_OBJ		:= $(patsubst $(SRC)/user/%.c, $(OUT)/user/%.o, $(shell find $(SRC)/user -name *.c))

OBJS = $(ARCH_OBJ) $(KERNEL_OBJ) $(LIB_OBJ) $(MM_OBJ) $(USER_OBJ)


# arch
$(ARCH_ASM_OBJ) : $(OUT)/$(ARCH)/%.o : $(SRC)/$(ARCH)/%.asm
	mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) $^ -o $@
$(ARCH_C_OBJ) : $(OUT)/$(ARCH)/%.o : $(SRC)/$(ARCH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -I $(SRC) $^ -o $@

# kernel
$(KERNEL_OBJ) : $(OUT)/kernel/%.o : $(SRC)/kernel/%.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -I $(SRC) $^ -o $@

# lib
$(LIB_OBJ) : $(OUT)/lib/%.o : $(SRC)/lib/%.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -I src $^ -o $@

# mm
$(MM_OBJ) : $(OUT)/mm/%.o : $(SRC)/mm/%.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -I src $^ -o $@

# user
$(USER_OBJ) : $(OUT)/user/%.o : $(SRC)/user/%.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -I src $^ -o $@



.DEFAULT_GOAL := x86_64.iso
.PHONY: x86_64 x86_64.iso run clean

x86_64: $(OBJS)
	mkdir -p $(dir $(TARGET))
	$(LD) $(LD_FLAGS) -o $(TARGET) $^
	grub-file --is-x86-multiboot2 $(TARGET)

x86_64.iso: x86_64
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(CONFIG)/x86_64/grub.cfg $(ISO_DIR)/boot/grub/
	mv $(TARGET) $(ISO_DIR)/boot/
	$(GRUB) -o $(TARGET_ISO) $(ISO_DIR)
	sync

run: clean x86_64.iso
	qemu-system-x86_64 ./dist/release/x86_64/kernel.iso

clean:
	-rm -r $(OUT)
