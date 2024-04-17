//
// Created by Raphael Frogoso on 14/04/2024.
//
#include "../headers/Board.h"
#include "../headers/Bug.h"
#include "../headers/Crawler.h"
#include "../headers/Hopper.h"

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


// Jamie helped me update my bug each time I move as I originally only looked at the board vector and not the bug vector
void Board::BugBoard()
{
    const int padding = 3;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    cout<<endl;
    // Iterate over each row
    for (int i = 0; i < 10; ++i)
    {
        // Iterate over each column in the current row
        for (int j = 0; j < 10; ++j)
        {
            cout << " (" << j << "," << i << "): ";
            bool iscellEmpty = true;
            for ( Bug *bug:bugsVector)
            {
                if (bug->getPosition().x == i && bug->getPosition().y == j) { //if bug position (x,y) is equal to board tile (i.j) then it has a bug on it so.
                    cout.width(padding); // Set the width for alignment
                    // If there's a bug in the cell, display its ID
                    cout << bug->id;
                    iscellEmpty = false;
                }
            }
            if (iscellEmpty == true)
            {
                cout.width(padding); // Set the width for alignment
                cout << "   ";
            }
        }
        cout<<endl;
        cout<<endl;
//        cout << "----------------------------------------------------------------------------------------------------------------" << endl;

    }
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
}


//https://stackoverflow.com/questions/38279657/c-dynamic-cast-with-inheritance <--- Dynamic cast of inherited bug of different type
void Board::displayAllCells()
{
    // Iterate over each cell
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << "(" << i << "," << j << "): "; // Display cell coordinates

            bool isCellEmpty = true;
            vector<string> bugsInCell; // Store Type of bug and ID in this vector
            for (Bug *bug : bugsVector)
            {
                // Check if there's a bug in the cell
                if (bug->getPosition().x == i && bug->getPosition().y == j) {
                    // Identify the bug type and ID
                    string bugDetail;
                    if (dynamic_cast<Crawler*>(bug))
                    {
                        bugDetail = "Crawler " + to_string(bug->id); // Crawler
                    }
                    else if (dynamic_cast<Hopper*>(bug))
                    {
                        bugDetail = "Hopper " + to_string(bug->id); // Hopper
                    }
                    bugsInCell.push_back(bugDetail); // Store bug type and ID
                    isCellEmpty = false;
                }
            }

            // Display bugs in the cell
            if (!isCellEmpty)
            {
                // Checks bugsInCell bug types and IDs for display
                for (int k = 0; k < bugsInCell.size(); ++k)
                {
                    // Prints one bug
                    cout << bugsInCell[k];

                    // if more than 1 bug
                    if (k != bugsInCell.size() - 1)
                    {
                        cout << ", ";
                    }
                }
            }
            else
            {
                cout << "empty";
            }
            cout << endl;
        }
    }
}

