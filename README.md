# DeliciOS

[[中文]](./README.zh.md)

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

# Building DeliciOS

DeliciOS can be compiled on 64-bit Linux or MacOS.

Run following command to build the `kernel.iso`. 

```shell
make
```

or

```shell
make x86_64.iso
```

When the `kernel.iso` has been built. Use following command to run Qemu.

```shell
qemu-system-x86_64 ./dist/release/x86_64/kernel.iso
```

# Future

I hope it can support earlier versions of Shell and GCC. (like a modern Linux 0.01)

And in the end, We will refactor it. Write all core code in the stupidest (simplest) way.

I hope to help some lost person who loves the operating system (such as me).

# Acknowledgement

- [Linux](https://github.com/torvalds/linux)
- [SynestiaOS](https://github.com/SynestiaOS/SynestiaOS)
- [Simple-XX/SimpleKernel](https://github.com/Simple-XX/SimpleKernel)
- [xinu-os/xinu](https://github.com/xinu-os/xinu)
- [pritamzope/OS](https://github.com/pritamzope/OS)
- To be added...(too much)

# License

DeliciOS is under the GPLv2 License. See the [LICENSE](./LICENSE) file for details.
