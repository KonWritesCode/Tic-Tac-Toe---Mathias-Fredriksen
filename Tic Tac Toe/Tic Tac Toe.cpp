//Written by Mathias Fredriksen
//Thanks to Sten Rune Lyngmo for finding a simpler solution for coloring text in the console
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::string ticTac[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; //Decides wether it should be an X, O or an number at the different positions on the board
int colorCode[9] = {37, 37, 37, 37, 37, 37, 37, 37, 37}; //Decides the color of each tictac

std::vector<int> previouslyChosenNumbers; //Contains data of all the previously chosen numbers between each game

int playerAmount;
int chosenNumber;

int playerTurn; //Player one's turn = 0, Player Two's turn = 1
bool gameEnded;

//AI
int difficultyAI;

std::string colorText(std::string text, int textColor) {

    // https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    // Grey = 37, Red 91, Green = 92, Yellow 93, White = 97

    return "\033[" + std::to_string(textColor) + 'm' + text + "\033[0m";
}

void opponentAI()
{
    if (difficultyAI == 0) //Easy mode
    {
        //In Easy mode, the AI will just randomly place in an empty space.
        //The AI should be quite easy to beat since the AI won't try to win or stop the player on purpose.

        //Randomly choose a number betwen 1 and 9
        srand(time(NULL));
        chosenNumber = rand() % 9+1;

        //Check if the number has already been taken before
        while (std::count(previouslyChosenNumbers.begin(), previouslyChosenNumbers.end(), chosenNumber) == true)
        {
            chosenNumber = rand() % 9 + 1;
        }

        previouslyChosenNumbers.emplace_back(chosenNumber);
        --chosenNumber;
        ticTac[chosenNumber] = "O";
        colorCode[chosenNumber] = 97;

        playerTurn = 0;
    }
    else if(difficultyAI == 1) //Normal Mode
    {
        //On Normal Mode the AI will prioritze instead of just placing randomly.
        //The AI should be somewhat difficult to beat, as it now has a list of priorites

        //The order of how the AI prioritizes:
        //1. Check if it's possible for the AI to win on its next move
        //2. Check if it's possible to stop the opponent from getting 3 in a row
        //3. Make a random move

        bool hasChosenNumberAI{ false };
        std::string O_or_X;
        
        //The AI looks for anywhere it can place to win by getting 3 in a row.
        //If the AI can't win durring it's next move, it will instead see if it can stop the player from getting 3 in a row.
        for (int k = 0; k <= 1 && !hasChosenNumberAI; k++) 
        {
            if (k == 0)
            {
                O_or_X = "O";
            }
            else if (k == 1)
            {
                O_or_X = "X";
            }

            //Horizontal Lines
            for (int i = 0; i <= 6 && !hasChosenNumberAI; i += 3)
            {
                if (ticTac[i] == ticTac[i + 1] && ticTac[i] == O_or_X && ticTac[i+2] == std::to_string(i+3) || ticTac[i + 1] == ticTac[i + 2] && ticTac[i+1] == O_or_X && ticTac[i] == std::to_string(i+1) || ticTac[i] == ticTac[i + 2] && ticTac[i] == O_or_X && ticTac[i + 1] == std::to_string(i + 2) )
                {
                    int j{i};
                    while (ticTac[j] == O_or_X)
                    {
                        j += 1;
                    }
                    chosenNumber = j;
                    ++chosenNumber;
                    previouslyChosenNumbers.emplace_back(chosenNumber);
                    --chosenNumber;

                    ticTac[chosenNumber] = "O";
                    colorCode[chosenNumber] = 97;

                    playerTurn = 0;
                    hasChosenNumberAI = true;
                }
            }
            //Vertical Lines
            for (int i = 0; i <= 2 && !hasChosenNumberAI; i++)
            {
                if (ticTac[i] == ticTac[i + 3] && ticTac[i + 6] == std::to_string(i + 7) && ticTac[i] == O_or_X || ticTac[i + 3] == ticTac[i + 6] && ticTac[i] == std::to_string(i + 1) && ticTac[i + 3] == O_or_X || ticTac[i] == ticTac[i + 6] && ticTac[i + 3] == std::to_string(i + 4) && ticTac[i] == O_or_X)
                {
                    int j{ i };
                    //Checks which of the three areas in the lane there is an empty place
                    while (ticTac[j] == O_or_X)
                    {
                        j += 3;
                    }
                    chosenNumber = j;
                    ++chosenNumber;
                    previouslyChosenNumbers.emplace_back(chosenNumber);
                    --chosenNumber;

                    ticTac[chosenNumber] = "O";
                    colorCode[chosenNumber] = 97;

                    playerTurn = 0;
                    hasChosenNumberAI = true;
                }
            }
            if (!hasChosenNumberAI)
            {
                //Diagonal Top Left - Bottom Right
                if (ticTac[0] == ticTac[4] && ticTac[8] == "9" && ticTac[0] == O_or_X || ticTac[4] == ticTac[8] && ticTac[0] == "1" && ticTac[4] == O_or_X || ticTac[0] == ticTac[8] && ticTac[4] == "5" && ticTac[0] == O_or_X)
                {
                    int j{ 0 };
                    //Checks which of the three areas in the lane there is an empty place
                    while (ticTac[j] == O_or_X)
                    {
                        j += 4;
                    }
                    chosenNumber = j;
                    ++chosenNumber;
                    previouslyChosenNumbers.emplace_back(chosenNumber);
                    --chosenNumber;

                    ticTac[chosenNumber] = "O";
                    colorCode[chosenNumber] = 97;

                    playerTurn = 0;
                    hasChosenNumberAI = true;
                }
                else //Diagonal Top Right - Bottom Left
                if (ticTac[2] == ticTac[4] && ticTac[6] == "7" && ticTac[2] == O_or_X || ticTac[4] == ticTac[6] && ticTac[2] == "3" && ticTac[4] == O_or_X || ticTac[2] == ticTac[6] && ticTac[4] == "5" && ticTac[2] == O_or_X)
                {
                    int j{ 2 };
                    //Checks which of the three areas in the lane there is an empty place
                    while (ticTac[j] == O_or_X)
                    {
                        j += 2;
                    }
                    chosenNumber = j;
                    ++chosenNumber;
                    previouslyChosenNumbers.emplace_back(chosenNumber);
                    --chosenNumber;

                    ticTac[chosenNumber] = "O";
                    colorCode[chosenNumber] = 97;

                    playerTurn = 0;
                    hasChosenNumberAI = true;
                }
            }
        }
        //Choose a random location if,
        //The AI hasn't found anywhere it can place to win by getting 3 in a row, or to block the player from getting 3 in a row.
        if(!hasChosenNumberAI)
        {
            //Randomly choose a number betwen 1 and 9
            srand(time(NULL));
            chosenNumber = rand() % 9 + 1;

            //Check if the number has already been taken before
            while (std::count(previouslyChosenNumbers.begin(), previouslyChosenNumbers.end(), chosenNumber) == true)
            {
                chosenNumber = rand() % 9 + 1;
            }

            previouslyChosenNumbers.emplace_back(chosenNumber);
            --chosenNumber;
            ticTac[chosenNumber] = "O";
            colorCode[chosenNumber] = 97;

            playerTurn = 0;
            hasChosenNumberAI = true;
        }

        //Reset at the end of the loop
        hasChosenNumberAI = false;
    }
}

void drawBoard() 
{
    std::cout << colorText("<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n", 33);
    std::cout << "\t| " + colorText(ticTac[0], colorCode[0]) + " | " + colorText(ticTac[1], colorCode[1]) + " | " + colorText(ticTac[2], colorCode[2]) + " |\n";
    std::cout << "\t| " + colorText(ticTac[3], colorCode[3]) + " | " + colorText(ticTac[4], colorCode[4]) + " | " + colorText(ticTac[5], colorCode[5]) + " |\n";
    std::cout << "\t| " + colorText(ticTac[6], colorCode[6]) + " | " + colorText(ticTac[7], colorCode[7]) + " | " + colorText(ticTac[8], colorCode[8]) + " |\n";
    std::cout << "\n";
    std::cout << colorText("<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n", 33);
}

void winConditions()
{
    //If one of the players won, the Win color is green. If the AI wins, the color is red 
    int color;
    if (playerTurn == 0 && playerAmount == 1) 
    {
        color = 91;
    }
    else 
    {
        color = 92;
    }

    //Checks if there are three tictacs (of the same type) in all the different lines

    //Horizontal Lines
    for (int i = 0; i <= 6; i += 3)
    {
        if (ticTac[i] == ticTac[i + 1] && ticTac[i + 1] == ticTac[i + 2])
        {
            colorCode[i] = color;
            colorCode[i + 1] = color;
            colorCode[i + 2] = color;

            gameEnded = true;
        }
    }
    //Vertical Lines
    for(int i = 0; i <= 2; i++)
    {
        if(ticTac[i] == ticTac[i + 3] && ticTac[i + 3] == ticTac[i + 6])
        {
            colorCode[i] = color;
            colorCode[i + 3] = color;
            colorCode[i + 6] = color;

            gameEnded = true;
        }
    }
    //Diagonal line Top Left - Bottom Right
    if (ticTac[0] == ticTac[4] && ticTac[4] == ticTac[8])
    {
        colorCode[0] = color;
        colorCode[4] = color;
        colorCode[8] = color;

        gameEnded = true;
    }
    //Diagonal line Top Right - Bottom Left
    if (ticTac[2] == ticTac[4] && ticTac[4] == ticTac[6])
    {
        colorCode[2] = color;
        colorCode[4] = color;
        colorCode[6] = color;

        gameEnded = true;
    }
}

int main()
{
    std::string player1_Name;
    std::string player2_Name;

    //Introduction
    std::cout << colorText("Welcome to ", 97) << colorText("Tic-Tac-Toe", 93) << colorText("!\n", 97) << std::endl;

    //Singleplayer or multiplayer
    std::cout << "Choose the amount of players ('" << colorText("1", 97) << "' or '" << colorText("2", 97) << "'): ";
    std::cin >> playerAmount;

    while (std::cin.fail() || playerAmount <= 0 || playerAmount > 2)
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Choose the amount of players ('" << colorText("1", 97) << "' or '" << colorText("2", 97) << "'): ";
        std::cin >> playerAmount;
    }

    std::cin.clear();
    std::cin.ignore(32767, '\n');

    //Ask for the players names (And AI difficulty if Singleplayer mode)
    if (playerAmount == 1) 
    {
        //Choose AI difficulty
        std::string difficulty;
        std::cout << "Choose the AI difficulty (Type 'Easy' or 'Normal'): ";
        std::getline(std::cin, difficulty);

        while (std::cin.fail() || difficulty != "Easy" && difficulty != "Normal")
        {
            std::cout << "Choose the AI difficulty (Type 'Easy' or 'Normal'): ";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cin >> difficulty;
        }

        if(difficulty == "Easy")
        {
            difficultyAI = 0;
        }
        else if(difficulty == "Normal")
        {
            difficultyAI = 1;
        }

        std::cin.clear();
        std::cin.ignore(32767, '\n');

        //Ask for the player name
        std::cout << colorText("Player 1", 91) << ", please enter your name: ";
        std::getline(std::cin, player1_Name);
    }
    else if(playerAmount == 2)
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');

        std::cout << colorText("Player 1", 91) << ", please enter your name: ";
        std::getline(std::cin, player1_Name);
        std::cout << "\n" << colorText("Player 2", 91) << ", please enter your name: ";
        std::getline(std::cin, player2_Name);
    }


