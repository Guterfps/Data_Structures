
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra

TARGET = queue

all: debug

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -DNDEBUG -O3
release: $(TARGET)

$(TARGET): $(TARGET).o $(TARGET)_test.o 
		$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).o $(TARGET)_test.o slist.o
		
$(TARGET).o: $(TARGET).c slist.o $(TARGET).h slist.h
		$(CC) $(CFLAGS) -c $(TARGET).c 
		
slist.o: slist.c slist.h
		$(CC) $(CFLAGS) -c slist.c

$(TARGET)_test.o: $(TARGET)_test.c $(TARGET).h
		$(CC) $(CFLAGS) -c $(TARGET)_test.c
clean:
		$(RM) $(TARGET).out *.o
