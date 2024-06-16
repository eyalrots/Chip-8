#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
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

int init_chip8(chip8 *chip8, const char *rom_file)
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

int load_rom(chip8 *chip8, const char *rom_file) {
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

    if (rom_file_size > ROM_SIZE) {
        perror("ROM file too big!");
        fclose(rom_file);
        return 1;
    }

    char rom_buffer[rom_file_size];
    fread(rom_buffer, 1, rom_file_size, rom_file);

    for (int i = 0; i < rom_file_size; i++) {
        chip8->memory[START_OF_ROM + i] = rom_buffer[i];
    }

    fclose(rom_file);
    return 0;
}

//fetch-decode-execute
void fde(chip8 *chip8) {
    //fetch
    ushort command = chip8->memory[chip8->PC];
    uchar opcode = (command >> 8) & OPCODE_MSK; //takes 4 MSB bits of command (8(4) bit)
    uchar r_1 = (command >> 8) & FIRST_REG_MSK; //takes LSB nibble of the MSB byte (8(4) bit)
    uchar r_2 = command & SECOND_REG_MSK; //takes MSB nibble of LSB byte (8(4) bit)
    uchar c1 = command & CONST_C1; //takes LSB nibble of LSB byte (8(4) bit)
    uchar c2 = command & CONST_C2; //takes LSB byte (8 bit)
    ushort c3 = command & CONST_C3; //takes LSB nibble of MSB byte + LSB byte (16(12) bit)

    //decode + execute(in cases)
    switch (opcode) {
        case 0x00:
            decode_0(chip8, c2);
            break;
        case 0x10: //JP addr
            chip8->PC = c3;
            break;
        case 0x20: //CALL addr
            chip8->SP++;
            chip8->stack[chip8->SP] = chip8->PC;
            chip8->PC = c3;
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
            decode_8(chip8, c1, r_1, r_2);
            break;
        case 0x90://SNE Vx, Vy
            if (chip8->V[r_1] != chip8->V[r_2]){
                chip8->PC += 2;
            }
            break;
        case 0xA0://LD I, addr
            chip8->I = c3;
            break;
        case 0xB0://JP V0, addr
            chip8->PC = chip8->V[0] + c3;
            break;
        case 0xC0: //RND Vx, byte
            uchar rand = (uchar)(random() % 256);
            chip8->V[r_1] = rand & c2;
            break;
        case 0xD0: //DRW Vx, Vy, nibble(c1)
            decode_D(chip8, c1, r_1, r_2);
            break;
        case 0xE0:
            //call function for code E - Key presses.
            break;
        case 0xF0:
            //call function for code F
            break;
        default:
            break;
    }
}

void decode_0(chip8 *chip8, ushort c2) {
    switch (c2) {
        case 0x0E: //CLS
            memset(chip8->display, 0, DISPLAY_SIZE);
            break;
        case 0xEE: //RET
            chip8->PC = chip8->stack[chip8->SP];
            chip8->SP--;
            break;
        default:
            break;
    }
}

void decode_8(chip8 *chip8, uchar c1, uchar vx, uchar vy) {
    switch (c1)
    {
    case 0x00: //LD Vx, Vy
        chip8->V[vx] = chip8->V[vy];
        break;
    case 0x01: //OR Vx, Vy
        chip8->V[vx] = vx | vy;
        break;
    case 0x02: //AND Vx, Vy
        chip8->V[vx] = vx & vy;
        break;
    case 0x03: //XOR Vx, Vy
        chip8->V[vx] = vx ^ vy;
        break;
    case 0x04: //ADD Vx, Vy
        ushort temp = chip8->V[vx] + chip8->V[vy];
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
        break;
    }
}

void decode_D(chip8 *chip8, uchar c1, uchar vx, uchar vy) {
    // get x and y coordinants, & op wraps sprite to other side of display
    uchar x_cor = chip8->V[vx] & DISPLAY_WIDTH-1;
    uchar y_cor = chip8->V[vy] & DISPLAY_HIGHT-1;
    chip8->V[15] = 0;

    for (int i = 0; i < c1; i++) {
        uchar sprite = chip8->memory[chip8->I + i];

        for (int j = 0; j < 8; j++) {
            uchar pxl = sprite & BYTESCAN(j);

            if (chip8->display[x_cor][y_cor] == 1) {
                chip8->V[15] = 1;
            }
            else {
                chip8->V[15] = 0;
            }

            chip8->display[x_cor][y_cor] ^= pxl;

            x_cor++;
            if (x_cor >= DISPLAY_WIDTH) {
                break;
            }
        }

        y_cor++;
        if (y_cor >= DISPLAY_HIGHT) {
            break;
        }
    }
}

void decode_E(chip8 *chip8, uchar c2, uchar vx) {
    switch (c2)
    {
    case 0x9E: //SKP Vx
        
        break;
    
    default:
        break;
    }
}
