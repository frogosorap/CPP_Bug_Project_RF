//
// Created by Raphael Frogoso on 11/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_DIRECTION_H
#define CPP_BUG_PROJECT_RF_DIRECTION_H

#include <string>
#include <list>

using namespace std;

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

inline string directionString(Direction direction) {
    switch (direction) {
        case Direction::NORTH:
            return "NORTH";
        case Direction::SOUTH:
            return "South";
        case Direction::EAST:
            return "EAST";
        case Direction::WEST:
            return "WEST";
        default:
            return "No Direction";
    }
}
#endif //CPP_BUG_PROJECT_RF_DIRECTION_H