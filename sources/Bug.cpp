//
// Created by Raphael Frogoso on 11/04/2024.
//
#include "../headers/Bug.h"


int Bug::getID() const{
    return id;
}

int Pair::getX() {
    return 0;
}

int Pair::getY() {
    return 0;
}

bool Bug::isWayBlocked() {

    return false;
}
void Bug::move() {

}

Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return 0;
}

bool Bug::getIsAlive() const {
    return false;
}

bool Bug::getIsWayBlocked() const {
    return false;
}
