/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#include "ComponentsEditor.hpp"

Edition::ComponentsEditor::ComponentsEditor() {
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    label.reset(new Input(sf::Vector2f(350, 40), sf::Vector2f(1500, 80), "Label: "));
    posX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1500, 200), "X: "));
    posY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1500 + 115, 200), "Y: "));
    sizeX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1500, 250 + 50), "X: "));
    sizeY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1500 + 115, 250 + 50), "Y: "));
    rotation.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1500, 350), "Angle: "));

    componentSelection.reset(new SelectButton({1460, 400}, {300, 50}, options));
    addButton = sf::RectangleShape({100, 50});
    addButton.setFillColor(sf::Color(20, 20, 20));
}

Edition::ComponentsEditor::~ComponentsEditor() {
}

void Edition::ComponentsEditor::displayCategoryTitle(std::shared_ptr<sf::RenderWindow> window,
                                                     std::string title,
                                                     float posX,
                                                     float posY) {
    sf::Text text;
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    window->draw(text);
}

void Edition::ComponentsEditor::displayAddComponent(std::shared_ptr<sf::RenderWindow> window, int& posY) {
    componentSelection->setPosition({1460, static_cast<float>(posY)});
    componentSelection->display(*window.get());

    addButton.setPosition({1460 + 315, static_cast<float>(posY)});
    sf::Text addText = sf::Text();
    addText.setFont(this->font);
    addText.setString("Add");
    addText.setCharacterSize(35);
    addText.setFillColor(sf::Color::White);
    const sf::FloatRect textBounds = addText.getLocalBounds();
    const sf::Vector2f boxSize     = addButton.getSize();
    addText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    addText.setPosition(addButton.getPosition().x + boxSize.x / 2.0f,
                        addButton.getPosition().y + boxSize.y / 2.0f);
    window->draw(addButton);
    window->draw(addText);
    posY += 100;
}

void Edition::ComponentsEditor::displaySprite(std::shared_ptr<sf::RenderWindow> window, int& posY) {
    if (this->spriteDisplay != nullptr) {
        displayCategoryTitle(window, "Sprite Properties", window->getSize().x * 0.76, posY);

        this->spriteDisplay->rectSizeX->setPosition({1500, static_cast<float>(posY) + 50});
        this->spriteDisplay->rectSizeX->displayInput(window);

        this->spriteDisplay->rectSizeY->setPosition({1500 + 250, static_cast<float>(posY) + 50});
        this->spriteDisplay->rectSizeY->displayInput(window);

        this->spriteDisplay->rectPosX->setPosition({1500, static_cast<float>(posY) + 100});
        this->spriteDisplay->rectPosX->displayInput(window);

        this->spriteDisplay->rectPosY->setPosition({1500 + 250, static_cast<float>(posY) + 100});
        this->spriteDisplay->rectPosY->displayInput(window);

        posY += 150;
    }
}

void Edition::ComponentsEditor::displayHealth(std::shared_ptr<sf::RenderWindow> window, int& posY) {
    if (this->healthDisplay != nullptr) {
        displayCategoryTitle(window, "Health", window->getSize().x * 0.76, posY);
        this->healthDisplay->health->setPosition({1500, static_cast<float>(posY) + 50});
        posY += 100;
        this->healthDisplay->health->displayInput(window);
    }
}

void Edition::ComponentsEditor::displayShootStraightPatternDisplay(std::shared_ptr<sf::RenderWindow> window,
                                                                   int& posY) {
    if (this->shootStraightPatternDisplay != nullptr) {
        displayCategoryTitle(window, "Pattern Shoot Straight", window->getSize().x * 0.76, posY);
        this->shootStraightPatternDisplay->projectileSpeed->setPosition(
            {1500, static_cast<float>(posY) + 50});
        this->shootStraightPatternDisplay->projectileSpeed->displayInput(window);
        this->shootStraightPatternDisplay->shootCooldown->setPosition({1500, static_cast<float>(posY) + 100});
        this->shootStraightPatternDisplay->shootCooldown->displayInput(window);
        posY += 150;
    }
}

