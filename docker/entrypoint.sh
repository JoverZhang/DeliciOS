#/bin/bash

make

qemu-system-x86_64 ./dist/release/x86_64/kernel.iso -nographic -curses

