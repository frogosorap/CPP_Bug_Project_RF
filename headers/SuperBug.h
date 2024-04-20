//
// Created by Raphael Frogoso on 20/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_SUPERBUG_H
#define CPP_BUG_PROJECT_RF_SUPERBUG_H

#include "Bug.h"

class SuperBug : public Bug {
public:
    SuperBug(int id, int x, int y, Direction dir, int size);

    void move() override;

    void displayBugDetails() override;
};

#endif //CPP_BUG_PROJECT_RF_SUPERBUG_H
