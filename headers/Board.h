//
// Created by Raphael Frogoso on 14/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_BOARD_H
#define CPP_BUG_PROJECT_RF_BOARD_H

#include "Bug.h"

#include <vector>
#include <list>


class Board {


    vector<vector<Bug*>> boardVec10 = {
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
            {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}
    };

    vector<Bug*> bugsVector;

    Board(const vector<Bug *> &bugs);

public:
    Board();

    void initializeBugBoard(vector<Bug *> &bugsVec);

    void displayAllBugs();
};




#endif //CPP_BUG_PROJECT_RF_BOARD_H
