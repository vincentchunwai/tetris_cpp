#include "tetrisPieces.h"
#include <iostream>

// Constructor with default values
TetrisPiece::TetrisPiece(int x, int y, TetrisTypes t, TetrisColors c) 
    : x_coord(x), y_coord(y), type(t), color(c) {}

// Render Tetris piece
void TetrisPiece::render(sf::RenderWindow& window, std::vector<sf::Texture>& textures, TetrisColors color) {
    std::vector<sf::Sprite> tetrisPieces;
    sf::Texture& tetrisTexture = textures[static_cast<std::size_t>(color)];

    switch(type) {
        case TetrisTypes::I : {
            for (int i = 0; i < 4; ++i) {
                sf::Sprite sprite(tetrisTexture);
                sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                tetrisPieces.push_back(sprite);
            }
            break;
        }
        case TetrisTypes::J : {
            for (int i = 0; i < 3; ++i) {
                sf::Sprite sprite(tetrisTexture);
                sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                tetrisPieces.push_back(sprite);
                if (i == 2) {
                    sf::Sprite sprite(tetrisTexture);
                    sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord + displayBlockSize));
                    tetrisPieces.push_back(sprite);
                }
            }
            break;
        }
        case TetrisTypes::L : {
            for (int i = 0; i < 3; ++i) {
                sf::Sprite sprite(tetrisTexture);
                sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                tetrisPieces.push_back(sprite);
                if (i == 2) {
                    sf::Sprite sprite(tetrisTexture);
                    sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord - displayBlockSize));
                    tetrisPieces.push_back(sprite);
                }
            }
            break;
        }
        case TetrisTypes::O : {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    sf::Sprite sprite(tetrisTexture);
                    sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord + j * displayBlockSize));
                    tetrisPieces.push_back(sprite);
                }
            }
            break;
        }
        case TetrisTypes::Z : {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    sf::Sprite sprite(tetrisTexture);
                    if (j == 1 && i == 0) {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord + j * displayBlockSize));
                    } else if (j == 1 && i == 1) {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord - j * displayBlockSize));
                    } else {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                    }
                    tetrisPieces.push_back(sprite);
                }
            }
            break;
        }
        case TetrisTypes::T : {
            for (int i = 0; i < 3; ++i) {
                sf::Sprite sprite(tetrisTexture);
                sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                tetrisPieces.push_back(sprite);
                if (i == 1) {
                    // Add blocks below the middle position (j+1 to start at row below the top)
                    for (int j = 0; j < 2; ++j) {
                        sf::Sprite sprite(tetrisTexture);
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord + (j+1) * displayBlockSize));
                        tetrisPieces.push_back(sprite);
                    }
                }
            }
        
            break;
        }
        case TetrisTypes::S : {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    sf::Sprite sprite(tetrisTexture);
                    if (j == 1 && i == 0) {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord - j * displayBlockSize));
                    } else if (j == 1 && i == 1) {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord + j * displayBlockSize));
                    } else {
                        sprite.setPosition(sf::Vector2f(x_coord + i * displayBlockSize, y_coord));
                    }
                    tetrisPieces.push_back(sprite);
                }
            }
            break;
        }
        
    }            
    for (const auto& block: tetrisPieces) {
        window.draw(block);
    }
}