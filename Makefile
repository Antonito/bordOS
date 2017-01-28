# Definitions
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

# Sources
ARCH_FILES:=

BOOT_FILES:=

DISPLAY_FILES:=

DRIVERS_FILES:=

MEM_FILES:=

FS_FILES:=

SRC:= 		$(ARCH_FILES) $(BOOT_FILES) $(DISPLAY_FILES) $(DRIVERS_FILES) $(MEM_FILES) $(FS_FILES)

# Objects
OBJ_DIR=	./obj/

OBJ_C:=		%(SRC:%.c=$(OBJ_DIR)%_c.o)

OBJ_AS:=	%(SRC:%.s=$(OBJ_DIR)%_s.o)

OBJ:=		$(filter %.o, $(OBJ_AS) $(OBJ_C))

# Rules
include $(MK_DIR)rules.mk

build:	$(NAME)
	@$(ISO) $(ISOFLAGS) && $(ECHO) "$(CLEAR)[ $(GREEN)OK$(CLEAR) ] Built\t$(WHITE)$(OS)\n" || "$(CLEAR)[ $(RED)KO$(CLEAR) ] Built\t$(WHITE)$(OS)\n"

run:	build
	$(EMU) $(OS)

.PHONY:	all clean fclean re run build
