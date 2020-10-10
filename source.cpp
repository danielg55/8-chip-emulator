#include <iostream>
#include <chrono>
#include "headers/chip8.h"
#include "headers/platform.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        exit(EXIT_FAILURE);
    }

    int videoScale = stoi(argv[1]);
    int cycleDelay = stoi(argv[2]);
    char const *romFilename = argv[3];

    Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.LoadROM(romFilename);

    int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

    auto lastCycleTime = chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = platform.ProcessInput(chip8.keypad);

        auto currentTime = chrono::high_resolution_clock::now();
        float dt = chrono::duration<float, chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;

            chip8.Cycle();

            platform.Update(chip8.video, videoPitch);
            for (int i = 0; i < VIDEO_HEIGHT; i++)
            {
                for (int j = 0; j < VIDEO_WIDTH; j++)
                {
                    cout << chip8.video[i * VIDEO_WIDTH + j] << " ";
                }
                cout << endl;
            }
            getchar();
        }
    }

    return 0;
}
