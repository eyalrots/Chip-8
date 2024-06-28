#include "chip8.h"

#define TIMER_DELAY 1667

int emulate_cycle(chip8_t *chip8, SDL_Renderer* renderer, int cycle_counter);