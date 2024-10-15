/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetSelector
*/

#include "AssetSelector.hpp"

Edition::AssetSelector::AssetSelector()
{
    std::string assetPath = std::string("assets");
    AssetSelectorView = sf::View(sf::FloatRect(500, 0, 500, 1100));
    findAndLoadAsset(assetPath);
}

Edition::AssetSelector::~AssetSelector()
{
}

void Edition::AssetSelector::display(std::shared_ptr<sf::RenderWindow> window)
{
    std::vector<sf::RectangleShape> elements;
    int Posx = window->getSize().x * 0.75;
    int Posy = 100 + scrollOffset;

    sf::RectangleShape shape2(sf::Vector2f(window->getSize().x * 0.25, 1080));
    shape2.setPosition(sf::Vector2f(Posx, 0));
    shape2.setFillColor(sf::Color::White);
    window->draw(shape2);

    float totalHeight = 0;
    for (auto& it: this->assetMap["assets/game_launch"]) {
        totalHeight += 150;
    }

    float viewHeight = window->getSize().y;
    maxScrollOffset = viewHeight - totalHeight;

    for (auto& it: this->assetMap["assets/game_launch"]) {
        sf::RectangleShape shape(sf::Vector2f(window->getSize().x * 0.25, 100));
        shape.setPosition(sf::Vector2f(Posx, Posy));
        shape.setTexture(it.second);
        elements.push_back(shape);
        Posy += 150;
    }

    for (auto& it: elements) {
        window->draw(it);
    }
}

void Edition::AssetSelector::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset += scrollSpeed;
        } else {
            scrollOffset -= scrollSpeed;
        }
    
        scrollOffset = std::clamp(scrollOffset, maxScrollOffset, 0.0f);
    }
}

void Edition::AssetSelector::findAndLoadAsset(const std::string &assetPath)
{
    for (const auto & entry : std::filesystem::directory_iterator(assetPath)) {
        std::string str = entry.path();
        size_t found = 0;
        found = str.find_last_of("/\\");
        std::string folder = str.substr(0,found);
        std::string file = str.substr(found+1);
        if (entry.is_directory()) {
            findAndLoadAsset(assetPath + PATH_SEPARATOR + file);
        } else {
            if (std::find(this->extensions.begin(), this->extensions.end(), entry.path().extension()) != this->extensions.end()) {
                sf::Texture *texture = new sf::Texture;
                if (!texture->loadFromFile(entry.path())) {
                    std::cout << "fail to load: " << entry.path() << std::endl;
                }
                this->assetMap[assetPath][entry.path()] = texture;
            }
        }
    }
}

