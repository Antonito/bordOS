# Started on 28-01-2017
# Definitions
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

VPATH=		$(KERNEL_DIR)

# Sources
ARCH_FILES:=	$(addprefix ./arch/x86/,	\
		gdt.s				\
		gdt.c				\
		idt.s				\
		idt.c				\
		isr.s				\
		isr.c				\
		irq.c				\
		irq.s				\
		halt.s				\
		interrupts.s			\
		in.s				\
		out.s				\
		)

BOOT_FILES:=	$(addprefix ./boot/,		\
		boot.s				\
		kmain.c				\
		)

DISPLAY_FILES:= $(addprefix ./display/,		\
		kernel_display.c		\
		)

LIB_FILES:=	$(addprefix ./lib/,		\
		strlen.c			\
		memcmp.c			\
		memcpy.c			\
		memset.c			\
		)

DRIVERS_FILES:=

MEM_FILES:=

FS_FILES:=

SRC:= 		$(ARCH_FILES) $(BOOT_FILES) $(DISPLAY_FILES) $(LIB_FILES) $(DRIVERS_FILES) $(MEM_FILES) $(FS_FILES)

# Rules
include $(MK_DIR)rules.mk

.PHONY:	all clean fclean re run build
