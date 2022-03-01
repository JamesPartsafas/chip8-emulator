#include "Chip8.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Argument usage: " << argv[0] << "<Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    }

    int videoScaleFactor = std::stoi(argv[1]);
    int minClockCycleDelay = std::stoi(argv[2]);
    char const* romName = argv[3];

    Renderer renderer(
        "Chip-8 Emulator", 
        VIDEO_WIDTH * videoScaleFactor, 
        VIDEO_HEIGHT * videoScaleFactor, 
        VIDEO_WIDTH, 
        VIDEO_HEIGHT
    );

    Chip8 chip8;
    chip8.LoadROM(romName);

    int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = renderer.ProcessInput(chip8.keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float delayTimer = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (delayTimer > minClockCycleDelay)
        {
            lastCycleTime = currentTime;
            chip8.Cycle();
            renderer.UpdateScreen(chip8.video, videoPitch);
        }
    }
    
    return 0;
}
