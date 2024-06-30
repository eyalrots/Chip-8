#include "chip8.h"

#define TIMER_DELAY 8

int emulate_cycle(chip8_t *chip8, SDL_Renderer* renderer, int cycle_counter);