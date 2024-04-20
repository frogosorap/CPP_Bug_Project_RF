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
    sf::Sprite sprite;
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

void runGame(Board *board, vector<Bug *> &bugVec, Texture& crawlerTexture, Texture& hopperTexture, Texture& knightTexture);

void createTile(vector<tile*> &tiles, vector<Bug *> &bugVec, Texture& crawlerTexture, Texture& hopperTexture, Texture& knightTexture);


int main() {

    Texture crawlerTexture;
    if (!crawlerTexture.loadFromFile("images/crawler.png")) {
        cerr << "Failed to load crawler texture sprite" << endl;
        return EXIT_FAILURE;
    }

    Texture hopperTexture;
    if (!hopperTexture.loadFromFile("images/hopper.png")) {
        cerr << "Failed to load hopper texture sprite" << endl;
        return EXIT_FAILURE;
    }

    Texture knightTexture;
    if (!knightTexture.loadFromFile("images/knight.png")) {
        cerr << "Failed to load knight texture sprite" << endl;
        return EXIT_FAILURE;
    }

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
                runGame(board, bug_vector,crawlerTexture,hopperTexture,knightTexture);
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

//
// https://chat.openai.com/ <-- Used ChatGPT to debug why my code isn't displaying the board each time I tapped.
// https://www.youtube.com/watch?v=aEDP7uhaiJc&ab_channel=Zenva <-- I used to guide me with Texture and Sprites
// https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php <-- Notes I referred to from class to understand sprite in SFML

// https://discuss.cocos2d-x.org/t/how-would-you-properly-size-sprites/49614  <-- Scaling sprites according to given size
// https://discuss.cocos2d-x.org/t/sprite-scaling-problems-c/24813 <-- Debugging related issues regarding sprites going out of the frame

void createTile(vector<tile*> &tiles, vector<Bug *> &bugVec, Texture& crawlerTexture, Texture& hopperTexture, Texture& knightTexture)
{

    // Get the size of the tiles
    float tileSize = 50.0f;

    for (Bug *bug : bugVec)
    {
        // Creates tile for each individual bug
        tile *t = new tile();
        t->sprite.setPosition(bug->getPosition().getX() * tileSize , bug->getPosition().getY() * tileSize);

        // Set texture image from "images" folder based on the type of bug
        if (dynamic_cast<Crawler*>(bug))
        {
            t->sprite.setTexture(crawlerTexture);
        }
        else if (dynamic_cast<Hopper*>(bug))
        {
            t->sprite.setTexture(hopperTexture);
        }
        else if (dynamic_cast<Knight*>(bug))
        {
            t->sprite.setTexture(knightTexture);
        }

        // Scale the sprite to fit the tile size while it's aspect ratio
        float scaleFactor = tileSize / max(t->sprite.getLocalBounds().width, t->sprite.getLocalBounds().height);
        t->sprite.setScale(scaleFactor, scaleFactor);

        tiles.push_back(t);
    }
}


void runGame(Board *board, vector<Bug *> &bugVec, Texture& crawlerTexture, Texture& hopperTexture, Texture& knightTexture) {
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

    // Create tiles for bugs and declares the parameter of passed images
    createTile(tiles, bugVec, crawlerTexture, hopperTexture, knightTexture);

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
                    // Calls the tap method
                    board->tap();
                    // Clear tiles then update the board vector with the new bug vector after calling tap again
                    tiles.clear();
                    createTile(tiles, bugVec, crawlerTexture, hopperTexture, knightTexture);
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
            window.draw(t->sprite);
        }
        window.display();
    }
}