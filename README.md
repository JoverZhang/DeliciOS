# DeliciOS

DeliciOS (homonym "delicious") is a simple 64-bit Operating System kernel written by C11.

Its Bootloader uses GRUB, and it already has some basic kernel features:

- Process Management
- Memory Management
- System call (soft interrupt)
- Keyboard input
- Text output (console)

Following the principle of "just for fun", I think it also needs the following features:

- SMP
- File System (maybe VFS)
- Socket (TCP)

# Future

I hope it can support earlier versions of Shell and GCC. (like a modern Linux 0.01)

And in the end, We will refactor it. Write all core code in the stupidest (simplest) way.

I hope to help some lost person who loves the operating system (such as me).

# License

DeliciOS is under the GPLv2 License. See the [LICENSE](./LICENSE) file for details.
