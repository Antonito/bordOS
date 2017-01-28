# BordOS specific definitions
EMU=			qemu-system-i386
ISO=			grub-mkrescue

BUILD_DIR=		./build/
KERNEL_DIR=		./kernel/
OS=			$(BUILD_DIR)/bordOS.iso
LOG_DIR=		$(BUILD_DIR)/logs/
ISO_DIR=		$(BUILD_DIR)/iso/
ISO_BOOT_DIR=		$(ISO_DIR)boot/
BOCHSCONF=		$(BUILD_DIR)/bochsrc.conf
SERIAL_LOG=		$(LOG_DIR)/serial
GRUB_MENU=		$(ISO_BOOT_DIR)/grub/grub.cfg
STAGE2=			$(ISO_BOOT_DIR)/grb/stage2_eltorito
LINK_SCRIPT=		$(KERNEL_DIR)/link.ld

# Start virtual machine with 512MB of RAM
EMUFLAGS=		$(OS) -m 512M
EMUFLAGSDBG=		-s -S

ISOFLAGS=		--output=$(OS) $(ISO_DIR)

# Usual Definitions for Makefile
NAME=			$(ISO_DIR)kernel.elf
MODE=			kernel
DEBUG=			no

## ASM ##
ASM_LOCAL_COMP_FLAGS=

## C ###
C_LOCAL_COMP_FLAGS=	-I$(KERNEL_DIR)		\
			-I/usr/include/

### C++ ###
CPP_LOCAL_COMP_FLAGS=
