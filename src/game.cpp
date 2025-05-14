#include "game.h"
#include "tetrisPieces.h"
#include "tetrisTypes.h"
#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

Game::Game() {
}

void Game::run(sf::RenderWindow& window) {
    std::vector<sf::Texture> textures;
    initializeTextures(textures);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 6); // 0 to 6 for TetrisTypes enum
    std::uniform_int_distribution<int> dist2(1, 9); // 1 to 9 for Tetris Color
    std::uniform_int_distribution<int> dist3(0, 900); // 0 to 900 for x-coordinates
    // Store pieces that have reached the bottom
    std::vector<TetrisPiece> bottomTetris;    
    
    int randomX = dist3(gen);
    int pos_y = 0;
    TetrisTypes randomType = static_cast<TetrisTypes>(dist(gen));
    TetrisColors randomColor = static_cast<TetrisColors>(dist2(gen));

    TetrisPiece currentPiece(randomX, pos_y, randomType);
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
        }

        // Move piece down based on time
        if (clock.getElapsedTime().asSeconds() > dropTime) {
            pos_y += 40;
            
            int pieceHeight = 0;

            switch(randomType) {
                case TetrisTypes::I:
                    pieceHeight = PIECE_SIZE;
                    break;
                case TetrisTypes::O:
                    pieceHeight = PIECE_SIZE * 2;
                    break;
                default:
                    pieceHeight = PIECE_SIZE * 2;
                    break;
            }
            

            if (pos_y + pieceHeight >= Game::GAME_BOTTOM) {
                currentPiece = TetrisPiece(randomX, pos_y - 40, randomType);
                currentPiece.color = randomColor;
                bottomTetris.push_back(currentPiece);

                // Create a new piece
                randomX = dist3(gen);
                pos_y = 0;
                randomType = static_cast<TetrisTypes>(dist(gen));
                randomColor = static_cast<TetrisColors>(dist2(gen));
                currentPiece = TetrisPiece(randomX, pos_y, randomType);
                currentPiece.color = randomColor;
            } else {
                currentPiece = TetrisPiece(randomX, pos_y, randomType);
                currentPiece.color = randomColor;
            }
            clock.restart();
        } 
        window.clear();

        // Draw bottom pieces
        for (TetrisPiece p : bottomTetris) {
            p.render(window, textures, p.color);
        }

        // Draw current piece
        currentPiece.render(window, textures, currentPiece.color);

        window.display();

    }


}