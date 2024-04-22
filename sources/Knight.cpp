//
// Created by Raphael Frogoso on 18/04/2024.
//


#include <random>
#include <string>
#include <list>
#include <iostream>
#include "../headers/Knight.h"

using namespace std;

Knight::Knight(int id, int x, int y, Direction dir, int size) {
    this -> id = id;
    Pair pair(x,y);
    this -> position = pair;
    this -> direction = dir;
    this -> size = size;
    this -> isAlive = true;
}


// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range  <--- Random number
// https://stackoverflow.com/questions/30540078/using-c-rand-to-get-random-directions-up-down-left-right-always-getting <--- static_cast with the use of rand numbers
// For my new Bug type I have introduced the same method as I did for my crawler, only difference is that each box that my knight bug
// hops to, it can either go on in any direction, meaning that is completely random and unpredictable.

void Knight::move()
{
    if(getIsWayBlocked())
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 3);
        int randDirection = dist(gen);

        setDirection(static_cast<Direction>(randDirection)); // Set a random direction
    }
    else
    {
        Pair newPos = getPosition();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 3);
        int randDirection = dist(gen);

        // Converts the randDirection integer to one of the values of my enum direction
        setDirection(static_cast<Direction>(randDirection)); // Set a random direction

        switch(getDirection())
        {
            case Direction::NORTH:
                newPos.setY(newPos.getY() - 1); // One box up
                break;
            case Direction::SOUTH:
                newPos.setY(newPos.getY() + 1); // One box down
                break;
            case Direction::EAST:
                newPos.setX(newPos.getX() + 1); // One box right
                break;
            case Direction::WEST:
                newPos.setX(newPos.getX() - 1); // One box left
                break;
        }

        // Check if the new position will hit a wall between 0 and 9
        if (newPos.getX() < 0 || newPos.getX() > 9 || newPos.getY() < 0 || newPos.getY() > 9)
        {
            // If possibly hitting a wall, set a new random direction
            randDirection = dist(gen);
            setDirection(static_cast<Direction>(randDirection));
        }
        else
        {
            setPosition(newPos); // Update the new position newPos
        }
    }
}

void Knight::displayBugDetails() {

    cout << "Knight, ID: " + to_string(id) + ", Position (" +to_string(position.getX()) + ", "
            +to_string(position.getY()) + ")" + ", Size: " + to_string(size) + ", Direction: " +
            directionString(direction);
    if (isAlive)
    {
        cout << ", Alive.";
    }
    else
    {
        cout << ", Dead.";
    }
}

