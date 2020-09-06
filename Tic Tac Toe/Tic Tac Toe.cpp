//Written by Mathias Fredriksen
//Thanks to Sten Rune Lyngmo for finding a simpler solution for coloring text in the console
#include <iostream>
#include <string>
#include <stdlib.h>


std::string ticTac[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; //Decides wether it should be an X, O or an number at the different positions on the board
int colorCode[] = {37, 37, 37, 37, 37, 37, 37, 37, 37}; //Decides the color of each
int chosenNumber;

int playerTurn; //Player one's turn = 0, Player Two's turn = 1
bool gameEnded;

std::string colorText(std::string text, int textColor) {

    // https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    // Green = 92, White = 97, Grey = 37

    return "\033[" + std::to_string(textColor) + 'm' + text + "\033[0m";
}

void drawBoard() 
{
    std::cout << colorText("<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n", 97);
    std::cout << "\t| " + colorText(ticTac[0], colorCode[0]) + " | " + colorText(ticTac[1], colorCode[1]) + " | " + colorText(ticTac[2], colorCode[2]) + " |\n";
    std::cout << "\t| " + colorText(ticTac[3], colorCode[3]) + " | " + colorText(ticTac[4], colorCode[4]) + " | " + colorText(ticTac[5], colorCode[5]) + " |\n";
    std::cout << "\t| " + colorText(ticTac[6], colorCode[6]) + " | " + colorText(ticTac[7], colorCode[7]) + " | " + colorText(ticTac[8], colorCode[8]) + " |\n";
    std::cout << "\n";
    std::cout << colorText("<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n", 97);
}

void winConditions()
{
    //Vertical Line Left
    if (ticTac[0] == "X" && ticTac[3] == "X" && ticTac[6] == "X" || ticTac[0] == "O" && ticTac[3] == "O" && ticTac[6] == "O")
    {
        colorCode[0] = 92;
        colorCode[3] = 92;
        colorCode[6] = 92;

        gameEnded = true;
    }
    //Vertical line Middle
    if (ticTac[1] == "X" && ticTac[4] == "X" && ticTac[7] == "X" || ticTac[1] == "O" && ticTac[4] == "O" && ticTac[7] == "O")
    {
        colorCode[1] = 92;
        colorCode[4] = 92;
        colorCode[7] = 92;

        gameEnded = true;
    }
    //Vertical line Right
    if (ticTac[2] == "X" && ticTac[5] == "X" && ticTac[8] == "X" || ticTac[2] == "O" && ticTac[5] == "O" && ticTac[8] == "O")
    {
        colorCode[2] = 92;
        colorCode[5] = 92;
        colorCode[8] = 92;

        gameEnded = true;
    }
    //Horizontal line Top
    if (ticTac[0] == "X" && ticTac[1] == "X" && ticTac[2] == "X" || ticTac[0] == "O" && ticTac[1] == "O" && ticTac[2] == "O")
    {
        colorCode[0] = 92;
        colorCode[1] = 92;
        colorCode[2] = 92;

        gameEnded = true;
    }
    //Horizontal line Middle
    if (ticTac[3] == "X" && ticTac[4] == "X" && ticTac[5] == "X" || ticTac[3] == "O" && ticTac[4] == "O" && ticTac[5] == "O")
    {
        colorCode[3] = 92;
        colorCode[4] = 92;
        colorCode[5] = 92;

        gameEnded = true;
    }
    //Horizontal line Bottom
    if (ticTac[6] == "X" && ticTac[7] == "X" && ticTac[8] == "X" || ticTac[6] == "O" && ticTac[7] == "O" && ticTac[8] == "O")
    {
        colorCode[6] = 92;
        colorCode[7] = 92;
        colorCode[8] = 92;

        gameEnded = true;
    }
    //Diagonal line Top Left - Bottom Right
    if (ticTac[0] == "X" && ticTac[4] == "X" && ticTac[8] == "X" || ticTac[0] == "O" && ticTac[4] == "O" && ticTac[8] == "O")
    {
        colorCode[0] = 92;
        colorCode[4] = 92;
        colorCode[8] = 92;

        gameEnded = true;
    }
    //Diagonal line Bottom Left - Top Right
    if (ticTac[6] == "X" && ticTac[4] == "X" && ticTac[2] == "X" || ticTac[6] == "O" && ticTac[4] == "O" && ticTac[2] == "O")
    {
        colorCode[6] = 92;
        colorCode[4] = 92;
        colorCode[2] = 92;

        gameEnded = true;
    }
}

int main()
{
    std::string player1_Name;
    std::string player2_Name;

    //Introduction
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    std::cout << "Player 1, please enter your name: ";
    std::getline(std::cin, player1_Name);
    std::cout << "Great! Player 2, please enter your name: ";
    std::getline(std::cin, player2_Name);

    system("cls");


    //Decide which player that starts
    playerTurn = rand() % 1;

    //Gameplay
    while(!gameEnded)
    {
        drawBoard();
        
        if (playerTurn == 0) //Player 1
        {
            std::cout << colorText(player1_Name, 91) << ", it's your turn!\n";
            std::cout << "Enter the number of where you'd like to place an " << colorText("X", 93) << ": ";
            std::cin >> chosenNumber;

            while (std::cin.fail() || chosenNumber <= 0 || chosenNumber > 9) //ADD Already chosen numbers
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Error, please type a number between 1 and 9, that hasn't yet been taken: ";
                std::cin >> chosenNumber;
            }
            --chosenNumber;

            std::cin.clear();
            std::cin.ignore(32767, '\n');
            ticTac[chosenNumber] = "X";
            colorCode[chosenNumber] = 97;

            playerTurn = 1;
        }
        else if (playerTurn == 1) //Player 2
        {
            std::cout << colorText(player2_Name, 91) << ", it's your turn!\n";
            std::cout << "Enter the number of where you'd like to place an " << colorText("O", 93) << ": ";
            std::cin >> chosenNumber;

            while (std::cin.fail() || chosenNumber <= 0 || chosenNumber > 9) //Reminder: Add already chosen numbers...................
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Error, please type a number between 1 and 9, that hasn't yet been taken: ";
                std::cin >> chosenNumber;
            }
            --chosenNumber;
            ticTac[chosenNumber] = "O";
            colorCode[chosenNumber] = 97;

            playerTurn = 0;
        }

        winConditions();

        system("cls");
    }

    //Victory
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

    return 0;
}
