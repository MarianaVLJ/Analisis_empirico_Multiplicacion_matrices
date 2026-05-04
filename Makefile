CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude

SRC = src/matrix.c main.c
TARGET = experiment

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
