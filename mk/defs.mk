# Commands definitions
RM:=		rm -f
ECHO:=		echo -ne
RANLIB:=	ar rcs
CP:=		cp
CHDIR:=		cd
IGNORE:=	2> /dev/null ||:
STRIP:=		strip

# Paths
ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR:=	./bin/
INSTALL_PATH:=	$(ROOT_DIR)/$(INSTALL_DIR)

# Compilation and link definitions
LD=		ld
AS=		nasm
CC=		i686-elf-gcc
CXX=		clang++

## Architecture
ASFLAGS:=
CFLAGS:=	-m32					\
		-ffreestanding				\
		-fno-builtin				\
		-fno-stack-protector			\
		-nostartfiles				\
		-nodefaultlibs
CXXFLAGS:=
LDFLAGS:=	-T $(LINK_SCRIPT)			\
		-melf_i386

ELF_FORMAT:=	elf32

###### GENERAL #####
## ASSEMBLY
ASFLAGS:=	-f $(ELF_FORMAT)			\
		$(ASM_LOCAL_COMP_FLAGS)

## C
C_VER:=		gnu99
CFLAGS+=	-W					\
		-Wall					\
		-Wextra					\
		-Wshadow				\
		-Wpointer-arith				\
		-Wfloat-equals				\
		-std=$(C_VER)				\
		$(C_LOCAL_COMP_FLAGS)

## C++
CPP_VER:=	c++14
CXXFLAGS+=	-W					\
		-Wall					\
		-Wextra					\
		-std=$(CPP_VER)				\
		$(CPP_LOCAL_COMP_FLAGS)

###### DEBUG #####
include $(MK_DIR)./debug.mk