void Edition::ComponentsEditor::displayShootPlayerPatternDisplay(std::shared_ptr<sf::RenderWindow> window,
                                                                 int& posY) {
    if (this->shootPlayerPatternDisplay != nullptr) {
        displayCategoryTitle(window, "Pattern Shoot Player", window->getSize().x * 0.76, posY);
        this->shootPlayerPatternDisplay->projectileSpeed->setPosition({1500, static_cast<float>(posY) + 50});
        this->shootPlayerPatternDisplay->projectileSpeed->displayInput(window);
        this->shootPlayerPatternDisplay->shootCooldown->setPosition({1500, static_cast<float>(posY) + 100});
        this->shootPlayerPatternDisplay->shootCooldown->displayInput(window);
        posY += 150;
    }
}

void Edition::ComponentsEditor::displayPlayerFollowingPatternDisplay(std::shared_ptr<sf::RenderWindow> window,
                                                                     int& posY) {
    if (this->playerFollowingPatternDisplay != nullptr) {
        displayCategoryTitle(window, "Player Following Pattern", window->getSize().x * 0.76, posY);
        this->playerFollowingPatternDisplay->speed->setPosition({1500, static_cast<float>(posY) + 50});
        this->playerFollowingPatternDisplay->speed->displayInput(window);
        posY += 100;
    }
}

void Edition::ComponentsEditor::displayStraightLinePatternDisplay(std::shared_ptr<sf::RenderWindow> window,
                                                                  int& posY) {
    if (this->straightLinePatternDisplay != nullptr) {
        displayCategoryTitle(window, "Straight Line Pattern", window->getSize().x * 0.76, posY);
        this->straightLinePatternDisplay->speed->setPosition({1500, static_cast<float>(posY) + 50});
        this->straightLinePatternDisplay->speed->displayInput(window);
        posY += 100;
    }
}

void Edition::ComponentsEditor::displayWavePatternDisplay(std::shared_ptr<sf::RenderWindow> window,
                                                          int& posY) {
    if (this->wavePatternDisplay != nullptr) {
        displayCategoryTitle(window, "Wave Pattern", window->getSize().x * 0.76, posY);
        this->wavePatternDisplay->amplitude->setPosition({1500, static_cast<float>(posY) + 50});
        this->wavePatternDisplay->amplitude->displayInput(window);
        this->wavePatternDisplay->frequency->setPosition({1500, static_cast<float>(posY) + 100});
        this->wavePatternDisplay->frequency->displayInput(window);
        posY += 150;
    }
}

void Edition::ComponentsEditor::displayTypeDisplay(std::shared_ptr<sf::RenderWindow> window, int& posY) {
    if (this->typeDisplay != nullptr) {
        displayCategoryTitle(window, "Type", window->getSize().x * 0.76, posY);
        this->typeDisplay->type->setPosition({1500, static_cast<float>(posY) + 50});
        this->typeDisplay->type->display(*window.get());
        posY += 150;
    }
}

void Edition::ComponentsEditor::display(std::shared_ptr<sf::RenderWindow> window) {
    currentPosY = 80 + this->scrollOffset;
    label->setPosition({1460, static_cast<float>(currentPosY)});
    label->displayInput(window);
    currentPosY += 50;
    displaySprite(window, currentPosY);
    displayCategoryTitle(window, "Position", window->getSize().x * 0.76, static_cast<float>(currentPosY));
    currentPosY += 50;
    posX->setPosition({1500, static_cast<float>(currentPosY)});
    posX->displayInput(window);
    posY->setPosition({1500 + 115, static_cast<float>(currentPosY)});
    posY->displayInput(window);
    currentPosY += 50;
    displayCategoryTitle(window, "Size", window->getSize().x * 0.76, static_cast<float>(currentPosY));
    currentPosY += 50;
    sizeX->setPosition({1500, static_cast<float>(currentPosY)});
    sizeX->displayInput(window);
    sizeY->setPosition({1500 + 115, static_cast<float>(currentPosY)});
    sizeY->displayInput(window);
    currentPosY += 50;
    displayCategoryTitle(window, "Rotation", window->getSize().x * 0.76, static_cast<float>(currentPosY));
    currentPosY += 50;
    rotation->setPosition({1500, static_cast<float>(currentPosY)});
    rotation->displayInput(window);
    currentPosY += 50;
    displayHealth(window, currentPosY);
    displayPlayerFollowingPatternDisplay(window, currentPosY);
    displayShootPlayerPatternDisplay(window, currentPosY);
    displayShootStraightPatternDisplay(window, currentPosY);
    displayStraightLinePatternDisplay(window, currentPosY);
    displayWavePatternDisplay(window, currentPosY);
    displayTypeDisplay(window, currentPosY);
    displayAddComponent(window, currentPosY);
    maxScrollOffset = (window->getSize().y + (80 + this->scrollOffset - currentPosY));
}

