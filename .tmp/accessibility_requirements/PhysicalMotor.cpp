/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicalMotor
*/

#include "PhysicalMotor.hpp"

PhysicalMotor::PhysicalMotor()
{
    _upKey1 = sf::Keyboard::Z;
    _upKey2 = sf::Keyboard::Up;

    _downKey1 = sf::Keyboard::S;
    _downKey2 = sf::Keyboard::Down;

    _leftKey1 = sf::Keyboard::Q;
    _leftKey2 = sf::Keyboard::Left;

    _rightKey1 = sf::Keyboard::D;
    _rightKey2 = sf::Keyboard::Right;

    _shootKey1 = sf::Keyboard::Space;
    _shootKey2 = sf::Keyboard::Space;

    _showMenuControls = true;
    _sensibility = 1;
    _deadZoneJoystick = 0.1;
}

PhysicalMotor::~PhysicalMotor()
{
}

void PhysicalMotor::changeControls(sf::Window &window)
{
    if (_showMenuControls == false) // If the menu is not shown, we don't need to check for inputs
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { // If the escape key is pressed, we hide the menu
        _showMenuControls = false;
        return;
    }

    // Display the menu, need to click on the key to change it
}
