//
// Created by Raphael Frogoso on 11/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_BUG_H
#define CPP_BUG_PROJECT_RF_BUG_H

#include <list>
#include "Direction.h"
#include <string>

using namespace std;

struct Pair{

    int x; int y;

    Pair(int xP, int yP)
    {
        x = xP;
        y = yP;
    }
    // Pair Getters

    int getX() const;
    int getY() const;

    // Pair Setters

    void setX(int xS)
    {
        x = xS;
    }
    void setY(int yS)
    {
        y = yS;
    }

};

class Bug {
    //    list<pair<int,int>> path;
    list<Pair> path;

    bool isWayBlocked() const;

    virtual void move()=0;

public:
    int id;
//    pair<int, int> position;
    Pair position = Pair(0,0);
    Direction direction;
    int size;
    bool isAlive;

    // Getters

    int getID() const;
    Direction getDirection() const;
    int getSize() const;
    bool getIsAlive() const;
//    virtual getMove(); is it a field?
    bool getIsWayBlocked() const;
    const list<Pair> &getPath() const;

    // Setters

    void setID(int Id);
    const Pair &getPosition() const;
//  Direction setter?
    void setDirection(Direction dir);
    void setSize(int size);
    void setIsAlive(bool alive);
//    virtual setter?
    void setIsWayBlocked(bool blocked);
    void setPosition(const Pair &position);

    virtual void displayBugDetails()=0;
};


#endif //CPP_BUG_PROJECT_RF_BUG_H

