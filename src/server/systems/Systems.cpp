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

void Systems::control_system(Registry &reg, bool up, bool down, bool left, bool right, RType::Logger &logger)
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

            if (up) {
                vel->y = -1.0f;
            }
            if (down) {
                vel->y = 1.0f;
            }
            if (left) {
                vel->x = -1.0f;
            }
            if (right) {
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

void Systems::check_borders_collisions(Registry &reg, size_t entityId, Position_s *entityPos,
    Size_s *entitySize, Type_s *entityType, std::pair<size_t, size_t> MapSize, RType::Logger &logger)
{
    if (entityType->type == EntityType::PROJECTILE &&
        (entityPos->x < 0 || entityPos->x + entitySize->x > MapSize.first ||
        entityPos->y < 0 || entityPos->y + entitySize->y > MapSize.second)) {
        reg.kill_entity(entityId);
        std::cerr << "Projectile " << entityId << " deleted (out of window)" << std::endl;
        //send to clients
    }
}

void Systems::check_entities_collisions(Registry &reg, size_t entityId1, Position_s *entityPos1, Size_s *entitySize1,
    size_t entityId2, Position_s *entityPos2, Size_s *entitySize2, RType::Logger &logger)
{
    bool collisionX = entityPos1->x < entityPos2->x + entitySize2->x &&
                      entityPos1->x + entitySize1->x > entityPos2->x;
    bool collisionY = entityPos1->y < entityPos2->y + entitySize2->y &&
                      entityPos1->y + entitySize1->y > entityPos2->y;

    if (collisionX && collisionY) {
        logger.log(RType::Logger::LogType::INFO, "Entity %d collided with entity %d", entityId1, entityId2);
        // send_collision_to_clients(entityId1, entityId2);
    }
}

void Systems::collision_system(Registry &reg, std::pair<size_t, size_t> MapSize, RType::Logger &logger)
{
    auto &positions = reg.get_components<Position_s>();
    auto &sizes = reg.get_components<Size_s>();
    auto &types = reg.get_components<Type_s>();

    for (size_t i = 0; i < positions.size() && i < sizes.size(); i++) {
        auto &entityPos = positions[i];
        auto &entitySize = sizes[i];
        auto &entityType = types[i];
        if (entityPos && entitySize, entityType) {
            check_borders_collisions(reg, i, &(*entityPos), &(*entitySize), &(*entityType), MapSize, logger);

            for (size_t j = i + 1; j < positions.size() && j < sizes.size(); ++j) {
                auto &entityPos2 = positions[j];
                auto &entitySize2 = sizes[j];

                if (entityPos2 && entitySize2) {
                    check_entities_collisions(reg, i, &(*entityPos), &(*entitySize), j, &(*entityPos2), &(*entitySize2), logger);
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

void Systems::Straight_line_pattern_system(Registry &reg)
{
    auto &patterns =  reg.get_components<StraightLinePattern>();
    auto &positions =  reg.get_components<Position>();
    auto &velocitys =  reg.get_components<Velocity>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto &pattern = patterns[i];
        auto &position = positions[i];
        auto &velocity = velocitys[i];
        if (pattern && position && velocity) {
            velocity->x = -1;
        }
    }
}
