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

const Pair &Bug::getPosition() const {
    return position;
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

const list<Pair> &Bug::getPath() const {
    return path;
}

void Bug::setID(int id) {
    Bug::id = id;
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





