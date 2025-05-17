#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <utility>

using namespace std;

class TetrisPiece;
class Game {
    public:
        const static int WINDOW_WIDTH = 960;
        const static int WINDOW_HEIGHT = 1080;
        const static int GAME_BOTTOM = WINDOW_HEIGHT - 30;
        const static int PIECE_SIZE = 30;
        const static int BLOCK_HEIGHT = 30;
        const static int BLOCK_WIDTH = 31;
        Game();
        vector<pair<int, int>> occupiedBlocks;

        void run(sf::RenderWindow& window);
        pair<int, int> getLeftMostBlockPosition(array<pair<int, int>, 4> blockPositions);

        pair<int, int> getRightMostBlockPosition(array<pair<int, int>, 4> blockPositions);
        
        pair<int, int> getBottomMostBlockPosition(array<pair<int, int>, 4> blockPositions);

        void addOccupiedBlocks(array<pair<int, int>, 4> blockPositions);

        int getHighestOccupiedYGivenX(vector<pair<int, int>> bottomSurfaceBlocks);

        bool checkCollision(TetrisPiece& piece);

        bool checkSideCollision(const TetrisPiece& piece, int direction);
};


#endif