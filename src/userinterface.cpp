#include "userinterface.h"
#include "scores.h"
#include <iostream>
#include <string>


UserInterface::UserInterface() : _gameSatusFlag{quit}
{
}

void UserInterface::ChoiceMenu()
{
    //Display the main menue
    std::cout << std::endl;
    std::cout << " ### WELCOME TO SNAKE GAME ###" << std::endl;
    std::cout << " =============================" << std::endl;
    std::cout << " Please make your choice and" << std::endl;
    std::cout << "       then press Enter" << std::endl  << std::endl;
    std::cout << " 1. Start a new game" << std::endl;
    std::cout << " 2. Top 10 high scores" << std::endl;
    std::cout << " 3. Quit the game" << std::endl;
    std::cout << " =============================" << std::endl;

    int choice;
    bool flag  = true;

    while(flag)
    {
        if (!(std::cin >> choice)) // number pressed? => no
        {
            // Input is not a number
            std::cin.clear();
            while (std::cin.get() != '\n')
                continue;
            // Give user feedback that only numbers as displayed are allowed
            std::cout << "Only number 1, 2 or 3 as input allowed. Please try again" << std::endl;
        }
        else
        // Input is a number, proof if in between 1 to 3
        if ((choice < 1) || (choice > 3))
        {
            std::cout << "Only number 1, 2 or 3 as input allowed. Please try again" << std::endl;
                continue;
        }
        else 
        {
            flag = false;
        }
    }    
    switch (choice)
    {
        case 1: // start the game
        {
            _gameSatusFlag = play;
        };
        break;

        case 2: // display high scores
        {
            Scores highScores;
            highScores.printScores();
            _gameSatusFlag = score;
        };
        break;

        case 3: 
        {
            std::cout << std::endl << "Snake Game terminated successfully!" << std::endl;
            _gameSatusFlag = quit;
        };
    }
}


GameStatus UserInterface::GetGameStatus()
{
    return _gameSatusFlag;
}