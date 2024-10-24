//Qusay Edkymish
//Oct/16th/2024
//Class representing a ship on the board

#ifndef SHIP_H
#define SHIP_H

#include <string>
using namespace std;

class Ship
{
public:
    string name;       //Name of the ship (e.g., Destroyer, Battleship)
    int size;          //Size of the ship (number of parts)
    char symbol;       //Symbol representing the ship on the board
    bool isVertical;   //Direction of the ship (vertical or horizontal)
    bool hasBeenHit;   //Flag to check if the ship has been hit for the first time
    int row, col;

    //Constructor
    Ship(const string &shipName, int s, char sym);

};

#endif //!SHIP_H