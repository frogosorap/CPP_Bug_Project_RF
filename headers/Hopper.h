//
// Created by Raphael Frogoso on 13/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_HOPPER_H
#define CPP_BUG_PROJECT_RF_HOPPER_H

#include <list>
#include "Bug.h"
#include <string>

class Hopper : public Bug {
public:
    Hopper(int id,int x,int y,Direction dir,int size, int hopLength);



    void move() override;
    int hopLength;
};

#endif //CPP_BUG_PROJECT_RF_HOPPER_H