void Edition::ComponentsEditor::updateSelectedEntity(std::shared_ptr<Edition::Asset> asset) {
    _asset = asset;
    this->playerFollowingPatternDisplay.reset();
    this->shootStraightPatternDisplay.reset();
    this->shootPlayerPatternDisplay.reset();
    this->healthDisplay.reset();
    this->wavePatternDisplay.reset();
    this->typeDisplay.reset();

    auto& sprite        = this->_asset->getComponent<Sprite>();
    this->spriteDisplay = std::make_unique<SpriteDisplay>();
    this->spriteDisplay->initialize(sprite.rectSize, sprite.rectPos);
    try {
        auto& health        = this->_asset->getComponent<Health>();
        this->healthDisplay = std::make_unique<HealthDisplay>();
        this->healthDisplay->initialize(health.health);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        auto& pattern                       = this->_asset->getComponent<PlayerFollowingPattern>();
        this->playerFollowingPatternDisplay = std::make_unique<PlayerFollowingPatternDisplay>();
        this->playerFollowingPatternDisplay->initialize(pattern.speed);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        auto& pattern                     = this->_asset->getComponent<ShootStraightPattern>();
        this->shootStraightPatternDisplay = std::make_unique<ShootStraightPatternDisplay>();
        this->shootStraightPatternDisplay->initialize(pattern.projectileSpeed, pattern.shootCooldown);
    } catch (const std::exception& e) {
    }
    try {
        auto& pattern                   = this->_asset->getComponent<ShootPlayerPattern>();
        this->shootPlayerPatternDisplay = std::make_unique<ShootPlayerPatternDisplay>();
        this->shootPlayerPatternDisplay->initialize(pattern.projectileSpeed, pattern.shootCooldown);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        auto& pattern                    = this->_asset->getComponent<StraightLinePattern>();
        this->straightLinePatternDisplay = std::make_unique<StraightLinePatternDisplay>();
        this->straightLinePatternDisplay->initialize(pattern.speed);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        auto& pattern            = this->_asset->getComponent<Wave_pattern>();
        this->wavePatternDisplay = std::make_unique<Wave_patternDisplay>();
        this->wavePatternDisplay->initialize(pattern.amplitude, pattern.frequency);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        this->_asset->getComponent<Type>();
        this->typeDisplay = std::make_unique<TypeDisplay>();
        this->typeDisplay->initialize();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    this->posX->setInput(std::to_string(static_cast<int>(this->_asset->getComponent<Position>().x)));
    this->posY->setInput(std::to_string(static_cast<int>(this->_asset->getComponent<Position>().y)));
    this->sizeX->setInput(std::to_string(static_cast<int>(this->_asset->getComponent<Size>().x)));
    this->sizeY->setInput(std::to_string(static_cast<int>(this->_asset->getComponent<Size>().y)));
}

void Edition::ComponentsEditor::addComponent() {
    std::string selectedComponent = this->componentSelection->getSelectedOption();
    if (selectedComponent == "Health") {
        this->healthDisplay = std::make_unique<HealthDisplay>();
        this->healthDisplay->initialize(100);
        this->_asset->addComponent<Health>(Health{100, 100, false, true});
    }
    if (selectedComponent == "PlayerFollowingPattern") {
        this->playerFollowingPatternDisplay = std::make_unique<PlayerFollowingPatternDisplay>();
        this->playerFollowingPatternDisplay->initialize(1);
        this->_asset->addComponent<PlayerFollowingPattern>(PlayerFollowingPattern{1});
    }
    if (selectedComponent == "ShootStraightPattern") {
        this->shootStraightPatternDisplay = std::make_unique<ShootStraightPatternDisplay>();
        this->shootStraightPatternDisplay->initialize(1, 5);
        this->_asset->addComponent<ShootStraightPattern>(
            ShootStraightPattern{1, 5, std::chrono::steady_clock::now()});
    }
    if (selectedComponent == "ShootPlayerPattern") {
        this->shootPlayerPatternDisplay = std::make_unique<ShootPlayerPatternDisplay>();
        this->shootPlayerPatternDisplay->initialize(1, 5);
        this->_asset->addComponent<ShootPlayerPattern>(
            ShootPlayerPattern{1, 5, std::chrono::steady_clock::now()});
    }

    if (selectedComponent == "StraightLinePattern") {
        this->straightLinePatternDisplay = std::make_unique<StraightLinePatternDisplay>();
        this->straightLinePatternDisplay->initialize(-1);
        this->_asset->addComponent<StraightLinePattern>(StraightLinePattern{-1});
    }
    if (selectedComponent == "Wave_pattern") {
        this->wavePatternDisplay = std::make_unique<Wave_patternDisplay>();
        this->wavePatternDisplay->initialize(1.0, 0.02);
        this->_asset->addComponent<Wave_pattern>(Wave_pattern{1.0, 0.02, std::chrono::steady_clock::now()});
    }
    if (selectedComponent == "Type") {
        this->typeDisplay = std::make_unique<TypeDisplay>();
        this->typeDisplay->initialize();
        this->_asset->addComponent<Type>(Type{EntityType::ENEMY});
    }
}

void Edition::ComponentsEditor::handleSpriteInput(const sf::Event& event) {
    if (this->spriteDisplay != nullptr && this->_asset != nullptr) {
        auto& sprite = this->_asset->getComponent<Sprite>();
        if (this->spriteDisplay->rectSizeX->checkInput(event)) {
            std::string input = this->spriteDisplay->rectSizeX->getInput();
            if (!input.empty()) {
                int sizeX = std::stoi(input);
                this->_asset->addComponent<Sprite>(Sprite{
                    sprite.spritePath, {sizeX, sprite.rectSize[1]}, {sprite.rectPos[0], sprite.rectPos[1]}});
            }
        }
        if (this->spriteDisplay->rectSizeY->checkInput(event)) {
            std::string input = this->spriteDisplay->rectSizeY->getInput();
            if (!input.empty()) {
                int sizeY = std::stoi(input);
                this->_asset->addComponent<Sprite>(Sprite{
                    sprite.spritePath, {sprite.rectSize[0], sizeY}, {sprite.rectPos[0], sprite.rectPos[1]}});
            }
        }
        if (this->spriteDisplay->rectPosX->checkInput(event)) {
            std::string input = this->spriteDisplay->rectPosX->getInput();
            if (!input.empty()) {
                int posX = std::stoi(input);
                this->_asset->addComponent<Sprite>(Sprite{
                    sprite.spritePath, {sprite.rectSize[0], sprite.rectSize[1]}, {posX, sprite.rectPos[1]}});
            }
        }
        if (this->spriteDisplay->rectPosY->checkInput(event)) {
            std::string input = this->spriteDisplay->rectPosY->getInput();
            if (!input.empty()) {
                int posY = std::stoi(input);
                this->_asset->addComponent<Sprite>(Sprite{
                    sprite.spritePath, {sprite.rectSize[0], sprite.rectSize[1]}, {sprite.rectPos[0], posY}});
            }
        }
    }
}

void Edition::ComponentsEditor::handleHealthInput(const sf::Event& event) {
    if (this->healthDisplay != nullptr && this->_asset != nullptr) {
        if (this->healthDisplay->health->checkInput(event)) {
            std::string input = this->healthDisplay->health->getInput();
            if (input.empty())
                this->_asset->addComponent<Health>(Health{0, 100, false, true});
            else
                this->_asset->addComponent<Health>(Health{std::stoul(input), std::stoul(input), false, true});
        }
    }
}

void Edition::ComponentsEditor::handleShootStraightPatternInput(const sf::Event& event) {
    if (this->shootStraightPatternDisplay != nullptr && this->_asset != nullptr) {
        if (this->shootStraightPatternDisplay->projectileSpeed->checkInput(event)) {
            std::string input = this->shootStraightPatternDisplay->projectileSpeed->getInput();
            if (!input.empty())
                this->_asset->addComponent<ShootStraightPattern>(ShootStraightPattern{
                    std::stof(input), this->_asset->getComponent<ShootStraightPattern>().shootCooldown,
                    std::chrono::steady_clock::now()});
        }

        if (this->shootStraightPatternDisplay->shootCooldown->checkInput(event)) {
            std::string input = this->shootStraightPatternDisplay->shootCooldown->getInput();
            if (!input.empty())
                this->_asset->addComponent<ShootStraightPattern>(
                    ShootStraightPattern{this->_asset->getComponent<ShootStraightPattern>().projectileSpeed,
                                         std::stof(input), std::chrono::steady_clock::now()});
        }
    }
}

void Edition::ComponentsEditor::handleShootPlayerPatternInput(const sf::Event& event) {
    if (this->shootPlayerPatternDisplay != nullptr && this->_asset != nullptr) {
        if (this->shootPlayerPatternDisplay->projectileSpeed->checkInput(event)) {
            std::string input = this->shootPlayerPatternDisplay->projectileSpeed->getInput();
            if (!input.empty())
                this->_asset->addComponent<ShootPlayerPattern>(ShootPlayerPattern{
                    std::stof(input), this->_asset->getComponent<ShootPlayerPattern>().shootCooldown,
                    std::chrono::steady_clock::now()});
        }

        if (this->shootPlayerPatternDisplay->shootCooldown->checkInput(event)) {
            std::string input = this->shootPlayerPatternDisplay->shootCooldown->getInput();
            if (!input.empty())
                this->_asset->addComponent<ShootPlayerPattern>(
                    ShootPlayerPattern{this->_asset->getComponent<ShootPlayerPattern>().projectileSpeed,
                                       std::stof(input), std::chrono::steady_clock::now()});
        }
    }
}

void Edition::ComponentsEditor::handlePlayerFollowingPatternInput(const sf::Event& event) {
    if (this->playerFollowingPatternDisplay != nullptr && this->_asset != nullptr) {
        if (this->playerFollowingPatternDisplay->speed->checkInput(event)) {
            std::string input = this->playerFollowingPatternDisplay->speed->getInput();
            if (!input.empty())
                this->_asset->addComponent<PlayerFollowingPattern>(PlayerFollowingPattern{std::stof(input)});
        }
    }
}

void Edition::ComponentsEditor::handleStraightLinePatternInput(const sf::Event& event) {
    if (this->straightLinePatternDisplay != nullptr && this->_asset != nullptr) {
        if (this->straightLinePatternDisplay->speed->checkInput(event)) {
            std::string input = this->straightLinePatternDisplay->speed->getInput();
            if (!input.empty())
                this->_asset->addComponent<StraightLinePattern>(StraightLinePattern{std::stof(input)});
        }
    }
}

void Edition::ComponentsEditor::handleWavePatternInput(const sf::Event& event) {
    if (this->wavePatternDisplay != nullptr && this->_asset != nullptr) {
        if (this->wavePatternDisplay->amplitude->checkInput(event)) {
            std::string input = this->wavePatternDisplay->amplitude->getInput();
            if (!input.empty())
                this->_asset->addComponent<Wave_pattern>(
                    Wave_pattern{std::stof(input), this->_asset->getComponent<Wave_pattern>().frequency,
                                 std::chrono::steady_clock::now()});
        }

        if (this->wavePatternDisplay->frequency->checkInput(event)) {
            std::string input = this->wavePatternDisplay->frequency->getInput();
            if (!input.empty())
                this->_asset->addComponent<Wave_pattern>(
                    Wave_pattern{this->_asset->getComponent<Wave_pattern>().amplitude, std::stof(input),
                                 std::chrono::steady_clock::now()});
        }
    }
}

void Edition::ComponentsEditor::handleTypeInput(const sf::Event& event) {
    if (this->typeDisplay != nullptr && this->_asset != nullptr) {
        if (this->typeDisplay->type->handleInput(event)) {
            const std::unordered_map<std::string, EntityType> entityMap = {
                {"PLAYER", PLAYER},
                {"ENEMY", ENEMY},
                {"PLAYER_PROJECTILE", PLAYER_PROJECTILE},
                {"ENEMY_PROJECTILE", ENEMY_PROJECTILE},
                {"BACKGROUND", BACKGROUND},
                {"OBSTACLE", OBSTACLE},
                {"POWERUP", POWERUP}};
            std::string selectedType = this->typeDisplay->type->getSelectedOption();
            auto it                  = entityMap.find(selectedType);
            this->_asset->addComponent<Type>(Type{it->second});
        }
    }
}

void Edition::ComponentsEditor::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed
        || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved) {
        label->checkInput(event);
        if (posX->checkInput(event) && this->_asset != nullptr) {
            if (posX->getInput().empty())
                this->_asset->move(20, this->_asset->getComponent<Position>().y);
            else
                this->_asset->move(std::stoi(posX->getInput()), this->_asset->getComponent<Position>().y);
        }
        if (posY->checkInput(event) && this->_asset != nullptr) {
            if (posY->getInput().empty())
                this->_asset->move(this->_asset->getComponent<Position>().x, 100);
            else
                this->_asset->move(this->_asset->getComponent<Position>().x, std::stoi(posY->getInput()));
        }
        if (sizeX->checkInput(event) && this->_asset != nullptr) {
            if (sizeX->getInput().empty())
                this->_asset->addComponent<Size>(Size{1, this->_asset->getComponent<Size>().y});
            else
                this->_asset->addComponent<Size>(
                    Size{std::stoul(sizeX->getInput()), this->_asset->getComponent<Size>().y});
        }
        if (sizeY->checkInput(event) && this->_asset != nullptr) {
            if (sizeY->getInput().empty())
                this->_asset->addComponent<Size>(Size{this->_asset->getComponent<Size>().x, 1});
            else
                this->_asset->addComponent<Size>(
                    Size{this->_asset->getComponent<Size>().x, std::stoul(sizeY->getInput())});
        }
        if (rotation->checkInput(event) && this->_asset != nullptr) {
            if (rotation->getInput().empty())
                this->_asset->addComponent<Rotation>(Rotation{0});
            else
                this->_asset->addComponent<Rotation>(Rotation{std::stof(rotation->getInput())});
        }
        handleSpriteInput(event);
        handleHealthInput(event);
        handlePlayerFollowingPatternInput(event);
        handleShootPlayerPatternInput(event);
        handleShootStraightPatternInput(event);
        handleStraightLinePatternInput(event);
        handleTypeInput(event);
        handleWavePatternInput(event);
        if (event.type == sf::Event::MouseButtonPressed && _asset != nullptr) {
            sf::Vector2f mousPos;
            mousPos.x = static_cast<float>(event.mouseButton.x);
            mousPos.y = static_cast<float>(event.mouseButton.y);
            if (addButton.getGlobalBounds().contains(mousPos)) {
                addComponent();
            }
        }
        componentSelection->handleInput(event);
    }
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset += scrollSpeed;
        } else {
            scrollOffset -= scrollSpeed;
        }
        scrollOffset = std::clamp(scrollOffset, maxScrollOffset - (500), 0.0f);
    }
}