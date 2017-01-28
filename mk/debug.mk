### ASM ###
ifeq ($(DEBUG), yes)
ASFLAGS+=	-DDEBUG					\
		-g

LDASMFLAGS+=	-g
else
ASFLAGS+=	-DNDEBUG
endif

### C ###
ifeq ($(DEBUG), yes)
CFLAGS+=	-DDEBUG					\
		-g					\
		-Wformat-security			\
		-fstack-protector			\
		-fomit-frame-pointer

LDCFLAGS+=	-g					\
		-rdynamic				\
		-ldl					\
		-lrt

else
CFLAGS+=	-DNDEBUG
endif

### C++ ###
ifeq ($(DEBUG), yes)
CXXFLAGS+=	-DDEBUG					\
		-g					\
		-Wformat-security			\
		-fstack-protector			\
		-fomit-frame-pointer

LDCXXFLAGS+=	-g					\
		-rdynamic				\
		-ldl					\
		-lrt
else
CXXFLAGS+=	-DNDEBUG
endif
