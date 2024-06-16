CC = gcc

ifeq ($(shell uname -s),Darwin)	
	CC = gcc-14
endif

SDL = SDL2-2.30.3
CFLAGS = -I./$(SDL)/include -I.
LDFLAGS = -L./$(SDL)/build -lSDL2 -static

SRC = chip8.c emulator.c
TARGET = emulator.out

all: sdl chip8

chip8:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)	

sdl:
	cd $(SDL) && \
	rm -rf build; \
	mkdir build; \
	cd build && \
	cmake -DSDL_STATIC=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release .. && \
	make -j$(shell nproc)

clean:
	rm -f $(TARGET) && \
	cd $(SDL)/build && make clean