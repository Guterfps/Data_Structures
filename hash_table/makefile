CC = gcc
CFLAGS = -fPIC -ansi -pedantic-errors -Wall -Wextra
CCFLAGS = -ansi -pedantic-errors -Wall -Wextra
LDFLAGS = -shared 
TARGET = $(shell basename $(CURDIR))
DIRLIB = ../libs/$(MAKECMDGOALS)
DIROBJ = ../obj/$(MAKECMDGOALS)
TARGET_LIB = lib$(TARGET).so
DIRINC = ../include/
DEPLIBS = dlist
LINKFLAGS = $(addprefix -l,$(DEPLIBS))

SRCS = $(TARGET).c 
OBJS = $(SRCS:.c=.o)

define newline


endef

.PHONY: all clean debug release

all: 
	make debug -s
	make release -s

debug: CFLAGS += -g
debug: lib
			
release: CFLAGS += -DNDEBUG -O3
release: lib

lib: $(DIRLIB)/${TARGET_LIB}

test: DIRLIB = ../libs/debug
test: CCFLAGS += -g
test: $(TARGET).out

test_release: DIRLIB = ../libs/release
test_release: CCFLAGS += -DNDEBUG -O3
test_release: $(TARGET).out
		
$(TARGET).out: $(TARGET)_test.o 
		$(CC) $(CCFLAGS) $(TARGET)_test.o -o $(TARGET).out -I$(DIRINC) -L$(DIRLIB) \
		-Wl,-rpath,$(DIRLIB) -l$(TARGET)
		
$(TARGET): $(TARGET).o $(TARGET)_test.o
		$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).o $(TARGET)_test.o
		
$(DIROBJ)/$(TARGET).o: $(TARGET).c $(DIRINC)
		$(CC) $(CFLAGS) -c $(TARGET).c -I$(DIRINC) -o $(DIROBJ)/$(TARGET).o 

$(TARGET)_test.o: $(TARGET)_test.c $(DIRINC)
		$(CC) $(CCFLAGS) -c $(TARGET)_test.c -I$(DIRINC)

$(DIRLIB)/$(TARGET_LIB): $(DIROBJ)/$(OBJS) $(DIRINC)/$(TARGET).h
		$(foreach dir,$(DEPLIBS),@$(MAKE) $(MAKECMDGOALS) -C ../$(dir) $(newline))
		$(CC) $(LDFLAGS) -o $@ $^ -I$(DIRINC) -L$(DIRLIB) \
		-Wl,-rpath,$(DIRLIB) $(LINKFLAGS)


$(SRCS:.c=.d):%.d:%.c
		$(CC) $(CFLAGS) -I$(DIRINC) -MM $< >$@

include $(SRCS:.c=.d)

clean:
		$(RM) ../libs/debug/${TARGET_LIB} ../libs/release/${TARGET_LIB}\
		../obj/debug/${OBJS} $(SRCS:.c=.d) ../obj/release/${OBJS} *.out *.o
		$(foreach dir,$(DEPLIBS),@$(MAKE) $(MAKECMDGOALS) -C ../$(dir) $(newline))

