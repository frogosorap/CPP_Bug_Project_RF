//
// Created by Raphael Frogoso on 13/04/2024.
//
#include <iostream>
#include <vector>
#include "../headers/Hopper.h"
#include <random>

Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength) {
    this -> id = id;
    Pair pair(x,y);
    this -> position = pair;
    this -> direction = dir;
    this -> size = size;
    this -> isAlive = true;
    this -> hopLength = hopLength;
}

// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range <--- Random Number

void Hopper::move()
{
    if (getIsWayBlocked())
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 3);
        int randDirection = dist(gen);

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
//        int hopLength = rand() % 3 + 2; // Random hop length between 2 and 4

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
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, 3);
            int randDirectionE = dist(gen);
            switch (randDirectionE)
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

//
// https://gamedev.stackexchange.com/questions/179157/sdl2-c-how-to-make-enemy-move-in-random-directions <--- Hopper ignoring current direction and choose other 3 paths
//https://www.geeksforgeeks.org/static_cast-in-cpp/ <--- Use of static cast guide

//void Hopper::move() {
//    if (getIsWayBlocked()) {
//        vector<Direction> availableDirections;
//
//        // Check all directions except the current one
//        for (int i = 0; i < 4; ++i) {
//            Direction newDirection = static_cast<Direction>(i);
//            if (newDirection != getDirection()) {
//                availableDirections.push_back(newDirection);
//            }
//        }
//
//        // Randomly select one of the available directions
//        int randIndex = rand() % availableDirections.size();
//        setDirection(availableDirections[randIndex]);
//    } else {
//        Pair newPos = getPosition();
//        int hopLength = rand() % 3 + 2; // Random hop length between 2 and 4
//
//        // Add newPos to the current direction and hopLength
//        switch(getDirection()) {
//            case Direction::NORTH:
//                newPos.setY(newPos.getY() - hopLength); // Hop up
//                break;
//            case Direction::SOUTH:
//                newPos.setY(newPos.getY() + hopLength); // Hop down
//                break;
//            case Direction::EAST:
//                newPos.setX(newPos.getX() + hopLength); // Hop right
//                break;
//            case Direction::WEST:
//                newPos.setX(newPos.getX() - hopLength); // Hop left
//                break;
//        }
//
//        // Check if the newPos will hit a wall or pass a wall
//        if (newPos.getX() < 0 || newPos.getX() >= 10 || newPos.getY() < 0 || newPos.getY() >= 10) {
//            // If hop hits the edge, set a new random direction
//            int randDirection = rand() % 4;
//            setDirection(static_cast<Direction>(randDirection));
//        } else {
//            setPosition(newPos); // Update the new position newPos
//        }
//    }
//}

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