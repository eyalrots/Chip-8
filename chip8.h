//masking
#define OPCODE_MSK      0xF0
#define REG_MSK         0x0F
#define CONST_C1        0x0F
#define CONST_C2        0xFF
#define CONST_C3        0x0FFF

//size of inner stuff
#define COMMAND_SIZE    0x10

#define REG_FILE_SIZE   0x10
#define SIZE_OF_STACK   0x10

#define DISPLAY_FACTOR  0x10
#define DISPLAY_HIGHT   0x20
#define DISPLAY_WIDTH   0x40
#define DISPLAY_SIZE    ((DISPLAY_HIGHT * DISPLAY_FACTOR) * (DISPLAY_WIDTH * DISPLAY_FACTOR) * sizeof(char))

#define START_OF_MEMORY 0x000
#define END_OF_MEMORY   0xFFF
#define MEMORY_SIZE     (END_OF_MEMORY - START_OF_MEMORY)

#define START_OF_INTER  0x000
#define END_OF_INTER    0x1FF
#define INTER_SIZE      (END_OF_INTER - START_OF_INTER)

#define START_OF_ROM    0x200
#define END_OF_ROM      0xFFF
#define ROM_SIZE        (END_OF_ROM - START_OF_ROM)

#define START_OF_FONT   0x000
#define END_OF_FONT     0x050
#define FONT_SIZE       (END_OF_FONT - START_OF_FONT)

#define BYTESCAN(N)     (0x80 >> N)

#define SCANCODE_LIST   {30,31,32,33,20,26,8,21,4,22,7,9,29,27,6,25}
#define KEYS_SIZE       0x10

typedef unsigned char   uchar;
typedef unsigned short  ushort;

typedef struct Chip8 
{
    ushort  PC;
    ushort  I;
    ushort  SP;
    uchar   DT;
    uchar   ST;

    ushort  stack[SIZE_OF_STACK];
    uchar   memory[MEMORY_SIZE];
    uchar   V[REG_FILE_SIZE];

    uchar   display[DISPLAY_HIGHT*DISPLAY_FACTOR][DISPLAY_WIDTH*DISPLAY_FACTOR];
} chip8_t;

extern const uchar charfont[FONT_SIZE];

int init_chip8(chip8_t *chip8, const char *rom_file);
int load_rom(chip8_t *chip8, const char *rom_file);

int fde(chip8_t *chip8);
int decode_0(chip8_t *chip8, ushort c2);
int decode_8(chip8_t *chip8, uchar c1, uchar vx, uchar vy);
void decode_D(chip8_t *chip8, uchar c1, uchar vx, uchar vy);
int decode_E(chip8_t *chip8, uchar c2, uchar vx);
int decode_F(chip8_t *chip8, uchar c2, uchar vx);
int key_decode(uchar key, uchar flag);
int cycle(chip8_t *chip8);
