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

# CC = gcc

# # SDL2 Configuration
# SDL = SDL2-2.30.3   
# SDL_BUILD_DIR = build
# CFLAGS = -I$(SDL_BUILD_DIR)/include -I.
# LDFLAGS = -L$(SDL_BUILD_DIR)/lib -Wl,-rpath=/usr/ -lSDL2 -lSDL2main 

# # Source & Target
# SRC = chip8.c emulator.c
# TARGET = emulator.out

# # Build Targets
# all: sdl chip8

# chip8: $(SRC)
# 	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

# sdl: $(SDL_BUILD_DIR)/lib/libSDL2.dylib

# $(SDL_BUILD_DIR)/lib/libSDL2.dylib:
# 	cd $(SDL) && \
# 	rm -rf $(SDL_BUILD_DIR); \
# 	mkdir -p $(SDL_BUILD_DIR); \
# 	cd $(SDL_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release .. && \
# 	    make -j$(shell nproc) && \
# 	    sudo make install

# clean:
# 	rm -f $(TARGET) 
# 	if [ -d $(SDL_BUILD_DIR) ]; then \
# 		cd $(SDL_BUILD_DIR) && sudo make uninstall && make clean; \
# 	fi
