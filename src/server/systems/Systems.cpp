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
            if (type->type == EntityType::PROJECTILE) {
                if (vel->x == 0) {
                    vel->x = 3;
                }
            }
            pos->x += vel->x;
            pos->y += vel->y;
            if (vel->x != 0 || vel->y != 0) {
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
    (void)logger;
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
    Size_s *entitySize, Type_s *entityType, std::pair<size_t, size_t> MapSize, RType::Logger &logger, std::unique_ptr<NetworkSender> &networkSender)
{
    (void)logger;
    if ((entityType->type == EntityType::ENEMY_PROJECTILE || entityType->type == EntityType::PLAYER_PROJECTILE) &&
        (entityPos->x < 0 || entityPos->x + entitySize->x > MapSize.first ||
        entityPos->y < 0 || entityPos->y + entitySize->y > MapSize.second)) {
        reg.kill_entity(entityId);
        std::cerr << "Projectile " << entityId << " deleted (out of window)" << std::endl;
        networkSender->sendDeleteEntity(entityId);
    }
    if (entityType->type == EntityType::ENEMY && entityPos->x < 0) {
        reg.kill_entity(entityId);
        std::cerr << "enemy " << entityId << " deleted (out of window)" << std::endl;
        networkSender->sendDeleteEntity(entityId);
    }
}

void Systems::check_entities_collisions(Registry &reg, size_t entityId1, Position_s *entityPos1, Size_s *entitySize1,
    size_t entityId2, Position_s *entityPos2, Size_s *entitySize2, RType::Logger &logger, std::unique_ptr<NetworkSender> &networkSender,
    Type_s *entityType1, Type_s *entityType2)
{
    (void)reg;
    bool collisionX = entityPos1->x < entityPos2->x + entitySize2->x && entityPos1->x + entitySize1->x > entityPos2->x;
    bool collisionY = entityPos1->y < entityPos2->y + entitySize2->y && entityPos1->y + entitySize1->y > entityPos2->y;

    bool playerTakeDamage = (entityType1->type == EntityType::PLAYER && entityType2->type == EntityType::ENEMY_PROJECTILE) ||
                            (entityType1->type == EntityType::PLAYER && entityType2->type == EntityType::ENEMY);

    bool enemyTakeDamage =  (entityType1->type == EntityType::ENEMY && entityType2->type == EntityType::PLAYER_PROJECTILE);

    if (playerTakeDamage && collisionX && collisionY) {
        auto &healths = reg.get_components<Health_s>();
        auto &damages = reg.get_components<Damage_s>();
        auto &tags = reg.get_components<Tag_s>();

        for (size_t i = 0; i < healths.size() && i < damages.size() && i < tags.size(); ++i) {
            auto &health = healths[i];
            auto &damage = damages[i];
            auto &tag = tags[i];

            if (health && damage && tag && tag->tag == "player") {
                health->health -= damage->damage;
                networkSender->sendHealthUpdate(i, health->health);
            }
        }
    }

    if (enemyTakeDamage && collisionX && collisionY) {
        auto &healths = reg.get_components<Health_s>();
        auto &damages = reg.get_components<Damage_s>();
        auto &tags = reg.get_components<Tag_s>();

        for (size_t i = 0; i < healths.size() && i < damages.size() && i < tags.size(); ++i) {
            auto &health = healths[i];
            auto &damage = damages[i];
            auto &tag = tags[i];

            if (health && damage && tag && tag->tag == "enemy") {
                health->health -= damage->damage;
                networkSender->sendHealthUpdate(i, health->health);
            }
        }
    }
}

void Systems::collision_system(Registry &reg, std::pair<size_t, size_t> MapSize, std::unique_ptr<NetworkSender> &networkSender, RType::Logger &logger)
{
    auto &positions = reg.get_components<Position_s>();
    auto &sizes = reg.get_components<Size_s>();
    auto &types = reg.get_components<Type_s>();

    for (size_t i = 0; i < positions.size() && i < sizes.size(); i++) {
        auto &entityPos = positions[i];
        auto &entitySize = sizes[i];
        auto &entityType = types[i];
        if (entityPos && entitySize, entityType) {
            check_borders_collisions(reg, i, &(*entityPos), &(*entitySize), &(*entityType), MapSize, logger, networkSender);

            for (size_t j = i + 1; j < positions.size() && j < sizes.size(); ++j) {
                auto &entityPos2 = positions[j];
                auto &entitySize2 = sizes[j];
                auto &entityType2 = types[j];

                if (entityPos2 && entitySize2) {
                    check_entities_collisions(reg, i, &(*entityPos), &(*entitySize), j, &(*entityPos2), &(*entitySize2), logger, networkSender, &(*entityType), &(*entityType2));
                }
            }
        }
    }
}

