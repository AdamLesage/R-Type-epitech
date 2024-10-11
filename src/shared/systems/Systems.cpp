/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#include "Systems.hpp"

void Systems::position_system(Registry &reg)
{
    auto &positions = reg.get_components<Position_s>();
    auto &velocities = reg.get_components<Velocity_s>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos && vel) {
            pos->x += vel->x;
            pos->y += vel->y;
        }
    }
}

void Systems::control_system(Registry &reg, sf::RenderWindow &window, std::shared_ptr<RType::IMediator> mediator, std::function<void()> shootSound)
{
    (void)reg;
    if (window.hasFocus() == false) {
        return;
    }

    for (int key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            // If the key is a letter or a number return the ASCII value
            if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
                if (mediator != nullptr) {
                    if (key == sf::Keyboard::X) // Shoot, TODO: change according to the key binding in key.cfg file
                        shootSound();
                    mediator->notify("Game", std::to_string(static_cast<int>('A' + (key - sf::Keyboard::A))));
                }
            } else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
                if (mediator != nullptr) {
                    mediator->notify("Game", std::to_string(static_cast<int>('0' + (key - sf::Keyboard::Num0))));
                }
            }
        }
    }
}



void Systems::draw_system(Registry &reg, sf::RenderWindow &window)
{
    auto &positions = reg.get_components<Position_s>();
    auto &drawables = reg.get_components<Drawable_s>();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto &pos = positions[i];
        auto &draw = drawables[i];

        if (pos && draw) {
            draw->shape.setPosition(pos->x, pos->y);
            window.draw(draw->shape);
        }
    }
}

void Systems::collision_system(Registry &reg, sf::RenderWindow &window)
{
    auto &positions = reg.get_components<Position_s>();
    auto &drawables = reg.get_components<Drawable_s>();

    sf::Vector2u windowSize = window.getSize();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto &pos1 = positions[i];
        auto &draw1 = drawables[i];

        if (pos1 && draw1) {
            sf::FloatRect bounds = draw1->shape.getGlobalBounds();

            if (bounds.left < 0 || bounds.left + bounds.width > windowSize.x ||
                bounds.top < 0 || bounds.top + bounds.height > windowSize.y) {
                std::cerr << "Collision detected between entity " << i << " and the window border" << std::endl;
            }

            for (size_t j = i + 1; j < positions.size() && j < drawables.size(); ++j) {
                auto &pos2 = positions[j];
                auto &draw2 = drawables[j];

                if (pos2 && draw2) {
                    if (draw1->shape.getGlobalBounds().intersects(draw2->shape.getGlobalBounds())) {
                        std::cerr << "Collision detected between entity " << i << " and entity " << j << std::endl;
                    }
                }
            }
        }
    }
}

void Systems::direction_system(Registry &reg)
{
    auto &velocities = reg.get_components<Velocity_s>();
    auto &directions = reg.get_components<Direction_s>();

    for (size_t i = 0; i < velocities.size() && i < directions.size(); ++i) {
        auto &vel = velocities[i];
        auto &dir = directions[i];

        if (vel && dir) {
            vel->x = dir->x;
            vel->y = dir->y;
        }
    }
}
