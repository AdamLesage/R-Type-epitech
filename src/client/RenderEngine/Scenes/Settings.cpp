/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#include "Settings.hpp"
RType::Settings::Settings(std::shared_ptr<sf::RenderWindow> _window) {
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
    if (!colorblindShader[0].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Deuteranopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading deuteranopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[1].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Protanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading protanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[2].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Tritanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading tritanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[3].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Achromatopsia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading achromatopsia shader" << std::endl;
        return;
    }
    if (!colorblindShader[4].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Normal_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading normal shader" << std::endl;
        return;
    }
    RenderTexture.create(1920, 1080);
}

RType::Settings::~Settings() {
}

const char* RType::Settings::get_key_value(libconfig::Config &cfg, const char* key_name) {
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

int RType::Settings::set_key_value(libconfig::Config &cfg, const char* key_name, const char* new_value) {
    char path[100];
    snprintf(path, sizeof(path), "Keys.%s.value", key_name);
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

void RType::Settings::moveUp() {
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        selectSound.play();
    }
}

void RType::Settings::moveDown() {
    if (selectedOption + 1 < 8) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        selectSound.play();
    }
}

int RType::Settings::getSelectedOption() const {
    return selectedOption;
}

void RType::Settings::changeKey(std::string key) {
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
        set_key_value(cfg, "Keys7", newKey2.c_str());
        try {
            cfg.writeFile(configPath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            std::cerr << "Error while writing file: " << configPath << std::endl;
            return;
        }
        return;
    }
    else if (key.find("COLORBLIND") != std::string::npos) {
        if (key == "COLORBLIND: Normal") {
            newKey2 = "Deuteranopia";
        } else if (key == "COLORBLIND: Deuteranopia") {
            newKey2 = "Protanopia";
        } else if (key == "COLORBLIND: Protanopia") {
            newKey2 = "Tritanopia";
        } else if (key == "COLORBLIND: Tritanopia") {
            newKey2 = "Achromatopsia";
        } else if (key == "COLORBLIND: Achromatopsia") {
            newKey2 = "Normal";
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
    RenderTexture.draw(menuOptions[selectedOption]);
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

void RType::Settings::displayInput()
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
    if (!ShootInputTexture.loadFromFile(std::string("assets") + PATH_SEPARATOR + "input" + PATH_SEPARATOR + "Keyboard" + PATH_SEPARATOR + "keyboard_" + shootinput + ".png")) {
        std::cerr << "Error loading shoot input texture" << std::endl;
        return;
    }
    ShootInputSprite.setTexture(ShootInputTexture);

    for (int i = 0; i < 4; ++i) {
        std::string arrowKey = "Keys" + std::to_string(i + 1);
        std::string arrowInput = std::string(get_key_value(cfg, arrowKey.c_str()));
        std::transform(arrowInput.begin(), arrowInput.end(), arrowInput.begin(), ::tolower);
        if (!arrowTexture[i].loadFromFile(std::string("assets") + PATH_SEPARATOR + "input" + PATH_SEPARATOR + "Keyboard" + PATH_SEPARATOR + "keyboard_" + arrowInput + ".png")) {
            std::cerr << "Error loading arrow input texture for " << arrowKey << std::endl;
            return;
        }
        arrowSprite[i].setTexture(arrowTexture[i]);
    }

    RenderTexture.draw(ShootInputSprite);
    for (int i = 0; i < 4; ++i) {
        RenderTexture.draw(arrowSprite[i]);
    }
}

void RType::Settings::runScene()
{
    
}

void RType::Settings::display() {
    RenderTexture.clear();
    RenderTexture.draw(background);
    RenderTexture.draw(logoSprite);
    displayInput();

    for (int i = 0; i < 8; ++i) {
        RenderTexture.draw(menuOptions[i]);
    }
    RenderTexture.display();
    sf::Sprite sprite(RenderTexture.getTexture());
        libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";

    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    std::string colorblind = std::string(get_key_value(cfg, "Keys8"));
    if (colorblind.find("Deuteranopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[0]);
    } else if (colorblind.find("Protanopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[1]);
    } else if (colorblind.find("Tritanopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[2]);
    } else if (colorblind.find("Achromatopsia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[3]);
    } else {
        window->draw(sprite, &colorblindShader[4]);
    }
    window->display();

}

void RType::Settings::initTextAndSprites()
{
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    std::string optionsText[] = {"UP         : ", "DOWN       : ", "LEFT       : ", "RIGHT      : ",
                                 "SHOOT      : ", "SETTINGS   : ",  "SUBTITLES : ", "COLORBLIND : "};
    for (int i = 0; i < 8; i++) {
        optionsText[i] += get_key_value(cfg, ("Keys" + std::to_string(i + 1)).c_str());
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(1920 / 2 - 40, 200 + i * 100));
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

void RType::Settings::displaySettings(bool ingame)
{
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
                        case 7:
                            if (menuOptions[7].getString().toAnsiString().find("Normal") != std::string::npos) {
                                changeKey("COLORBLIND: Normal");
                                menuOptions[7].setString("COLORBLIND: Deuteranopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Deuteranopia") != std::string::npos) {
                                changeKey("COLORBLIND: Deuteranopia");
                                menuOptions[7].setString("COLORBLIND: Protanopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Protanopia") != std::string::npos) {
                                changeKey("COLORBLIND: Protanopia");
                                menuOptions[7].setString("COLORBLIND: Tritanopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Tritanopia") != std::string::npos) {
                                changeKey("COLORBLIND: Tritanopia");
                                menuOptions[7].setString("COLORBLIND: Achromatopsia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Achromatopsia") != std::string::npos) {
                                changeKey("COLORBLIND: Achromatopsia");
                                menuOptions[7].setString("COLORBLIND: Normal");
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