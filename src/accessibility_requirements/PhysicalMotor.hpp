/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicalMotor
*/

#ifndef PHYSICALMOTOR_HPP_
#define PHYSICALMOTOR_HPP_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

class PhysicalMotor {
    public:
        PhysicalMotor();
        ~PhysicalMotor();

        void changeControls(sf::Window &window);
        bool isUpKeyPressed() const { return sf::Keyboard::isKeyPressed(_upKey1) || sf::Keyboard::isKeyPressed(_upKey2); }
        bool isDownKeyPressed() const { return sf::Keyboard::isKeyPressed(_downKey1) || sf::Keyboard::isKeyPressed(_downKey2); }
        bool isLeftKeyPressed() const { return sf::Keyboard::isKeyPressed(_leftKey1) || sf::Keyboard::isKeyPressed(_leftKey2); }
        bool isRightKeyPressed() const { return sf::Keyboard::isKeyPressed(_rightKey1) || sf::Keyboard::isKeyPressed(_rightKey2); }
        void setShowMenuControls(bool showMenuControls) { _showMenuControls = showMenuControls; }
        bool getShowMenuControls() { return _showMenuControls; }
        void setSensibility(float sensibility) { _sensibility = sensibility; }
        float getSensibility() { return _sensibility; }
        void setDeadZoneJoystick(float deadZoneJoystick) { _deadZoneJoystick = deadZoneJoystick; }
        float getDeadZoneJoystick() { return _deadZoneJoystick; }
        void setUpKey1(sf::Keyboard::Key upKey1) { _upKey1 = upKey1; }
        sf::Keyboard::Key getUpKey1() { return _upKey1; }
        void setUpKey2(sf::Keyboard::Key upKey2) { _upKey2 = upKey2; }
        sf::Keyboard::Key getUpKey2() { return _upKey2; }
        void setDownKey1(sf::Keyboard::Key downKey1) { _downKey1 = downKey1; }
        sf::Keyboard::Key getDownKey1() { return _downKey1; }
        void setDownKey2(sf::Keyboard::Key downKey2) { _downKey2 = downKey2; }
        sf::Keyboard::Key getDownKey2() { return _downKey2; }
        void setLeftKey1(sf::Keyboard::Key leftKey1) { _leftKey1 = leftKey1; }
        sf::Keyboard::Key getLeftKey1() { return _leftKey1; }
        void setLeftKey2(sf::Keyboard::Key leftKey2) { _leftKey2 = leftKey2; }
        sf::Keyboard::Key getLeftKey2() { return _leftKey2; }
        void setRightKey1(sf::Keyboard::Key rightKey1) { _rightKey1 = rightKey1; }
        sf::Keyboard::Key getRightKey1() { return _rightKey1; }
        void setRightKey2(sf::Keyboard::Key rightKey2) { _rightKey2 = rightKey2; }
        sf::Keyboard::Key getRightKey2() { return _rightKey2; }
        void setShootKey1(sf::Keyboard::Key shootKey1) { _shootKey1 = shootKey1; }
        sf::Keyboard::Key getShootKey1() { return _shootKey1; }
        void setShootKey2(sf::Keyboard::Key shootKey2) { _shootKey2 = shootKey2; }
        sf::Keyboard::Key getShootKey2() { return _shootKey2; }

    protected:
        sf::Keyboard::Key _upKey1;
        sf::Keyboard::Key _upKey2;

        sf::Keyboard::Key _downKey1;
        sf::Keyboard::Key _downKey2;

        sf::Keyboard::Key _leftKey1;
        sf::Keyboard::Key _leftKey2;

        sf::Keyboard::Key _rightKey1;
        sf::Keyboard::Key _rightKey2;

        sf::Keyboard::Key _shootKey1;
        sf::Keyboard::Key _shootKey2;

        float _sensibility;
        float _deadZoneJoystick;

        bool _showMenuControls;
    private:
};

#endif /* !PHYSICALMOTOR_HPP_ */
