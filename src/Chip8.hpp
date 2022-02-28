#pragma once

#include <cstdint>
#include <random>

const unsigned KEY_COUNT = 16;
const unsigned VIDEO_WIDTH = 64;
const unsigned VIDEO_HEIGHT = 32;
const unsigned REGISTER_COUNT = 16;
const unsigned MEMORY_SIZE = 4096;
const unsigned STACK_HEIGHT = 16;

class Chip8
{
public:
    Chip8();
    void LoadROM(char const* filename);
    void Cycle();

    uint8_t keypad[KEY_COUNT]{};
    uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{};

private:
    uint8_t registers[REGISTER_COUNT]{};
    uint8_t memory[MEMORY_SIZE]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[STACK_HEIGHT]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint16_t opcode;

    std::default_random_engine randGenerator;
    std::uniform_int_distribution<uint8_t> randByte;

    //Opcodes
    #pragma region

    //Do nothing
    void OP_NULL();

    //CLS (Clear display)
    void OP_00E0();

    //RET (Return)
    void OP_00EE();

    //JP (Set pc to nnn)
    void OP_1nnn();

    //CALL (call subroutine at nnn)
    void OP_2nnn();

    //SE Vx, byte (skip next instruction if Vx == kk)
    void OP_3xkk();

    //SNE Vx, byte (skip next instruction if Vx != kk)
    void OP_4xkk();

    //SE Vx, Vy
    void OP_5xy0();

    //LD Vx, byte (load kk into register Vx)
    void OP_6xkk();

    //ADD Vx, byte
    void OP_7xkk();

    //LD Vx, Vy
    void OP_8xy0();

    //OR Vx, Vy
    void OP_8xy1();

    //AND Vx, Vy
    void OP_8xy2();

    //XOR Vx, Vy
    void OP_8xy3();

    //ADD Vx, Vy (Vx = Vx - Vy)
    void OP_8xy4();

    //SUB Vx, Vy
    void OP_8xy5();

    //SHR Vx (Shift right)
    void OP_8xy6();

    //SUBN Vx, Vy (Vx = Vy - Vx, subtract without borrow)
    void OP_8xy7();

    //SHL Vx (Shift left)
    void OP_8xyE();

    //SNE Vx, Vy
    void OP_9xy0();

    //LD Index, addr
    void OP_Annn();

    //JP V0, addr (jump to location nnn + V0)
    void OP_Bnnn();

    //RND Vx, byte (set Vx = randByte AND kk)
    void OP_Cxkk();

    //DRW Vx, Vy, nibble (display n sprite starting at mem location I at (Vx, Vy))
    void OP_Dxyn();

    //SKP Vx (skip next instruction if value with Vx is pressed)
    void OP_Ex9E();

    //SKNP Vx
    void OP_ExA1();

    //LD Vx, DT  (Load delay timer value into Vx)
    void OP_Fx07();

    //LD Vx, K (wait for key press and store value entered into Vx)
    void OP_Fx0A();

    //LD DT, Vx (set delay timer to Vx)
    void OP_Fx15();

    //LD ST, Vx (set sound timer to Vx)
    void OP_Fx18();

    //ADD I, Vx
    void OP_Fx1E();

    //LD I, Vx (Set I to location of sprite for digit Vx)
    void OP_Fx29();

    //LD B, Vx (Store BCD representation of Vx at I, I+1, I+2)
    void OP_Fx33();

    //LD [I], Vx (store registers V0 to Vx in memory starting at location I)
    void OP_Fx55();

    //LD Vx, [I] (Read registers V0 to Vx starting at location I)
    void OP_Fx65();

    #pragma endregion

    //Function Table
	typedef void (Chip8::*Chip8Func)();

    void Table0();
    void Table8();
    void TableE();
    void TableF();

	Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
	Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};
};
