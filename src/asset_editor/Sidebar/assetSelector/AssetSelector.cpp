/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetSelector
*/

#include "AssetSelector.hpp"

Edition::AssetSelector::AssetSelector(std::shared_ptr<sf::RenderWindow> window)
{
    _window = window;
    std::string assetPath = std::string("assets");
    AssetSelectorView = sf::View(sf::FloatRect(500, 0, 500, 1100));
    findAndLoadAsset(assetPath);
    std::vector<std::string> directory;
    directory.reserve(this->assetMap.size());
    for (auto it : this->assetMap) {
        directory.push_back(it.first);
    }
    this->selectBar = std::make_unique<Edition::SelectBar>(directory, _window->getSize().x * 0.775, 50, _window->getSize().x - _window->getSize().x * 0.775);
    updateRectangleShape();
}

Edition::AssetSelector::~AssetSelector()
{
}

void Edition::AssetSelector::display()
{
    for (auto& it: displayShape) {
        _window->draw(*it.second.get());
    }
    this->selectBar->display(_window);
}

void Edition::AssetSelector::updateRectangleShape()
{
    int Posx = _window->getSize().x * 0.775;
    int Posy = this->selectBar->getHeightSelectBar() + scrollOffset;
    std::string category = this->selectBar->findSelectedOption();


    float totalHeight = 0;
    for (auto& it : this->assetMap[category]) {
        totalHeight += 150;
    }

    float viewHeight = _window->getSize().y;
    maxScrollOffset = viewHeight - totalHeight;

    displayShape.clear();
    displayShape.reserve(this->assetMap[category].size());
    for (auto& it: this->assetMap[category]) {
        if (Posy > this->selectBar->getHeightSelectBar()) {
            std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(_window->getSize().x * 0.20, 100));
            shape->setPosition(sf::Vector2f(Posx, Posy));
            shape->setTexture(it.second.get());
            displayShape.push_back(std::make_pair(it.first, shape));
        }
        Posy += 150;
    }
}

void Edition::AssetSelector::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
        if (selectBar->handleEvent(event)) {
            updateRectangleShape();
        }
    }
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset += scrollSpeed;
        } else {
            scrollOffset -= scrollSpeed;
        }
        scrollOffset = std::clamp(scrollOffset, maxScrollOffset - this->selectBar->getHeightSelectBar(), 0.0f);
        updateRectangleShape();
    }
}

std::string Edition::AssetSelector::handlePickSprite(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved) {
        for (auto& it: displayShape) {
            if (it.second->getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
                it.second->setFillColor(sf::Color(150, 150, 150));
            } else {
                it.second->setFillColor(sf::Color::White);
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& it: displayShape) {
            if (it.second->getGlobalBounds().contains((event.mouseButton.x), (event.mouseButton.y))) {
                it.second->setFillColor(sf::Color(130, 130, 130));
                return (it.first);
            }
        }
    }
    return "";
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
                std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile(entry.path())) {
                    std::cout << "fail to load: " << entry.path() << std::endl;
                }
                size_t found = 0;
                found = folder.find_last_of("/\\");
                std::string file = folder.substr(found+1);
                this->assetMap[file][entry.path()] = texture;
            }
        }
    }
}

