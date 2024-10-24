//Qusay Edkymish
//Oct/16th/2024
//BattleShip Game Project Final Step#


#include <iostream>
#include <cctype>
#include <ctime>  //For time()
#include "ChessBoard.h" //Include the ChessBoard Class
#include "Ship.h"       //Include the Ship Class
using namespace std;

//Function Prototype
bool getPosition(int& row, int& col);
void displayHeader();

//main function
int main()
{
    //Header display
    displayHeader();

    //Instuctions
    cout << "Please enter your moves in the format of a letter for the column (A-J) followed by a number for the row (1-10). Or enter Quit to end the game\n";
    cout << "For example, 'B4' or 'A10' or 'quit'.\n\n";

    //Random number generator
    srand(time(0));

    ChessBoard board;

    //Create the ships
    Ship frigate("Frigate", 2, 'F');
    Ship submarine("Submarine", 3, 'S');
    Ship destroyer("Destroyer", 3, 'D');
    Ship battleship("Battleship", 4, 'B');
    Ship aircraftCarrier("Aircraft Carrier", 5, 'A');

    //Place the ships 
    board.placeShip(frigate);
    board.placeShip(submarine);
    board.placeShip(destroyer);
    board.placeShip(battleship);
    board.placeShip(aircraftCarrier);

    int row, col;
    int consecutiveMisses = 15;

    while (true)
    {
        //Get user input for position
        if (!getPosition(row, col))
        {
            if (row == -1 && col == -1)
            {
                cout << "\nThanks for playing! Goodbye!\n";
                board.displayBoard(true);  //Show full board before exiting
                break;
            }
            else
            {
                continue;  //Invalid input, retry
            }
        }


        //Ensure valid row/col range
        if (row < 0 || row >= 10 || col < 0 || col >= 10)
        {
            cout << "Invalid input range. Please try again.\n";
            continue; //Skip processing if input is invalid
        }

        //Process hit or miss at the given position (row, col)
        bool isHit = board.hitOrMiss(row, col);

        if (isHit)
        {
            consecutiveMisses = 15; //Reset miss counter on a hit
        }
        else
        {
            consecutiveMisses--; //Increment miss counter
            cout << "Remaining tries: " << consecutiveMisses << "\n\n"; //Display misses
            if (consecutiveMisses == 0)
            {
                cout << "You missed 15 times in a row. Game over!\n";
                board.displayBoard(true);
                break;
            }
        }

        //Check if all ships have been destroyed
        if (board.getRemainingShips() == 0)
        {
            cout << "\nCongratulations! You have destroyed all the ships!\n";
            board.displayBoard(true);
            break;
        }

        //Display the updated board
        board.displayBoard(false);
    }

    return 0;
}


//Position Input Function
bool getPosition(int& row, int& col)
{
    string input;
    cout << "Enter position: ";
    cin >> input;

    //Convert input to uppercase for consistency
    for (char& c : input) c = toupper(c);

    //Check if the user wants to quit
    if (input == "QUIT")
    {
        //Special Value of row and col to end the game.
        row = -1;
        col = -1;
        return false; // End the game
    }

    // Input validation: must be 2 or 3 characters (e.g., B4 or B10)
    if (input.length() < 2 || input.length() > 3)
    {
        cout << "Invalid input. Please try again.\n";
        return false;  //Indicate invalid input, no further processing
    }

    // Check if the first character is a valid column letter (A-J)
    char colChar = input[0];
    if (colChar < 'A' || colChar > 'J')
    {
        cout << "Invalid column. Please enter a letter between A and J.\n";
        return false;  // Indicate invalid input, no further processing
    }

    // Check if the remaining characters are digits and within the valid range (1-10)
    string rowStr = input.substr(1);
    for (char digit : rowStr)
    {
        if (!isdigit(digit))  // If any character is not a digit
        {
            cout << "Invalid row number. Please enter a valid number between 1 and 10.\n";
            return false;  // Indicate invalid input, no further processing
        }
    }

    // Convert rowStr to an integer and check if it's within the range 1-10
    int rowNum = stoi(rowStr);
    if (rowNum < 1 || rowNum > 10)
    {
        cout << "Invalid row. Please enter a number between 1 and 10.\n";
        return false;  // Indicate invalid input, no further processing
    }

    // If all checks pass, convert valid input to row and column (zero-indexed)
    col = colChar - 'A';  // 'A' is 0, 'J' is 9
    row = rowNum - 1;     // 1-10 becomes 0-9

    return true; // Valid input, continue game
}

//Header Function
void displayHeader()
{
    cout << "===============================" << endl;
    cout << "   Welcome to BattleShip Game   " << endl;
    cout << "===============================" << endl;
    cout << "       By Qusay Edkymish      " << endl;
    cout << endl;

    //ASCII Art of a battleship
    cout << "        __/___                 " << endl;
    cout << "  _____/______|                " << endl;
    cout << "  \\____________\\______________ " << endl;
    cout << "  /_/_/\\  /_/_/                " << endl;
    cout << "  \"   \"\"  \"   \"                 " << endl;
    cout << "===============================" << endl;
    cout << endl;

    //Game starting
    cout << "Press any key to start the game..." << endl;
    cin.ignore();  //Wait for user input to continue
}