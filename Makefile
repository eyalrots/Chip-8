CC = gcc

SDL = SDL2-2.30.3
SDL_LIB_PATH = /usr/local/lib
SDL_INCLUDE_PATH = /usr/local/include

CFLAGS = -I$(SDL_INCLUDE_PATH)/SDL2 -I. -Wl,-rpath,$(SDL_LIB_PATH)
LDFLAGS = -L$(SDL_LIB_PATH) -lSDL2 -lSDL2main

SRC = chip8.c emulator.c
TARGET = emulator.out

all: sdl chip8

chip8:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)
	codesign --entitlements entitlements.plist -f -s - $(TARGET)

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
