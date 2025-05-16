#include "game.h"
#include "tetrisPieces.h"
#include "tetrisTypes.h"
#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

Game::Game() {
}

int getMaxX(TetrisTypes type, int blockWidth, int windowWidth) {
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

void Game::run(sf::RenderWindow& window) {
    std::vector<sf::Texture> textures;
    initializeTextures(textures);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 6); // 0 to 6 for TetrisTypes enum
    std::uniform_int_distribution<int> dist2(1, 9); // 1 to 9 for Tetris Color

    // Calculate the number of blocks that can fit horizontally
    const int BLOCK_WIDTH = 31;
    const int BLOCK_HEIGHT = 30;

    // Store pieces that have reached the bottom
    std::vector<TetrisPiece> bottomTetris;    
    TetrisTypes randomType = static_cast<TetrisTypes>(dist(gen));
    
    int maxX = getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);
    std::uniform_int_distribution<int> dist3(0, maxX / BLOCK_WIDTH); // x-coordinates
    int currentX = dist3(gen) * BLOCK_WIDTH;
    int currentY = 0;

    TetrisColors randomColor = static_cast<TetrisColors>(dist2(gen));

    TetrisPiece currentPiece(currentX, currentY, randomType);
    currentPiece.color = randomColor;

    // Game clock for controlling piece movement
    sf::Clock clock;
    float dropTime = 1.0f;

    int pieceHeight = 0;
    int pieceWidth = 0;

    switch(randomType) {
        case TetrisTypes::I:
            pieceHeight = PIECE_SIZE;
            pieceWidth = BLOCK_WIDTH * 4;
            break;
        case TetrisTypes::O:
            pieceHeight = PIECE_SIZE * 2;
            pieceWidth = BLOCK_WIDTH * 2;
            break;
        case TetrisTypes::T:
            pieceHeight = BLOCK_HEIGHT * 3;
            pieceWidth = BLOCK_WIDTH * 3;
            break;
        case TetrisTypes::J:
        case TetrisTypes::S:
        case TetrisTypes::Z:
            pieceHeight = BLOCK_HEIGHT * 2;
            pieceWidth = BLOCK_WIDTH * 3;
            break;
        case TetrisTypes::L:
            pieceHeight = BLOCK_HEIGHT;
            pieceWidth = BLOCK_WIDTH * 2;
            break;
        default:
            pieceHeight = BLOCK_HEIGHT * 2;
            pieceWidth = BLOCK_WIDTH * 2;
            break;
    }
    while(window.isOpen()) {
        while(const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            // Keyboard input to move the piece
            else if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                    if (currentPiece.x_coord - BLOCK_WIDTH >= 0) {
                        currentPiece.x_coord -= BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    } 
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                    int maxX = getMaxX(currentPiece.type, BLOCK_WIDTH, WINDOW_WIDTH);
                    if (currentPiece.x_coord + BLOCK_WIDTH <= maxX) {
                        currentPiece.x_coord += BLOCK_WIDTH;
                        currentX = currentPiece.x_coord;
                    }
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    if (currentPiece.y_coord + pieceHeight + BLOCK_HEIGHT < GAME_BOTTOM) {
                        currentPiece.y_coord += BLOCK_HEIGHT;
                        currentY = currentPiece.y_coord;
                    }
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    while(currentY + pieceHeight + BLOCK_HEIGHT < GAME_BOTTOM) {
                        currentY += BLOCK_HEIGHT;
                    }
                    currentPiece.y_coord = currentY;
                }
            }
        }

        // Move piece down based on time
        if (clock.getElapsedTime().asSeconds() > dropTime) {
            currentY += BLOCK_HEIGHT;
        
            

            if (currentY + pieceHeight >= GAME_BOTTOM) {
                // Move piece back to last valid position before hitting bottom
                currentPiece = TetrisPiece(currentX, currentY - BLOCK_HEIGHT, randomType);
                currentPiece.color = randomColor;
                bottomTetris.push_back(currentPiece);

                // Create a new piece
                randomType = static_cast<TetrisTypes>(dist(gen));

                maxX = getMaxX(randomType, BLOCK_WIDTH, WINDOW_WIDTH);

                std::uniform_int_distribution<int> newDist3(0, maxX / BLOCK_WIDTH);

                currentX = newDist3(gen) * BLOCK_WIDTH;
                currentY = 0;
                randomColor = static_cast<TetrisColors>(dist2(gen));

                // Update piece dimensions for the new type
                switch(randomType) {
                    case TetrisTypes::I:
                        pieceHeight = PIECE_SIZE;
                        pieceWidth = BLOCK_WIDTH * 4;
                        break;
                    case TetrisTypes::O:
                        pieceHeight = PIECE_SIZE * 2;
                        pieceWidth = BLOCK_WIDTH * 2;
                        break;
                    case TetrisTypes::T:
                        pieceHeight = BLOCK_HEIGHT * 3;
                        pieceWidth = BLOCK_WIDTH * 3;
                        break;
                    case TetrisTypes::J:
                    case TetrisTypes::S:
                    case TetrisTypes::Z:
                        pieceHeight = BLOCK_HEIGHT * 2;
                        pieceWidth = BLOCK_WIDTH * 3;
                        break;
                    case TetrisTypes::L:
                        pieceHeight = BLOCK_HEIGHT;
                        pieceWidth = BLOCK_WIDTH * 2;
                        break;
                    default:
                        pieceHeight = BLOCK_HEIGHT * 2;
                        pieceWidth = BLOCK_WIDTH * 2;
                        break;
                }

                currentPiece = TetrisPiece(currentX, currentY, randomType);
                currentPiece.color = randomColor;
            } else {
                currentPiece = TetrisPiece(currentX, currentY, randomType);
                currentPiece.color = randomColor;
            }
            clock.restart();
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