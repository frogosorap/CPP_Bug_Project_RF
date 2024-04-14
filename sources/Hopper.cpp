//
// Created by Raphael Frogoso on 13/04/2024.
//
#include <iostream>
#include "../headers/Hopper.h"

Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength) {
    this -> id = id;
    Pair pair(x,y);
    this -> position = pair;
    this -> direction = dir;
    this -> size = size;
    this -> isAlive = true;
    this -> hopLength = hopLength;
}

void Hopper::move() {
    if (getIsWayBlocked())
    {
        int randDirection = rand() % 4;
        switch (randDirection)
        {
            case 0:
                setDirection(Direction::NORTH);
                break;
            case 1:
                setDirection(Direction::SOUTH);
                break;
            case 2:
                setDirection(Direction::EAST);
                break;
            case 3:
                setDirection(Direction::WEST);
                break;
        }
    }
    else
    {
        Pair newPos = getPosition();
        int hopLength = rand() % 3 + 2; // Random hop length between 2 and 4

        // Add newPos to the current direction and hopLength
        switch(getDirection())
        {
            case Direction::NORTH:
                newPos.setY(newPos.getY() - hopLength); // Hop up
                break;
            case Direction::SOUTH:
                newPos.setY(newPos.getY() + hopLength); // Hop down
                break;
            case Direction::EAST:
                newPos.setX(newPos.getX() + hopLength); // Hop right
                break;
            case Direction::WEST:
                newPos.setX(newPos.getX() - hopLength); // Hop left
                break;
        }

        // Check if the newPos will hit a wall or pass a wall
        if (newPos.getX() < 0 || newPos.getX() >= 10 || newPos.getY() < 0 || newPos.getY() >= 10)
        {
            // If hop hits the edge, set a new random direction
            int randDirection = rand() % 4;
            switch (randDirection)
            {
                case 0:
                    setDirection(Direction::NORTH);
                    break;
                case 1:
                    setDirection(Direction::SOUTH);
                    break;
                case 2:
                    setDirection(Direction::EAST);
                    break;
                case 3:
                    setDirection(Direction::WEST);
                    break;
            }
        }
        else
        {
            setPosition(newPos); // Update the new position newPos
        }
    }
}

void Hopper::displayBugDetails() {

    cout << "Hopper, ID: " + to_string(id) + ", Position (" +to_string(position.getX()) + ", "
            +to_string(position.getY()) + ")" + ", Size: " + to_string(size) + ", Direction: " +
            directionString(direction) + ", Hop Length: " + to_string(hopLength);
    if (isAlive)
    {
        cout << ", Alive.";
    }
    else
    {
        cout << ", Dead.";
    }

}