#include "tetrisTypes.h"

// Specific initialization for yukulel_minos texture
void initializeTextures(std::vector<sf::Texture>& textures) {
    sf::Image palette;
    if (!palette.loadFromFile("assets/yukulel_minos.png")) {
        std::cerr << "Failed to load palette image" << std::endl;
        return;
    }
    int numBlocks = 12;
    int blockWidth = palette.getSize().x / numBlocks;
    int blockHeight = palette.getSize().y;

    std::vector<sf::IntRect> texturesRects;
    for(int i = 0; i < numBlocks; ++i) {
        texturesRects.push_back(sf::IntRect({i * blockWidth, 0}, {blockWidth, blockHeight}));
    }

    std::cout << "blockWidth: " << blockWidth << std::endl;
    std::cout << "blockHeight: " << blockHeight << std::endl;

    for(const sf::IntRect& rect: texturesRects) {
        sf::Texture texture;
        if (!texture.loadFromImage(palette, true, rect)) {
            std::cerr << "Failed to load texture from palette" << std::endl;
            return;
        }
        textures.push_back(texture);
    }
}
