CC = gcc
CFLAGS = -fPIC -ansi -pedantic-errors -Wall -Wextra
CCFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -shared 
TARGET = $(shell basename $(CURDIR))
DIRLIB = $(shell dirname $(shell dirname $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))))/ds/libs/$(MAKECMDGOALS)
DIROBJ = $(shell dirname $(shell dirname $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))))/ds/obj/$(MAKECMDGOALS)
TARGET_LIB = lib$(TARGET).so
DIRINC = $(shell dirname $(shell dirname $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))))/ds/include/
DEPLIBS = uid
LINKFLAGS = $(addprefix -l,$(DEPLIBS))

SRCS = $(TARGET).c 
OBJS = $(SRCS:.c=.o)

define newline


endef

.PHONY: all clean debug release

all: 
	make debug
	make release

debug: CFLAGS += -g
debug: lib
			
release: CFLAGS += -DNDEBUG -O3
release: lib

lib: ${TARGET_LIB}

test: DIRLIB = ../libs/debug
test: $(TARGET).out
		./$(TARGET).out
		
$(TARGET).out: $(TARGET)_test.o 
		$(CC) $(CCFLAGS) $(TARGET)_test.o -o $(TARGET).out -I$(DIRINC) -L$(DIRLIB) \
		-Wl,-rpath,$(DIRLIB) -l$(TARGET) -luid
		
$(TARGET): $(TARGET).o $(TARGET)_test.o
		$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).o $(TARGET)_test.o
		
$(TARGET).o: $(TARGET).c $(DIRINC)
		$(CC) $(CFLAGS) -c $(TARGET).c -I$(DIRINC) -o $(DIROBJ)/$(TARGET).o 

$(TARGET)_test.o: $(TARGET)_test.c $(DIRINC)
		$(CC) $(CFLAGS) -c $(TARGET)_test.c -I$(DIRINC)

$(TARGET_LIB): $(OBJS)
		$(foreach dir,$(DEPLIBS),@$(MAKE) $(MAKECMDGOALS) -C ../$(dir) $(newline))
		$(CC) $(LDFLAGS) -o $(DIRLIB)/$@ $(DIROBJ)/$^ -I$(DIRINC) -L$(DIRLIB) \
		-Wl,-rpath,$(DIRLIB) $(LINKFLAGS)

$(SRCS:.c=.d):%.d:%.c
		$(CC) $(CFLAGS) -I$(DIRINC) -MM $< >$@

include $(SRCS:.c=.d)


clean:
		$(RM) ../libs/debug/${TARGET_LIB} ../libs/release/${TARGET_LIB}\
		../obj/debug/${OBJS} $(SRCS:.c=.d) ../obj/release/${OBJS} *.out *.o
		$(foreach dir,$(DEPLIBS),@$(MAKE) $(MAKECMDGOALS) -C ../$(dir) $(newline))

