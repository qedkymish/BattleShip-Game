//Qusay Edkymish
//Oct/16th/2024
//Ship Class

#include "Ship.h"
#include <iostream>
using namespace std;

//Constructor
Ship::Ship(const string &shipName, int s, char sym) : name(shipName), size(s), symbol(sym), isVertical(true), row(0), col(0), hasBeenHit(false) {}