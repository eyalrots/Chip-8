CC = gcc

ifeq ($(shell uname -s),Darwin)	
	CC = gcc-14
endif

SDL = SDL2-2.30.3
CFLAGS = -I./$(SDL)/include -I.
LDFLAGS = -L./$(SDL)/build -lSDL2 -static

SRC = chip8.c emulator.c
TARGET = emulator

all: 
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)