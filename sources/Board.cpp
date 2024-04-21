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

#include <cstdlib>
#include <ctime>

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
    cout << "=========================================" << endl;
    cout << "======   BUG BOARD INITIALIZED   ========" << endl;
    cout << "=========================================" << endl;
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
    cout<< "================================= Display All Bugs =================================" << endl;
    for (int i = 0; i < bugsVector.size(); i++)
    {
        cout << "\n";
        bugsVector.at(i) -> displayBugDetails();
    }
    cout<< "\n\n====================================================================================\n" << endl;
}


void Board::tap(){
    // method for getting position
    // method for moving position
    // idea is to get the bug's position, delete it there
    // paste the new bug position onto the board

    moveBug();
    fight();
}

void Board::fight()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // Iterate over each cell in the board
            if (boardVec10[i][j] != nullptr)
            {
                // Check if a bug is in the cell
                Bug *currentBug = boardVec10[i][j];
                Pair currentPos = currentBug->getPosition();

                // Check if there's another bug in cell
                for (int k = 0; k < bugsVector.size(); k++)
                {
                    Bug *otherBug = bugsVector[k];

                    // Check other bugs as current bug cannot fight themselves
                    // Check if other bug is in the same (x,y) cell as current bug
                    // Check if other bug is alive
                    if (otherBug != currentBug && otherBug->getPosition().getX() == currentPos.getX() &&
                        otherBug->getPosition().getY() == currentPos.getY() && otherBug->getIsAlive())
                    {
                        // If there's another bug in the same cell and it's alive, perform fight
                        if (currentBug->getIsAlive())
                        {
                            // If current bug is greater than other bug
                            if (currentBug->getSize() > otherBug->getSize())
                            {
                                // Current bug wins, update sizes and mark the other bug dead
                                int newSize = currentBug->getSize() + otherBug->getSize();
                                if (newSize > 20) newSize = 20; // Limit size to 20
                                currentBug->setSize(newSize);
                                otherBug->setSize(0); // Set size of defeated bug to 0
                                otherBug->setIsAlive(false); // Mark defeated bug as dead
                                otherBug->setEatenBy(currentBug->getID());
                            }
                            else if (currentBug->getSize() < otherBug->getSize())
                            {
                                // Current bug loses, update sizes and mark the current bug dead
                                int newSize = otherBug->getSize() + currentBug->getSize();
                                if (newSize > 20) newSize = 20; // Limit size to 20
                                otherBug->setSize(newSize);
                                currentBug->setSize(0); // Set size of defeated bug to 0
                                currentBug->setIsAlive(false); // Mark defeated bug as dead
                                currentBug->setEatenBy(otherBug->getID());
                            }
                            else
                            {
                                // Randomly decide which bug wins if they're of the same size
                                random_device rd;
                                mt19937 gen(rd());
                                uniform_int_distribution<> dist(0, 1);
                                int randWinner = dist(gen); // Generate random number between 0 and 1

                                if (randWinner == 0)
                                {
                                    // Current bug wins, update sizes and mark the other bug dead
                                    int newSize = currentBug->getSize() + otherBug->getSize();
                                    if (newSize > 20) newSize = 20; // Limit size to 20
                                    currentBug->setSize(newSize);
                                    otherBug->setSize(0); // Set size of defeated bug to 0
                                    otherBug->setIsAlive(false); // Mark defeated bug dead
                                    otherBug->setEatenBy(currentBug->getID());
                                }
                                else
                                {
                                    // Other bug wins, update sizes and mark the current bug dead
                                    int newSize = otherBug->getSize() + currentBug->getSize();
                                    if (newSize > 20) newSize = 20; // Limit size to 20
                                    otherBug->setSize(newSize);
                                    currentBug->setSize(0); // Set size of defeated bug to 0
                                    currentBug->setIsAlive(false); // Mark defeated bug dead
                                    currentBug->setEatenBy(otherBug->getID());
                                }
                            }
                        }
                        break; // Exit the loop after finding one other bug in the same cell
                    }
                }
            }
        }
    }
}

void Board::moveBug()
{
    for (int i=0; i<bugsVector.size();i++)
    {
        if(bugsVector[i]->getIsAlive())
        {
            bugsVector[i] -> move();
            bugsVector[i]->updatePathHistory();
        }
    }
}

void Board::lifeHistory()
{
    cout << "=========================================" << endl;
    cout << "========   BUG LIFE HISTORY    ==========" << endl;
    cout << "=========================================\n" << endl;
    for (Bug *bug: bugsVector) {
        cout << getLifeHistory(bug) << endl;
    }
    cout<<endl;
}

string Board::getLifeHistory(Bug *bug)
{
    string bugLifeHistory = "Path Taken by Bug " + to_string(bug->getID()) + ": ";
    for (const auto &pos : bug->getPathHistory())
    {
        bugLifeHistory += "(" + to_string(pos.getX()) + "," + to_string(pos.getY()) + ") ";
    }
    if (!bug->getIsAlive())
    {
        bugLifeHistory += "Eaten by Bug " + to_string(bug->getEatenBy());
    }
    return bugLifeHistory;
}

//https://www.javatpoint.com/cpp-date-and-time <--- Getting local time of computer
//https://olafurw.com/2018-05-03-strftime-and-fixed-size-buffers/ <--- Formatting strftime so it can be put into string
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
    cout << "\n----------------------------------------------------------------------------------------------------------------" << endl;
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
    cout << "=========================================" << endl;
    cout << "========   DISPLAY ALL CELLS   ==========" << endl;
    cout << "=========================================\n" << endl;
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

                    // Include the status (dead or alive)
                    if (bug->getIsAlive())
                    {
                        bugDetail += " Alive";
                    }
                    else
                    {
                        bugDetail += " Dead";
                    }

                    bugsInCell.push_back(bugDetail); // Store bug type, ID, and status
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

// https://stackoverflow.com/questions/4184468/sleep-for-milliseconds <--- Sleep time for 1 second
void Board::runSim()
{
    int aliveCount = bugsVector.size(); // Initialize with the total number of bugs
    while (aliveCount > 1)
    {
        aliveCount = 0; // Reset the count of alive bugs
        tap();
        BugBoard();
        for (Bug* bug : bugsVector)
        {
            if (bug->getIsAlive())
            {
                aliveCount++;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    // Display the winner when only one bug is left
    for (Bug* bug : bugsVector)
    {
        if (bug->getIsAlive())
        {
            cout << "Bug " << bug->getID() << " is the winner!" << endl;
            break;
        }
    }
}