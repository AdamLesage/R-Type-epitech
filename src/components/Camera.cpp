/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Camera
*/

#include "Camera.hpp"

Component::Camera::Camera()
{
    _view.setSize(1920, 1080);
    _view.setCenter(1920 / 2, 1080 / 2);
}

Component::Camera::~Camera()
{
}
