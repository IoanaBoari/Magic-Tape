.phony: build run clean

CC=gcc
CFLAGS=-Wall -Werror -g
TARGET=tema1

build: $(TARGET)

$(TARGET): tema1.c tema1.h
	$(CC) $(CFLAGS) -o $(TARGET) tema1.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
