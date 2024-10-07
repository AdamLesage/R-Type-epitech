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
                    case 0:
                        games->displayGame();
                        break;
                    case 1:
                        settings->displaySettings();
                        break;
                    case 2:
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

        window->display();
    }
}