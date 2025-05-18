#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "game.h"
#include "tetrisPieces.h"
#include "tetrisTypes.h"
#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

Game::Game() {
}

bool Game::checkSideCollision(const TetrisPiece& piece, int direction) {
    // 1) Make a moved copy
    TetrisPiece testPiece = piece;
    testPiece.x_coord += direction * BLOCK_WIDTH;

    // 2) Recompute its blockPositions
    testPiece.updatePosition();

    // 3) Test against the left and right walls
    auto [lblockX, lblockY] = getLeftMostBlockPosition(testPiece.blockPositions);
    auto [rblockX, rblockY] = getRightMostBlockPosition(testPiece.blockPositions);
    if (lblockX < 0 || rblockX + BLOCK_WIDTH > WINDOW_WIDTH) {
        return true;
    }

    // 4) Test overlap with already-occupied cells
    for (auto& b : testPiece.blockPositions) {
        if (std::find(occupiedBlocks.begin(),
                    occupiedBlocks.end(), b)
          != occupiedBlocks.end())
          return true;
    }

    return false;
}

bool Game::checkCollision(TetrisPiece& piece) {
    piece.updatePosition();

    for (auto const& b: piece.blockPositions) {
        if (std::find(occupiedBlocks.begin(), occupiedBlocks.end(), b)
            != occupiedBlocks.end()) 
        {
            return true;
        }
    }

    return false;
}

int Game::getHighestOccupiedYGivenX(vector<pair<int, int>> bottomSurfaceBlocks) {
    
    if (occupiedBlocks.empty()) {
        return GAME_BOTTOM; // Return bottom of game area if no blocks exist
    }

    int highestOccupiedY = 0; 

    for (const auto& bottomBlock : bottomSurfaceBlocks) {
        int x = bottomBlock.first;

        // Find the highest occupied block at this X position
        int highestAtX = GAME_BOTTOM;
        for (const auto& occupiedBlock : occupiedBlocks) {
            if (occupiedBlock.first == x && occupiedBlock.second < highestAtX) {
                highestAtX = occupiedBlock.second;
            }
        }


        // Update overall highest if this column is higher
        if (highestAtX < highestOccupiedY || highestOccupiedY == 0) {
            highestOccupiedY = highestAtX;
        }
    }
    return highestOccupiedY;
}

void Game::addOccupiedBlocks(array<pair<int, int>, 4> blockPositions) {
    for (const auto& block: blockPositions) {
        occupiedBlocks.push_back(block);
    }
}

pair<int, int> Game::getLeftMostBlockPosition(array<pair<int, int>, 4> blockPositions){
    int leftMostX = blockPositions[0].first;
    int leftMostY = blockPositions[0].second;
    for (const auto& block : blockPositions) {
        if (block.first < leftMostX) {
            leftMostX = block.first;
            leftMostY = block.second;
        }
    }
    return {leftMostX, leftMostY};
}

pair<int, int> Game::getRightMostBlockPosition(array<pair<int, int>, 4> blockPositions){
    int rightMostX = blockPositions[0].first;
    int rightMostY = blockPositions[0].second;
    for (const auto& block : blockPositions) {
        if (block.first > rightMostX) {
            rightMostX = block.first;
            rightMostY = block.second;
        }
    }
    return {rightMostX, rightMostY};
}

pair<int, int> Game::getBottomMostBlockPosition(array<pair<int, int>, 4> blockPositions){
    int bottomMostX = blockPositions[0].first;
    int bottomMostY = blockPositions[0].second;
    for (const auto& block : blockPositions) {
        if (block.second > bottomMostY) {
            bottomMostX = block.first;
            bottomMostY = block.second;
        }
    }
    return {bottomMostX, bottomMostY};
}

