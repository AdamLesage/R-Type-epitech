/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#include "Settings.hpp"

Settings::Settings(std::shared_ptr<sf::RenderWindow> _window)
{
    this->window = _window;
    if (!font.loadFromFile("assets/r-type.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    if (!logoTexture.loadFromFile("assets/rtypelogo.png")) {
        std::cerr << "Error loading logo" << std::endl;
        return;
    }

    if (!backgroundTexture.loadFromFile("assets/background/menu.jpg")) {
        std::cerr << "Error loading background" << std::endl;
        return;
    }

    background.setTexture(&backgroundTexture);
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(1920, 1080));
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(sf::Vector2f(1920 / 2 - logoTexture.getSize().x / 2, 50));
}

Settings::~Settings()
{
}
void Settings::moveUp()
{
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void Settings::moveDown()
{
    if (selectedOption + 1 < 6) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int Settings::getSelectedOption() const
{
    return selectedOption;
}

void Settings::changeKey(std::string key)
{
    std::string newKey = key.substr(0, 8);
    menuOptions[selectedOption].setString("PRESS A KEY");
    display();
    sf::Event event2 = event;
    std::cout << "event2.key.code : " << event2.key.code << std::endl;
    std::cout << "event.key.code : " << event.key.code << std::endl;
    bool keyPressed = false;
    while (!keyPressed) {
        while (window->pollEvent(event2)) {
            if (event2.type == sf::Event::KeyPressed) {
                keyPressed = true;
                if (event2.key.code >= sf::Keyboard::A && event2.key.code <= sf::Keyboard::Z) {
                    newKey += static_cast<char>(event2.key.code + 'A');
                } else if (event2.key.code >= sf::Keyboard::Num1 && event2.key.code <= sf::Keyboard::Num9) {
                    newKey += static_cast<char>(event2.key.code - sf::Keyboard::Num1 + '1');
                } else if (event2.key.code == sf::Keyboard::Space) {
                    newKey += "SPACE";
                } else if (event2.key.code == sf::Keyboard::Escape) {
                    newKey += "ESCAPE";
                } else {
                    std::cerr << "Unsupported key" << std::endl;
                    keyPressed = false;
                    continue;
                }
                break;
            }
        }
    }
    menuOptions[selectedOption].setString(newKey);
}

void Settings::display()
{
    window->draw(background);
    window->draw(logoSprite);
    for (int i = 0; i < 6; ++i) {
        window->draw(menuOptions[i]);
    }
    window->display();
}

void Settings::displaySettings()
{
    if (!window) {
        std::cerr << "Error: window is null" << std::endl;
        return;
    }
    selectedOption = 0;
    std::string optionsText[] = {"UP    : Z", "DOWN  : S", "LEFT  : Q", "RIGHT : D", "SHOOT : SPACE", "QUIT  : ESCAPE"};
    for (int i = 0; i < 6; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(1920 / 2 - 20, 300 + i * 100));
    }
    while (window->isOpen()) {
        window->clear();
        display();
        window->display();
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) {
                    moveUp();
                    break;
                }
                if(event.key.code == sf::Keyboard::Down) {
                    moveDown();
                    break;
                }
                if(event.key.code == sf::Keyboard::Escape) {
                    return;
                }
                if(event.key.code == sf::Keyboard::Enter) {
                    switch (getSelectedOption()) {
                    case 0:
                        std::cout << menuOptions[0].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[0].getString().toAnsiString());
                        break;
                    case 1:
                        std::cout << menuOptions[1].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[1].getString().toAnsiString());
                        break;
                    case 2:
                        std::cout << menuOptions[2].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[2].getString().toAnsiString());
                        break;
                    case 3:
                        std::cout << menuOptions[3].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[3].getString().toAnsiString());
                        break;
                    case 4:
                        std::cout << menuOptions[4].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[4].getString().toAnsiString());
                        break;
                    case 5:
                        std::cout << menuOptions[5].getString().toAnsiString() << std::endl;
                        changeKey(menuOptions[5].getString().toAnsiString());
                        break;
                    }
                }
            }
        }
        display();
    }
}