//
// Created by Raphael Frogoso on 13/04/2024.
//


#include <random>
#include <string>
#include <list>
#include <iostream>
#include "../headers/Crawler.h"

using namespace std;

Crawler::Crawler(int id, int x, int y, Direction dir, int size) {
    this -> id = id;
    Pair pair(x,y);
    this -> position = pair;
    this -> direction = dir;
    this -> size = size;
    this -> isAlive = true;
}

void Crawler::move() {
    if(getIsWayBlocked())
    {
        int randDirection = rand()%4;
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

