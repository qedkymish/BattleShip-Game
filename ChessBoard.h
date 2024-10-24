//Qusay Edkymish
//Oct/16th/2024
//ChessBoard Class modified for BattleShip game. Updated


#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Ship.h"

class ChessBoard
{
private:
    static const int ROWS = 10; //Number of rows on the board
    static const int COLS = 10; //Number of columns on the board
    Ship* board[ROWS][COLS];    //Change board to store pointers to Ship objects
    int hitCount;               //Total number of successful hits
    int totalShipParts;         //Total number of ship parts (used to end the game)
    int totalShips;             //Number of whole ships remaining

public:
    ChessBoard();                                    //Constructor
    void displayBoard(bool showShips);               //Displays the board
    void resetBoard();                               //Resets the board
    bool hitOrMiss(int row, int col);                //Process hit or miss
    void placeShip(Ship& ship);                      //Places a ship on the board
    int getRemainingShips() const { return totalShips; } //Return total ships
};

#endif //!CHESSBOARD_H