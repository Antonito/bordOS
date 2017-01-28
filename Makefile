# Definitions
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

VPATH=		$(KERNEL_DIR)

# Sources
ARCH_FILES:=

BOOT_FILES:=	$(addprefix ./boot/,	\
		boot.s			\
		kmain.c			\
		)

DISPLAY_FILES:=

DRIVERS_FILES:=

MEM_FILES:=

FS_FILES:=

SRC:= 		$(ARCH_FILES) $(BOOT_FILES) $(DISPLAY_FILES) $(DRIVERS_FILES) $(MEM_FILES) $(FS_FILES)

# Rules
include $(MK_DIR)rules.mk

.PHONY:	all clean fclean re run build