void Systems::shoot_system(Registry &reg, entity_t playerId, std::unique_ptr<NetworkSender> &networkSender, RType::Logger &logger)
{
    (void)logger;
    auto &positions = reg.get_components<Position_s>();
    auto &types = reg.get_components<Type_s>();
    auto &shootingSpeeds = reg.get_components<ShootingSpeed_s>();
    auto &shoots = reg.get_components<Shoot>();
    auto &sizes = reg.get_components<Size>();

    auto &pos = positions[playerId];
    auto &type = types[playerId];
    auto &shootingSpeed = shootingSpeeds[playerId];
    auto &shoot = shoots[playerId];
    auto &size = sizes[playerId];

    if (type && type->type == EntityType::PLAYER && shoot->canShoot) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> fs = now - shoot->shootCooldown;
        float elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

        if (elapsed_seconds >= shootingSpeed->shooting_speed) {
            shoot->shootCooldown = now;
            float projectileX = pos->x + 10;
            float projectileY = pos->y;

            entity_t projectile = reg.spawn_entity();
            reg.add_component<Position_s>(projectile, Position_s{projectileX + (size->x / 2), projectileY + (size->y / 2) - (30 / 2)});
            reg.add_component<Velocity_s>(projectile, Velocity_s{3.0f, 0.0f});
            reg.add_component<Type_s>(projectile, Type_s{EntityType::PLAYER_PROJECTILE});
            reg.add_component<Damage_s>(projectile, Damage_s{10});
            reg.add_component<Size>(projectile, Size{70, 30});

            networkSender->sendCreateProjectil(projectile, projectileX, projectileY, playerId);
        }
    }
}

bool Systems::read_scores_file(libconfig::Config &cfg, const std::string &configPath)
{
    try {
        cfg.readFile(configPath.c_str());
        return true;
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Error while reading file." << std::endl;
        return false;
    } catch (const libconfig::ParseException &ParserError) {
        std::cerr << "Parse error at " << ParserError.getFile()
                  << ":" << ParserError.getLine() << " - "
                  << ParserError.getError() << std::endl;
        return false;
    }
}

void Systems::update_scores(libconfig::Config &cfg, const std::string &playerNames, size_t totalScore)
{
    libconfig::Setting &root = cfg.getRoot();
    libconfig::Setting &lastScores = root["scores"];
    libconfig::Setting &highScores = root["highscores"];

    std::vector<std::pair<std::string, int>> lastTenScores;
    for (int i = 0; i < lastScores.getLength(); ++i) {
        std::string name = lastScores[i]["name"];
        int value = lastScores[i]["value"];
        lastTenScores.push_back({name, value});
    }

    lastTenScores.push_back({playerNames, totalScore});
    if (lastTenScores.size() > 10) {
        lastTenScores.erase(lastTenScores.begin());
    }

    for (auto i = 0u; i < lastTenScores.size(); ++i) {
        lastScores[i].add("name", libconfig::Setting::TypeString) = lastTenScores[i].first;
        lastScores[i].add("value", libconfig::Setting::TypeInt) = lastTenScores[i].second;
    }

    std::vector<std::pair<std::string, int>> bestScores;
    for (int i = 0; i < highScores.getLength(); ++i) {
        std::string name = highScores[i]["name"];
        int value = highScores[i]["value"];
        bestScores.push_back({name, value});
    }

    bestScores.push_back({playerNames, totalScore});
    std::sort(bestScores.begin(), bestScores.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                  return a.second > b.second;
              });
    bestScores.resize(3);

    for (auto i = 0u; i < bestScores.size(); ++i) {
        highScores[i].add("name", libconfig::Setting::TypeString) = bestScores[i].first;
        highScores[i].add("value", libconfig::Setting::TypeInt) = bestScores[i].second;
    }
}

bool Systems::write_to_scores_file(libconfig::Config &cfg, const std::string &configPath)
{
    try {
        cfg.writeFile(configPath.c_str());
        std::cout << "Scores successfully written to: " << configPath << std::endl;
        return true;
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Error while writing file: " << configPath << std::endl;
        return false;
    }
}

void Systems::score_system(Registry &reg)
{
    auto &hp = reg.get_components<Health_s>();
    auto &controllable = reg.get_components<Controllable_s>();

    for (size_t i = 0; i < hp.size() && i < controllable.size(); ++i) {
        if (hp[i] && controllable[i] && hp[i]->health > 0) {
            return;
        }
    }

    std::string configPath = "../../config/scores.cfg";
    libconfig::Config cfg;

    if (!read_scores_file(cfg, configPath))
        return;

    auto &scores = reg.get_components<Score_s>();
    auto &names = reg.get_components<Tag_s>();
    size_t totalScore = 0;
    std::string playerNames = "";

    for (size_t i = 0; i < scores.size(); ++i) {
        if (scores[i]) {
            totalScore += scores[i]->score;
        }
        if (names[i]) {
            if (!playerNames.empty()) playerNames += " & ";
            playerNames += names[i]->tag;
        }
    }
    update_scores(cfg, playerNames, totalScore);
    write_to_scores_file(cfg, configPath);
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

void Systems::wave_pattern_system(Registry &reg, float totalTime, RType::Logger &logger)
{
    (void)logger;
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
            velocity->x = pattern->speed;
        }
    }
}

