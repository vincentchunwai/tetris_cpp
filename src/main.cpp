#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Tetris SFML");
    window.setFramerateLimit(144);

    // Load palette image containing all the colors
    sf::Image palette;
    if (!palette.loadFromFile("assets/yukulel_minos.png")) {
        std::cerr << "Failed to load palette image" << std::endl;
        return -1;
    }

    int numBlocks = 12;
    int blockWidth = palette.getSize().x / numBlocks;
    int blockHeight = palette.getSize().y;

    std::vector<sf::IntRect> textureRects;
    for (int i = 0; i < numBlocks; ++i) {
        textureRects.push_back(sf::IntRect({i * blockWidth, 0}, {blockWidth, blockHeight}));
    }

    std::vector<sf::Texture> blockTextures;
    for (const sf::IntRect& rect: textureRects) {
        sf::Texture texture;
        if (!texture.loadFromImage(palette, true, rect)) {
            std::cerr << "Failed to load texture from palette" << std::endl;
            return -1;
        }
        blockTextures.push_back(texture);
    }

    sf::Texture& tetrisTexture = blockTextures[0];

    int displayBlockSize = 50;

    sf::Vector2f basePosition(300.f, 150.f);

    std::vector<sf::Sprite> tetrisPieces;
    for (int i = 0; i < 3; ++i) {
        sf::Sprite sprite(tetrisTexture);
        sprite.setPosition(sf::Vector2f(basePosition.x + i * displayBlockSize, basePosition.y));
        tetrisPieces.push_back(sprite);
    }

    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        for (const auto& block : tetrisPieces) {
            window.draw(block);
        }
        
        window.display();
    }

    return 0;
}