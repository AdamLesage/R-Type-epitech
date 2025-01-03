/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#include "Systems.hpp"

void Systems::position_system(Registry& reg) {
    auto& positions  = reg.get_components<Position_s>();
    auto& velocities = reg.get_components<Velocity_s>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto& pos = positions[i];
        auto& vel = velocities[i];

        if (pos && vel) {
            pos->x += vel->x;
            pos->y += vel->y;
        }
    }
}

void Systems::control_system(Registry& reg,
                             sf::RenderWindow& window,
                             std::shared_ptr<RType::IMediator> mediator,
                             std::function<void()> shootSound) {
    (void)reg;
    if (window.hasFocus() == false) {
        return;
    }

    for (int key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            // If the key is a letter or a number return the ASCII value
            if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
                if (mediator != nullptr) {
                    if (key == sf::Keyboard::X) // Shoot, TODO: change according to the key binding in key.cfg
                                                // file
                        shootSound();
                    mediator->notify("Game", std::to_string(static_cast<int>('A' + (key - sf::Keyboard::A))));
                }
            } else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
                if (mediator != nullptr) {
                    mediator->notify("Game",
                                     std::to_string(static_cast<int>('0' + (key - sf::Keyboard::Num0))));
                }
            }
        }
    }
}

void Systems::draw_system(Registry& reg, sf::RenderWindow& window) {
    auto& positions = reg.get_components<Position_s>();
    auto& drawables = reg.get_components<Drawable_s>();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto& pos  = positions[i];
        auto& draw = drawables[i];

        if (pos && draw) {
            draw->shape.setPosition(pos->x, pos->y);
            window.draw(draw->shape);
        }
    }
}

void Systems::collision_system(Registry& reg, sf::RenderWindow& window) {
    auto& positions = reg.get_components<Position_s>();
    auto& drawables = reg.get_components<Drawable_s>();

    sf::Vector2u windowSize = window.getSize();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto& pos1  = positions[i];
        auto& draw1 = drawables[i];

        if (pos1 && draw1) {
            sf::FloatRect bounds = draw1->shape.getGlobalBounds();

            if (bounds.left < 0 || bounds.left + bounds.width > windowSize.x || bounds.top < 0
                || bounds.top + bounds.height > windowSize.y) {
                std::cerr << "Collision detected between entity " << i << " and the window border"
                          << std::endl;
            }

            for (size_t j = i + 1; j < positions.size() && j < drawables.size(); ++j) {
                auto& pos2  = positions[j];
                auto& draw2 = drawables[j];

                if (pos2 && draw2) {
                    if (draw1->shape.getGlobalBounds().intersects(draw2->shape.getGlobalBounds())) {
                        std::cerr << "Collision detected between entity " << i << " and entity " << j
                                  << std::endl;
                    }
                }
            }
        }
    }
}

void Systems::direction_system(Registry& reg, libconfig::Config &playerConfig) {
    auto& types      = reg.get_components<Type>();
    auto& directions = reg.get_components<Direction>();
    auto& sprites = reg.get_components<Sprite>();

    for (size_t i = 0; i < types.size() && i < directions.size(); ++i) {
        auto& type  = types[i];
        auto& dir = directions[i];
        auto& sprite = sprites[i];

        if (dir && type && sprite) {
            if (type->type == EntityType::PLAYER) {
                try {
                    libconfig::Setting& player = playerConfig.lookup("players")[0];
                    libconfig::Setting& directionRect = player.lookup("directionRect");
                    if (dir->y > 0) {
                        libconfig::Setting& down = directionRect.lookup("Down");
                        sprite->rectPos[0] = down.lookup("rectPos")[0];
                        sprite->rectPos[1] = down.lookup("rectPos")[1];
                    } else if (dir->y < 0) {
                        libconfig::Setting& up = directionRect.lookup("Up");
                        sprite->rectPos[0] = up.lookup("rectPos")[0];
                        sprite->rectPos[1] = up.lookup("rectPos")[1];
                    } else if (dir->y == 0) {
                        libconfig::Setting& none = directionRect.lookup("None");
                        sprite->rectPos[0] = none.lookup("rectPos")[0];
                        sprite->rectPos[1] = none.lookup("rectPos")[1];
                    }                    
                }  catch (const libconfig::SettingNotFoundException &e) {
                    std::cerr << "directionRect setting not found: " << e.what() << std::endl;
                } catch (const std::exception &e) {
                    std::cerr << "Error from direction system: player setting" << e.what() << std::endl;
                }
            }
        }
    }
}

void Systems::annimation_system(Registry& reg) {
    auto& annimations = reg.get_components<Annimation>();
    auto& sprites = reg.get_components<Sprite>();

    for (size_t i = 0; i < annimations.size() && i < sprites.size(); ++i) {
        auto& annimation = annimations[i];
        auto& sprite = sprites[i];

        if (annimation && sprite) {
            auto now                        = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - annimation->lastExecution;
            float elapsed_seconds           = std::chrono::duration_cast<std::chrono::milliseconds>(fs).count();
            if (elapsed_seconds >= annimation->annimationSpeed * 1000) {
                annimation->lastExecution = std::chrono::steady_clock::now();
                annimation->index++;
                sprite->rectPos[0] = annimation->annimation[annimation->index % annimation->annimation.size() - 1][0];
                sprite->rectPos[1] = annimation->annimation[annimation->index % annimation->annimation.size() - 1][1];
            }
        }
    }
}