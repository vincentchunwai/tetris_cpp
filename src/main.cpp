#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tetrisPieces.h"
#include "tetrisTypes.h"
#include "game.h"

int main()
{   

    auto window = sf::RenderWindow(sf::VideoMode({960, 1080u}), "Tetris SFML");
    window.setFramerateLimit(144);

    auto game = Game::Game();

    game.run(window);

    return 0;
}