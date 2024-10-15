#include "RightSidebar.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define LIB_EXTENSION ".dll"
    #define PATH_SEPARATOR "\\"
#else
    #include <dlfcn.h>
    #define LIB_EXTENSION ".so"
    #define PATH_SEPARATOR "/"
#endif

Edition::RightSidebar::RightSidebar()
{
    _currentSidebarSelection = "Assets";
    _isSidebarOpen = true;
}

Edition::RightSidebar::~RightSidebar()
{
}

void Edition::RightSidebar::toggleSidebar()
{
    static auto lastToggleTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastToggleTime);

    if (duration.count() >= 1) {
        _isSidebarOpen = !_isSidebarOpen;
        lastToggleTime = currentTime;
    }
}

void Edition::RightSidebar::drawContainer(sf::RenderWindow &window)
{
    static float currentWidth = window.getSize().x * 0.25;
    float targetWidth = _isSidebarOpen ? window.getSize().x * 0.25 : 0;
    float transitionSpeed = 10.0f; // Adjust this value for faster/slower transition

    if (currentWidth != targetWidth) {
        if (currentWidth < targetWidth) {
            currentWidth += transitionSpeed;
            if (currentWidth > targetWidth) currentWidth = targetWidth;
        } else {
            currentWidth -= transitionSpeed;
            if (currentWidth < targetWidth) currentWidth = targetWidth;
        }
    }

    unsigned int sidebarHeight = window.getSize().y;

    sf::RectangleShape sidebar(sf::Vector2f(currentWidth, sidebarHeight));
    sidebar.setFillColor(sf::Color(50, 50, 50));
    sidebar.setPosition(window.getSize().x - currentWidth, 0);

    // Set border
    sidebar.setOutlineThickness(1);
    sidebar.setOutlineColor(sf::Color::White);

    window.draw(sidebar);
}

void Edition::RightSidebar::drawCloseContainer(sf::RenderWindow &window)
{
    // Display a close button at the top left of the sidebar with a size of 20x20
    unsigned int closeSize = 40;
    static float closeButtonX = window.getSize().x * 0.75;
    float targetX = _isSidebarOpen ? window.getSize().x * 0.75 : window.getSize().x - closeSize;
    float transitionSpeed = 10.0f; // Adjust this value for faster/slower transition

    if (closeButtonX != targetX) {
        if (closeButtonX < targetX) {
            closeButtonX += transitionSpeed;
            if (closeButtonX > targetX) closeButtonX = targetX;
        } else {
            closeButtonX -= transitionSpeed;
            if (closeButtonX < targetX) closeButtonX = targetX;
        }
    }

    sf::RectangleShape close(sf::Vector2f(closeSize, closeSize));
    close.setFillColor(sf::Color(50, 50, 50));
    close.setPosition(closeButtonX, 0);

    // Set border
    close.setOutlineThickness(1);
    close.setOutlineColor(sf::Color::White);

    // Display icon like ">>" in the close button if the sidebar is opened or "<<" if the sidebar is closed
    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    font.loadFromFile(fontPath);
    sf::Text closeText;
    closeText.setFont(font);
    if (_isSidebarOpen == true) closeText.setString(">>");
    else closeText.setString("<<");
    closeText.setCharacterSize(30);
    closeText.setFillColor(sf::Color::White);
    closeText.setPosition(closeButtonX + 10, 0);

    // If the close button is clicked, toggle the sidebar
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x >= closeButtonX && mousePos.x <= closeButtonX + closeSize
            && mousePos.y >= 0 && mousePos.y <= closeSize) {
            this->toggleSidebar();
            return;
        }
    }

    window.draw(close);
    window.draw(closeText);
}

void Edition::RightSidebar::displayTabSelections(sf::RenderWindow &window)
{
    int gap = 10;
    int padding = 20;
    float startX = window.getSize().x * 0.75 + 75;
    float startY = 0;

    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur lors du chargement de la police " << fontPath << std::endl;
        return;
    }

    // Browse each element of _sidebarSelections
    float currentX = startX;
    for (size_t i = 0; i < _sidebarSelections.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(_sidebarSelections[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(currentX, startY);

        // Create a background rectangle for the text
        sf::FloatRect textBounds = text.getGlobalBounds();
        sf::RectangleShape background(sf::Vector2f(textBounds.width + padding, textBounds.height + padding));
        background.setPosition(textBounds.left - padding / 2, textBounds.top - padding / 2);

        // Set the background color to gray if the current selection is the same as the current element
        if (_currentSidebarSelection == _sidebarSelections[i]) {
            background.setFillColor(sf::Color(125, 125, 125));
        } else {
            background.setFillColor(sf::Color(50, 50, 50));
        }

        // Check if the mouse is over the current element
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x >= background.getPosition().x && mousePos.x <= background.getPosition().x + background.getSize().x &&
            mousePos.y >= background.getPosition().y && mousePos.y <= background.getPosition().y + background.getSize().y) {
            background.setFillColor(sf::Color(100, 100, 100));  // Couleur survolée

            // If the mouse is over the current element and the left button is pressed, set the current selection to the current element
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->setCurrentSidebarSelection(_sidebarSelections[i]);
                background.setFillColor(sf::Color(175, 175, 175));
            }
        }

        // Draw the background and the text
        window.draw(background);
        window.draw(text);

        // Update the currentX position for the next element
        currentX += textBounds.width + padding + gap;
    }
}



void Edition::RightSidebar::draw(sf::RenderWindow &window)
{
    this->drawContainer(window);
    this->drawCloseContainer(window);
    this->displayTabSelections(window);
}