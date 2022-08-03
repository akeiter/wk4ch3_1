#include <iostream>
#include <thread>
#include <chrono>

int ThreadVar = 0;

bool DidQuit = false;
bool ShouldDecrementLife = false;

struct Character
{
    float Position = 0.0f;
    int Score = 0;
    int Lives = 1;

    void DisplayStats()
    {
        std::cout << "Lives: " << Lives << std::endl;
    }
};

Character Player;

void UpdateCharacter1()
{
    while (!DidQuit)
    {
        if (ShouldDecrementLife)
        {
            if (Player.Lives > 0)
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::this_thread::yield();
                --Player.Lives;
            }
        }
    }
}

void UpdateCharacter2()
{
    while (!DidQuit)
    {
        if (ShouldDecrementLife)
        {
            if (Player.Lives > 0)
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::this_thread::yield();
                --Player.Lives;
            }
        }
    }
}

void HelloWorldThread()
{
    while (!DidQuit)
    {
        ThreadVar++;
        if (ThreadVar > 1000)
        {
            ThreadVar = 0;
        }
    }
}

void ProcessInput()
{
    while (!DidQuit)
    {
        std::cout << "'a' to decrement player life" << std::endl;
        std::cout << "'d' to display player stats" << std::endl;
        std::cout << "'q' to quit" << std::endl;
        char UserInput;
        std::cin >> UserInput;
        switch (UserInput)
        {
        case 'a':
            ShouldDecrementLife = true;
            break;
        case'd':
            Player.DisplayStats();
            break;
        case 'q':
            DidQuit = true;
            break;
        default:
            break;
        }
        DidQuit = (UserInput == 'q');
    }
}

int main()
{

    std::thread InputHandler(ProcessInput);
    std::thread CharacterUpdate1(UpdateCharacter1);
    std::thread CharacterUpdate2(UpdateCharacter2);

    InputHandler.join();
    CharacterUpdate1.join();
    CharacterUpdate2.join();

    return 0;
}

