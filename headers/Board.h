//
// Created by Raphael Frogoso on 14/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_BOARD_H
#define CPP_BUG_PROJECT_RF_BOARD_H

#include "Bug.h"

#include <vector>
#include <list>


class Board {

    Board(vector<Bug *> &bugs);

    vector<vector<Bug*>> boardVec10;

    vector<Bug*> bugsVector;

    Board(const vector<Bug *> &bugs);

public:
    Board();

    void initializeBugBoard(vector<Bug *> &bugsVec);

    void displayAllBugs();

    void tap();

    void fight();

    void moveBug();

    void lifeHistory();

    string getLifeHistory(Bug *bug);

    void outputFile();

    void BugBoard();

    void displayAllCells();

    void runSim();
};




#endif //CPP_BUG_PROJECT_RF_BOARD_H
