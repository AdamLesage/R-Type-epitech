/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <SFML/Graphics/View.hpp>

namespace Component {
    class Camera {
        public:
            Camera();
            ~Camera();

        protected:
            sf::View _view;
        private:
    };
}

#endif /* !CAMERA_HPP_ */
