//
// Created by Raphael Frogoso on 11/04/2024.
//
#include <iostream>
#include "../headers/Bug.h"
using namespace std;

int Bug::getID() const{
    return id;
}

int Pair::getX() const{
    return x;
}

int Pair::getY() const{
    return y;
}

const Pair &Bug::getPosition() const {
    return position;
}

bool Bug::getIsWayBlocked() const {
    return isWayBlocked();
}


Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return size;
}

bool Bug::getIsAlive() const {
    return isAlive;
}


const list<Pair> &Bug::getPath() const {
    return path;
}

void Bug::setID(int Id) {
    Bug::id = Id;
}

void Bug::setDirection(Direction dir) {
    Bug::direction = dir;
}

void Bug::setSize(int size) {
    Bug::size = size;
}

void Bug::setIsAlive(bool alive) {
    Bug::isAlive = alive;
}

void Bug::setPosition(const Pair &position) {
    Bug::position = position;
}

bool Bug::isWayBlocked() const {
    // Get current position of the bug
    Pair currentPosition = getPosition();

    // Check if current position is out of bounds based on direction
    switch (getDirection())
    {
        case Direction::NORTH:
            if (currentPosition.getY() <= 0)
            {
                return true; // If bug is facing north, it checks if its current Y coordinate is less than or equal to 0.
            }
            break;
        case Direction::SOUTH:
            if (currentPosition.getY() >= 9)
            {
                return true; // // If bug is facing north, it checks if its current Y coordinate is less than or equal to 10.
            }
            break;
        case Direction::EAST:
            if (currentPosition.getX() >= 9)
            {
                return true; // If bug is facing north, it checks if its current X coordinate is less than or equal to 10.
            }
            break;
        case Direction::WEST:
            if (currentPosition.getX() <= 0)
            {
                return true; // If bug is facing north, it checks if its current X coordinate is less than or equal to 0.
            }
            break;
    }

    return false; // If bug path is not blocked
}

const list<Pair> &Bug::getPathHistory() const {
    return pathHistory;
}

void Bug::updatePathHistory() {
    pathHistory.push_back(getPosition());
}

int Bug::getEatenBy() const {
    return eatenBy;
}

void Bug::setEatenBy(int id) {
    eatenBy = id;
}

string Bug::getTypeOfBug() const {
    return typeOfBug;
}

void Bug::setTypeOfBug(const string& type) {
    typeOfBug = type;
}