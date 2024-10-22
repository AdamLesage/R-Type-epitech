/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#include "Settings.hpp"
Settings::Settings(std::shared_ptr<sf::RenderWindow> _window) {
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

Settings::~Settings() {
}

const char* Settings::get_key_value(libconfig::Config &cfg, const char* key_name) {
    const char* value;

    char path[100];
    snprintf(path, sizeof(path), "Keys.%s.value", key_name);

    try {
        cfg.lookupValue(path, value);
        return value;
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Key not found: " << key_name << std::endl;
        return NULL;
    }
}

int Settings::set_key_value(libconfig::Config &cfg, const char* key_name, const char* new_value) {
    char path[100];
    snprintf(path, sizeof(path), "Keys.%s.value", key_name);
    if (strcmp(path, "Keys.Keys8.value") == 0) {
        strcpy(path, "Keys.Keys7.value");
    }
    if (strcmp(key_name, "Keys8") == 0) {
        key_name = "Keys7";
    }
    libconfig::Setting &setting = cfg.lookup(path);
    try {
        if (cfg.exists(path)) {
            setting = new_value;
            return 0;
        } else {
            std::cerr << "Key not found: " << key_name << std::endl;
            return -1;
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Key not found: " << key_name << std::endl;
        return -1;
    } catch (const libconfig::SettingTypeException &tex) {
        std::cerr << "Invalid type for key: " << key_name << std::endl;
        return -1;
    }
}

void Settings::moveUp() {
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void Settings::moveDown() {
    if (selectedOption + 1 < 7) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int Settings::getSelectedOption() const {
    return selectedOption;
}

void Settings::changeKey(std::string key) {
    std::string newKey = key.substr(0, 11);
    std::string newKey2;
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";

    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    if (key == "SUBTITLES: ON" || key == "SUBTITLES: OFF") {
        if (key.find("ON") != std::string::npos) {
            newKey2 = "OFF";
        } else {
            newKey2 = "ON";
        }
        set_key_value(cfg, "Keys8", newKey2.c_str());
        try {
            cfg.writeFile(configPath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            std::cerr << "Error while writing file: " << configPath << std::endl;
            return;
        }
        return;
    }
    menuOptions[selectedOption].setString("PRESS A KEY");

    display();
    sf::Event event2 = event;
    bool keyPressed  = false;
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
    std::string tmpKey = newKey;
    newKey.clear();
    newKey = tmpKey.substr(0, 11);
    set_key_value(cfg, ("Keys" + std::to_string(selectedOption + 1)).c_str(), newKey2.c_str());
    try {
        cfg.writeFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while writing file: " << configPath << std::endl;
        return;
    }
}

void Settings::displayInput()
{
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";

    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    std::string shootinput = std::string(get_key_value(cfg, "Keys5"));
    std::transform(shootinput.begin(), shootinput.end(), shootinput.begin(), ::tolower);
    if (!ShootInputTexture.loadFromFile("assets/input/Keyboard/keyboard_" + shootinput + ".png")) {
        std::cerr << "Error loading shoot input texture" << std::endl;
        return;
    }
    ShootInputSprite.setTexture(ShootInputTexture);

    for (int i = 0; i < 4; ++i) {
        std::string arrowKey = "Keys" + std::to_string(i + 1);
        std::string arrowInput = std::string(get_key_value(cfg, arrowKey.c_str()));
        std::transform(arrowInput.begin(), arrowInput.end(), arrowInput.begin(), ::tolower);
        if (!arrowTexture[i].loadFromFile("assets/input/Keyboard/keyboard_" + arrowInput + ".png")) {
            std::cerr << "Error loading arrow input texture for " << arrowKey << std::endl;
            return;
        }
        arrowSprite[i].setTexture(arrowTexture[i]);
    }

    window->draw(ShootInputSprite);
    for (int i = 0; i < 4; ++i) {
        window->draw(arrowSprite[i]);
    }
}

void Settings::display() {
    window->draw(background);
    window->draw(logoSprite);
    for (int i = 0; i < 7; ++i) {
        window->draw(menuOptions[i]);
    }
    displayInput();
    window->display();
}

void Settings::initTextAndSprites()
{
        libconfig::Config cfg;
        std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
        try {
            cfg.readFile(configPath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            std::cerr << "I/O error while reading file." << std::endl;
            return;
        }
        std::string optionsText[] = {"UP       : ", "DOWN     : ", "LEFT     : ", "RIGHT    : ",
                                     "SHOOT    : ", "SETTINGS: ",  "SUBTITLES: "};
        for (int i = 0; i < 7; i++) {
            optionsText[i] += get_key_value(cfg, ("Keys" + std::to_string(i + 1)).c_str());
            menuOptions[i].setFont(font);
            menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
            menuOptions[i].setString(optionsText[i]);
            menuOptions[i].setPosition(sf::Vector2f(1920 / 2 - 40, 300 + i * 100));
        }
        sf::Vector2f shootInputPosition = menuOptions[4].getPosition();
        shootInputPosition.x -= 80;
        shootInputPosition.y -= 10;
        ShootInputSprite.setPosition(shootInputPosition);
        for (int i = 0; i < 4; ++i) {
            sf::Vector2f arrowPosition = menuOptions[i].getPosition();
            arrowPosition.x -= 80;
            arrowPosition.y -= 10;
            arrowSprite[i].setPosition(arrowPosition);
        }
}

void Settings::displaySettings(bool ingame) {
    if (!ingame) {
        if (!window) {
            std::cerr << "Error: window is null" << std::endl;
            return;
        }
        selectedOption = 0;
        initTextAndSprites();
        while (window->isOpen()) {
            window->clear();
            display();
            window->display();
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) window->close();

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        moveUp();
                        break;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        moveDown();
                        break;
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        return;
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        switch (getSelectedOption()) {
                        case 0:
                            changeKey(menuOptions[0].getString().toAnsiString());
                            break;
                        case 1:
                            changeKey(menuOptions[1].getString().toAnsiString());
                            break;
                        case 2:
                            changeKey(menuOptions[2].getString().toAnsiString());
                            break;
                        case 3:
                            changeKey(menuOptions[3].getString().toAnsiString());
                            break;
                        case 4:
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