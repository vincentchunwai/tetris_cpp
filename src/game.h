#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <utility>
#include <map>
#include <set>
#include "tetrisTypes.h"

using namespace std;


class TetrisPiece;
class Game {
    public:
        // Line Clearing
        bool isClearing = false;
        float clearDuration = 0.3f;
        float blinkInterval = 0.1f;
        sf::Clock clearClock;
        vector<int> clearRows;
        
        const static int WINDOW_WIDTH = 465;
        const static int WINDOW_HEIGHT = 1080;
        const static int GAME_BOTTOM = WINDOW_HEIGHT - 30;
        const static int PIECE_SIZE = 30;
        const static int BLOCK_HEIGHT = 30;
        const static int BLOCK_WIDTH = 31;
        Game();
        //vector<pair<pair<int, int>, int>> occupiedBlocks;
        //void addOccupiedBlocks(array<pair<int, int>, 4> blockPositions);

        struct OccupiedCell {
            int x, y;
            TetrisColors color;
        };

        vector<OccupiedCell> occupiedBlocks;
        void addOccupiedBlocks(array<pair<int,int>,4>& blockPositions,
                                TetrisColors color);

        void run(sf::RenderWindow& window);
        pair<int, int> getLeftMostBlockPosition(array<pair<int, int>, 4> blockPositions);

        pair<int, int> getRightMostBlockPosition(array<pair<int, int>, 4> blockPositions);
        
        pair<int, int> getBottomMostBlockPosition(array<pair<int, int>, 4> blockPositions);


        int getHighestOccupiedYGivenX(vector<pair<int, int>> bottomSurfaceBlocks);

        bool checkCollision(const TetrisPiece& piece);

        bool checkSideCollision(const TetrisPiece& piece, int direction);

        bool Game::isValidPosition(const TetrisPiece& piece);

        // Line clearing
        vector<int> findFullLines();
        void removeLines(const vector<int>& rows);
};


#endif