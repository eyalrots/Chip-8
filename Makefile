CC = gcc

SDL = SDL2-2.30.3
CFLAGS = -I/usr/local/include/SDL2 -I.
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2main

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
	cmake -DCMAKE_BUILD_TYPE=Release .. && \
	make -j$(shell nproc) && \
	sudo make install

clean:
	rm -f $(TARGET) && \
	cd $(SDL)/build && sudo make uninstall && make clean