#include "headers/Bug.h"
#include "headers/Crawler.h"
#include "headers/Hopper.h"
#include "headers/Board.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void readFile(vector<Bug *> &bugVec, const string &fileName,Board *board);

int main() {

    cout << "Hello, World!" << endl;
    vector<Bug *> bug_vector;
    auto *board = new Board();
    readFile(bug_vector, "bugs.txt", board);


    int option = -1;
    while (option != 0) {
        cout << "\n===============================" << endl;
        cout << "= 1. Initialise bug Board     =" << endl;
        cout << "= 2. Display all Bugs         =" << endl;
        cout << "= 0. End program              =" << endl;
        cout << "===============================" << endl;

        cin >> option;

        switch (option) {
            case (1):
                board->initializeBugBoard(bug_vector);
                break;
            case (2):
                board->displayAllBugs();
                break;
            case (0):
                cout << "Goodbye." << endl;
                break;
        }
    }

    delete board; // Freeing memory allocated for the board
}

void readFile(vector<Bug *> &bugVec, const string &fileName,Board *board)
{
    ifstream inputFile(fileName);
    while (!inputFile.eof()) {
        string line;

        getline(inputFile, line);
        stringstream ss(line);
        string token;
        vector<string> tokens;
        char delimiter = ';';

        cout <<line;
        while (getline(ss, token, delimiter)) {

            tokens.push_back(token);
        }

        int id = stoi(tokens.at(1));
        int x = stoi(tokens.at(2));
        int y = stoi(tokens.at(3));
        int dir = stoi(tokens.at(4));
        int size = stoi(tokens.at(5));
        Direction d;
        if (dir == 1) {
            d = Direction::NORTH;
        } else if (dir == 2) {
            d = Direction::EAST;
        } else if (dir == 3) {
            d = Direction::SOUTH;
        } else {
            d = Direction::WEST;
        }
        if (tokens.at(0) == "C") {
            auto *c = new Crawler(id, x, y, d, size);
            bugVec.push_back(c);
        }
        else {
            int hopLength = stoi(tokens.at(6));
            auto *h = new Hopper(id, x, y, d, size, hopLength);
            bugVec.push_back(h);
        }
    }

    inputFile.close();
}
