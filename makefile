CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -Iinclude -std=c99

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

TARGET = miningit

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
