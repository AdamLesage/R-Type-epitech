#include "Lobby.hpp"

RType::Lobby::Lobby(std::shared_ptr<sf::RenderWindow> _window) : window(_window), selectedOption(0)
{
    this->window = _window;
    if (!font.loadFromFile("src/client/asset/r-type.ttf"))
    {
        throw std::runtime_error("Error loading font");
    }

    playerTextures.resize(5);
    playerSprites.resize(5);

    for (int i = 0; i < 5; ++i)
    {
        playersNames[i].setFont(font);
        playersNames[i].setString("Player " + std::to_string(i + 1));
        playersNames[i].setCharacterSize(24);
        playersNames[i].setFillColor(sf::Color::White);

        if (!playerTextures[i].loadFromFile("src/client/asset/player/player_" + std::to_string(i + 1) + ".png"))
        {
            throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
        }
        playerSprites[i].setTexture(playerTextures[i]);
        playerSprites[i].setTextureRect(sf::IntRect(0, 0, 263, 116));
        playerSprites[i].setScale(0.7, 0.7);
    }

    float totalHeight = window->getSize().y;
    float playerAreaHeight = 500;
    float playerStartY = (totalHeight - playerAreaHeight) / 2.0f;

    for (int i = 0; i < 5; ++i)
    {
        float verticalSpacing = 100;
        float currentY = playerStartY + i * verticalSpacing;

        playersNames[i].setPosition(window->getSize().x / 3.0f, currentY);
        playerSprites[i].setPosition((window->getSize().x / 3.0f) + 200, currentY - 10);
    }

    if (!backgroundBuffer.loadFromFile("src/client/asset/Sounds/lobby.ogg"))
    {
        throw std::runtime_error("Error loading background music");
    }
    backgroundMusic.setBuffer(backgroundBuffer);

    if (!backgroundTexture.loadFromFile("src/client/asset/background/menu.jpg"))
    {
        throw std::runtime_error("Error loading background texture");
    }
    if (!logoTexture.loadFromFile("src/client/asset/rtypelogo.png"))
    {
        throw std::runtime_error("Error loading logo texture");
    }
    background.setTexture(&backgroundTexture);
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(window->getSize().x / 2.0f - logoTexture.getSize().x / 2.0f, 50);
    if (!selectBuffer.loadFromFile("src/client/asset/Sounds/selectsound.wav"))
    {
        throw std::runtime_error("Error loading select sound");
    }
    selectSound.setBuffer(selectBuffer);

    std::string optionsText[] = {"1. Play", "2. Settings", "3. Quit"};
    for (int i = 0; i < 3; ++i)
    {
        menuOptions[i].setFont(font);
        menuOptions[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menuOptions[i].setString(optionsText[i]);

        float optionWidth = menuOptions[i].getLocalBounds().width;
        float totalMenuWidth = (3 * optionWidth) + (2 * 100);
        float xPos = (window->getSize().x / 2.0f) - (totalMenuWidth / 2.0f) + i * (optionWidth + 100);
        menuOptions[i].setPosition(xPos, window->getSize().y - 100);
    }

    try
    {
        games = std::make_shared<Game>(window);
        // games->setMediator(std::shared_ptr<IMediator>(this->_mediator));
        settings = std::make_shared<Settings>(window);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

RType::Lobby::~Lobby() = default;

void RType::Lobby::moveRight()
{
    if (selectedOption + 1 < 3)
    {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

void RType::Lobby::moveLeft()
{
    if (selectedOption - 1 >= 0)
    {
        menuOptions[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
        selectSound.play();
    }
}

int RType::Lobby::getSelectedOption() const
{
    return selectedOption;
}

void RType::Lobby::adjustVolume(bool increase)
{
    float currentVolume = backgroundMusic.getVolume();
    if (increase)
    {
        currentVolume = std::min(100.0f, currentVolume + 10.0f);
    }
    else
    {
        currentVolume = std::max(0.0f, currentVolume - 10.0f);
    }
    backgroundMusic.setVolume(currentVolume);
}

void RType::Lobby::handleKeyPress(const sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
    {
        adjustVolume(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
    {
        adjustVolume(false);
    }
}

void RType::Lobby::displaySound()
{
    float currentVolume = backgroundMusic.getVolume();
    float maxVolume = 100.0f;
    float volumeBarWidth = 200.0f;
    float volumeBarHeight = 20.0f;
    float volumePercentage = currentVolume / maxVolume;

    sf::RectangleShape volumeBarBackground(sf::Vector2f(volumeBarWidth, volumeBarHeight));
    volumeBarBackground.setFillColor(sf::Color(0, 0, 75)); 
    volumeBarBackground.setPosition(window->getSize().x - volumeBarWidth - 20, 20);

    sf::RectangleShape volumeBarForeground(sf::Vector2f(volumeBarWidth * volumePercentage, volumeBarHeight));
    volumeBarForeground.setFillColor(sf::Color::Green);
    volumeBarForeground.setPosition(window->getSize().x - volumeBarWidth - 20, 20);

    sf::Text volumeText;
    volumeText.setFont(font);
    volumeText.setString("Volume:");
    volumeText.setCharacterSize(24);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(window->getSize().x - volumeBarWidth - 100, 20);

    window->draw(volumeBarBackground);
    window->draw(volumeBarForeground);
    window->draw(volumeText);
}

void RType::Lobby::displayLobby()
{
    if (!window) {
        std::cerr << "Error: window is null" << std::endl;
        return;
    }
    backgroundMusic.play();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            handleKeyPress(event);
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    moveRight();
                    break;
                case sf::Keyboard::Left:
                    moveLeft();
                    break;
                case sf::Keyboard::Return:
                    switch (getSelectedOption())
                    {
                    case 0: // Start game
                        backgroundMusic.stop();
                        if (_mediator != nullptr) {
                            _mediator->notify("RenderingEngine", "play");
                        } else {
                            std::cerr << "Error: Mediator is null" << std::endl;
                        }
                        games->_mediator = _mediator;
                        games->displayGame();
                        break;
                    case 1:
                        settings->displaySettings(false);
                        break;
                    case 2:
                        backgroundMusic.stop();
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
        window->draw(background);
        window->draw(logoSprite);

        for (const auto &option : menuOptions)
        {
            window->draw(option);
        }

        for (int i = 0; i < 5; ++i)
        {
            window->draw(playersNames[i]);
            window->draw(playerSprites[i]);
        }
        displaySound();
        window->display();
    }
}

void RType::Lobby::setMediator(std::shared_ptr<RType::IMediator> mediator)
{
    _mediator = mediator;
}
