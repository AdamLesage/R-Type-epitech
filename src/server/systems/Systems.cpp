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

void Systems::control_system(Registry &reg)
{
    auto &velocities = reg.get_components<Velocity_s>();
    auto &controllables = reg.get_components<Controllable_s>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto &vel = velocities[i];
        auto &ctrl = controllables[i];

        if (vel && ctrl) {
            vel->x = 0;
            vel->y = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                vel->y = -1.0f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                vel->y = 1.0f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                vel->x = -1.0f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                vel->x = 1.0f;
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

void Systems::logging_system(SparseArray<Position_s> const &positions, SparseArray<Velocity_s> const &velocities)
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto const& pos = positions[i];
        auto const& vel = velocities[i];
        if (pos && vel) {
            std::cerr << i << " : Position = { " << pos.value().x << " , " << pos.value().y
                    << " } , Velocity = { " << vel.value().x << " , " << vel.value().y
                    << " }" << std::endl;
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
                reg.kill_entity(i);
                std::cerr << "Projectile " << i << " deleted (out of window)" << std::endl;
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

void Systems::shoot_system(Registry &reg, entity_t playerId, float deltaTime, bool shootRequest)
{
    auto &positions = reg.get_components<Position_s>();
    auto &types = reg.get_components<Type_s>();
    auto &shootingSpeeds = reg.get_components<ShootingSpeed_s>();
    static std::unordered_map<entity_t, float> shootCooldown;

    shootCooldown[playerId] += deltaTime;

    auto &pos = positions[playerId];
    auto &type = types[playerId];
    auto &shootingSpeed = shootingSpeeds[playerId];

    if (type && type->type == EntityType::PLAYER && shootRequest && shootCooldown[playerId] >= shootingSpeed->shooting_speed) {
        shootCooldown[playerId] = 0.0f;

        float projectileX = pos->x + 10;
        float projectileY = pos->y;

        entity_t projectile = reg.spawn_entity();
        reg.add_component<Position_s>(projectile, Position_s{projectileX, projectileY});
        reg.add_component<Velocity_s>(projectile, Velocity_s{3.0f, 0.0f});
        reg.add_component<Type_s>(projectile, Type_s{EntityType::PROJECTILE});
        reg.add_component<Damage_s>(projectile, Damage_s{10});

        // send_projectile_to_clients(type, projectileId, projectileX, projectileY);
    }
}

void Systems::health_system(Registry &reg)
{
    auto &healths = reg.get_components<Health_s>();
    auto &types = reg.get_components<Type_s>();

    static auto lastUpdate = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();

    size_t regenerationRate = 5; //load from config

    if (elapsedTime >= 1) {
        lastUpdate = now;

        for (size_t i = 0; i < healths.size() && i < types.size(); ++i) {
            auto &health = healths[i];
            auto &type = types[i];
            if (health && type && type->type == EntityType::PLAYER) {
                health->health += regenerationRate;
                if (health->health > health->maxHealth) {
                    health->health = health->maxHealth;
                }
            }
        }
    }
}
