/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#include "Menu.hpp"

RType::Menu::Menu()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type Menu");

    if (!font.loadFromFile("src/client/asset/r-type.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    if (!logoTexture.loadFromFile("src/client/asset/rtypelogo.png")) {
        std::cerr << "Error loading logo" << std::endl;
        return;
    }
    if (!backgroundTexture.loadFromFile("src/client/asset/background/menu.jpg")) {
        std::cerr << "Error loading background" << std::endl;
        return;
    }
    background.setTexture(&backgroundTexture);
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(1920, 1080));
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(sf::Vector2f(1920 / 2 - logoTexture.getSize().x / 2, 50));
    if (!selectBuffer.loadFromFile("src/client/asset/Sounds/selectsound.wav")) {
        std::cerr << "Error loading select sound" << std::endl;
    } else {
        selectSound.setBuffer(selectBuffer);
    }
    std::string optionsText[] = {"1. Lobby", "2. Settings", "3. Quit"};
    for (int i = 0; i < 3; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(200, 300 + i * 100));
    }
    try {
        // games = std::make_shared<Game>(window);
        settings = std::make_shared<Settings>(window);
        lobby = std::make_shared<Lobby>(window);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    selectedOption = 0;
}


void RType::Menu::draw()
{
    window->draw(background);
    window->draw(logoSprite);

    for (int i = 0; i < 3; ++i) {
        window->draw(menuOptions[i]);
    }
}

void RType::Menu::moveUp()
{
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void RType::Menu::moveDown()
{
    if (selectedOption + 1 < 3) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int RType::Menu::getSelectedOption() const
{
    return selectedOption;
}

void RType::Menu::displayMenu()
{

    window->setFramerateLimit(60);
    window->clear();
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
                        std::cout << "Lobby" << std::endl;
                        //  games->displayGame();
                        lobby->displayLobby();
                        break;
                    case 1:
                         settings->displaySettings();
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
        draw();
        window->display();
    }
}

// int main()
// {
//     std::cout << "Starting Menu" << std::endl;
//     Menu menu(1920, 1080);
//     menu.displayMenu();
//     return 0;
// }