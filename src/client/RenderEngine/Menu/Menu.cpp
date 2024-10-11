/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#include "Menu.hpp"

RType::Menu::Menu(std::shared_ptr<sf::RenderWindow> wndw, std::shared_ptr<IMediator> mediator) {
    (void)mediator;
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
    if (!selectBuffer.loadFromFile("assets/Sounds/selectsound.wav")) {
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
    std::string soundPath = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "menu.ogg";
    if (!backgroundBuffer.loadFromFile(soundPath)) {
        throw std::runtime_error("Error loading select sound");
    }
    backgroundMusic.setBuffer(backgroundBuffer);
    try {
        // games = std::make_shared<Game>(window);
        settings = std::make_shared<Settings>(window);
        lobby    = std::make_shared<Lobby>(window);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    selectedOption = 0;
    backgroundMusic.play();
    backgroundMusic.setLoop(true);
}

void RType::Menu::draw() {
    window->draw(background);
    window->draw(logoSprite);

    for (int i = 0; i < 3; ++i) {
        window->draw(menuOptions[i]);
    }
}

void RType::Menu::moveUp() {
    if (selectedOption - 1 >= 0) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void RType::Menu::moveDown() {
    if (selectedOption + 1 < 3) {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int RType::Menu::getSelectedOption() const {
    return selectedOption;
}

void RType::Menu::adjustVolume(bool increase) {
    float currentVolume = backgroundMusic.getVolume();
    if (increase) {
        currentVolume = std::min(100.0f, currentVolume + 10.0f);
    } else {
        currentVolume = std::max(0.0f, currentVolume - 10.0f);
    }
    backgroundMusic.setVolume(currentVolume);
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

void RType::Menu::displaySound() {
    float currentVolume    = backgroundMusic.getVolume();
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

    window->draw(volumeBarBackground);
    window->draw(volumeBarForeground);
    window->draw(volumeTextShadow);
    window->draw(volumeText);
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

    window->draw(backgroundRect);
    window->draw(subtitleShadow);
    window->draw(subtitle);
}

int RType::Menu::displayMenu() {
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
                    backgroundMusic.stop();
                    return (1);
                case 1:
                    return (2);
                case 2:
                    backgroundMusic.stop();
                    return (3);
                }
                break;
            default:
                break;
            }
        }
    }
    draw();
    displaySound();
    config_t cfg;
    config_init(&cfg);
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    if (!config_read_file(&cfg, configPath.c_str())) {
        printf("Error while loading config file!\n");
        config_destroy(&cfg);
        return (84);
    }
    std::string keyValue = settings->get_key_value(&cfg, "Keys7");
    if (keyValue == "ON") {
        displaySubtitles();
    }

    return (0);
}

void RType::Menu::setMediator(std::shared_ptr<RType::IMediator> mediator) {
    _mediator = mediator;
}
