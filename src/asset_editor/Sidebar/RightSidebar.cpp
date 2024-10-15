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
    float assetsTextPosX = window.getSize().x * 0.75 + 150;
    float assetsTextPosY = 0;
    float componentsTextPosX = assetsTextPosX + 100 + gap;
    float componentsTextPosY = 0;

    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur lors du chargement de la police " << fontPath << std::endl;
        return;
    }

    sf::Text assetsText;
    assetsText.setFont(font);
    assetsText.setString("Assets");
    assetsText.setCharacterSize(30);
    assetsText.setFillColor(sf::Color::White);
    assetsText.setPosition(assetsTextPosX, assetsTextPosY);

    // create background rectangle around "Assets"
    sf::FloatRect assetsBounds = assetsText.getGlobalBounds();
    sf::RectangleShape assetsBackground(sf::Vector2f(assetsBounds.width + padding, assetsBounds.height + padding));
    assetsBackground.setPosition(assetsBounds.left - padding / 2, assetsBounds.top - padding / 2);
    if (_currentSidebarSelection == "Assets") assetsBackground.setFillColor(sf::Color(125, 125, 125));
    else assetsBackground.setFillColor(sf::Color(50, 50, 50));

    sf::Text componentsText;
    componentsText.setFont(font);
    componentsText.setString("Components");
    componentsText.setCharacterSize(30);
    componentsText.setFillColor(sf::Color::White);
    componentsText.setPosition(componentsTextPosX, componentsTextPosY);

    // Ajuster le rectangle autour de "Components"
    sf::FloatRect componentsBounds = componentsText.getGlobalBounds();
    sf::RectangleShape componentsBackground(sf::Vector2f(componentsBounds.width + padding, componentsBounds.height + padding));
    componentsBackground.setPosition(componentsBounds.left - padding / 2, componentsBounds.top - padding / 2);
    if (_currentSidebarSelection == "Components") componentsBackground.setFillColor(sf::Color(125, 125, 125));
    else componentsBackground.setFillColor(sf::Color(50, 50, 50));

    // Vérifier la position de la souris
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Mettre en surbrillance le fond si la souris passe dessus
    if (mousePos.x >= assetsBackground.getPosition().x && mousePos.x <= assetsBackground.getPosition().x + assetsBackground.getSize().x
        && mousePos.y >= assetsBackground.getPosition().y && mousePos.y <= assetsBackground.getPosition().y + assetsBackground.getSize().y) {
        assetsBackground.setFillColor(sf::Color(100, 100, 100));  // Couleur survolée
        // Vérifier le clic sur "Assets"
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->setCurrentSidebarSelection("Assets");
            assetsBackground.setFillColor(sf::Color(175, 175, 175));
        }
    }

    if (mousePos.x >= componentsBackground.getPosition().x && mousePos.x <= componentsBackground.getPosition().x + componentsBackground.getSize().x
        && mousePos.y >= componentsBackground.getPosition().y && mousePos.y <= componentsBackground.getPosition().y + componentsBackground.getSize().y) {
        componentsBackground.setFillColor(sf::Color(100, 100, 100));  // Couleur survolée
        // Vérifier le clic sur "Components"
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->setCurrentSidebarSelection("Components");
            componentsBackground.setFillColor(sf::Color(175, 175, 175));
        }
    }

    // Dessiner les rectangles de fond et les textes
    window.draw(assetsBackground);
    window.draw(assetsText);
    window.draw(componentsBackground);
    window.draw(componentsText);
}


void Edition::RightSidebar::draw(sf::RenderWindow &window)
{
    this->drawContainer(window);
    this->drawCloseContainer(window);
    this->displayTabSelections(window);
}