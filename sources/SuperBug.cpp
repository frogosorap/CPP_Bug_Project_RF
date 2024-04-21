//
// Created by Raphael Frogoso on 20/04/2024.
//
//
// Created by Raphael Frogoso on 13/04/2024.
//


#include <random>
#include <string>
#include <list>
#include <iostream>
#include "../headers/SuperBug.h"

using namespace std;

SuperBug::SuperBug(int id, int x, int y, Direction dir, int size) {
    this -> id = id;
    Pair pair(x,y);
    this -> position = pair;
    this -> direction = dir;
    this -> size = size;
    this -> isAlive = true;
}


// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range  <--- Random number
void SuperBug::move() {
    if(getIsWayBlocked())
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
        setPosition(newPos); // Update the new position newPos
    }
}

void SuperBug::moveUp() {
    Pair newPos = getPosition();
    newPos.setY(newPos.getY() - 1); // One box up
    setPosition(newPos);
}

void SuperBug::moveDown() {
    Pair newPos = getPosition();
    newPos.setY(newPos.getY() + 1); // One box down
    setPosition(newPos);
}

void SuperBug::moveLeft() {
    Pair newPos = getPosition();
    newPos.setX(newPos.getX() - 1); // One box left
    setPosition(newPos);
}

void SuperBug::moveRight() {
    Pair newPos = getPosition();
    newPos.setX(newPos.getX() + 1); // One box right
    setPosition(newPos);
}

void SuperBug::displayBugDetails() {

    cout << "Super Bug, ID: " + to_string(id) + ", Position (" +to_string(position.getX()) + ", "
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

