#include "Chip8.hpp"
#include <cstdint>
#include <fstream>
#include <cstring>
#include <chrono>
#include <random>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_STARTING_ADDRESS = 0x50;

//Contains data for drawing the characters 0 to F
uint8_t fontset[FONTSET_SIZE] =
{
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
}

Chip8::Chip8() :
    randGenerator(std::chrono::system_clock::now().time_since_epoch().count())
{
    //Set program counter to start of ROM location
    pc = START_ADDRESS;

    //Load fontset
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_STARTING_ADDRESS + i] = fontset[i];
    }

    //Initialize random number generation
    randByte = std::uniform_int_distribution<int8_t>(0, 255U);

    //Prepare function table pointers
}

void Chip8::LoadROM(char const* filename)
{
    //Open file as binary stream
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        //Get size of file, then go back to beginning to fill a buffer before 
        //loading contents into memory from starting address
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for (long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
}