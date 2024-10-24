//Qusay Edkymish
//Oct/16th/2024
//ChessBoard Class modified for BattleShip game. Updated


#include "ChessBoard.h"
#include <iostream>
#include <iomanip>  //For setw()
#include <cstdlib>  //For random ship placement
using namespace std;

//Constructor to initialize the board
ChessBoard::ChessBoard()
{
    resetBoard();

    //Initialize the variable to zero
    totalShips = 0;
}

//Reset the board to empty spaces (initialize with nullptr)
void ChessBoard::resetBoard()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            board[r][c] = nullptr;  // Initialize with nullptr to represent empty water
        }
    }
}

//Display the board
void ChessBoard::displayBoard(bool showShips = false)
{
    //Display total ships above the board
    cout << "Total Reamining Ships: " << totalShips << "\n\n";

    //Print column headers (A to J)
    cout << "   ";
    for (char c = 'A'; c <= 'J'; c++)
    {
        cout << setw(2) << c << " "; //Increase spacing for better alignment
    }
    cout << endl;

    //Print the board row by row
    for (int r = 0; r < ROWS; r++)
    {
        //Print row numbers (handle single and double digits)
        cout << (r + 1 < 10 ? " " : "") << r + 1 << " ";
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c] != nullptr)
            {
                if (board[r][c]->symbol == 'X' || board[r][c]->symbol == 'O')
                {
                    cout << setw(2) << board[r][c]->symbol << " ";  //Show hit or miss
                }
                else if (showShips)
                {
                    cout << setw(2) << board[r][c]->symbol << " ";  //Show ships
                }
                else
                {
                    cout << setw(2) << '~' << " ";  //Hide ships, show water
                }
            }
            else
            {
                cout << setw(2) << '~' << " ";
            }
        }
        cout << endl;
    }
}

//Process hits and misses
bool ChessBoard::hitOrMiss(int row, int col)
{
    if (board[row][col] != nullptr && board[row][col]->symbol != 'X' && board[row][col]->symbol != 'O')
    {
        //Mark the ship as hit
        cout << "\nYou hit the " << board[row][col]->name << "!\n\n";
        board[row][col]->symbol = 'X';

        Ship* hitShip = board[row][col];

        //Decrease totalShips only when the ship is hit for the first time
        if (!hitShip->hasBeenHit)
        {
            hitShip->hasBeenHit = true;  //Mark ship as hit
            totalShips--;  //Decrease the total number of ships
        }
        return true;
    }
    else if (board[row][col] == nullptr)
    {
        //Mark the ship as miss
        board[row][col] = new Ship("Water", 0, 'O');
        cout << "\nIt's a miss!\n\n";
        return false;
    }
    else
    {
        cout << "\nAlready attacked this position.\n\n";
        return false;
    }
}

//Place a ship on the board
void ChessBoard::placeShip(Ship& ship)
{
    bool placed = false;

    while (!placed)
    {
        ship.isVertical = rand() % 2;  //Randomly set the direction (vertical/horizontal)
        int row = rand() % 10;         //Random row
        int col = rand() % 10;         //Random column
        bool spaceFree = true;

        //Check if the ship can fit without going out of bounds or overlapping
        if (ship.isVertical) //Vertical placement
        {
            if (row + ship.size > ROWS) continue; //Ensure ship fits
            for (int i = 0; i < ship.size; i++)
            {
                if (board[row + i][col] != nullptr) //Check if space is occupied
                {
                    spaceFree = false;
                    break;
                }
            }
        }
        else //Horizontal placement
        {
            if (col + ship.size > COLS) continue; //Ensure ship fits
            for (int i = 0; i < ship.size; i++)
            {
                if (board[row][col + i] != nullptr) //Check if space is occupied
                {
                    spaceFree = false;
                    break;
                }
            }
        }

        //Place the ship if space is free
        if (spaceFree)
        {
            if (ship.isVertical)
            {
                for (int i = 0; i < ship.size; i++)
                {
                    board[row + i][col] = &ship;
                }
            }
            else
            {
                for (int i = 0; i < ship.size; i++)
                {
                    board[row][col + i] = &ship;
                }
            }
            totalShipParts += ship.size; //Count total ship parts
            totalShips++;  //Count total ships
            placed = true;
        }
    }
}