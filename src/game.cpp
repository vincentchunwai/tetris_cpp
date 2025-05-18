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

bool Game::isValidPosition(const TetrisPiece& piece) {
    TetrisPiece test = piece;
    test.updatePosition();

    auto [lX, lY] = getLeftMostBlockPosition(test.blockPositions);
    auto [rX, rY] = getRightMostBlockPosition(test.blockPositions);

    if (lX < 0 || rX + BLOCK_WIDTH > WINDOW_WIDTH) 
        return false;
    
    for (auto const& b : test.blockPositions) {
        auto it = std::find_if(
            occupiedBlocks.begin(), occupiedBlocks.end(),
            [&](auto const& oc){
                return oc.x == b.first 
                    && oc.y == b.second;
            });
        if (it != occupiedBlocks.end())
            return false;
    }
    return true;
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
        auto it = std::find_if(
            occupiedBlocks.begin(), occupiedBlocks.end(),
            [&](auto const& oc) {
                return oc.x == b.first && oc.y == b.second;
            }
        );
        if (it != occupiedBlocks.end()) {
            return true;
        }
    }

    return false;
}

bool Game::checkCollision(const TetrisPiece& piece) {

    // for (auto const& b: piece.blockPositions) {
    //     if (std::find(occupiedBlocks.begin(), occupiedBlocks.end(), b)
    //         != occupiedBlocks.end()) 
    //     {
    //         return true;
    //     }
    // }

    for (auto const& b: piece.blockPositions) {
        auto it = std::find_if(
            occupiedBlocks.begin(), occupiedBlocks.end(),
            [&](auto const& oc) {
                return oc.x == b.first && oc.y == b.second;
            }
        );
        if (it != occupiedBlocks.end()) {
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
            if (occupiedBlock.x == x && occupiedBlock.y < highestAtX) {
                highestAtX = occupiedBlock.y;
            }
        }


        // Update overall highest if this column is higher
        if (highestAtX < highestOccupiedY || highestOccupiedY == 0) {
            highestOccupiedY = highestAtX;
        }
    }
    return highestOccupiedY;
}

