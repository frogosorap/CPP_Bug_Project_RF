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

}

