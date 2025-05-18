#include "tetrisPieces.h"
#include <iostream>

// Constructor with default values
TetrisPiece::TetrisPiece(int x, int y, TetrisTypes t, TetrisColors c, 
                         std::array<std::pair<int, int>, 4> pos) 
    : x_coord(x), y_coord(y), type(t), color(c), blockPositions(pos) {
}

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
std::array<std::pair<int, int>, 4> TetrisPiece::render(sf::RenderWindow& window, std::vector<sf::Texture>& textures, TetrisColors color) {
    std::vector<sf::Sprite> tetrisPieces;
    sf::Texture& tetrisTexture = textures[static_cast<size_t>(color)];
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
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
            adjustPosition(Game::WINDOW_WIDTH, Game::GAME_BOTTOM);
            addBlocks(blockPositions, tetrisPieces, tetrisTexture);
            break;
        }
        
    }           
    for (const auto& block: tetrisPieces) {
        window.draw(block);
    }

    return blockPositions;
}

vector<pair<int, int>> TetrisPiece::getBottomSurfaceBlocks() {
    vector<pair<int, int>> bottomSurfaceBlocks;
    if (blockPositions.empty()) return bottomSurfaceBlocks;
    // sort by first value
    sort(blockPositions.begin(), blockPositions.end(), [](const pair<int, int> &a, const pair<int, int>& b) {
        return a.first < b.first;
    });

    int current_x = blockPositions[0].first;
    int max_y = blockPositions[0].second;

    for (size_t i = 1; i < blockPositions.size(); ++i) {
        auto [x, y] = blockPositions[i];

        if (x == current_x) {
            max_y = std::max(max_y, y);
        } else {
            bottomSurfaceBlocks.emplace_back(current_x, max_y);
            current_x = x;
            max_y = y;
        }
    }

    bottomSurfaceBlocks.emplace_back(current_x, max_y);

    return bottomSurfaceBlocks;
}

void TetrisPiece::adjustPosition(int screenWidth, int screenHeight) {
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (const auto& block: blockPositions) {
        minX = std::min(minX, block.first);
        maxX = std::max(maxX, block.first);
        minY = std::min(minY, block.second);
        maxY = std::max(maxY, block.second);
    }

    int adjustX = 0;
    int adjustY = 0;

    // Check left boundary
    if (minX < 0) {
        adjustX = -minX;
    }

    // Check right boundary
    if (maxX + DISPLAY_BLOCK_WIDTH > screenWidth) {
        adjustX = screenWidth - (maxX + DISPLAY_BLOCK_WIDTH);
    }

    if (maxY + DISPLAY_BLOCK_HEIGHT > screenHeight) {
        adjustY = screenHeight - (maxY + DISPLAY_BLOCK_HEIGHT);
    }

    if (adjustX != 0 || adjustY != 0) {
        x_coord += adjustX;
        y_coord += adjustY;
        
        // Update all block positions
        for (auto& block : blockPositions) {
            block.first += adjustX;
            block.second += adjustY;
        }
    }

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


void TetrisPiece::updatePosition() {
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
            break;
        }
        
    }            
}