/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
    Menu(float width, float height);
    ~Menu() = default;
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;

private:
    int selectedOption;
    sf::Font font;
    sf::Text menuOptions[3]; // Play, Settings, Quit
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::SoundBuffer selectBuffer;
    sf::Sound selectSound;
};

#endif /* !MENU_HPP_ */