void Systems::player_following_pattern_system(Registry &reg)
{
    auto &patterns =  reg.get_components<PlayerFollowingPattern>();
    auto &velocitys =  reg.get_components<Velocity>();
    auto &positions = reg.get_components<Position>();

    for (size_t i = 0; i < patterns.size(); ++i) {
        auto &pattern = patterns[i];
        auto &velocity = velocitys[i];
        auto &position = positions[i];

        if (pattern && velocity && position) {
            std::array<float, 2> target_pos = this->find_closest_player(reg, &(*position));
            velocity->x = target_pos[0] - position->x;
            velocity->y = target_pos[1] - position->y;
            float magnitude = std::sqrt((velocity->x * velocity->x) + (velocity->y * velocity->y));

            if (magnitude > 0) {
                velocity->x = (velocity->x / magnitude) * pattern->speed;
                velocity->y = (velocity->y / magnitude) * pattern->speed;
            }
        }
    }
}

void Systems::shoot_straight_pattern_system(Registry &reg, std::unique_ptr<NetworkSender> &networkSender)
{
    auto &patterns =  reg.get_components<ShootStraightPattern>();
    auto &positions =  reg.get_components<Position>();
    auto &velocitys =  reg.get_components<Velocity>();
    auto &sizes = reg.get_components<Size>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto &pattern = patterns[i];
        auto &position = positions[i];
        auto &velocity = velocitys[i];
        auto &size = sizes[i];
    
        if (pattern && position && velocity && size) {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->lastShotTime;
            float elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

            if (elapsed_seconds >= pattern->shootCooldown && pattern->shootCooldown > 1) {
                pattern->lastShotTime = now;
                entity_t projectile = reg.spawn_entity();
                reg.add_component<Position_s>(projectile, Position_s{position->x, position->y + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile, Velocity_s{-1 * pattern->projectileSpeed, 0});
                reg.add_component<Type_s>(projectile, Type_s{EntityType::ENEMY_PROJECTILE});
                reg.add_component<Damage_s>(projectile, Damage_s{10});
                reg.add_component<Size>(projectile, Size{70, 30});
                networkSender->sendCreateProjectil(projectile, position->x, position->y, i);
            }
        }
    }
}

void Systems::shoot_player_pattern_system(Registry &reg, std::unique_ptr<NetworkSender> &networkSender)
{
    auto &patterns =  reg.get_components<ShootPlayerPattern>();
    auto &velocitys =  reg.get_components<Velocity>();
    auto &positions = reg.get_components<Position>();
    auto &sizes = reg.get_components<Size>();

    for (size_t i = 0; i < patterns.size(); ++i) {
        auto &pattern = patterns[i];
        auto &velocity = velocitys[i];
        auto &position = positions[i];
        auto &size = sizes[i];

        if (pattern && velocity && position && size) {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->lastShotTime;
            float elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

            if (elapsed_seconds >= pattern->shootCooldown) {
                pattern->lastShotTime = now;
                
                std::array<float, 2> target_pos = this->find_closest_player(reg, &(*position));
                std::array<float, 2> projectile_velocity = {target_pos[0] - position->x, target_pos[1] - position->y};
                float magnitude = std::sqrt((projectile_velocity[0] * projectile_velocity[0]) + (projectile_velocity[1] * projectile_velocity[1]));
                if (magnitude > 0) {
                    projectile_velocity[0] = (projectile_velocity[0] / magnitude) * pattern->projectileSpeed;
                    projectile_velocity[1] = (projectile_velocity[1] / magnitude) * pattern->projectileSpeed;
                }
                entity_t projectile = reg.spawn_entity();
                reg.add_component<Position_s>(projectile, Position_s{position->x, position->y + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile, Velocity_s{projectile_velocity[0], projectile_velocity[1]});
                reg.add_component<Type_s>(projectile, Type_s{EntityType::ENEMY_PROJECTILE});
                reg.add_component<Damage_s>(projectile, Damage_s{10});
                reg.add_component<Size>(projectile, Size{70, 30});
                networkSender->sendCreateProjectil(projectile, position->x, position->y, i);
            }
        }
    }
}

std::array<float, 2> Systems::find_closest_player(Registry &reg, Position *position_entity)
{
    float min_target_distance = 1000000;
    float target_x = 0;
    float target_y = 0;
    auto &positions = reg.get_components<Position>();
    auto &types = reg.get_components<Type>();

    for (size_t j = 0; j < positions.size(); ++j) {
        auto &target_position = positions[j];
        auto &target_type = types[j];
        if (target_position && target_type && target_type->type == EntityType::PLAYER) {
            float target_distance = abs(target_position->x - position_entity->x) + abs(target_position->y - position_entity->y);
            if (target_distance < min_target_distance) {
                min_target_distance = target_distance;
                target_x = target_position->x;
                target_y = target_position->y;
            }
        }
    }
    return (std::array<float, 2>({target_x, target_y}));
}
