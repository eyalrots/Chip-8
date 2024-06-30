#include <stdio.h>
#include <SDL2/SDL.h>
#include "emulator.h"

// int main(int argc, char *argv[]) {
//     printf("fuck you eyal, you are gay!\n");
//     exit(0);
// }

#define ROM "Paddles.ch8"

int main(int argc, char* argv[]) {
    chip8_t chip8;
    if (init_chip8(&chip8, ROM) != 0) { 
        perror("Init not successful!"); 
        return 1;
    }
    printf("build seccesful!\n");
    // SDL Initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create Window
    SDL_Window* window = SDL_CreateWindow("Chip 8 Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH*DISPLAY_FACTOR, DISPLAY_HIGHT*DISPLAY_FACTOR, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create Renderer (for drawing)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
    
    // Render Loop (just keeps the window open)
    SDL_bool quit = SDL_FALSE;
    SDL_Event e;
    int cycle_counter = 0;
    while (!quit) {
        // Handle Events (look for quit event to close window)
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
        }
        if (emulate_cycle(&chip8, renderer, cycle_counter) == 1)
            break;
        else
            cycle_counter ++;
            
        if (cycle_counter > TIMER_DELAY)
            cycle_counter = 0;
    }

    // Cleanup (free resources)
    printf("cleanup\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int emulate_cycle(chip8_t *chip8, SDL_Renderer* renderer, int cycle_counter) {
    if (cycle(chip8) == 1) { 
        printf("chip cycle exited with exit code 1\n");
        return 1;
    }
    //timer ahndlling
    if (cycle_counter == TIMER_DELAY) {
        //printf("timer decreased\n");
        if (chip8->DT != 0x00)
            chip8->DT --;
        if (chip8->ST != 0x00)
            chip8->ST --;
    }
    //Print display using SDL
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int h = 0; h < DISPLAY_HIGHT*DISPLAY_FACTOR; h++) {
        for (int w = 0; w < DISPLAY_WIDTH*DISPLAY_FACTOR; w++) {
            if (chip8->display[h][w] == 1) {
                SDL_RenderDrawPoint(renderer, w, h);
            }
        }
    }  
    SDL_RenderPresent(renderer);
    return 0;
}
