/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** SelectBar
*/

#include "SelectBar.hpp"

Edition::SelectBar::SelectBar(std::vector<std::string> selectOption, float x, float y, int maxWidth)
{
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur lors du chargement de la police " << fontPath << std::endl;
        return;
    }
    float startX = x;
    float startY = y;
    _selectionOption = selectOption;
    for (size_t i = 0; i < _selectionOption.size(); i++) {
        if (x + 150 - startX >= maxWidth) {
            x = startX;
            y += 55;
        }
        sf::RectangleShape shape(sf::Vector2f(150, 30));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Transparent);

        // Création du texte associé à chaque option
        sf::Text text;
        text.setFont(font); // Utilisation de la police membre
        text.setString(_selectionOption[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
        shape.setSize(sf::Vector2f(text.getLocalBounds().width + 5, 55));

        // Centrage du texte par rapport au bouton
        const sf::FloatRect bounds(text.getLocalBounds());
        const sf::Vector2f box(shape.getSize());
        text.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

        _selectionButton.push_back(shape);
        _selectionText.push_back(text);
        x += shape.getSize().x + 10;
        height = (y - startY);
    }

    _selectionButton[0].setFillColor(sf::Color(125, 125, 125));
}

Edition::SelectBar::~SelectBar()
{
}

void Edition::SelectBar::display(std::shared_ptr<sf::RenderWindow> window) {
    for (size_t i = 0; i < _selectionOption.size(); i++) {
        if (i == selectedOptionIndex) {
            _selectionButton[i].setFillColor(sf::Color(125, 125, 125));
        }
        window->draw(_selectionButton[i]);
        window->draw(_selectionText[i]);
    }
}

int Edition::SelectBar::getHeightSelectBar() {
    return height;
}
std::vector<std::string> Edition::SelectBar::getSelectOption() {
    return _selectionOption;
}
int Edition::SelectBar::findSelectedIndex() {
    return selectedOptionIndex;               
}

std::string Edition::SelectBar::findSelectedOption()
{
    return (this->_selectionOption[this->selectedOptionIndex]);
}

void Edition::SelectBar::handleEvent(const sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        // Parcourir chaque bouton
        for (size_t i = 0; i < _selectionButton.size(); i++) {
            sf::RectangleShape& button = _selectionButton[i];

            // Utiliser la position de la souris depuis l'événement MouseMoved
            if (button.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
                // Changer la couleur du bouton lorsqu'il est survolé
                button.setFillColor(sf::Color(100, 100, 100));  // Couleur survolée
            } else {
                // Remettre à la couleur par défaut si la souris n'est plus dessus
                button.setFillColor(sf::Color::Transparent);  // Couleur par défaut
            }
        }

    }

    // Gérer l'événement de clic de la souris
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Parcourir chaque bouton
        for (size_t i = 0; i < _selectionButton.size(); i++) {
            sf::RectangleShape& button = _selectionButton[i];

            // Utiliser la position de la souris depuis l'événement MouseButtonPressed
            if (button.getGlobalBounds().contains((event.mouseButton.x), (event.mouseButton.y))) {
                // Changer la couleur du bouton lorsqu'il est cliqué
                button.setFillColor(sf::Color(175, 175, 175));  // Couleur en cliquant

                // Mettre à jour l'index de l'option sélectionnée
                selectedOptionIndex = i;
            }
        }
    }
}
