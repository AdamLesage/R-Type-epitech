/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#include "menu.hpp"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("asset/r-type.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    if (!logoTexture.loadFromFile("asset/rtypelogo.png")) {
        std::cerr << "Error loading logo" << std::endl;
        return;
    }

    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(sf::Vector2f(width / 2 - logoTexture.getSize().x / 2, 50));

    if (!selectBuffer.loadFromFile("asset/selectsound.wav")) {
        std::cerr << "Error loading select sound" << std::endl;
    } else {
        selectSound.setBuffer(selectBuffer);
    }

    std::string optionsText[] = {"1. Play", "2. Settings", "3. Quit"};
    for (int i = 0; i < 3; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(200, 300 + i * 100));
    }

    selectedOption = 0;
}

void Menu::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(logoSprite);

    for (int i = 0; i < 3; ++i) {
        window->draw(menuOptions[i]);
    }
}

void Menu::moveUp()
{
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void Menu::moveDown()
{
    if (selectedOption + 1 < 3) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int Menu::getSelectedOption() const
{
    return selectedOption;
}

void Menu::displayMenu()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type Menu");
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    moveUp();
                    break;

                case sf::Keyboard::Down:
                    moveDown();
                    break;

                case sf::Keyboard::Enter:
                    switch (getSelectedOption()) {
                    case 0:
                        std::cout << "Play" << std::endl;
                        break;
                    case 1:
                        std::cout << "Settings" << std::endl;
                        break;
                    case 2:
                        std::cout << "Quit" << std::endl;
                        window->close();
                        break;
                    }
                    break;

                default:
                    break;
                }
            }
        }

        window->clear();
        draw(window);
        window->display();
    }
}

int main()
{
    Menu menu(1920, 1080);
    menu.displayMenu();
    return 0;
}