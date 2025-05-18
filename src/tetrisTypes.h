#ifndef TETRISTYPES_H
#define TETRISTYPES_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

enum class TetrisTypes {
    I = 0,
    J = 1,
    L = 2 ,
    O = 3,
    S = 4,
    T = 5,
    Z = 6,
};

// Function prototype for initializing textures
void initializeTextures(std::vector<sf::Texture>& textures);


enum class TetrisColors {
    RED = 1,
    ORANGE = 2,
    YELLOW = 3,
    GREEN = 4,
    TEAL = 5,
    BLUE = 6,
    PURPLE = 7,
    WHITE = 8,
    GREY = 9,
};


#endif // TETRISTYPES_H