start: //Starting point when the game restarts

    system("cls");

    //Randomly decides which player that starts
    srand(time(NULL));
    playerTurn = rand() % 2;

    //Gameplay
    while(!gameEnded && previouslyChosenNumbers.size() < 9)
    {
        drawBoard();

        if (playerTurn == 0) //Player 1
        {
            std::cout << colorText(player1_Name, 91) << ", it's your turn!\n\n";
            std::cout << "Enter the number of where you'd like to place an " << colorText("X", 93) << ": ";
            std::cin >> chosenNumber;

            while (std::cin.fail() || chosenNumber <= 0 || chosenNumber > 9 || std::count(previouslyChosenNumbers.begin(), previouslyChosenNumbers.end(), chosenNumber) == true)
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Error, please type a number between 1 and 9, that hasn't yet been taken: ";
                std::cin >> chosenNumber;
            }
            std::cin.clear();
            std::cin.ignore(32767, '\n');

            previouslyChosenNumbers.emplace_back(chosenNumber);
            --chosenNumber;
            ticTac[chosenNumber] = "X";
            colorCode[chosenNumber] = 97;

            playerTurn = 1;
        }
        else if (playerTurn == 1 && playerAmount == 2) //Player 2
        {
            std::cout << colorText(player2_Name, 91) << ", it's your turn!\n\n";
            std::cout << "Enter the number of where you'd like to place an " << colorText("O", 93) << ": ";
            std::cin >> chosenNumber;

            while (std::cin.fail() || chosenNumber <= 0 || chosenNumber > 9 || std::count(previouslyChosenNumbers.begin(), previouslyChosenNumbers.end(), chosenNumber) == true) 
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Error, please type a number between 1 and 9, that hasn't yet been taken: ";
                std::cin >> chosenNumber;
            }
            std::cin.clear();
            std::cin.ignore(32767, '\n');

            previouslyChosenNumbers.emplace_back(chosenNumber);
            --chosenNumber;
            ticTac[chosenNumber] = "O";
            colorCode[chosenNumber] = 97;

            playerTurn = 0;
        }
        else if(playerTurn == 1 && playerAmount == 1) //AI
        {
            opponentAI();
        }

        winConditions();

        system("cls");
    }

    //Tie
    if (previouslyChosenNumbers.size() >= 9 && !gameEnded) 
    {
        system("cls");
        drawBoard();
        std::cout << colorText("It's a tie!\n", 93);
    }
    else if(gameEnded && playerAmount == 2) //Victory (2 players)
    {
        system("cls");
        drawBoard();

        //NB: playerTurn is flipped for this part
        if (playerTurn == 1)
        {
            std::cout << colorText("Congratulations ", 92) << player1_Name << colorText("! You Win!", 92) << std::endl;
        }
        else {
            std::cout << colorText("Congratulations ", 92) << player2_Name << colorText("! You Win!", 92) << std::endl;
        }
    }
    else if(gameEnded && playerAmount == 1) //Victory or Failure (Single Player)
    {
        system("cls");
        drawBoard();

        //NB: playerTurn is flipped for this part
        if (playerTurn == 1)
        {
            std::cout << colorText("Congratulations ", 92) << player1_Name << colorText("! You Win!", 92) << std::endl;
        }
        else {
            std::cout << colorText("Too bad ", 91) << player1_Name << colorText("! You Lost!", 91) << std::endl;
        }
    }

    //Ask the player to Restart or Quit
    char playerInput;
    std::cout << "\nType 'R' to restart or '0' to quit: ";
    std::cin >> playerInput;

    while (std::cin.fail() || playerInput != 'r' && playerInput != 'R' && playerInput != '0')
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Type 'R' to restart or '0' to quit: ";
        std::cin >> playerInput;
    }

    //Restart
    if(playerInput == 'r' || playerInput == 'R')
    {
        previouslyChosenNumbers.clear();
        for(int i = 0; i < 9; i++)
        {
            colorCode[i] = 37;
            ticTac[i] = std::to_string(i + 1);
        }
        gameEnded = false;

        goto start;
    }
    //Quit
    else
    {
        exit(0);
    }
}
