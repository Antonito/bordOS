# Definitions
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

VPATH=		$(KERNEL_DIR)

# Sources
ARCH_FILES:=

BOOT_FILES:=	$(addprefix ./boot/,	\
		boot.s			\
		)

DISPLAY_FILES:=

DRIVERS_FILES:=

MEM_FILES:=

FS_FILES:=

SRC:= 		$(ARCH_FILES) $(BOOT_FILES) $(DISPLAY_FILES) $(DRIVERS_FILES) $(MEM_FILES) $(FS_FILES)

# Rules
include $(MK_DIR)rules.mk

build:	$(NAME)
	@$(ISO) $(ISOFLAGS) && $(ECHO) "$(CLEAR)[ $(GREEN)OK$(CLEAR) ] Built\t$(WHITE)$(OS)\n" || "$(CLEAR)[ $(RED)KO$(CLEAR) ] Built\t$(WHITE)$(OS)\n"

run:
	$(EMU) $(OS)

.PHONY:	all clean fclean re run build
