#include "headers/Bug.h"
#include "headers/Crawler.h"
#include "headers/Hopper.h"
#include "headers/Board.h"
#include "headers/Knight.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct tile
{
    CircleShape shape;
    bool isSelected = false;
    Color color;
    tile() : color(Color::White) // default color is white
    {
        shape.setRadius(20);
    }

    bool contains(int x, int y)
    {
        int shapeX = ((int)shape.getPosition().x / 50) * 50;
        int shapeY = ((int)shape.getPosition().y / 50) * 50;
        return x == shapeX && y == shapeY;
    }

    sf::Vector2f getPosition()
    {
        int shapeX = ((int)shape.getPosition().x / 50) * 50;
        int shapeY = ((int)shape.getPosition().y / 50) * 50;
        return Vector2f(shapeX, shapeY);
    }
};

void readFile(vector<Bug *> &bugVec, const string &fileName,Board *board);

void findBugByGivenID(const vector<Bug *> &bugVec);

void runGame(Board *board, vector<Bug *> &bugVec);

void createTile(vector<tile*> &tiles, vector<Bug *> &bugVec);


int main() {

    cout << "Hello, World!" << endl;
    vector<Bug *> bug_vector;
    auto *board = new Board();
    readFile(bug_vector, "bugs.txt", board);


    int option = -1;
    while (option != 0) {
        cout << "\n=======================================" << endl;
        cout << "= 1. Initialise bug Board               =" << endl;
        cout << "= 2. Display all Bugs                   =" << endl;
        cout << "= 3. Find a Bug                         =" << endl;
        cout << "= 4. Tap the Bug Board                  =" << endl;
        cout << "= 5. Display Life History of all Bugs   =" << endl;
        cout << "= 6. Display All Cells                  =" << endl;
        cout << "= 7. Run Simulation                     =" << endl;
        cout << "= 8. Exit                               =" << endl;
        cout << "=========================================" << endl;

        cin >> option;

        switch (option) {
            case (1):
                board->initializeBugBoard(bug_vector);
                break;
            case (2):
                board->displayAllBugs();
                break;
            case(3):
                findBugByGivenID(bug_vector);
                break;
            case(4):
                board -> tap();
                board -> BugBoard();
                break;
            case(5):
                board -> lifeHistory();
                break;
            case(6):
                board -> displayAllCells();
                break;
            case(7):
                board -> runSim();
                break;
            case(8):
                board -> outputFile();
                option = 0;
                break;
            case(9):
                runGame(board, bug_vector);
                break;
        }
    }

    delete board; // Freeing memory allocated for the board
}

//https://stackoverflow.com/questions/65294610/c-project-cant-read-file-when-building-with-cmake <--- Reading bugs.txt from Cmake file
void readFile(vector<Bug *> &bugVec, const string &fileName,Board *board)
{
    string filePath = "cmake-build-debug/" + fileName; // Adjust the path here
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error: Problem with file. " << fileName << endl;
        return;
    }
//    ifstream inputFile(fileName);
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
//        char bugType = '\O';
//        bugType = tokens[0][0];

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
        else if(tokens.at(0) == "K")
        {
            auto *k = new Knight(id, x, y, d, size);
            bugVec.push_back(k);
        }
        else {
            int hopLength = stoi(tokens.at(6));
            auto *h = new Hopper(id, x, y, d, size, hopLength);
            bugVec.push_back(h);
        }
//        switch(bugType)
//        {
//            case 'C':
//                auto *c = new Crawler(id, x, y, d, size);
//                bugVec.push_back(c);
//                break;
//            case 'H':
//                int hopLength = stoi(tokens.at(6));
//                auto *h = new Hopper(id, x, y, d, size, hopLength);
//                bugVec.push_back(h);
//                break;
//        }

    }
    inputFile.close();
}

void findBugByGivenID(const vector<Bug *> &bugVec)
{
    cout << "Enter ID of Bug to search: ";
    int input;
    bool found = false;
    cin >> input;

    auto it = bugVec.begin(); // initialize it to the beginning of the bugVec

    // iterator loops through all elements of the bugVec vector until the iterator it reaches the end of the vector
    while (it != bugVec.end()) {
        Bug *b = *it; // dereference the iterator it to get the pointer to the current Bug object
        if (b->getID() == input) {
            cout << "Bug " << input << " found." <<endl;
            b->displayBugDetails();
            return;
        }
        it++; // iterates through the next element
    }
    cout << "Bug " << input << " does not exist." <<endl;
}

// https://chat.openai.com/ <-- Used ChatGPT to debug why my code isn't displaying the board each time I tapped.
void createTile(vector<tile*> &tiles, vector<Bug *> &bugVec)
{
    for (Bug *bug : bugVec)
    {
        // Creates tile for each individual bug
        tile *t = new tile();
        t->shape.setPosition(bug->getPosition().getX() * 50+5, bug->getPosition().getY() * 50+5); // Assuming each bug occupies one tile
        // Set the color of the tile based on the bug type
        if (dynamic_cast<Crawler*>(bug))
        {
            t->color = Color::Green;
        }
        else if (dynamic_cast<Hopper*>(bug))
        {
            t->color = Color::Blue;
        }
        else if (dynamic_cast<Knight*>(bug))
        {
            t->color = Color::Red;
        }
        t->shape.setFillColor(t->color);
        tiles.push_back(t);
    }
}


void runGame(Board *board, vector<Bug *> &bugVec)
{
    RenderWindow window(VideoMode(500, 500), "Bug Game");
    vector<RectangleShape> bg;
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            RectangleShape shape;
            shape.setPosition(r * 50, c * 50);
            shape.setSize(Vector2f(50, 50));
            shape.setFillColor((r + c) % 2 == 0 ? Color(150, 75, 20) : Color(100, 20, 5));
            bg.push_back(shape);
        }
    }

    vector<tile*> tiles;

    // Create tiles for bugs
    createTile(tiles, bugVec);

    window.setFramerateLimit(40);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                // Check if the left mouse button is pressed
                if (event.mouseButton.button == Mouse::Left)
                {
                    // Call the tap() function of the Board class
                    board->tap();
                    // Clear tiles and recreate them based on the updated bug vector
                    tiles.clear();
                    createTile(tiles, bugVec);
                }
            }
        }

        window.clear();
        for (RectangleShape &s : bg)
        {
            window.draw(s);
        }
        // Draw tiles for bugs
        for (tile* t : tiles) {
            window.draw(t->shape);
        }
        window.display();
    }
}