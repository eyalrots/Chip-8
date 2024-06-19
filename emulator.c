#include <stdio.h>
#include <SDL2/SDL.h>
#include "emulator.h"
#include "chip8.h"

#define ROM "ibm_logo.ch8"

int main()
{
    struct chip8 *chip8;
    if (init_chip8(chip8, ROM) != 0) { 
        perror("Init not successful!"); 
        return 1;
    }
    printf("build seccesful!\n");
    //Init SDL display
    //init sdl video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    //init window (display)
    SDL_Window* window = SDL_CreateWindow("SDL Display Example", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          DISPLAY_WIDTH, DISPLAY_HIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //init render for emulator display
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //init events for keyboard use
    if (SDl_Init(SDL_INIT_EVENTS) != 0) { 
        SDL_Quit();
        return 1; 
    }
    // emulator cycle
    int flag = 0;
    while (flag == 0) {
        emulate_cycle(chip8, renderer);
        printf("emulate cycle successful!\n");
    }

    //cleanup for SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void emulate_cycle(chip8 *chip8, SDL_Renderer* renderer) {
    cycle(chip8);
    printf("chip cycle successful!\n");
    //Print display using SDL
    for (int h = 0; h < DISPLAY_HIGHT; h++) {
        for (int w = 0; w < DISPLAY_WIDTH; w++) {
            if (chip8->display[h,w] == 1) {
                SDL_RenderDrawPoint(renderer, w, h);
            }
        }
    }
    SDL_RenderPresent(renderer);
    return;
}
