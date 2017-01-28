include $(MK_DIR)./objs.mk

NAME_EXTENSION=	$(suffix $(NAME))

# Messages
include $(MK_DIR)./strings.mk

# Rules
$(NAME):	$(OBJ)
		@$(LD) $(OBJ) $(LDFLAGS) -o $(NAME) && $(OK_LINK) || $(KO_LINK)

# Compiles ASM files
$(OBJ_DIR)%_s.o:	%.s
		@$(AS) $(ASFLAGS) -o $@ $< && \
		$(OK_COMP)$<$(END_LINE) || $(KO_COMP)$<$(END_LINE)

# Compiles C files
$(OBJ_DIR)%_c.o:	%.c
		@$(CC) $(CFLAGS) -c -o $@ $< && \
		$(OK_COMP)$<$(END_LINE) || $(KO_COMP)$<$(END_LINE)

# Compiles C++ files
$(OBJ_DIR)%_cpp.o:	%.cpp
		@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
		$(OK_COMP)$<$(END_LINE) || $(KO_COMP)$<$(END_LINE)

all:		$(NAME)

# Prints informations
infos:
		@$(INFOS)

# Removes binary + call clean
fclean:		clean
		@$(RM) $(NAME)
		@$(RM_BIN)

# Removes .o files
clean:
		@$(RM) $(OBJ)
		@$(RM_OBJ)

# Calls fclean and all
re:		fclean all

build:	$(NAME)
	@$(ISO) $(ISOFLAGS) && $(OK_BUILD) || $(KO_BUILD)

run:
	$(EMU) $(OS)

.PHONY: all clean fclean re run build
