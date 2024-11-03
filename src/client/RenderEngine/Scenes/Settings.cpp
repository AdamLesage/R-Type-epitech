/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#include "Settings.hpp"
RType::Settings::Settings(std::shared_ptr<sf::RenderWindow> _window) {
    this->window = _window;
    if (!font.loadFromFile(std::string("assets") + PATH_SEPARATOR + "r-type.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    if (!logoTexture.loadFromFile(std::string("assets") + PATH_SEPARATOR + "rtypelogo.png")) {
        std::cerr << "Error loading logo" << std::endl;
        return;
    }

    if (!backgroundTexture.loadFromFile(std::string("assets") + PATH_SEPARATOR + "background" + PATH_SEPARATOR
                                        + "menu.jpg")) {
        std::cerr << "Error loading background" << std::endl;
        return;
    }

    background.setTexture(&backgroundTexture);
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(1920, 1080));
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(sf::Vector2f(0, 0));
    if (!colorblindShader[0].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                              + PATH_SEPARATOR // loard tge shader for the Deuteranopia
                                              + "Deuteranopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading deuteranopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[1].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                              + PATH_SEPARATOR // loard tge shader for the Protanopia
                                              + "Protanopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading protanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[2].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                              + PATH_SEPARATOR // loard tge shader for the Tritanopia
                                              + "Tritanopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading tritanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[3].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                              + PATH_SEPARATOR // loard tge shader for the Achromatopsia
                                              + "Achromatopsia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading achromatopsia shader" << std::endl;
        return;
    }
    if (!colorblindShader[4].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                              + PATH_SEPARATOR // loard tge shader for the Normal
                                              + "Normal_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading normal shader" << std::endl;
        return;
    }
    RenderTexture.create(1920, 1080);
}

RType::Settings::~Settings() {
}

const std::string
RType::Settings::get_key_value(libconfig::Config& cfg,
                               const std::string key_name) { // get the value of a key from the cfg file
    std::string value;
    std::string keys = "Keys." + key_name + ".value";

    try {
        cfg.lookupValue(keys.c_str(), value);
        return value;
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Key not found: " << key_name << std::endl;
        return NULL;
    }
}

int RType::Settings::set_key_value(libconfig::Config& cfg,
                                   const std::string key_name,
                                   const std::string new_value) { // set the value of a key from the cfg file
    std::string path = "Keys." + key_name + ".value";
    try {
        if (cfg.exists(path)) {
            libconfig::Setting& setting = cfg.lookup(path);
            setting                     = new_value;
            return 0;
        } else {
            std::cerr << "Key not found: " << key_name << std::endl;
            return -1;
        }
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Key not found: " << key_name << std::endl;
        return -1;
    } catch (const libconfig::SettingTypeException& tex) {
        std::cerr << "Invalid type for key: " << key_name << std::endl;
        return -1;
    }
}

void RType::Settings::moveUp() {   // move up the selected option
    if (selectedOption - 1 >= 0) { // for the 9 options of menuOptions such as UP, DOWN, LEFT, RIGHT, SHOOT,
                                   // SETTINGS, SUBTITLES, COLORBLIND, FRIENDLY FIRE
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        selectSound.play();
    }
}

void RType::Settings::moveDown() { // move down the selected option
    if (selectedOption + 1 < 9) {  // for the 9 options of menuOptions such as UP, DOWN, LEFT, RIGHT, SHOOT,
                                   // SETTINGS, SUBTITLES, COLORBLIND, FRIENDLY FIRE
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        selectSound.play();
    }
}

int RType::Settings::getSelectedOption() const { // get the selected option
    return selectedOption;
}

