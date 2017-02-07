# bordOS : A hobbyist POSIX kernel

## Requirements
- i686-elf-binutils
- i686-elf-gcc
- i686-elf-gdb
- GNU Make 
- xorriso
- mtools
- grub-mkrescue
- nasm

## Building

We use *GNU Make* to build the kernel.
``` bash
make
```
Build the ISO file using the following command
``` bash
make build
```
Run the kernel (using *qemu-system-i386*)
``` bash
make run
```

## Debug
You can debug the kernel using *Qemu* and *GDB*.
The emulator needs to be started in debug mode.
``` bash
make re DEBUG=yes; make build; make debug
```
Then, you can connect to the GDB Server, which was started on the emulator.
``` bash
gdb 

# The following commands need to be typed in gdb's terminal
target remote ip:port # ex: target remote localhost:1234
symbol-file path_to_bin # ex: symbol-file ./build/iso/kernel.bin

# Then you should specify any breakpoints, if needed
c # Since you're on a remote server, you can't "start" the app, you need to continue its execution
```

## Developping

We aim POSIX compatibility, and portability. That being said, you need to restrict machine-independant code.
This kind of code should be located into the /arch/ folder.

Every function declared in /arch/arch.h should be implemented for every available architecture.

## Authors

This project is developped by Antoine Baché and Lucas Troncy. 
