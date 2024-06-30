#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"

const uchar charfont[FONT_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const ushort font_locations[0x10] = {0x0000, 0x0005, 0x000A, 0x000F, 0x0014, 0x0019, 0x1E, 0x23, 0x28, 0x2D, 0x32, 0x37, 0x3C, 0x41, 0x46, 0x4B};

const uchar scancodes[KEYS_SIZE] = {30,31,32,33,20,26,8,21,4,22,7,9,29,27,6,25}; //1,2,3,4,Q,W,E,R,A,S,D,F,Z,X,C,V

int init_chip8(chip8_t *chip8, const char *rom_file)
{
    //init special-perpose registers
    chip8->PC = START_OF_ROM;
    chip8->I = 0;
    chip8->SP = 0;
    chip8->DT = 0;
    chip8->ST = 0;
        
    memset(chip8->display, 0, DISPLAY_SIZE);

    //init interpreter code in ram
    for (int i = 0; i <= FONT_SIZE; i++) {
        chip8->memory[i] = charfont[i];
    }

    //read rom to ram
    if (load_rom(chip8, rom_file) != 0) {
        return 1;
    }

    return 0;
}

int load_rom(chip8_t *chip8, const char *rom_file) {
    int rom_file_size;
    FILE *rfd;

    struct stat st;
    if (stat(rom_file, &st) != 0) {
        return 1;
    }
    rom_file_size = st.st_size;

    rfd = fopen(rom_file, "rb");
    if (rfd == NULL) {
        return 1;
    }
    printf("<<YAIR>> file size: %d\n", rom_file_size);

    if (rom_file_size > ROM_SIZE) {
        perror("ROM file too big!");
        fclose(rfd);
        return 1;
    }

    char rom_buffer[rom_file_size];
    fread(rom_buffer, 1, rom_file_size, rfd);

    for (int i = 0; i < rom_file_size; i++) {
        chip8->memory[START_OF_ROM + i] = rom_buffer[i];
    }


    fclose(rfd);
    return 0;
}

//fetch-decode-execute
int fde(chip8_t *chip8) {
    //fetch
    ushort command = chip8->memory[chip8->PC] << 8 | chip8->memory[chip8->PC + 1];
    //ushort command = chip8->memory[chip8->PC];
    ushort opcode = (command >> 8) & OPCODE_MSK; //takes 4 MSB bits of command (8(4) bit)
    uchar r_1 = (command >> 8) & REG_MSK; //takes LSB nibble of the MSB byte (8(4) bit)
    uchar r_2 = (command >> 4) & REG_MSK; //takes MSB nibble of LSB byte (8(4) bit)
    uchar c1 = command & CONST_C1; //takes LSB nibble of LSB byte (8(4) bit)
    uchar c2 = command & CONST_C2; //takes LSB byte (8 bit)
    ushort c3 = command & CONST_C3; //takes LSB nibble of MSB byte + LSB byte (16(12) bit)
    int jump = 0;
    uchar rand;
    // if (chip8->V[0x0A] == 0x00) {
    //     printf("stooooop there's an ERROR here!!!\n");
    //     //return 1;
    // }
    // if (c3 == 0x0000 && opcode == 0x0A)
    //     printf("<<YAKIR>> address 0x%04X commad: 0x%04X\n", chip8->memory[chip8->PC], command);
    //decode + execute(in cases)
    if (command == 0xA2F2)
        printf("A2F2: I 0x%04X\n", chip8->I);
    switch (opcode) {
        case 0x00:            
            if (decode_0(chip8, c2) == 1) { return 1;}
            break;
        case 0x10: //JP addr
            chip8->PC = c3;
            jump = 1;
            break;
        case 0x20: //CALL addr
            chip8->SP++;
            chip8->stack[chip8->SP] = chip8->PC;
            chip8->PC = c3;
            jump = 1;
            break;
        case 0x30://SE Vx, byte
            if (chip8->V[r_1] == c2){
                chip8->PC += 2;
            }
            break;
        case 0x40://SNE Vx, byte
            if (chip8->V[r_1] != c2){
                chip8->PC += 2;
            }
            break;
        case 0x50://SE Vx, Vy
            if (chip8->V[r_1] == chip8->V[r_2]){
                chip8->PC += 2;
            }
            break;
        case 0x60://LD Vx, byte
            chip8->V[r_1] = c2;
            break;
        case 0x70://ADD Vx, byte
            chip8->V[r_1] += c2;
            break;
        case 0x80:
            if (decode_8(chip8, c1, r_1, r_2) == 1) { return 1;}
            break;
        case 0x90://SNE Vx, Vy
            if (chip8->V[r_1] != chip8->V[r_2]){
                chip8->PC += 2;
            }
            break;
        case 0xA0://LD I, addr
            if (command == 0xA2F2)
                printf("A: I 0x%04X\n", chip8->I);
            chip8->I = c3;
            break;
        case 0xB0://JP V0, addr
            chip8->PC = chip8->V[0] + c3;
            jump = 1;
            break;
        case 0xC0: //RND Vx, byte
            rand = (uchar)(random() % 256);
            chip8->V[r_1] = rand & c2;
            break;
        case 0xD0: //DRW Vx, Vy, nibble(c1)
            decode_D(chip8, c1, r_1, r_2);
            break;
        case 0xE0:
            if (decode_E(chip8, c2, r_1) == 1) { return 1;}
            break;
        case 0xF0:
            if (decode_F(chip8, c2, r_1) == 1) { return 1;}
            break;
        default:
            return 1;
    }

    if (!jump) {
        chip8->PC += 2;
    }
    if (chip8->I == 0x0000)
        printf("<<YAKIR>> address 0x%04X commad: 0x%04X\n", chip8->memory[chip8->PC], command);
    return 0;
}

int decode_0(chip8_t *chip8, ushort c2) {
    switch (c2) {
        case 0xE0: //CLS
            memset(chip8->display, 0, DISPLAY_SIZE);
            break;
        case 0xEE: //RET
            chip8->PC = chip8->stack[chip8->SP];
            chip8->SP--;
            break;
        default:
            return 1;
    }
    return 0;
}

int decode_8(chip8_t *chip8, uchar c1, uchar vx, uchar vy) {
    ushort temp;
    switch (c1)
    {
    case 0x00: //LD Vx, Vy
        chip8->V[vx] = chip8->V[vy];
        break;
    case 0x01: //OR Vx, Vy
        chip8->V[vx] = chip8->V[vx] | chip8->V[vy];
        break;
    case 0x02: //AND Vx, Vy
        chip8->V[vx] = chip8->V[vx] & chip8->V[vy];
        break;
    case 0x03: //XOR Vx, Vy
        chip8->V[vx] = chip8->V[vx] ^ chip8->V[vy];
        break;
    case 0x04: //ADD Vx, Vy
        temp = chip8->V[vx] + chip8->V[vy];
        if (((temp >> 8) & CONST_C2) != 0x00) {
            chip8->V[15] = 1;
        }
        else {
            chip8->V[15] = 0;
        }
        chip8->V[vx] = (temp & CONST_C2);
        break;
    case 0x05: //SUB Vx, Vy
        if (chip8->V[vx] > chip8->V[vy]) {
            chip8->V[15] = 1;
        }
        else {
            chip8->V[15] = 0;
        }
        chip8->V[vx] -= chip8->V[vy];
        break;
    case 0x06: //SHR Vx {, Vy}
        chip8->V[vx] = chip8->V[vy]; //only for COSMAC VIP - need to be configurable by emulator!
        if ((chip8->V[vx] & 0x01) == 0x01) {
             chip8->V[15] = 1;
        }
        else {
            chip8->V[15] = 0;
        }
        chip8->V[vx] = (chip8->V[vx] >> 1);
        break;
    case 0x07: // SUBN Vx, Vy
        
        if (chip8->V[vy] > chip8->V[vx]) {
            chip8->V[15] = 1;
        }
        else {
            chip8->V[15] = 0;
        }
        chip8->V[vx] = chip8->V[vy] - chip8->V[vx];
        break;
    case 0x0E: //SHL Vx {, Vy}
        chip8->V[vx] = chip8->V[vy]; //only for COSMAC VIP - need to be configurable by emulator!
        if ((chip8->V[vx] & 0x10) == 0x10) {
             chip8->V[15] = 1;
        }
        else {
            chip8->V[15] = 0;
        }
        chip8->V[vx] = (chip8->V[vx] << 1);
        break;
    default:
        return 1;
    }
    return 0;
}

void decode_D(chip8_t *chip8, uchar c1, uchar vx, uchar vy) {
    // get x and y coordinants, & op wraps sprite to other side of display
    uchar x_cor = chip8->V[vx] & DISPLAY_WIDTH - 1;
    uchar y_cor = chip8->V[vy] & DISPLAY_HIGHT - 1;
    int fact_x_cor = x_cor * DISPLAY_FACTOR;
    int fact_y_cor = y_cor * DISPLAY_FACTOR;
    //printf("V[vx] 0x%02X V[vy] 0x%02X\n", chip8->V[vx], chip8->V[vy]);
    // if (x_cor == 0x14)
    //     printf("current sprite been drawn 0x%04X\n", chip8->I);
    if (chip8->I == 0x0000)
        printf("new draw\n");
    chip8->V[15] = 0;
    for (int i = 0; i < c1; i++) {
        uchar sprite = chip8->memory[chip8->I + i];

        for (int j = 0; j < 8; j++) {
            uchar pxl = sprite & BYTESCAN(j);
            if (chip8->I == 0x0000 && j == 0)
                printf("sprite 0x%02X I+i 0x%04X\n", sprite, (chip8->I+i));

            if (chip8->display[fact_y_cor][fact_x_cor] == 1) {
                chip8->V[15] = 1;
            }

            // if (chip8->I == 0x0001) {
            //     printf("x 0x%02X y 0x%02X\n", fact_x_cor, fact_y_cor);
            //     printf("0x%04X \n", chip8->display[fact_y_cor][fact_x_cor]);
            // }

            for (int x = 0; x < DISPLAY_FACTOR; x++) {
                for (int y = 0; y < DISPLAY_FACTOR; y++) {
                    if (pxl != 0)
                        chip8->display[fact_y_cor + y][fact_x_cor + x] ^= 1;
                }
            }

            // if (chip8->I == 0x0001) {
            //     printf("x 0x%02X y 0x%02X\n", fact_x_cor, fact_y_cor);
            //     printf("0x%04X \n", chip8->display[fact_y_cor][fact_x_cor]);
            // }

            fact_x_cor += DISPLAY_FACTOR;
            if (fact_x_cor >= DISPLAY_WIDTH * DISPLAY_FACTOR) {
                break;
            }
            
        }
        fact_x_cor = x_cor * DISPLAY_FACTOR;
        fact_y_cor += DISPLAY_FACTOR;
        if (fact_y_cor >= DISPLAY_HIGHT * DISPLAY_FACTOR) {
            break;
        }
        
    }
    return;
}

int decode_E(chip8_t *chip8, uchar c2, uchar vx) {
    SDL_PumpEvents(); //update keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    uchar is_pressed = key_decode(chip8->V[vx], 0x00);
    if (is_pressed == 0xFF) { return 1; }

    switch (c2)
    {
    case 0x9E: //SKP Vx
        if (state[is_pressed] == 1) {
            chip8->PC += 2;
        }
        break;
    case 0xA1: //SKNP Vx
        if (state[is_pressed] == 0) {
            chip8->PC += 2;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

int key_decode(uchar key, uchar flag) {
    flag = (flag == 0xFF) ? 0xFF : 0x00;
    if (flag == 0xFF) { //check which key is pressed
        switch (key)
        {
        case SDL_SCANCODE_1:
            return 0x00;
            break;
        case SDL_SCANCODE_2:
            return 0x01;
            break;
        case SDL_SCANCODE_3:
            return 0x02;
            break;
        case SDL_SCANCODE_4:
            return 0x03;
            break;
        case SDL_SCANCODE_Q:
            return 0x04;
            break;
        case SDL_SCANCODE_W:
            return 0x05;
            break;
        case SDL_SCANCODE_E:
            return 0x06;
            break;
        case SDL_SCANCODE_R:
            return 0x07;
            break;
        case SDL_SCANCODE_A:
            return 0x08;
            break;
        case SDL_SCANCODE_S:
            return 0x09;
            break;
        case SDL_SCANCODE_D:
            return 0x0A;
            break;
        case SDL_SCANCODE_F:
            return 0x0B;
            break;
        case SDL_SCANCODE_Z:
            return 0x0C;
            break;
        case SDL_SCANCODE_X:
            return 0x0D;
            break;
        case SDL_SCANCODE_C:
            return 0x0E;
            break;
        case SDL_SCANCODE_V:
            return 0x0F;
            break;
        default:
            return 0xFF;
            break;
        }
    } else if (flag == 0x00){ //check if V[vx] key was pressed
        switch (key)
        {
        case 0x00:
            return SDL_SCANCODE_1;
            break;
        case 0x01:
            return SDL_SCANCODE_2;
            break;
        case 0x02:
            return SDL_SCANCODE_3;
            break;
        case 0x03:
            return SDL_SCANCODE_4;
            break;
        case 0x04:
            return SDL_SCANCODE_Q;
            break;
        case 0x05:
            return SDL_SCANCODE_W;
            break;
        case 0x06:
            return SDL_SCANCODE_E;
            break;
        case 0x07:
            return SDL_SCANCODE_R;
            break;
        case 0x08:
            return SDL_SCANCODE_A;
            break;
        case 0x09:
            return SDL_SCANCODE_S;
            break;
        case 0x0A:
            return SDL_SCANCODE_D;
            break;
        case 0x0B:
            return SDL_SCANCODE_F;
            break;
        case 0x0C:
            return SDL_SCANCODE_Z;
            break;
        case 0x0D:
            return SDL_SCANCODE_X;
            break;
        case 0x0E:
            return SDL_SCANCODE_C;
            break;
        case 0x0F:
            return SDL_SCANCODE_V;
            break;
        default:
            return 0xFF;
            break;
        }
    }
    return 0xFF;
}

int decode_F(chip8_t *chip8, uchar c2, uchar vx) {
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    char is_pressed;
    uchar key_pressed;
    switch (c2)
    {
    case 0x07: // LD Vx, DT
        chip8->V[vx] = chip8->DT;
        break;
    case 0x0A: // LD Vx, K
        is_pressed = -1; //need to check scancode list.
        while (is_pressed == -1) {
            for (int i = 0; i < KEYS_SIZE; i++) {
                if (state[scancodes[i]] == 1) {
                    key_pressed = key_decode(scancodes[i], 0xFF);
                    if (key_decode != 0xFF) {
                        is_pressed = 0;
                    }
                }
            }
        }
        chip8->V[vx] = is_pressed;
        break;
    case 0x15: // LD DT, Vx
        chip8->DT = chip8->V[vx];
        break;
    case 0x18: // LD ST, Vx
        chip8->ST = chip8->V[vx];
        break;
    case 0x1E: // ADD I, Vx
        chip8->I += chip8->V[vx];
        if (chip8->I == 0)
            printf("I=0");
        break;
    case 0x29: // LD F, Vx
        chip8->I = font_locations[chip8->V[vx]];
        break;
    case 0x33: // LD B, Vx
        printf("33: I 0x%04X\n", chip8->I); //PROBLEM HERE!!!
        printf("prev command: 0x%04X\n", chip8->memory[chip8->PC - 2] << 8 | chip8->memory[chip8->PC - 1]);
        chip8->memory[chip8->I] = chip8->V[vx] / 100; //hundreds
        chip8->memory[chip8->I+1] = (chip8->V[vx] / 10) % 10; //tens
        chip8->memory[chip8->I+2] = chip8->V[vx] % 10; //ones
        break;
    case 0x55: // LD [I], Vx
        for (int i = 0; i <= vx; i++) {
            printf("55: I+i 0x%04X\n", chip8->I+i);
            chip8->memory[chip8->I+i] = chip8->V[i];
        }
        break;
    case 0x65: // LD Vx, [I]
        for (int i = 0; i <= vx; i++) {
            chip8->V[i] = chip8->memory[chip8->I+i];
        }
        break;
    default:
        return 1;
    }
    return 0;
}

int cycle(chip8_t *chip8) {
    //time delay equivalent to 1MHz
    struct timespec req = {0, 1000};
    nanosleep(&req, NULL);
    //fetch - decode - execute
    if (fde(chip8) == 1) 
        return 1;
    return 0;
}
