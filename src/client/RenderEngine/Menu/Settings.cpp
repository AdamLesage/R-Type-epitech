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
}

Settings::~Settings()
{
}

const char* Settings::get_key_value(config_t *cfg, const char *key_name) {
    const char *value;

    char path[100];
    snprintf(path, sizeof(path), "Keys.%s.value", key_name);

    if(config_lookup_string(cfg, path, &value)) {
        return value;
    } else {
        printf("Clé non trouvée : %s\n", key_name);
        return NULL;
    }
}

int Settings::set_key_value(config_t *cfg, const char *key_name, const char *new_value) {
    char path[100];
    snprintf(path, sizeof(path), "Keys.%s.value", key_name);

    config_setting_t *setting = config_lookup(cfg, path);
    if (setting != NULL) {
        config_setting_set_string(setting, new_value);
        return 0;
    } else {
        printf("Clé non trouvée : %s\n", key_name);
        return -1;
    }
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
    if (selectedOption + 1 < 7) {
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
    std::string newKey = key.substr(0, 11);
    std::string newKey2;
    config_t cfg;
    config_init(&cfg);
    if (!config_read_file(&cfg, "src/config/key.cfg")) {
        printf("Erreur lors du chargement du fichier de configuration\n");
        config_destroy(&cfg);
        return;
    }
    if (key == "SUBTITLES: ON" || key == "SUBTITLES: OFF") {
        if (key.find("ON") != std::string::npos) {
            newKey2 = "OFF";
        } else {
            newKey2 = "ON";
        }
        set_key_value(&cfg, "Keys7", newKey2.c_str());
        if (!config_write_file(&cfg, "src/config/key.cfg")) {
            printf("Erreur lors de l'écriture du fichier\n");
        }
        config_destroy(&cfg);
        return;
    }
    menuOptions[selectedOption].setString("PRESS A KEY");

    display();
    sf::Event event2 = event;
    bool keyPressed = false;
    while (!keyPressed) {
        while (window->pollEvent(event2)) {
            if (event2.type == sf::Event::KeyPressed) {
                keyPressed = true;
                if (event2.key.code >= sf::Keyboard::A && event2.key.code <= sf::Keyboard::Z) {
                    newKey2 = static_cast<char>(event2.key.code + 'A');
                } else if (event2.key.code >= sf::Keyboard::Num1 && event2.key.code <= sf::Keyboard::Num9) {
                    newKey2 = static_cast<char>(event2.key.code - sf::Keyboard::Num1 + '1');
                } else if (event2.key.code == sf::Keyboard::Space) {
                    newKey2 = "SPACE";
                } else if (event2.key.code == sf::Keyboard::Escape) {
                    newKey2 = "ESCAPE";
                } else if (event2.key.code == sf::Keyboard::Right) {
                    newKey2 = "Right arrow";
                } else if (event2.key.code == sf::Keyboard::Left) {
                    newKey2 = "Left arrow";
                } else if (event2.key.code == sf::Keyboard::Down) {
                    newKey2 = "Down arrow";
                } else if (event2.key.code == sf::Keyboard::Up) {
                    newKey2 = "Up arrow";
                } else {
                    std::cerr << "Unsupported key" << std::endl;
                    keyPressed = false;
                    continue;
                }
                break;
            }
        }
    }
    newKey += newKey2;
    menuOptions[selectedOption].setString(newKey);
    newKey.substr(0, 11);
    set_key_value(&cfg, ("Keys" + std::to_string(selectedOption + 1)).c_str(), newKey2.c_str());
    if (!config_write_file(&cfg, "src/config/key.cfg")) {
        printf("Erreur lors de l'écriture du fichier\n");
    }
    config_destroy(&cfg);
}

void Settings::display()
{
    window->draw(background);
    window->draw(logoSprite);
    for (int i = 0; i < 7; ++i) {
        window->draw(menuOptions[i]);
    }
    window->display();
}

void Settings::displaySettings(bool ingame)
{
    if (!ingame) {
        if (!window) {
            std::cerr << "Error: window is null" << std::endl;
            return;
        }
        selectedOption = 0;
        config_t cfg;
        config_init(&cfg);
        if (!config_read_file(&cfg, "src/config/key.cfg")) {
            printf("Erreur lors du chargement du fichier de configuration\n");
            config_destroy(&cfg);
            return;
        }
        std::string optionsText[] = {"UP       : ", "DOWN     : ", "LEFT     : ", "RIGHT    : ", "SHOOT    : ", "SETTINGS: ", "SUBTITLES: "};
        for (int i = 0; i < 7; i++) {
            optionsText[i] += get_key_value(&cfg, ("Keys" + std::to_string(i + 1)).c_str());
            menuOptions[i].setFont(font);
            menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
            menuOptions[i].setString(optionsText[i]);
            menuOptions[i].setPosition(sf::Vector2f(1920 / 2 - 40, 300 + i * 100));
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
                            break;
                        case 6:
                            if (menuOptions[6].getString().toAnsiString().find("ON") != std::string::npos) {
                                changeKey("SUBTITLES: ON");
                                menuOptions[6].setString("SUBTITLES: OFF");
                            } else {
                                changeKey("SUBTITLES: OFF");
                                menuOptions[6].setString("SUBTITLES: ON");
                            }
                            break;
                        }
                    }
                }
            }
            display();
        }
    }
}