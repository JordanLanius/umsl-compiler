CC = gcc
CFLAGS = -Wall -ggdb

TARGET = compfs
OBJS = main.o generator.o stack.o tree.o parser.o scanner.o character.o errhandler.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	/bin/rm -f *.o $(TARGET)

cleanout:
	/bin/find . -name \*.asm -type f -delete
