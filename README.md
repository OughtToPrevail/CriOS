# CriOS

## What is CriOS?
CriOS is an operating system developed for research and learning
how operating systems are built from scratch.

The project implements the following features:
* GDT
* IDT
* Keyboard Support (with capslock and such)
* Mouse Support
* A basic virtual file system (based on initrd)
* Heap Management with Paging
* Process Management with scheduler
* User mode
* Basic graphics with VGA (this was mostly for fun)
* Additionally, basic utilities had to be implemented such as printf, Vector, Function and such

## Development info
* OS: Linux
* Bootloader: GRUB (Possibly in the future make a custom bootloader?) (comes with Linux)
* IDE: CLion (can be installed via Ubuntu Software app)
* Emulator: qemu (sudo apt-get install qemu-system-i386)
* Languages: C++/Assembly (sudo apt-get install build-essential nasm)
* Debugger: GDB (should come with Linux)

To run the OS, run the emulate section in the makefile