void Game::addOccupiedBlocks(array<pair<int,int>,4>& blockPositions, TetrisColors color) {
    for (auto [x, y]: blockPositions) {
        occupiedBlocks.push_back({x, y, color});
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
    //std::vector<TetrisPiece> bottomTetris;    
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
                if (keyPressed->code == sf::Keyboard::Key::Left){
                    currentPiece.render(window, textures, currentPiece.color);
    
                    // Check for left boundary and collisions
                    if (!checkSideCollision(currentPiece, -1)) {
                        currentPiece.x_coord -= BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Right) {
                    currentPiece.render(window, textures, currentPiece.color);
                    
                    // Check for right boundary and collisions
                    if (!checkSideCollision(currentPiece, 1)) {
                        currentPiece.x_coord += BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    }

                } else if (keyPressed->code == sf::Keyboard::Key::Down) {
                    currentPiece.render(window, textures, currentPiece.color);
                    pair<int, int> bottomBlock = getBottomMostBlockPosition(currentPiece.blockPositions);
                    vector<pair<int, int>> bottomSurfaces = currentPiece.getBottomSurfaceBlocks();


                    if (bottomBlock.second + BLOCK_HEIGHT >= GAME_BOTTOM) {
                        currentPiece.updatePosition();
                        addOccupiedBlocks(currentPiece.blockPositions, currentPiece.color);
                        //bottomTetris.push_back(currentPiece);
                        
                        clearRows = findFullLines();
                        if (!clearRows.empty()) {
                            isClearing = true;
                            clearClock.restart();
                        } else {
                            // Create a new piece
                            randomType = static_cast<TetrisTypes>(dist(gen));
                            maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                            std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                            currentX = newDist3(gen) * BLOCK_WIDTH;
                            currentY = 0;
                            randomColor = static_cast<TetrisColors>(dist2(gen));
                            currentPiece = TetrisPiece(currentX, currentY, randomType);
                            currentPiece.color = randomColor;
                        }
                    } else {
                        // Create a test piece one position down
                        TetrisPiece testPiece = currentPiece;
                        testPiece.y_coord += BLOCK_HEIGHT;
                        testPiece.render(window, textures, testPiece.color);

                        if (checkCollision(testPiece)) {
                            currentPiece.updatePosition();
                            addOccupiedBlocks(currentPiece.blockPositions, currentPiece.color);
                            //bottomTetris.push_back(currentPiece);

                            clearRows = findFullLines();
                            if (!clearRows.empty()) {
                                isClearing = true;
                                clearClock.restart();
                            } else {
                                // Create a new piece
                                randomType = static_cast<TetrisTypes>(dist(gen));
                                maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                                std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                                currentX = newDist3(gen) * BLOCK_WIDTH;
                                currentY = 0;
                                randomColor = static_cast<TetrisColors>(dist2(gen));
                                currentPiece = TetrisPiece(currentX, currentY, randomType);
                                currentPiece.color = randomColor;
                            }
                        } else {
                            currentY += BLOCK_HEIGHT;
                            currentPiece.y_coord = currentY;
            
                            int oldSpinState = currentPiece.spinState;
                            currentPiece = TetrisPiece(currentX, currentY, randomType);
                            currentPiece.color = randomColor;
                            currentPiece.spinState = oldSpinState;
                        }
                    }

                } else if (keyPressed->code == sf::Keyboard::Key::Space) {
                    // Hard drop
                    int oldSpin = currentPiece.spinState;

                    while(true) {
                        TetrisPiece testPiece = currentPiece;
                        testPiece.spinState = oldSpin;
                        testPiece.y_coord += BLOCK_HEIGHT;
                        // Recompute blockPositions
                        testPiece.updatePosition();

                        // hit floor?
                        auto [bx, by] = getBottomMostBlockPosition(testPiece.blockPositions);
                        if (by + BLOCK_HEIGHT > GAME_BOTTOM)
                        break;

                        // hit stack?
                        if (!isValidPosition(testPiece))
                            break;

                        currentPiece = std::move(testPiece);
                        currentY = currentPiece.y_coord;
                    }

                    // lock in place
                    currentPiece.updatePosition();
                    addOccupiedBlocks(currentPiece.blockPositions, currentPiece.color);
                    //bottomTetris.push_back(currentPiece);


                    clearRows = findFullLines();
                    if (!clearRows.empty()) {
                        isClearing = true;
                        clearClock.restart();
                    } else {
                        // spawn next piece…
                        randomType = static_cast<TetrisTypes>(dist(gen));
                        maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                        std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                        currentX = newDist3(gen) * BLOCK_WIDTH;
                        currentY = 0;
                        randomColor = static_cast<TetrisColors>(dist2(gen));
                        currentPiece = TetrisPiece(currentX, currentY, randomType);
                        currentPiece.color = randomColor;
                    }


                } else if (keyPressed->code == sf::Keyboard::Key::Tab) {
                    // Rotate piece
                    //Check Collision
                    TetrisPiece test = currentPiece;
                    test.spinState = (currentPiece.spinState + 1) % 4;
                    
                    test.updatePosition();
                    test.adjustPosition(WINDOW_WIDTH, GAME_BOTTOM);
                    
                    auto lb= getLeftMostBlockPosition(test.blockPositions);
                    auto rb = getRightMostBlockPosition(test.blockPositions);
                    bool inBounds = (lb.first >= 0 && rb.first + BLOCK_WIDTH <= WINDOW_WIDTH);

                    bool hitStack = false;
                    for (auto const& b : test.blockPositions) {
                        auto it = std::find_if(
                            occupiedBlocks.begin(), occupiedBlocks.end(),
                            [&](auto const& oc){
                                return oc.x == b.first 
                                    && oc.y == b.second;
                            });
                        if (it != occupiedBlocks.end()) {
                            hitStack = true;
                            break;
                        }
                    }

                    if (inBounds && !hitStack) {
                        currentPiece = std::move(test);
                        currentPiece.updatePosition();
                        //std::cout << "didn't hit anything" << std::endl;
                    }
                }
            }
        }
        // Check for clearing lines
        if (isClearing) {
            float t = clearClock.getElapsedTime().asSeconds();
            //bool blinkOn = fmod(t, blinkInterval*2) < blinkInterval;
            if (t >= clearDuration) {
                removeLines(clearRows);
                isClearing = false;
                // spawn next piece…
                randomType = static_cast<TetrisTypes>(dist(gen));
                maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                currentX = newDist3(gen) * BLOCK_WIDTH;
                currentY = 0;
                randomColor = static_cast<TetrisColors>(dist2(gen));
                currentPiece = TetrisPiece(currentX, currentY, randomType);
                currentPiece.color = randomColor;
            }
            // draw scene with blinking cleared lines
            window.clear();

            for (auto& b : occupiedBlocks) {
                int row = b.y / BLOCK_HEIGHT;
                bool onCleared = find(clearRows.begin(), clearRows.end(), row) != clearRows.end();
                if (onCleared){
                    sf::Sprite sprite(textures[static_cast<int>(b.color)]);
                    sprite.setPosition(sf::Vector2f(b.x, b.y));
                    int alpha = static_cast<int>(255 * (1 - fmod(t, blinkInterval*2) / blinkInterval));
                    sprite.setColor(sf::Color(0, 255, 0, alpha));
                    window.draw(sprite);
                    //continue;
                } else {
                    // sf::Sprite sprite(textures[static_cast<int>(b.color)]);
                    // sprite.setPosition(sf::Vector2f(b.x, b.y));
                    // window.draw(sprite);
                }
            }

            window.display();
            continue;
        }

        // Move piece down based on time
        if (clock.getElapsedTime().asSeconds() > dropTime) {
            
            clock.restart();
            
            currentPiece.render(window, textures, currentPiece.color);

            pair<int, int> bottomBlock = getBottomMostBlockPosition(currentPiece.blockPositions);
            vector<pair<int, int>> bottomSurfaces = currentPiece.getBottomSurfaceBlocks();

            
            if (bottomBlock.second + BLOCK_HEIGHT >= GAME_BOTTOM) {
                currentPiece.updatePosition();
                addOccupiedBlocks(currentPiece.blockPositions, currentPiece.color);
                //bottomTetris.push_back(currentPiece);

                clearRows = findFullLines();
                if (!clearRows.empty()) {
                    isClearing = true;
                    clearClock.restart();
                } else {
                    // Create a new piece
                    randomType = static_cast<TetrisTypes>(dist(gen));
                    maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                    std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                    currentX = newDist3(gen) * BLOCK_WIDTH;
                    currentY = 0;
                    randomColor = static_cast<TetrisColors>(dist2(gen));
                    currentPiece = TetrisPiece(currentX, currentY, randomType);
                    currentPiece.color = randomColor;
                }
                
            } else {
                // Create a test piece one position down
                TetrisPiece testPiece = currentPiece;
                testPiece.y_coord += BLOCK_HEIGHT;
                testPiece.render(window, textures, testPiece.color);

                if (checkCollision(testPiece)) {
                    currentPiece.updatePosition();
                    addOccupiedBlocks(currentPiece.blockPositions, currentPiece.color);
                    //bottomTetris.push_back(currentPiece);

                    // Create a new piece when collision occurs
                    clearRows = findFullLines();
                    if (!clearRows.empty()) {
                        isClearing = true;
                        clearClock.restart();
                    } else {
                        // Create a new piece
                        randomType = static_cast<TetrisTypes>(dist(gen));
                        maxX = TetrisPiece::getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
                        std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);
                        currentX = newDist3(gen) * BLOCK_WIDTH;
                        currentY = 0;
                        randomColor = static_cast<TetrisColors>(dist2(gen));
                        currentPiece = TetrisPiece(currentX, currentY, randomType);
                        currentPiece.color = randomColor;
                    }
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
        // for (TetrisPiece p : bottomTetris) {
        //     p.render(window, textures, p.color);
        // }
        for (auto& cell : occupiedBlocks) {
            sf::Sprite sprite(textures[static_cast<int>(cell.color)]);
            sprite.setPosition(sf::Vector2f(cell.x, cell.y));
            window.draw(sprite);
        }

        currentPiece.updatePosition();
        // Draw current piece
        currentPiece.render(window, textures, currentPiece.color);

        window.display();

    }


}

// vector<int> Game::findFullLines() {
//     std::map<int, int> countAtY;
//     for (auto& b : occupiedBlocks)
//         countAtY[b.y]++;

//     vector<int> lines;
//     int cellsPerRow = WINDOW_WIDTH / BLOCK_WIDTH;
//     for (auto& [y, c] : countAtY) {
//         if (c >= cellsPerRow)
//             lines.push_back(y);
//     }
//     return lines;
// }

// void Game::removeLines(const vector<int>& rows){
//     set<int> rowSet(rows.begin(), rows.end());

//     // Remove blocks that are in the cleared rows
//     occupiedBlocks.erase(
//         std::remove_if(occupiedBlocks.begin(), occupiedBlocks.end(),
//             [&](auto& b){return rowSet.count(b.y) > 0;}),
//         occupiedBlocks.end() 
//     );

//     for (int clearedY : rows) {
//         for (auto& b : occupiedBlocks) {
//             if (b.y < clearedY) { // above the cleared line
//                 b.y += BLOCK_HEIGHT; // drop down one row
//             }
//         }
//     }
// }


vector<int> Game::findFullLines() {
    // how many cells fit across the playfield?
    int cols = WINDOW_WIDTH / BLOCK_WIDTH;  // use BLOCK_HEIGHT == actual tile size
    map<int,int> countAtRow;

    for(auto& c : occupiedBlocks) {
        int row = c.y / BLOCK_HEIGHT;
        countAtRow[row]++;
    }

    vector<int> lines;
    for(auto const& [row, cnt] : countAtRow) {
        if(cnt >= cols)
            lines.push_back(row);
    }
    return lines;
}

void Game::removeLines(const vector<int>& rows) {
    // Sort so we can binary_search
    auto sorted = rows;
    std::sort(sorted.begin(), sorted.end());

    vector<OccupiedCell> keep;
    keep.reserve(occupiedBlocks.size());

    for(auto const& oc : occupiedBlocks) {
        int row = oc.y / BLOCK_HEIGHT;
        // 1) skip any cell on a cleared row
        if(std::binary_search(sorted.begin(), sorted.end(), row))
            continue;

        // 2) count how many cleared rows lie *below* this one
        int shiftCount = int(std::count_if(
            sorted.begin(), sorted.end(),
            [&](int clearedRow){ return clearedRow > row; }
        ));

        // 3) drop it down
        OccupiedCell nc = oc;
        nc.y = (row + shiftCount) * BLOCK_HEIGHT;
        keep.push_back(nc);
    }

    occupiedBlocks = std::move(keep);
    if (!findFullLines().empty()) {
        clearRows = findFullLines();
        isClearing = true;
    }
}