### General ###
END_LINE:=	"\n$(CLEAR)"

### Generation ###
OK_GEN:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Generated $(CYAN)"$(NAME)$(END_LINE)
KO_GEN:=	$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Generated $(CYAN)"$(NAME)$(END_LINE)

### Compilation ###
OK_COMP:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Compiled "
KO_COMP:=	$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Compiled "

### Link ###
OK_LINK:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Linked $(CYAN)"$(NAME)$(END_LINE)
KO_LINK:=	$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Linked $(CYAN)"$(NAME)$(END_LINE)

### Clean / fclean ###
RM_OBJ:=	$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed OBJs files [$(MODE)]"$(END_LINE)
RM_BIN:=	$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed $(CYAN)"$(NAME)$(END_LINE)

### Tests / Benchmark ###
NO_TEST:=	$(ECHO) "$(WHITE)No test available."$(END_LINE)
NO_BENCH:=	$(ECHO) "$(WHITE)No benchmark available."$(END_LINE)

## Build ##
OK_BUILD:=	$(ECHO) "$(WHITE)[ $(GREEN)OK$(WHITE) ] Built\t$(CYAN)$(OS)"$(END_LINE)
KO_BUILD:=	$(ECHO) "$(WHITE)[ $(RED)KO$(WHITE) ] Built\t$(CYAN)$(OS)"$(END_LINE)

### Infos messages ###
INFO_SEP:=	"$(WHITE)----------\n"

INFO_ASM:=	"Assembler:\t\t$(AS)\n"	\
		"Flags:\t\t\t$(ASFLAGS)\n"

INFO_C:=	"C Compiler:\t\t$(CC)\n"	\
		"Flags:\t\t\t$(CFLAGS)\n"

INFO_CPP:=	"Cpp Compiler:\t\t$(CXX)\n"	\
		"Flags:\t\t\t$(CXXFLAGS)\n"

INFO_LIB:=	"Static Lib:\t\t$(RANLIB)\n"

INFO_LINK:=	"Linker:\t\t$(LD)\n"		\
		"Flags:\t\t\t$(LDFLAGS)\n"

INFOS:=		$(ECHO) "$(CYAN)" $(INFO_ASM)	\
		$(INFO_SEP)			\
		"$(CYAN)"$(INFO_C)		\
		$(INFO_SEP)			\
		"$(CYAN)"$(INFO_CPP)		\
		$(INFO_SEP)			\
		"$(CYAN)"$(INFO_LIB)		\
		$(INFO_SEP)			\
		"$(CYAN)"$(INFO_LINK)		\
		"$(CLEAR)\n"

### Strip ###
STRIP_OK:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Stripped $(NAME)"$(END_LINE)
STRIP_KO:=	$(ECHO) "$(WHITE)[$(RED)OK$(WHITE)] Stripped $(NAME)"$(END_LINE)
