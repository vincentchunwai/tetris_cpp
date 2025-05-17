#include "tetrisPieces.h"
#include <iostream>

using namespace std;
// Constructor with default values
TetrisPiece::TetrisPiece(int x, int y, TetrisTypes t, TetrisColors c) 
    : x_coord(x), y_coord(y), type(t), color(c) {}

void addBlocks(const std::array<std::pair<int, int>, 4>& positions, 
               std::vector<sf::Sprite>& tetrisPieces,
               const sf::Texture& texture) {
    for(const auto& coords : positions) {
        sf::Sprite sprite(texture);
        sprite.setPosition(sf::Vector2f(coords.first, coords.second));
        tetrisPieces.push_back(sprite);
    }
}
// Render Tetris piece
array<pair<int, int>, 4> TetrisPiece::render(sf::RenderWindow& window, vector<sf::Texture>& textures, TetrisColors color) {
    vector<sf::Sprite> tetrisPieces;
    sf::Texture& tetrisTexture = textures[static_cast<size_t>(color)];
    array<pair<int, int>, 4> blockPositions;
    switch(type) {
        case TetrisTypes::I : {
            switch(spinState) {
                case 0:
                case 2:
                    // Horizontal
                    blockPositions = {
                        { 
                            {x_coord, y_coord}, 
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord}, 
                            {x_coord + 3 * DISPLAY_BLOCK_WIDTH, y_coord} 
                        }
                    };

                    break;
                case 1:
                case 3:
                    // Vertical
                    blockPositions = {
                        {
                            {x_coord, y_coord}, 
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord, y_coord + 2 * DISPLAY_BLOCK_HEIGHT}, 
                            {x_coord, y_coord + 3 * DISPLAY_BLOCK_HEIGHT} 
                        }
                    };

                    break;
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::J : {
            switch(spinState) {
                case 0: 
                    //  *
                    //  ***
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord - DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord},
                        }
                    };
                    break;
                case 1:
                    // **
                    // *
                    // *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 2:
                    // ***
                    //   *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 3:
                    //   *
                    //   *
                    //  **
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;

            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::L : {
            switch(spinState) {
                case 0: 
                    //    *
                    //  ***
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord - DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord - 2 * DISPLAY_BLOCK_WIDTH, y_coord},
                        }
                    };
                    break;
                case 1:
                    // *
                    // *
                    // **
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 2:
                    // ***
                    // *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 3:
                    // **
                    //  *
                    //  *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::O : {
            switch(spinState){
                case 0:
                case 1:
                case 2:
                case 3:
                    // **
                    // **
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::Z : {
            switch(spinState){
                case 0:
                case 2:
                    // **
                    //  **
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + 2 * DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 1:
                case 3:
                    //  *
                    // **
                    // *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::T : {
            switch(spinState){
                case 0:
                    // ***
                    //  *

                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 1:
                    //  *
                    // **
                    //  *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord - DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 2:
                    //  *
                    // ***
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            
                        }
                    };
                    break;
                case 3:
                    //  *
                    //  **
                    //  *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        case TetrisTypes::S : {
            switch(spinState) {
                case 0:
                case 2:
                    //  **
                    // **
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord - DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                        }
                    };
                    break;
                case 1:
                case 3:
                    // *
                    // **
                    //  *
                    blockPositions = {
                        {
                            {x_coord, y_coord},
                            {x_coord, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + DISPLAY_BLOCK_HEIGHT},
                            {x_coord + DISPLAY_BLOCK_WIDTH, y_coord + 2 * DISPLAY_BLOCK_HEIGHT},
                        }
                    };
            }
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        
    }            
    for (const auto& block: tetrisPieces) {
        window.draw(block);
    }

    return blockPositions;
}

int TetrisPiece::getMaxX(TetrisTypes type, int blockWidth, int windowWidth) {
    // Calculate the furthest right position a piece can be placed
    // such that it's still fully visible on screen
    
    // How many blocks from the left edge to the rightmost block
    int blocksFromLeftToRight = 0;
    
    switch(type) {
        case TetrisTypes::I:
            // I piece is 4 blocks wide
            blocksFromLeftToRight = 3; // 0,1,2,3 (4 blocks total, rightmost is at index 3)
            break;
        case TetrisTypes::O:
            // O piece is 2 blocks wide
            blocksFromLeftToRight = 1; // 0,1 (2 blocks total, rightmost is at index 1)
            break;
        case TetrisTypes::T:
            // T piece is 3 blocks wide
            blocksFromLeftToRight = 2; // 0,1,2 (3 blocks total, rightmost is at index 2)
            break;
        case TetrisTypes::S:
        case TetrisTypes::Z:
            // S and Z pieces are 3 blocks wide
            blocksFromLeftToRight = 1; // 0,1,2 (3 blocks total, rightmost is at index 2)
            break;
        case TetrisTypes::J:
        case TetrisTypes::L:
            // J and L pieces are 3 blocks wide
            blocksFromLeftToRight = 2; // 0,1,2 (3 blocks total, rightmost is at index 2)
            break;
        default:
            blocksFromLeftToRight = 2;
            break;
    }
    
    // Return the maximum x-coordinate of the leftmost block
    // such that the rightmost block is still on screen
    return windowWidth - (blocksFromLeftToRight * blockWidth) - blockWidth;
}