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

    moveBug();
}

void Board::getBugPosition()
{

}

void Board::moveBug()
{
    for (int i=0; i<bugsVector.size();i++)
    {
        bugsVector[i] -> move();
        bugsVector[i]->updatePathHistory();
    }
}

void Board::lifeHistory()
{
    for (Bug *bug: bugsVector) {
        cout << getLifeHistory(bug) << endl;
    }
}

string Board::getLifeHistory(Bug *bug)
{
    string bugLifeHistory = "Path Taken by Bug " + to_string(bug->getID()) + ": ";
    for (const auto &pos : bug->getPathHistory())
    {
        bugLifeHistory += "(" + to_string(pos.getX()) + "," + to_string(pos.getY()) + ") ";
    }
    return bugLifeHistory;
}

//https://www.javatpoint.com/cpp-date-and-time <--- Getting local time of computer
//https://olafurw.com/2018-05-03-strftime-and-fixed-size-buffers/ <--- formatting strftime so it can be put into string
void Board::outputFile()
{
    time_t now = time(0); // get current date/time with respect to system

    struct tm* timeinfo = localtime(&now);

    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d_%H-%M-%S", timeinfo); // Formats date and time

    string outputFileName = "bug's_life_history_" + string(buffer) + ".out.txt"; // Include formatted time in the file name
    ofstream output(outputFileName);
    for (Bug* bug : bugsVector)
    {
        output << getLifeHistory(bug) << "\n";
    }

    cout << "Saved your bug history in file: "<< outputFileName << endl;

    output.close();
}