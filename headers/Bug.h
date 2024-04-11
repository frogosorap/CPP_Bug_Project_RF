//
// Created by Raphael Frogoso on 11/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_BUG_H
#define CPP_BUG_PROJECT_RF_BUG_H

#include <list>
#include "Direction.h"
#include <string>

using namespace std;

struct Pair {

    int x; int y;

    Pair(int xP, int yP)
    {
        x = xP;
        y = yP;
    }

    static int getX() ;
    static int getY() ;

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
    int id;
    pair<int, int> position;
//    Pair position = Pair(0,0);
    Direction direction;
    bool isAlive;
    int size;
    list<pair<int,int>> path;
//    list<Pair> path;
    virtual void move();
    bool isWayBlocked();
};


#endif //CPP_BUG_PROJECT_RF_BUG_H

