//
// Created by Raphael Frogoso on 13/04/2024.
//

#ifndef CPP_BUG_PROJECT_RF_CRAWLER_H
#define CPP_BUG_PROJECT_RF_CRAWLER_H
#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, int x, int y, Direction dir, int size);

    void move() override;


};

#endif //CPP_BUG_PROJECT_RF_CRAWLER_H
