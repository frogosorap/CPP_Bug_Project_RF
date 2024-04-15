//
// Created by Raphael Frogoso on 14/04/2024.
//
#include "../headers/Board.h"

#include <fstream>
#include <iostream>
#include <thread>
#include <random>

using namespace std;



Board::Board(const vector<Bug *> &bugs){
    bugsVector = bugs;

}

//Board::Board()=default;

Board::Board()
{
    for (int j = 0; j < 10; ++j)
    {
        boardVec10.push_back(vector<Bug*>());
    }
}

void Board::initializeBugBoard(vector<Bug*> &bugsVec)
{
    bugsVector=bugsVec;
}

void Board::displayAllBugs()
{
    for (int i = 0; i < bugsVector.size(); i++)
    {
        cout << "\n";
        bugsVector.at(i) -> displayBugDetails();
    }
}

void Board::tap(){
    // method for getting position
    // method for moving position
    // idea is to get the bug's position, delete it there
    // paste the new bug position onto the board
}

void Board::getBugPosition()
{

}

void Board::moveBug()
{

}