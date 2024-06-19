#include <iostream>

#include "Leaderboard.h"

int main()
{
    int input;
    Leaderboard leaderboard;

    while (true)
    {
        leaderboard.Read();

        std::cout << "[1] Display" << std::endl;
        std::cout << "[2] New value" << std::endl;

        std::cin >> input;

        switch (input)
        {
        case 1:
            leaderboard.Display();
            break;

        case 2:
            std::cout << "Enter value: ";
            std::cin >> input;
            std::cout << "Placing: " << leaderboard.Update(input) << std::endl;
            break;
        }

        leaderboard.Write();
    }
}