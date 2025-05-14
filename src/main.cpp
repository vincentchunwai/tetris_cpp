#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tetrisPieces.h"
#include "tetrisTypes.h"
#include "game.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({900, 1080u}), "Tetris SFML");
    window.setFramerateLimit(144);

    auto game = Game::Game();

    game.run(window);
    // std::vector<sf::Texture> textures;
    // initializeTextures(textures);

    // TetrisPiece tetrisPieceT (300, 150, TetrisTypes::T);
    // TetrisPiece tetrisPieceI (400, 150, TetrisTypes::I);
    // TetrisPiece tetrisPieceJ (600, 150, TetrisTypes::J);
    // TetrisPiece tetrisPieceL (700, 150, TetrisTypes::L);
    // TetrisPiece tetrisPieceO (800, 150, TetrisTypes::O);
    // TetrisPiece tetrisPieceS (100, 150, TetrisTypes::S);
    // TetrisPiece tetrisPieceZ (200, 150, TetrisTypes::Z);


    // while (window.isOpen())
    // {
    //     while (const std::optional event = window.pollEvent())
    //     {
    //         if (event->is<sf::Event::Closed>())
    //         {
    //             window.close();
    //         }
    //     }

    //     window.clear();
    //     // for (const auto& block : tetrisPieces) {
    //     //     window.draw(block);
    //     // }

    //     tetrisPieceT.render(window, textures, TetrisColors::GREEN);
    //     tetrisPieceI.render(window, textures, TetrisColors::RED);
    //     tetrisPieceJ.render(window, textures, TetrisColors::BLUE);
    //     tetrisPieceL.render(window, textures, TetrisColors::PURPLE);
    //     tetrisPieceO.render(window, textures, TetrisColors::YELLOW);
    //     tetrisPieceS.render(window, textures, TetrisColors::ORANGE);
    //     tetrisPieceZ.render(window, textures, TetrisColors::GREY);

        
    //     window.display();
    // }

    return 0;
}