void Game::run(sf::RenderWindow& window) {
    std::vector<sf::Texture> textures;
    initializeTextures(textures);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 6); // 0 to 6 for TetrisTypes enum
    std::uniform_int_distribution<int> dist2(1, 9); // 1 to 9 for Tetris Color

    // Store pieces that have reached the bottom
    std::vector<TetrisPiece> bottomTetris;    
    TetrisTypes randomType = static_cast<TetrisTypes>(dist(gen));
    
    int maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
    std::uniform_int_distribution<int> dist3(0, maxX / BLOCK_WIDTH); // x-coordinates
    int currentX = dist3(gen) * BLOCK_WIDTH;
    int currentY = 0;

    TetrisColors randomColor = static_cast<TetrisColors>(dist2(gen));

    TetrisPiece currentPiece(currentX, currentY, randomType);
    currentPiece.color = randomColor;

    // Game clock for controlling piece movement
    sf::Clock clock;
    float dropTime = 1.0f;

    while(window.isOpen()) {
        while(const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            // Keyboard input to move the piece
            else if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                    currentPiece.render(window, textures, currentPiece.color);
    
                    // Check for left boundary and collisions
                    if (!checkSideCollision(currentPiece, -1)) {
                        currentPiece.x_coord -= BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    }
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                    currentPiece.render(window, textures, currentPiece.color);
                    
                    // Check for right boundary and collisions
                    if (!checkSideCollision(currentPiece, 1)) {
                        currentPiece.x_coord += BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    }

                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    currentPiece.render(window, textures, currentPiece.color);
                    pair<int, int> bottomBlock = getBottomMostBlockPosition(currentPiece.blockPositions);
                    vector<pair<int, int>> bottomSurfaces = currentPiece.getBottomSurfaceBlocks();


                    if (bottomBlock.second + BLOCK_HEIGHT >= GAME_BOTTOM) {
                        addOccupiedBlocks(currentPiece.blockPositions);
                        bottomTetris.push_back(currentPiece);
                        
                        // Create a new piece
                        randomType = static_cast<TetrisTypes>(dist(gen));
                        maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                        std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                        currentX = newDist3(gen) * BLOCK_WIDTH;
                        currentY = 0;
                        randomColor = static_cast<TetrisColors>(dist2(gen));
                        currentPiece = TetrisPiece(currentX, currentY, randomType);
                        currentPiece.color = randomColor;
                    } else {
                        // Create a test piece one position down
                        TetrisPiece testPiece = currentPiece;
                        testPiece.y_coord += BLOCK_HEIGHT;
                        testPiece.render(window, textures, testPiece.color);

                        if (checkCollision(testPiece)) {
                            addOccupiedBlocks(currentPiece.blockPositions);
                            bottomTetris.push_back(currentPiece);

                            // Create a new piece when collision occurs
                            randomType = static_cast<TetrisTypes>(dist(gen));
                            maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                            std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                            currentX = newDist3(gen) * BLOCK_WIDTH;
                            currentY = 0;
                            randomColor = static_cast<TetrisColors>(dist2(gen));
                            currentPiece = TetrisPiece(currentX, currentY, randomType);
                            currentPiece.color = randomColor;
                        } else {
                            currentY += BLOCK_HEIGHT;
                            currentPiece.y_coord = currentY;
            
                            int oldSpinState = currentPiece.spinState;
                            currentPiece = TetrisPiece(currentX, currentY, randomType);
                            currentPiece.color = randomColor;
                            currentPiece.spinState = oldSpinState;
                        }
                    }

                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    // Hard drop
                    int oldSpin = currentPiece.spinState;

                    while(true) {
                        TetrisPiece testPiece = currentPiece;
                        testPiece.y_coord += BLOCK_HEIGHT;
                        testPiece.spinState = oldSpin;
                        testPiece.render(window, textures, testPiece.color);

                        auto [bx, by] = getBottomMostBlockPosition(testPiece.blockPositions);
                        if (by + BLOCK_HEIGHT > GAME_BOTTOM) {
                            break;
                        }

                        if (checkCollision(testPiece)) {
                            break;
                        }

                        currentPiece = testPiece;
                        currentY = currentPiece.y_coord;
                    }

                    // lock in place
                    addOccupiedBlocks(currentPiece.blockPositions);
                    bottomTetris.push_back(currentPiece);

                    randomType = static_cast<TetrisTypes>(dist(gen));
                    maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                    std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                    currentX = newDist3(gen) * BLOCK_WIDTH;
                    currentY = 0;
                    randomColor = static_cast<TetrisColors>(dist2(gen));
                    currentPiece = TetrisPiece(currentX, currentY, randomType);
                    currentPiece.color = randomColor;

                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Tab) {
                    // Rotate piece
                    currentPiece.spinState = (currentPiece.spinState + 1) % 4;
                    
                }
            }
        }

        // Move piece down based on time
        if (clock.getElapsedTime().asSeconds() > dropTime) {
            
            clock.restart();
            
            currentPiece.render(window, textures, currentPiece.color);

            pair<int, int> bottomBlock = getBottomMostBlockPosition(currentPiece.blockPositions);
            vector<pair<int, int>> bottomSurfaces = currentPiece.getBottomSurfaceBlocks();

            
            if (bottomBlock.second + BLOCK_HEIGHT >= GAME_BOTTOM) {
                addOccupiedBlocks(currentPiece.blockPositions);
                bottomTetris.push_back(currentPiece);
                
                // Create a new piece
                randomType = static_cast<TetrisTypes>(dist(gen));
                maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                currentX = newDist3(gen) * BLOCK_WIDTH;
                currentY = 0;
                randomColor = static_cast<TetrisColors>(dist2(gen));
                currentPiece = TetrisPiece(currentX, currentY, randomType);
                currentPiece.color = randomColor;
            } else {
                // Create a test piece one position down
                TetrisPiece testPiece = currentPiece;
                testPiece.y_coord += BLOCK_HEIGHT;
                testPiece.render(window, textures, testPiece.color);

                if (checkCollision(testPiece)) {
                    addOccupiedBlocks(currentPiece.blockPositions);
                    bottomTetris.push_back(currentPiece);

                    // Create a new piece when collision occurs
                    randomType = static_cast<TetrisTypes>(dist(gen));
                    maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                    std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                    currentX = newDist3(gen) * BLOCK_WIDTH;
                    currentY = 0;
                    randomColor = static_cast<TetrisColors>(dist2(gen));
                    currentPiece = TetrisPiece(currentX, currentY, randomType);
                    currentPiece.color = randomColor;
                } else {
                    currentY += BLOCK_HEIGHT;
                    currentPiece.y_coord = currentY;
    
                    int oldSpinState = currentPiece.spinState;
                    currentPiece = TetrisPiece(currentX, currentY, randomType);
                    currentPiece.color = randomColor;
                    currentPiece.spinState = oldSpinState;
                }
            }
            //clock.restart();
        } 
        window.clear();

        sf::RectangleShape bottomLine(sf::Vector2f(WINDOW_WIDTH, 2));
        bottomLine.setPosition(sf::Vector2f(0, GAME_BOTTOM));
        bottomLine.setFillColor(sf::Color::Red);
        window.draw(bottomLine);
        // Draw bottom pieces
        for (TetrisPiece p : bottomTetris) {
            p.render(window, textures, p.color);
        }

        // Draw current piece
        currentPiece.render(window, textures, currentPiece.color);

        window.display();

    }


}