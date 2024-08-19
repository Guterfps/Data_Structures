CC = gcc
CFLAGS = -fPIC -ansi -pedantic-errors -Wall -Wextra
CCFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -shared 
TARGET = $(shell basename $(CURDIR))
TARGET_LIB = lib$(TARGET).so
DIROBJ = ../obj/$(MAKECMDGOALS)
DIRLIB = ../libs/$(MAKECMDGOALS)
DIRINC = ../include/
DEPLIBS = sort_list
LINKFLAGS = $(addprefix -l,$(DEPLIBS))

SRCS = $(TARGET).c 
OBJS = $(SRCS:.c=.o)

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
		-Wl,-rpath,$(DIRLIB) -l$(TARGET)
		
$(TARGET): $(TARGET).o $(TARGET)_test.o
		$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).o $(TARGET)_test.o
		
$(TARGET).o: $(TARGET).c $(DIRINC)
		$(CC) $(CFLAGS) -c $(TARGET).c -I$(DIRINC) -o $(DIROBJ)/$(TARGET).o 

$(TARGET)_test.o: $(TARGET)_test.c $(DIRINC)
		$(CC) $(CFLAGS) -c $(TARGET)_test.c -I$(DIRINC)

$(TARGET_LIB): $(OBJS)
		$(foreach dir,$(DEPLIBS),$(MAKE) $(MAKECMDGOALS) -C ../$(dir))
		$(CC) $(LDFLAGS) -o $(DIRLIB)/$@ $(DIROBJ)/$^ -I$(DIRINC) -L$(DIRLIB) \
		-Wl,-rpath,$(DIRLIB) $(LINKFLAGS)

$(SRCS:.c=.d):%.d:%.c
		$(CC) $(CFLAGS) -I$(DIRINC) -MM $< >$@

include $(SRCS:.c=.d)


clean:
		$(RM) ../libs/debug/${TARGET_LIB} ../libs/release/${TARGET_LIB}\
		../obj/debug/${OBJS} $(SRCS:.c=.d) ../obj/release/${OBJS} *.out *.o
		$(foreach dir,$(DEPLIBS),$(MAKE) $(MAKECMDGOALS) -C ../$(dir))

