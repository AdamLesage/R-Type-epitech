/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#include "Systems.hpp"

void Systems::position_system(Registry &reg, std::unique_ptr<NetworkSender> &networkSender, RType::Logger &logger)
{
    (void)logger;
    auto &positions = reg.get_components<Position_s>();
    auto &velocities = reg.get_components<Velocity_s>();
    auto &types = reg.get_components<Type>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &type = types[i];

        if (pos && vel) {
            pos->x += vel->x;
            pos->y += vel->y;
            if (vel->x != 0 || vel->y != 0) {
                std::cout << "entity: " << i << " pos: " << pos->x << ";" << pos->y << std::endl;
                networkSender->sendPositionUpdate(i, pos->x, pos->y);
            }
            if (type->type == EntityType::PLAYER) {
                vel->x = 0;
                vel->y = 0;
            }
        }
    }
}

void Systems::control_system(Registry &reg, RType::Logger &logger)
{
    (void)logger;
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

void Systems::draw_system(Registry &reg, sf::RenderWindow &window, RType::Logger &logger)
{
    (void)logger;
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

void Systems::logging_system(SparseArray<Position_s> const &positions, SparseArray<Velocity_s> const &velocities, RType::Logger &logger)
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

void Systems::collision_system(Registry &reg, sf::RenderWindow &window, RType::Logger &logger)
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

void Systems::shoot_system(Registry &reg, entity_t playerId, std::unique_ptr<NetworkSender> &networkSender, RType::Logger &logger)
{
    auto &positions = reg.get_components<Position_s>();
    auto &types = reg.get_components<Type_s>();
    auto &shootingSpeeds = reg.get_components<ShootingSpeed_s>();
    auto &shoots = reg.get_components<Shoot>();

    auto &pos = positions[playerId];
    auto &type = types[playerId];
    auto &shootingSpeed = shootingSpeeds[playerId];
    auto &shoot = shoots[playerId];
    if (type && type->type == EntityType::PLAYER && shoot->canShoot) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> fs = now - shoot->shootCooldown;
        float elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(fs).count();
        std::cout << elapsed_seconds;
        
        if (elapsed_seconds >= shootingSpeed->shooting_speed) {
            shoot->shootCooldown = now;
            float projectileX = pos->x + 10;
            float projectileY = pos->y;

            entity_t projectile = reg.spawn_entity();
            reg.add_component<Position_s>(projectile, Position_s{projectileX, projectileY});
            reg.add_component<Velocity_s>(projectile, Velocity_s{3.0f, 0.0f});
            reg.add_component<Type_s>(projectile, Type_s{EntityType::PROJECTILE});
            reg.add_component<Damage_s>(projectile, Damage_s{10});

            networkSender->sendCreateProjectil(projectile, projectileX, projectileY, playerId);
        }
    }
}

void Systems::wave_pattern_system(Registry &reg, float totalTime, RType::Logger &logger) {
    auto &patterns =  reg.get_components<Wave_pattern>();
    auto &positions =  reg.get_components<Position>();
    auto &velocitys =  reg.get_components<Velocity>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto &pattern = patterns[i];
        auto &position = positions[i];
        auto &velocity = velocitys[i];
        if (pattern && position && velocity) {
            velocity->x = -1;
            position->y += (pattern->amplitude * std::sin(pattern->frequency * totalTime));
        }
        // logger.log(RType::Logger::LogType::INFO, "Player %d shot a projectile", playerId);
    }
}

void Systems::death_system(Registry &reg, RType::Logger &logger)
{
    auto &healths = reg.get_components<Health_s>();
    auto &types = reg.get_components<Type_s>();

    for (size_t i = 0; i < healths.size() && i < types.size(); ++i) {
        auto &health = healths[i];
        auto &type = types[i];

        if (health && type && health->health <= 0) {
            reg.kill_entity(i);
            logger.log(RType::Logger::LogType::INFO, "Entity %d died", i);
            // send_death to client
        }
    }
}