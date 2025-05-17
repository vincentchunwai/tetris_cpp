#ifndef TETRISPIECES_H
#define TETRISPIECES_H
#include "tetrisTypes.h"
#include "game.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <utility>
#include <array>

using namespace std;

class TetrisPiece {
public:
    // Public member variables
    int x_coord;                  // X-coordinate of the piece
    int y_coord;                  // Y-coordinate of the piece
    static const int DISPLAY_BLOCK_WIDTH = 31;
    static const int DISPLAY_BLOCK_HEIGHT = 30;
    //const int displayBlockSize = 30; // Size of each block in pixels
    TetrisTypes type;             // The type of the Tetris piece (enum)
    TetrisColors color;
    int spinState = 0;
    array<pair<int, int>, 4> blockPositions;

    TetrisPiece& operator=(const TetrisPiece& other){
        if (this != &other) {
            x_coord = other.x_coord;
            y_coord = other.y_coord;
            type = other.type;
            color = other.color;
            blockPositions = other.blockPositions;
        }
        return *this;
    }

    void updatePosition();

    // Constructor with default values
    TetrisPiece(int x = 0, int y = 0, TetrisTypes t = TetrisTypes::I, TetrisColors c = TetrisColors::RED, 
                array<pair<int, int>, 4> pos = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}});

    void adjustPosition(int screenWidth, int screenHeight);
    
    array<pair<int, int>, 4> render(sf::RenderWindow& window, vector<sf::Texture>& textures, TetrisColors color);

    static int getMaxX(TetrisTypes type, int blockWidth, int windowWidth) ;

    vector<pair<int, int>> getBottomSurfaceBlocks();

};

#endif