void RType::Settings::changeKey(std::string key) { // change the key of the selected option
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
    if (key == "SUBTITLES: ON" || key == "SUBTITLES: OFF") { // if the key is subtitles on or off
        if (key.find("ON") != std::string::npos) {
            newKey2 = "OFF";
        } else {
            newKey2 = "ON";
        }
        set_key_value(cfg, "Keys7", newKey2); // set the value of the key 7 to the new subtitles value
        try {
            cfg.writeFile(configPath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            std::cerr << "Error while writing file: " << configPath << std::endl;
            return;
        }
        return;
    } else if (key.find("COLORBLIND")
               != std::string::npos) { // if the key is colorblind set to normal, deuteranopia, protanopia,
                                       // tritanopia, achromatopsia
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
        set_key_value(cfg, "Keys8", newKey2); // set the value of the key 8 to the new colorblind
                                              // value
        try {
            cfg.writeFile(configPath.c_str());
        } catch (const libconfig::FileIOException& fioex) {
            std::cerr << "Error while writing file: " << configPath << std::endl;
            return;
        }
        return;
    } else if (key == "FRIENDLY FIRE: ON"
               || key == "FRIENDLY FIRE: OFF") { // if the key is friendly fire on or off
        if (key.find("ON") != std::string::npos) {
            newKey2 = "OFF";
        } else {
            newKey2 = "ON";
        }
        set_key_value(cfg, "Keys9",
                      newKey2); // set the value of the key 9 to the new friendly fire value
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
                } else if (event2.key.code
                           == sf::Keyboard::Space) { // if the key is space change the display to SPACE
                    newKey2 = "SPACE";
                } else if (event2.key.code
                           == sf::Keyboard::Escape) { // if the key is escape change the display to ESCAPE
                    newKey2 = "ESCAPE";
                } else if (event2.key.code == sf::Keyboard::Right) { // if the key is right arrow change the
                                                                     // display to Right arrow
                    newKey2 = "Right arrow";
                } else if (event2.key.code == sf::Keyboard::Left) { // if the key is left arrow change the
                                                                    // display to Left arrow
                    newKey2 = "Left arrow";
                } else if (event2.key.code == sf::Keyboard::Down) { // if the key is down arrow change the
                                                                    // display to Down arrow
                    newKey2 = "Down arrow";
                } else if (event2.key.code
                           == sf::Keyboard::Up) { // if the key is up arrow change the display to Up arrow
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
    set_key_value(cfg, ("Keys" + std::to_string(selectedOption + 1)),
                  newKey2); // set the value of the selected option to the new key
    try {
        cfg.writeFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while writing file: " << configPath << std::endl;
        return;
    }
}

void RType::Settings::displayInput() { // display a sprite for the input of the settings
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";

    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    std::string keys5      = "Keys5";
    std::string shootinput = std::string(get_key_value(cfg, keys5));
    std::transform(shootinput.begin(), shootinput.end(), shootinput.begin(), ::tolower);
    if (!ShootInputTexture.loadFromFile(std::string("assets") + PATH_SEPARATOR + "input" + PATH_SEPARATOR
                                        + "Keyboard" + PATH_SEPARATOR + "keyboard_" + shootinput + ".png")) {
        std::cerr << "Error loading shoot input texture" << std::endl;
        return;
    }
    ShootInputSprite.setTexture(ShootInputTexture);

    for (int i = 0; i < 4; ++i) {
        std::string arrowKey   = "Keys" + std::to_string(i + 1);
        std::string arrowInput = std::string(get_key_value(cfg, arrowKey));
        std::transform(arrowInput.begin(), arrowInput.end(), arrowInput.begin(), ::tolower);
        if (!arrowTexture[i].loadFromFile(std::string("assets") + PATH_SEPARATOR + "input" + PATH_SEPARATOR
                                          + "Keyboard" + PATH_SEPARATOR + "keyboard_" + arrowInput
                                          + ".png")) {
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

void RType::Settings::runScene(float& latency)
{
    (void)latency;
}

void RType::Settings::display() {
    RenderTexture.clear();
    RenderTexture.draw(background);
    RenderTexture.draw(logoSprite);
    displayInput();

    for (int i = 0; i < 9; ++i) {
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
    std::string Keys8      = "Keys8";
    std::string colorblind = std::string(get_key_value(cfg, Keys8));
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

void RType::Settings::initTextAndSprites() {
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    std::string optionsText[] = {
        "UP            : ", "DOWN          : ", "LEFT          : ", "RIGHT         : ", "SHOOT         : ",
        "SETTINGS      : ", "SUBTITLES     : ", "COLORBLIND    : ", "FRIENDLY FIRE : "};
    for (int i = 0; i < 9; i++) { // display the options of the settings with the keys
        optionsText[i] += get_key_value(cfg, ("Keys" + std::to_string(i + 1)));
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(1920 / 2 - 40, 150 + i * 100));
    }
    sf::Vector2f shootInputPosition = menuOptions[4].getPosition();
    shootInputPosition.x -= 80;
    shootInputPosition.y -= 10;
    ShootInputSprite.setPosition(shootInputPosition);

    for (int i = 0; i < 4; ++i) { // display the arrows of the settings
        sf::Vector2f arrowPosition = menuOptions[i].getPosition();
        arrowPosition.x -= 80;
        arrowPosition.y -= 10;
        arrowSprite[i].setPosition(arrowPosition);
    }
}

void RType::Settings::displaySettings(bool ingame) {
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
                if (event.type == sf::Event::Closed) {
                    sendStateChange(-1);
                }
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
                            if (menuOptions[7].getString().toAnsiString().find("Normal")
                                != std::string::npos) {
                                changeKey("COLORBLIND: Normal");
                                menuOptions[7].setString("COLORBLIND: Deuteranopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Deuteranopia")
                                       != std::string::npos) {
                                changeKey("COLORBLIND: Deuteranopia");
                                menuOptions[7].setString("COLORBLIND: Protanopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Protanopia")
                                       != std::string::npos) {
                                changeKey("COLORBLIND: Protanopia");
                                menuOptions[7].setString("COLORBLIND: Tritanopia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Tritanopia")
                                       != std::string::npos) {
                                changeKey("COLORBLIND: Tritanopia");
                                menuOptions[7].setString("COLORBLIND: Achromatopsia");
                            } else if (menuOptions[7].getString().toAnsiString().find("Achromatopsia")
                                       != std::string::npos) {
                                changeKey("COLORBLIND: Achromatopsia");
                                menuOptions[7].setString("COLORBLIND: Normal");
                            }
                            break;
                        case 8:
                            if (menuOptions[8].getString().toAnsiString().find("ON") != std::string::npos) {
                                changeKey("FRIENDLY FIRE: ON");
                                menuOptions[8].setString("FRIENDLY FIRE: OFF");
                            } else {
                                changeKey("FRIENDLY FIRE: OFF");
                                menuOptions[8].setString("FRIENDLY FIRE: ON");
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