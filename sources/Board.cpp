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
        boardVec10.push_back(vector<Bug*>(10, nullptr));
    }
}

void Board::initializeBugBoard(vector<Bug*> &bugsVec)
{
    // Clear any existing bugs on the board
    for (auto& row : boardVec10) {
        for (auto& cell : row) {
            cell = nullptr;
        }
    }

    // Populate the board with bugs from bugsVec
    for (Bug* bug : bugsVec)
    {
        // Get the bug's position
        int x = bug->getPosition().getX();
        int y = bug->getPosition().getY();

        // Check if the bug's position is within the board's bounds
        if (x >= 0 && x < 10 && y >= 0 && y < 10)
        {
            // Place the bug onto the board
            boardVec10[y][x] = bug;
        }
        else
        {
            cout << "Bug position is out of bounds: (" << x << "," << y << ")" << endl;
        }
    }

    // Update the bugsVector with the new bugsVec
    bugsVector = bugsVec;
}


// Only working for displaying cells
//void Board::initializeBugBoard(vector<Bug*> &bugsVec)
//{
//    // Clear any existing bugs on the board
//    for (auto& row : boardVec10) {
//        for (auto& cell : row) {
//            cell = nullptr;
//        }
//    }
//
//    // Populate the board with bugs from bugsVec
//    for (Bug* bug : bugsVec)
//    {
//        // Get the bug's position
//        int x = bug->getPosition().getX();
//        int y = bug->getPosition().getY();
//
//        // Check if the bug's position is within the board's bounds
//        if (x >= 0 && x < 10 && y >= 0 && y < 10)
//        {
//            // Place the bug onto the board
//            boardVec10[y][x] = bug;
//        }
//        else
//        {
//            cout << "Bug position is out of bounds: (" << x << "," << y << ")" << endl;
//        }
//    }
//}

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
    displayAllCells();
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

void Board::displayAllCells()
{
    const int padding = 3;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    // Iterate over each row
    for (int i = 0; i < boardVec10.size(); ++i)
    {
        // Iterate over each column in the current row
        for (int j = 0; j < boardVec10[i].size(); ++j)
        {
            cout << "(" << j << "," << i << "): ";

            // If there's a bug in the cell, display its ID
            if (boardVec10[i][j] != nullptr)
            {
                cout.width(padding); // Set the width for alignment
                cout << boardVec10[i][j]->getID();
            }
            else
            {
                cout.width(padding); // Set the width for alignment
                cout << "---";
            }
            cout << " ";
        }
        cout<<endl;
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    }
}