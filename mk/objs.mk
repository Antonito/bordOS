OBJ_DIR:=		./obj/

OBJ_AS:=	$(SRC:%.s=$(OBJ_DIR)%_s.o)
OBJ_C:=		$(SRC:%.c=$(OBJ_DIR)%_c.o)
OBJ_CPP:=	$(SRC:%.cpp=$(OBJ_DIR)%_cpp.o)

OBJ:=		$(filter %.o, $(OBJ_AS) $(OBJ_C) $(OBJ_CPP))

ifneq ($(filter %.cpp, $(SRC)),)
LDFLAGS+=	-lstdc++
endif
