#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Game {
    public:
        const int WINDOW_HEIGHT = 1080;
        const int GAME_BOTTOM = WINDOW_HEIGHT - 50;
        const int PIECE_SIZE = 40;
        Game();

        void run(sf::RenderWindow& window);
};


#endif