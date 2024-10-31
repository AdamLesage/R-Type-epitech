/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#include "Menu.hpp"

RType::Menu::Menu(std::shared_ptr<sf::RenderWindow> wndw) {
    window = wndw;
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
    std::string optionsText[] = {"1. Lobby", "2. Settings", "3. Quit"};
    for (int i = 0; i < 3; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setPosition(sf::Vector2f(200, 300 + i * 100));
    }
    selectedOption = 0;
    std::string shaderPath = std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR;
    if (!colorblindShader[0].loadFromFile(shaderPath + "Deuteranopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading deuteranopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[1].loadFromFile(shaderPath + "Protanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading protanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[2].loadFromFile(shaderPath + "Tritanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading tritanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[3].loadFromFile(shaderPath + "Achromatopsia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading achromatopsia shader" << std::endl;
        return;
    }
    if (!colorblindShader[4].loadFromFile(shaderPath + "Normal_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading normal shader" << std::endl;
        return;
    }
    RenderTexture.create(1920, 1080);
    backgroundMusicVolume = 100.0f;
}

void RType::Menu::draw() {
    RenderTexture.draw(background);
    RenderTexture.draw(logoSprite);

    for (int i = 0; i < 3; ++i) {
        RenderTexture.draw(menuOptions[i]);
    }
}

void RType::Menu::moveUp() {
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        _mediator->notify("RenderingEngine", "selectSound");
    }
}

void RType::Menu::moveDown() {
    if (selectedOption + 1 < 3) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        _mediator->notify("RenderingEngine", "selectSound");
    }
}

int RType::Menu::getSelectedOption() const {
    return selectedOption;
}

void RType::Menu::adjustVolume(bool increase) {
    if (increase)
        _mediator->notify("RenderingEngine", "adjustVolume True");
    if (!increase)
        _mediator->notify("RenderingEngine", "adjustVolume False");
}

void RType::Menu::handleKeyPress(const sf::Event& event) {
    (void)event;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
        adjustVolume(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
        adjustVolume(false);
    }
}
void RType::Menu::setVolume(float number) {
    backgroundMusicVolume = number;
}

void RType::Menu::displaySound() {
    _mediator->notify("RenderingEngine", "getVolume");
    float currentVolume    = backgroundMusicVolume;
    float maxVolume        = 100.0f;
    float volumeBarWidth   = 200.0f;
    float volumeBarHeight  = 20.0f;
    float volumePercentage = currentVolume / maxVolume;

    sf::RectangleShape volumeBarBackground(sf::Vector2f(volumeBarWidth, volumeBarHeight));
    volumeBarBackground.setFillColor(sf::Color(0, 0, 75));
    volumeBarBackground.setOutlineThickness(2);
    volumeBarBackground.setOutlineColor(sf::Color::White);
    volumeBarBackground.setPosition(window->getSize().x - volumeBarWidth - 20, 20);

    sf::RectangleShape volumeBarForeground(sf::Vector2f(volumeBarWidth * volumePercentage, volumeBarHeight));
    volumeBarForeground.setFillColor(sf::Color::Blue);
    volumeBarForeground.setPosition(window->getSize().x - volumeBarWidth - 20, 20);

    sf::Text volumeText;
    volumeText.setFont(font);
    volumeText.setString("Volume:");
    volumeText.setCharacterSize(24);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setStyle(sf::Text::Bold);
    volumeText.setPosition(window->getSize().x - volumeBarWidth - 120, 15);

    sf::Text volumeTextShadow = volumeText;
    volumeTextShadow.setFillColor(sf::Color(0, 0, 0, 150));
    volumeTextShadow.setPosition(volumeText.getPosition().x + 2, volumeText.getPosition().y + 2);

    RenderTexture.draw(volumeBarBackground);
    RenderTexture.draw(volumeBarForeground);
    RenderTexture.draw(volumeTextShadow);
    RenderTexture.draw(volumeText);
}

void RType::Menu::displaySubtitles() {
    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Press Enter to select an option, you can also use the arrow keys to navigate");
    subtitle.setCharacterSize(48);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = subtitle.getLocalBounds();
    subtitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    subtitle.setPosition(window->getSize().x / 2.0f, window->getSize().y - 50);

    sf::Text subtitleShadow = subtitle;
    subtitleShadow.setFillColor(sf::Color(0, 0, 130, 150));
    subtitleShadow.setPosition(subtitle.getPosition().x + 2, subtitle.getPosition().y + 2);

    sf::RectangleShape backgroundRect;
    backgroundRect.setSize(sf::Vector2f(textRect.width + 20, textRect.height + 20));
    backgroundRect.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundRect.setOrigin(backgroundRect.getSize().x / 2.0f, backgroundRect.getSize().y / 2.0f);
    backgroundRect.setPosition(subtitle.getPosition());

    RenderTexture.draw(backgroundRect);
    RenderTexture.draw(subtitleShadow);
    RenderTexture.draw(subtitle);
}

void RType::Menu::runScene() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        handleKeyPress(event);

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
                    this->_mediator->notify("Mediator", "backgroundMusicStop");
                    this->sendStateChange(2);
                    return;
                case 1:
                    this->settings->display();
                    break;
                case 2:
                    this->sendStateChange(-1);
                    this->_mediator->notify("Mediator", "backgroundMusicStop");
                    return;
                }
                break;
            default:
                break;
            }
        }
    }
    draw();
    displaySound();
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        // return 84;
    }
    std::string keyValue = settings->get_key_value(cfg, "Keys7");
    if (keyValue == "ON") {
        displaySubtitles();
    }
    RenderTexture.display();
    sf::Sprite sprite(RenderTexture.getTexture());
        std::string colorblind = settings->get_key_value(cfg, "Keys8");
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
    // return (0);
}
