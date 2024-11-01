#include "Lobby.hpp"

RType::Lobby::Lobby(std::shared_ptr<sf::RenderWindow> _window) : window(_window), selectedOption(0) {
    this->window         = _window;
    this->_isOffline     = false;
    music                = false;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font");
    }
    playerTextures.resize(5);
    playerSprites.resize(5);
    backgroundMusicVolume = 100;
    for (int i = 0; i < 5; ++i) {
        playersNames[i].setFont(font);
        playersNames[i].setString("Player " + std::to_string(i + 1));
        playersNames[i].setCharacterSize(24);
        playersNames[i].setFillColor(sf::Color::White);
    }

    float totalHeight      = window->getSize().y;
    float playerAreaHeight = 500;
    float playerStartY     = (totalHeight - playerAreaHeight) / 2.0f;

    for (int i = 0; i < 5; ++i) {
        float verticalSpacing = 100;
        float currentY        = playerStartY + i * verticalSpacing;

        playersNames[i].setPosition(window->getSize().x / 3.0f, currentY);
        playerSprites[i].setPosition((window->getSize().x / 3.0f) + 200, currentY - 10);
    }

    if (!backgroundTexture.loadFromFile("assets/background/menu.jpg")) {
        throw std::runtime_error("Error loading background texture");
    }
    if (!logoTexture.loadFromFile("assets/rtypelogo.png")) {
        throw std::runtime_error("Error loading logo texture");
    }
    background.setTexture(&backgroundTexture);
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(window->getSize().x / 2.0f - logoTexture.getSize().x / 2.0f, 50);

    std::string optionsText[] = {"1. Play", "2. Settings", "3. Quit"};
    for (int i = 0; i < 3; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);

        float optionWidth    = menuOptions[i].getLocalBounds().width;
        float totalMenuWidth = (3 * optionWidth) + (2 * 100);
        float xPos = (window->getSize().x / 2.0f) - (totalMenuWidth / 2.0f) + i * (optionWidth + 100);
        menuOptions[i].setPosition(xPos, window->getSize().y - 200);
    }

    try {
        settings = std::make_shared<Settings>(window);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    if (!colorblindShader[0].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR
                                              + "Deuteranopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading deuteranopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[1].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR
                                              + "Protanopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading protanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[2].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR
                                              + "Tritanopia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading tritanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[3].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR
                                              + "Achromatopsia_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading achromatopsia shader" << std::endl;
        return;
    }
    if (!colorblindShader[4].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR
                                              + "Normal_shader.frag",
                                          sf::Shader::Fragment)) {
        std::cerr << "Error loading normal shader" << std::endl;
        return;
    }
    RenderTexture.create(1920, 1080);
}

RType::Lobby::~Lobby() = default;

void RType::Lobby::moveRight() {
    if (selectedOption + 1 < 3) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        _mediator->notify("RenderingEngine", "selectSound");
    }
}

void RType::Lobby::moveLeft() {
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Red);
        _mediator->notify("RenderingEngine", "selectSound");
    }
}

int RType::Lobby::getSelectedOption() const {
    return selectedOption;
}

void RType::Lobby::setVolume(float number) {
    backgroundMusicVolume = number;
}

void RType::Lobby::adjustVolume(bool increase) {
    if (increase) _mediator->notify("RenderingEngine", "adjustVolume2 True");
    if (!increase) _mediator->notify("RenderingEngine", "adjustVolume2 False");
}

void RType::Lobby::handleKeyPress(const sf::Event& event) {
    (void)event;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
        adjustVolume(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
        adjustVolume(false);
    }
}

void RType::Lobby::displaySound() {
    _mediator->notify("RenderingEngine", "getVolume2");
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

void RType::Lobby::displaySubtitles() {
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

void RType::Lobby::displayConnectedPlayer() {
    float totalHeight      = window->getSize().y;
    float playerAreaHeight = 500;
    float playerStartY     = (totalHeight - playerAreaHeight) / 2.0f;
    for (size_t i = 0; _camera->listEntityToDisplay.size() != i; ++i) {
        try {
            if (!playerTextures[i].loadFromFile(_camera->listEntityToDisplay[i].sprite.spritePath)) {
                throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        playerSprites[i].setTexture(playerTextures[i]);
        playerSprites[i].setTextureRect(sf::IntRect(_camera->listEntityToDisplay[i].sprite.rectPos[0],
                                                    _camera->listEntityToDisplay[i].sprite.rectPos[1],
                                                    _camera->listEntityToDisplay[i].sprite.rectSize[0],
                                                    _camera->listEntityToDisplay[i].sprite.rectSize[1]));
        playerSprites[i].setScale(0.7, 0.7);
        float verticalSpacing = 100;
        float currentY        = playerStartY + i * verticalSpacing;
        playersNames[i].setPosition(window->getSize().x / 3.0f, currentY);
        playerSprites[i].setPosition((window->getSize().x / 3.0f) + 200, currentY - 10);
        RenderTexture.draw(playersNames[i]);
        RenderTexture.draw(playerSprites[i]);
    }
}

void RType::Lobby::runScene(float& latency) {
    (void)latency;
    if (!window) {
        std::cerr << "Error: window is null" << std::endl;
        return;
    }
    sf::Event event;
    if (music != true) {
        music = true;
        _mediator->notify("RenderingEngine", "backgroundMusicStop");
        _mediator->notify("RenderingEngine", "backgroundMusicPlay2");
    }
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        handleKeyPress(event);
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Right:
                moveRight();
                break;
            case sf::Keyboard::Left:
                moveLeft();
                break;
            case sf::Keyboard::Return:
                switch (getSelectedOption()) {
                case 0: // Start game
                    this->_mediator->notify("Mediator", "backgroundMusicStop2");
                    std::cout << "Game is: " << (_isOffline == false ? "Online" : "Offline") << std::endl;
                    if (_isOffline == false) {
                        this->sendStateChange(3);
                    } else { // Notify the mediator to start the game offline
                        this->_mediator->notify("RenderingEngine", "Start offline game");
                    }
                    break;
                case 1:
                    settings->displaySettings(false);
                    break;
                case 2:
                    this->sendStateChange(-1);
                    this->_mediator->notify("Mediator", "backgroundMusicStop2");
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
    RenderTexture.draw(background);
    RenderTexture.draw(logoSprite);

    for (const auto& option : menuOptions) {
        RenderTexture.draw(option);
    }
    displayConnectedPlayer();
    displaySound();
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
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
}

void RType::Lobby::setCamera(std::shared_ptr<Camera> camera) {
    this->_camera = camera;
}

void RType::Lobby::setMutex(std::shared_ptr<std::mutex> mutex) {
    this->_mutex = mutex;
}