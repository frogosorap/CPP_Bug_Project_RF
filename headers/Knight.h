//
// Created by Raphael Frogoso on 18/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_KNIGHT_H
#define CPP_BUG_PROJECT_RF_KNIGHT_H
#include "Bug.h"


class Knight : public Bug {
public:
    Knight(int id, int x, int y, Direction dir, int size);

    void move() override;

    void displayBugDetails() override;
};

#endif //CPP_BUG_PROJECT_RF_KNIGHT_H
