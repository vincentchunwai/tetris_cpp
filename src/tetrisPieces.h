#ifndef TETRISPIECES_H
#define TETRISPIECES_H
#include "tetrisTypes.h"
#include "SFML/Graphics.hpp"
#include <vector>

class TetrisPiece {
public:
    // Public member variables
    int x_coord;                  // X-coordinate of the piece
    int y_coord;                  // Y-coordinate of the piece
    const int displayBlockSize = 30; // Size of each block in pixels
    TetrisTypes type;             // The type of the Tetris piece (enum)

    // Constructor with default values
    TetrisPiece(int x = 0, int y = 0, TetrisTypes t = TetrisTypes::I);

    
    void render(sf::RenderWindow& window, std::vector<sf::Texture>& textures, TetrisColors color);
};

#endif