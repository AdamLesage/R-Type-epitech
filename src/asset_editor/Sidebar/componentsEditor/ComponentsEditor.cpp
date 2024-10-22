/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#include "ComponentsEditor.hpp"

Edition::ComponentsEditor::ComponentsEditor()
{
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    label.reset(new Input(sf::Vector2f(350, 40), sf::Vector2f(1460, 80), "Label: "));
    posX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "X: "));
    posY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460 + 115, 200), "Y: "));
    sizeX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460, 250 + 50), "X: "));
    sizeY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460 + 115,  250 + 50), "Y: "));
    rotation.reset(new InputNumber(sf::Vector2f(70,40), sf::Vector2f(1460, 350), "Rotation: "));

    componentSelection.reset(new SelectButton({1460, 400}, {300, 50}, options));
    addButton = sf::RectangleShape({100, 50});
    addButton.setFillColor(sf::Color(20, 20, 20));
}

Edition::ComponentsEditor::~ComponentsEditor()
{
}

void Edition::ComponentsEditor::displayCategoryTitle(std::shared_ptr<sf::RenderWindow> window, std::string title, float posX, float posY)
{
    sf::Text text;
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    window->draw(text);
}

void Edition::ComponentsEditor::displayAddComponent(std::shared_ptr<sf::RenderWindow> window, int posY)
{
    componentSelection->setPosition({1460, static_cast<float>(posY)});
    componentSelection->display(*window.get());

    addButton.setPosition({1460 + 315, static_cast<float>(posY)});
    sf::Text addText = sf::Text();
    addText.setFont(this->font);
    addText.setString("Add");
    addText.setCharacterSize(35);
    addText.setFillColor(sf::Color::White);
    const sf::FloatRect textBounds = addText.getLocalBounds();
    const sf::Vector2f boxSize = addButton.getSize();
    addText.setOrigin(
        textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f
    );
    addText.setPosition(
        addButton.getPosition().x + boxSize.x / 2.0f,
        addButton.getPosition().y + boxSize.y / 2.0f
    );
    window->draw(addButton);
    window->draw(addText); 
}

void Edition::ComponentsEditor::displayHealth(std::shared_ptr<sf::RenderWindow> window, int &posY)
{
    if (this->healthDisplay != nullptr) {
        displayCategoryTitle(window, "Health", window->getSize().x * 0.76, posY);
        this->healthDisplay->health->setPosition({1500, posY + 50});
        posY += 100;
        this->healthDisplay->health->displayInput(window);
    }
}

void Edition::ComponentsEditor::display(std::shared_ptr<sf::RenderWindow> window)
{
    label->displayInput(window);
    displayCategoryTitle(window, "Position", window->getSize().x * 0.76, 150);
    posX->displayInput(window);
    posY->displayInput(window);
    displayCategoryTitle(window, "Size", window->getSize().x * 0.76, 250);
    sizeX->displayInput(window);
    sizeY->displayInput(window);
    rotation->displayInput(window);
    currentPosY = 400;
    displayHealth(window, currentPosY);
    displayAddComponent(window, currentPosY);
}

void Edition::ComponentsEditor::updateSelectedEntity(std::shared_ptr<Edition::Asset> asset)
{
    _asset = asset;
    this->posX->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().left)));
    this->posY->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().top)));
    this->sizeX->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().width)));
    this->sizeY->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().height)));
}

void Edition::ComponentsEditor::addComponent()
{
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
        this->_asset->addComponent<ShootStraightPattern>(ShootStraightPattern{1, 5, std::chrono::steady_clock::now()});
    }
    if (selectedComponent == "ShootPlayerPattern") {
        this->shootPlayerPatternDisplay = std::make_unique<ShootPlayerPatternDisplay>();
        this->shootPlayerPatternDisplay->initialize(1, 5);
        this->_asset->addComponent<ShootPlayerPattern>(ShootPlayerPattern{1, 5, std::chrono::steady_clock::now()});
    }
        
    if (selectedComponent == "StraightLinePattern") {
        this->straightLinePatternDisplay = std::make_unique<StraightLinePatternDisplay>();
        this->straightLinePatternDisplay->initialize(-1);
        this->_asset->addComponent<StraightLinePattern>(StraightLinePattern{-1});
    }
    if (selectedComponent == "Wave_pattern") {
        this->wavePatternDisplay = std::make_unique<Wave_patternDisplay>();
        this->wavePatternDisplay->initialize(1.f, 0.02f);
        this->_asset->addComponent<Wave_pattern>(Wave_pattern{1.f, 0.02f});
    }
    if (selectedComponent == "Type") {
        this->typeDisplay = std::make_unique<TypeDisplay>();
        this->typeDisplay->initialize();
        this->_asset->addComponent<Type>(Type{EntityType::ENEMY});
    }
    
}

void Edition::ComponentsEditor::handleHealthInput(const sf::Event &event)
{
    if (this->healthDisplay != nullptr && this->_asset != nullptr) {
        if (this->healthDisplay->health->checkInput(event)) {
            std::string input =  this->healthDisplay->health->getInput();
            if (input.empty())
                this->_asset->addComponent<Health>(Health{0});
            else
                this->_asset->addComponent<Health>(Health{std::stoul(input)});
        }
    }
}

void Edition::ComponentsEditor::handleInput(const sf::Event &event)
{
    if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved) {
        label->checkInput(event);
        if (posX->checkInput(event) && this->_asset != nullptr) {
            if (posX->getInput().empty())
                this->_asset->move(0, _asset->getGlobalBounds().top);
            else
                this->_asset->move(std::stoi(posX->getInput()), _asset->getGlobalBounds().top);
        }
        if (posY->checkInput(event) && this->_asset != nullptr) {
            if (posY->getInput().empty())
                this->_asset->move(_asset->getGlobalBounds().left, 0);
            else
                this->_asset->move(_asset->getGlobalBounds().left, std::stoi(posY->getInput()));
        }
        if (sizeX->checkInput(event) && this->_asset != nullptr) {
            if (sizeX->getInput().empty())
                this->_asset->addComponent<Size>(Size{1, this->_asset->getComponent<Size>().y});
            else
                this->_asset->addComponent<Size>(Size{std::stoul(sizeX->getInput()), this->_asset->getComponent<Size>().y});
        }
        if (sizeY->checkInput(event) && this->_asset != nullptr) {
            if (sizeY->getInput().empty())
                this->_asset->addComponent<Size>(Size{this->_asset->getComponent<Size>().y, 1});
            else
                this->_asset->addComponent<Size>(Size{this->_asset->getComponent<Size>().y, std::stoul(sizeY->getInput())});
        }
        if (rotation->checkInput(event) && this->_asset != nullptr) {
            if (rotation->getInput().empty())
                this->_asset->addComponent<Rotation>(Rotation{0});
            else
                this->_asset->addComponent<Rotation>(Rotation{std::stof(rotation->getInput())});
        }
        handleHealthInput(event);
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
}