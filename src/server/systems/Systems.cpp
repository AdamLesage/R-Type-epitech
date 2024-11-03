/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#include "Systems.hpp"

void Systems::position_system(Registry& reg,
                              std::unique_ptr<NetworkSender>& networkSender,
                              RType::Logger& logger) {
    (void)logger;
    auto& positions  = reg.get_components<Position_s>();
    auto& velocities = reg.get_components<Velocity_s>();
    auto& types      = reg.get_components<Type>();
    auto& directions = reg.get_components<Direction>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto& pos  = positions[i];
        auto& vel  = velocities[i];
        auto& type = types[i];

        if (pos && vel) {
            if (type->type == EntityType::ENEMY_PROJECTILE) {
                if (vel->x == 0) {
                    vel->x = -3;
                }
            } else if (type->type == EntityType::PLAYER_PROJECTILE) {
                if (vel->x == 0) {
                    vel->x = 3;
                }
            }
            if (type->type == EntityType::PLAYER) {
                auto &playerDirection = directions[i];
                if (playerDirection->x != vel->x || playerDirection->y != vel->y) {
                    playerDirection->x = vel->x;
                    playerDirection->y = vel->y;
                    networkSender->sendDirectionUpdate(i, playerDirection->x, playerDirection->y);
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

void Systems::control_system(
    Registry& reg, bool up, bool down, bool left, bool right, RType::Logger& logger) {
    (void)logger;
    auto& velocities    = reg.get_components<Velocity_s>();
    auto& controllables = reg.get_components<Controllable_s>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto& vel  = velocities[i];
        auto& ctrl = controllables[i];

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

void Systems::draw_system(Registry& reg, sf::RenderWindow& window, RType::Logger& logger) {
    (void)logger;
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

void Systems::logging_system(SparseArray<Position_s> const& positions,
                             SparseArray<Velocity_s> const& velocities,
                             RType::Logger& logger) {
    (void)logger;
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto const& pos = positions[i];
        auto const& vel = velocities[i];
        if (pos && vel) {
            std::cerr << i << " : Position = { " << pos.value().x << " , " << pos.value().y
                      << " } , Velocity = { " << vel.value().x << " , " << vel.value().y << " }" << std::endl;
        }
    }
}

void Systems::check_borders_collisions(Registry& reg,
                                       size_t entityId,
                                       Position_s* entityPos,
                                       Size_s* entitySize,
                                       Type_s* entityType,
                                       std::pair<size_t, size_t> MapSize,
                                       RType::Logger& logger,
                                       std::unique_ptr<NetworkSender>& networkSender) {
    (void)logger;
    if ((entityType->type == EntityType::ENEMY_PROJECTILE
         || entityType->type == EntityType::PLAYER_PROJECTILE)
        && (entityPos->x < 0 || entityPos->x + entitySize->x > MapSize.first || entityPos->y < 0
            || entityPos->y + entitySize->y > MapSize.second)) {
        reg.kill_entity(entityId);
        networkSender->sendDeleteEntity(entityId);
    }
    if (entityType->type == EntityType::ENEMY && entityPos->x < 0) {
        reg.kill_entity(entityId);
        networkSender->sendDeleteEntity(entityId);
    }
}

void Systems::check_entities_collisions(Registry& reg,
                                        size_t entityId1,
                                        Position_s* entityPos1,
                                        Size_s* entitySize1,
                                        size_t entityId2,
                                        Position_s* entityPos2,
                                        Size_s* entitySize2,
                                        RType::Logger& logger,
                                        std::unique_ptr<NetworkSender>& networkSender,
                                        Type_s* entityType1,
                                        Type_s* entityType2,
                                        bool friendlyfire)
{
    bool collisionX =
        entityPos1->x < entityPos2->x + entitySize2->x && entityPos1->x + entitySize1->x > entityPos2->x;
    bool collisionY =
        entityPos1->y < entityPos2->y + entitySize2->y && entityPos1->y + entitySize1->y > entityPos2->y;

    bool playerTakeDamage =
        (entityType1->type == EntityType::PLAYER && entityType2->type == EntityType::ENEMY_PROJECTILE)
        || (entityType1->type == EntityType::PLAYER && entityType2->type == EntityType::ENEMY) 
        || (entityType1->type == EntityType::PLAYER  && entityType2->type == EntityType::PLAYER_PROJECTILE && friendlyfire == true && entityId1 != reg.get_components<ParentId_s>()[entityId2]->ParentId);

    bool enemyTakeDamage =
        (entityType1->type == EntityType::ENEMY && entityType2->type == EntityType::PLAYER_PROJECTILE);

    bool playerTakeBonus =
        (entityType1->type == EntityType::PLAYER && entityType2->type == EntityType::POWERUP);

    bool bossTakeDamage =
        (entityType1->type == EntityType::BOSS && entityType2->type == EntityType::PLAYER_PROJECTILE);

    if (collisionX == false || collisionY == false
        || (playerTakeDamage == false && enemyTakeDamage == false && bossTakeDamage == false && playerTakeBonus == false)) { // No collision
        return;
    }

    if (playerTakeDamage && collisionX && collisionY) {
        auto &playerHealth = reg.get_components<Health_s>()[entityId1];
        auto &enemyDamage = reg.get_components<Damage_s>()[entityId2];
        

        if (playerHealth && enemyDamage) {
            if (playerHealth->isDamageable == true) {
                if (playerHealth->health < enemyDamage->damage) {
                    playerHealth->health = 0;
                } else {
                    playerHealth->health -= enemyDamage->damage;
                }
            }

            if (playerHealth->health <= 0) {
                reg.kill_entity(entityId1);
                networkSender->sendDeleteEntity(entityId1);
            } else {
                networkSender->sendHealthUpdate(entityId1, playerHealth->health);
            }
        } else {
            logger.log(RType::Logger::RTYPEERROR,
                       "Error while getting health or damage component for player");
        }
        // Delete entity that hit the player if it's a projectile
        if (entityType2->type == EntityType::ENEMY_PROJECTILE && playerHealth->isDamageable == true) {
            reg.kill_entity(entityId2);
            networkSender->sendDeleteEntity(entityId2);
        }
        if (entityType2->type == EntityType::PLAYER_PROJECTILE && playerHealth->isDamageable == true) {
            reg.kill_entity(entityId2);
            networkSender->sendDeleteEntity(entityId2);
        }
    }

    if (enemyTakeDamage && collisionX && collisionY) {
        // logger.log(RType::Logger::RTYPEINFO, "Enemy take damage");
        auto& enemyHealth      = reg.get_components<Health_s>()[entityId1];
        auto& projectileDamage = reg.get_components<Damage_s>()[entityId2];
        size_t maxHealth = enemyHealth->health;
        if (enemyHealth && projectileDamage) {
            if (projectileDamage->damage > enemyHealth->health) {
                enemyHealth->health = 0;
            } else {
                enemyHealth->health -= projectileDamage->damage;
            }
            if (enemyHealth->health <= 0) {
                reg.kill_entity(entityId1);
                networkSender->sendDeleteEntity(entityId1);
            } else {
                networkSender->sendHealthUpdate(entityId1, enemyHealth->health);
            }
        } else {
            logger.log(RType::Logger::RTYPEERROR, "Error while getting health or damage component for enemy");
        }
        if (reg.get_components<IsBigMissile>().size() > entityId2 && reg.get_components<IsBigMissile>()[entityId2]) {
            if (projectileDamage->damage <= maxHealth) {
                reg.kill_entity(entityId2);
                networkSender->sendDeleteEntity(entityId2);
            } else {
                projectileDamage->damage -= maxHealth;
            }
        } else if (!(reg.get_components<IsBigMissile>().size() > entityId2 && reg.get_components<IsBigMissile>()[entityId2])) {
            // If enemy take damage, it is only a projectile so we delete it
            reg.kill_entity(entityId2);
            networkSender->sendDeleteEntity(entityId2);
        }
    }

    if (playerTakeBonus && collisionX && collisionY) {
        auto& playerHealth = reg.get_components<Health_s>()[entityId1];
        auto& bonusType    = reg.get_components<Type_s>()[entityId2];
        auto& bonustag    = reg.get_components<Tag_s>()[entityId2];

        if (playerHealth && bonusType) {
            if (bonusType->type == EntityType::POWERUP && bonustag->tag == "shield_bonus") {
                playerHealth->health += 50;
                networkSender->sendHealthUpdate(entityId1, playerHealth->health);
            }
            if (bonusType->type == EntityType::POWERUP && bonustag->tag == "machinegun_bonus") {
                reg.get_components<ShootingSpeed_s>()[entityId1]->shooting_speed *= 0.9;
            }
            if (bonusType->type == EntityType::POWERUP && bonustag->tag == "rocket_bonus") {
                reg.get_components<CanShootMissiles>()[entityId1]->number += 3;
            }
            if (bonusType->type == EntityType::POWERUP && bonustag->tag == "beam_bonus") {
                reg.get_components<CanShootBigMissile>()[entityId1]->number += 1;
            }
            if (bonusType->type == EntityType::POWERUP && bonustag->tag == "clone_bonus") {
                entity_t entity = reg.spawn_entity();
                reg.add_component<Clone>(entity, Clone{entityId1});
                reg.add_component<Position>(entity, Position{entityPos1->x, entityPos1->y + 100});
                reg.add_component<Velocity>(entity, Velocity{0, 0});
                reg.add_component<Type>(entity, Type{EntityType::PLAYER});
                reg.add_component<Size>(entity, Size{130, 80});
                reg.add_component<Health>(entity, Health{1, 1, false, true});
                networkSender->sendCreatePlayer(4, entityPos1->x, entityPos1->y + 100);
            }
        } else {
            logger.log(RType::Logger::RTYPEERROR, "Error while getting health or type component for player");
        }
        reg.kill_entity(entityId2);
        networkSender->sendDeleteEntity(entityId2);
    }

    if (bossTakeDamage && collisionX && collisionY) {
        logger.log(RType::Logger::RTYPEINFO, "Boss take damage");
        auto& bossHealth      = reg.get_components<Health_s>()[entityId1];
        auto& projectileDamage = reg.get_components<Damage_s>()[entityId2];

        if (bossHealth && projectileDamage) { // if the boss has a health and the projectile has a damage
            bossHealth->health -= projectileDamage->damage;
            reg.kill_entity(entityId2); // destroy the projectile
            networkSender->sendDeleteEntity(entityId2);
            if (bossHealth->health <= 0) { // if the boss is dead
                reg.kill_entity(entityId1);
                networkSender->sendDeleteEntity(entityId1);
            } else { // if the boss is still alive
                networkSender->sendHealthUpdate(entityId1, bossHealth->health);
            }
        } else {
            logger.log(RType::Logger::RTYPEERROR, "Error while getting health or damage component for enemy");
        }
    }
}

struct SpatialHash {
    int cellSize;
    std::unordered_map<int, std::vector<size_t>> grid;

    // Renommage du paramètre du constructeur pour éviter le shadowing
    SpatialHash(int initialCellSize) : cellSize(initialCellSize) {}

    // Hash function for a cell key
    int hash(int x, int y) const {
        return std::hash<int>()(x / cellSize) ^ std::hash<int>()(y / cellSize);
    }

    // Insert an entity
    void insert(int x, int y, size_t entityIndex) {
        int cellKey = hash(x, y);
        grid[cellKey].push_back(entityIndex);
    }

    // Get nearby entities for a given position
    std::vector<size_t> getNearbyEntities(int x, int y) const {
        std::vector<size_t> nearbyEntities;
        
        // Pre compute the offsets for the 8 adjacent cells
        std::array<int, 9> offsets = {
            -1, -1, 0,   // Top-left, Top, Top-right
            -1,  0, 0,   // Left, Center, Right
            -1,  1, 0    // Bottom-left, Bottom, Bottom-right
        };

        // Iterate over the 8 adjacent cells
        for (size_t i = 0; i < offsets.size(); i += 1) {
            int adjacentCellKey = hash(x + offsets[i] * cellSize, y + offsets[i + 1] * cellSize);
            auto it = grid.find(adjacentCellKey);
            if (it != grid.end()) { // If the cell exists
                nearbyEntities.insert(nearbyEntities.end(), it->second.begin(), it->second.end());
            }
        }

        return nearbyEntities;
    }
};

void Systems::collision_system(Registry& reg,
                              std::pair<size_t, size_t> MapSize,
                              std::unique_ptr<NetworkSender>& networkSender,
                              RType::Logger& logger, bool friendlyfire) {
    auto &positions = reg.get_components<Position_s>();
    auto &sizes = reg.get_components<Size_s>();
    auto &types = reg.get_components<Type_s>();

    int cellSize = 100; 
    SpatialHash spatialHash(cellSize); // Create a spatial hash with a cell size of 100

    // Insert all entities into the spatial hash
    for (size_t i = 0; i < positions.size() && i < sizes.size(); ++i) {
        if (positions[i] && sizes[i]) {
            spatialHash.insert(positions[i]->x, positions[i]->y, i);
        }
    }

    // Check collisions between entities
    for (size_t i = 0; i < positions.size() && i < sizes.size(); ++i) {
        if (!positions[i] || !sizes[i] || !types[i])
            continue;

        auto &entityPos = *positions[i];
        auto &entitySize = *sizes[i];
        auto &entityType = *types[i];

        // Check if the entity is colliding with the map borders
        check_borders_collisions(reg, i, &entityPos, &entitySize, &entityType, MapSize, logger, networkSender);

        // Get nearby entities from the spatial hash
        auto nearbyEntities = spatialHash.getNearbyEntities(entityPos.x, entityPos.y);

        for (size_t j : nearbyEntities) {
            if (i == j || !positions[j] || !sizes[j] || !types[j]) continue;

            auto &entityPos2 = *positions[j];
            auto &entitySize2 = *sizes[j];
            auto &entityType2 = *types[j];

            // Check if the entities are colliding
            check_entities_collisions(reg, i, &entityPos, &entitySize, j, &entityPos2, &entitySize2, logger, networkSender, &entityType, &entityType2, friendlyfire);
        }
    }
}

void Systems::shoot_system(Registry& reg,
                           size_t clientId,
                           entity_t playerId,
                           std::unique_ptr<NetworkSender>& networkSender,
                           RType::Logger& logger) {
    (void)logger;
    bool haveShoot = false;
    auto& positions      = reg.get_components<Position_s>();
    auto& types          = reg.get_components<Type_s>();
    auto& shootingSpeeds = reg.get_components<ShootingSpeed_s>();
    auto& shoots         = reg.get_components<Shoot>();
    auto& sizes          = reg.get_components<Size>();
    auto& canShootMissiles       = reg.get_components<CanShootMissiles>();
    auto& canShootBigMissiles       = reg.get_components<CanShootBigMissile>();

    auto& pos           = positions[playerId];
    auto& type          = types[playerId];
    auto& shootingSpeed = shootingSpeeds[playerId];
    auto& shoot         = shoots[playerId];
    auto& size          = sizes[playerId];
    if (type && type->type == EntityType::PLAYER && shoot->canShoot) {
        auto now                        = std::chrono::steady_clock::now();
        std::chrono::duration<float> fs = now - shoot->shootCooldown;
        float elapsed_seconds           = std::chrono::duration_cast<std::chrono::milliseconds>(fs).count();
        if (elapsed_seconds >= shootingSpeed->shooting_speed * 1000) {
            haveShoot = true;
            shoot->shootCooldown = now;
            float projectileX    = pos->x + 10;

            entity_t projectile = reg.spawn_entity();
            reg.add_component<Type_s>(projectile, Type_s{EntityType::PLAYER_PROJECTILE});
            reg.add_component<ParentId>(projectile, ParentId{playerId});

            if (canShootBigMissiles.size() > playerId && canShootBigMissiles[playerId] && canShootBigMissiles[playerId]->number != 0) {
                canShootBigMissiles[playerId]->number--;
                float projectileY    = pos->y - (160 / 2);
                reg.add_component<Position_s>(
                    projectile, Position_s{projectileX + (size->x / 2), projectileY + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile, Velocity_s{2.5f, 0.0f});
                reg.add_component<Damage_s>(projectile, Damage_s{400});
                reg.add_component<Size>(projectile, Size{240, 160});
                reg.add_component<IsBigMissile>(projectile, IsBigMissile{true});
                networkSender->sendCreateBigMissile(playerId, projectileX, projectileY, clientId);
                networkSender->sendShootSound();
            } else if (canShootMissiles.size() > playerId && canShootMissiles[playerId] && canShootMissiles[playerId]->number != 0) {
                float projectileY    = pos->y - (30 / 2);
                reg.add_component<Position_s>(
                    projectile, Position_s{projectileX + (size->x / 2), projectileY + (size->y / 2) - (30 / 2)});
                canShootMissiles[playerId]->number--;
                reg.add_component<ShootEnnemyMissile>(projectile, ShootEnnemyMissile{3.0f});
                reg.add_component<Size>(projectile, Size{70, 30});
                reg.add_component<Damage_s>(projectile, Damage_s{200});
                reg.add_component<Velocity_s>(projectile, Velocity_s{0.1f, 0.1f});
                networkSender->sendCreateMissile(playerId, projectileX, projectileY);
                networkSender->sendShootSound();
            } else {
                float projectileY    = pos->y - (30 / 2);
                reg.add_component<Position_s>(
                    projectile, Position_s{projectileX + (size->x / 2), projectileY + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile, Velocity_s{3.0f, 0.0f});
                reg.add_component<Size>(projectile, Size{70, 30});
                reg.add_component<Damage_s>(projectile, Damage_s{25});
                networkSender->sendCreateProjectil(playerId, projectileX, projectileY, clientId);
                networkSender->sendShootSound();
            }
        }
    }
    if (haveShoot) {
        auto& clones  = reg.get_components<Clone>();
        for (size_t i = 0; i < clones.size(); ++i) {
            auto &clone = clones[i];
            if (clone && clone->playerId == playerId) {
                auto& clonePos = positions[i];
                auto& cloneSize = sizes[i];
                if (clonePos && cloneSize) {
                    entity_t projectile = reg.spawn_entity();
                    reg.add_component<Type_s>(projectile, Type_s{EntityType::PLAYER_PROJECTILE});
                    reg.add_component<ParentId>(projectile, ParentId{i});
                    float projectileY    = clonePos->y - (30 / 2);
                    reg.add_component<Position_s>(
                        projectile, Position_s{clonePos->x + 10 + (cloneSize->x / 2), projectileY + (cloneSize->y / 2) - (30 / 2)});
                    reg.add_component<Velocity_s>(projectile, Velocity_s{3.0f, 0.0f});
                    reg.add_component<Size>(projectile, Size{70, 30});
                    reg.add_component<Damage_s>(projectile, Damage_s{10});
            networkSender->sendCreateProjectil(i, clonePos->x + 10 + (cloneSize->x / 2), projectileY, 4);
                }
            }
        }
    }
}

void Systems::shoot_enemy_missile(Registry& reg) {
    auto& missiles  = reg.get_components<ShootEnnemyMissile>();
    auto& velocitys = reg.get_components<Velocity>();
    auto& positions = reg.get_components<Position>();

    for (size_t i = 0; i < missiles.size(); ++i) {
        auto& missile  = missiles[i];
        auto& velocity = velocitys[i];
        auto& position = positions[i];

        if (missile && velocity && position) {
            std::array<float, 2> target_pos = this->find_closest_entity(reg, &(*position), EntityType::ENEMY);
            velocity->x                     = target_pos[0] - position->x;
            velocity->y                     = target_pos[1] - position->y;
            float magnitude = std::sqrt((velocity->x * velocity->x) + (velocity->y * velocity->y));

            if (magnitude > 0) {
                velocity->x = (velocity->x / magnitude) * missile->speed;
                velocity->y = (velocity->y / magnitude) * missile->speed;
            }
        }
    }
}

bool Systems::read_scores_file(libconfig::Config& cfg, const std::string& configPath) {
    try {
        cfg.readFile(configPath.c_str());
        return true;
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while reading file." << std::endl;
        return false;
    } catch (const libconfig::ParseException& ParserError) {
        std::cerr << "Parse error at " << ParserError.getFile() << ":" << ParserError.getLine() << " - "
                  << ParserError.getError() << std::endl;
        return false;
    }
}

void Systems::update_scores(libconfig::Config& cfg, const std::string& playerNames, size_t totalScore) {
    libconfig::Setting& root       = cfg.getRoot();
    libconfig::Setting& lastScores = root["scores"];
    libconfig::Setting& highScores = root["highscores"];

    std::vector<std::pair<std::string, int>> lastTenScores;
    for (int i = 0; i < lastScores.getLength(); ++i) {
        std::string name = lastScores[i]["name"];
        int value        = lastScores[i]["value"];
        lastTenScores.push_back({name, value});
    }

    lastTenScores.push_back({playerNames, totalScore});
    if (lastTenScores.size() > 10) {
        lastTenScores.erase(lastTenScores.begin());
    }

    for (auto i = 0u; i < lastTenScores.size(); ++i) {
        lastScores[i].add("name", libconfig::Setting::TypeString) = lastTenScores[i].first;
        lastScores[i].add("value", libconfig::Setting::TypeInt)   = lastTenScores[i].second;
    }

    std::vector<std::pair<std::string, int>> bestScores;
    for (int i = 0; i < highScores.getLength(); ++i) {
        std::string name = highScores[i]["name"];
        int value        = highScores[i]["value"];
        bestScores.push_back({name, value});
    }

    bestScores.push_back({playerNames, totalScore});
    std::sort(bestScores.begin(), bestScores.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });
    bestScores.resize(3);

    for (auto i = 0u; i < bestScores.size(); ++i) {
        highScores[i].add("name", libconfig::Setting::TypeString) = bestScores[i].first;
        highScores[i].add("value", libconfig::Setting::TypeInt)   = bestScores[i].second;
    }
}

bool Systems::write_to_scores_file(libconfig::Config& cfg, const std::string& configPath) {
    try {
        cfg.writeFile(configPath.c_str());
        std::cout << "Scores successfully written to: " << configPath << std::endl;
        return true;
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while writing file: " << configPath << std::endl;
        return false;
    }
}

void Systems::score_system(Registry& reg) {
    auto& hp           = reg.get_components<Health_s>();
    auto& controllable = reg.get_components<Controllable_s>();

    for (size_t i = 0; i < hp.size() && i < controllable.size(); ++i) {
        if (hp[i] && controllable[i] && hp[i]->health > 0) {
            return;
        }
    }

    std::string configPath = "config/scores.cfg";
    libconfig::Config cfg;

    if (!read_scores_file(cfg, configPath)) return;

    auto& scores            = reg.get_components<Score_s>();
    auto& names             = reg.get_components<Tag_s>();
    size_t totalScore       = 0;
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

void Systems::health_system(Registry& reg) {
    auto& healths = reg.get_components<Health_s>();
    auto& types   = reg.get_components<Type_s>();

    static auto lastUpdate = std::chrono::steady_clock::now();
    auto now               = std::chrono::steady_clock::now();
    auto elapsedTime       = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();

    size_t regenerationRate = 5; // load from config

    if (elapsedTime >= 1) {
        lastUpdate = now;

        for (size_t i = 0; i < healths.size() && i < types.size(); ++i) {
            auto& health = healths[i];
            auto& type   = types[i];
            if (health && type && type->type == EntityType::PLAYER) {
                health->health += regenerationRate;
                if (health->health > health->maxHealth) {
                    health->health = health->maxHealth;
                }
            }
        }
    }
}

void Systems::death_system(Registry& reg, RType::Logger& logger) {
    auto& healths = reg.get_components<Health_s>();
    auto& types   = reg.get_components<Type_s>();

    for (size_t i = 0; i < healths.size() && i < types.size(); ++i) {
        auto& health = healths[i];
        auto& type   = types[i];

        if (health && type && health->health <= 0) {
            reg.kill_entity(i);
            logger.log(RType::Logger::LogType::RTYPEINFO, "Entity %d died", i);
            // send_death to client
        }
    }
}

void Systems::wave_pattern_system(Registry& reg, RType::Logger& logger) {
    (void)logger;
    auto& patterns  = reg.get_components<Wave_pattern>();
    auto& positions = reg.get_components<Position>();
    auto& velocitys = reg.get_components<Velocity>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& position = positions[i];
        auto& velocity = velocitys[i];
        if (pattern && position && velocity) {
            auto now                        = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->creation;
            float elapsed_seconds           = std::chrono::duration_cast<std::chrono::milliseconds>(fs).count();
            velocity->x = -1;
            position->y += (pattern->amplitude * std::sin(pattern->frequency * (elapsed_seconds / 10)));
        }
        // logger.log(RType::Logger::LogType::INFO, "Player %d shot a projectile", playerId);
    }
}

void Systems::wave_of_ennemy_from_boss1(Registry& reg, std::unique_ptr<NetworkSender>& networkSender)
{
    for (int ennemy_number = 0; ennemy_number < 5; ++ennemy_number) {
        size_t enemy = reg.spawn_entity();
        reg.add_component<Position>(enemy, Position_s{1620, (float)ennemy_number * 200});
        reg.add_component<Velocity>(enemy, Velocity_s{-1.0f, 0.0f});
        reg.add_component<Type>(enemy, Type_s{EntityType::ENEMY});
        reg.add_component<Health>(enemy, Health_s{100, 100, false, false});
        reg.add_component<Size>(enemy, Size{50, 50});
        reg.add_component<Damage>(enemy, Damage{20});
        if (ennemy_number == 0) {              
            reg.add_component<StraightLinePattern>(enemy, StraightLinePattern{-1});
            reg.add_component<ShootStraightPattern>(enemy, ShootStraightPattern{2.0, 2.0, std::chrono::steady_clock::now()});
            networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
        }
        if (ennemy_number == 1) {                       
            reg.add_component<Wave_pattern>(enemy, Wave_pattern{1.f, 0.02f, std::chrono::steady_clock::now()});
            reg.add_component<ShootStraightPattern>(enemy, ShootStraightPattern{2.0, 2.0, std::chrono::steady_clock::now()});
            networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
        }
        if (ennemy_number == 2) {                       
            reg.add_component<StraightLinePattern>(enemy, StraightLinePattern{-1});
            reg.add_component<ShootPlayerPattern>(enemy, ShootPlayerPattern{2, 5, std::chrono::steady_clock::now()});
            networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
        }
        if (ennemy_number == 3) {                       
            reg.add_component<StraightLinePattern>(enemy, StraightLinePattern{-1});
            reg.add_component<ShootStraightPattern>(enemy, ShootStraightPattern{2.0, 2.0, std::chrono::steady_clock::now()});
            networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
        }
        if (ennemy_number == 4) {                       
            reg.add_component<PlayerFollowingPattern>(enemy, PlayerFollowingPattern{0.5f});
            reg.add_component<ShootPlayerPattern>(enemy, ShootPlayerPattern{2, 5, std::chrono::steady_clock::now()});
            networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
        }
    }
}

void Systems::wave_of_ennemy_from_boss2(Registry& reg, std::unique_ptr<NetworkSender>& networkSender)
{
    for (int ennemy_number = 0; ennemy_number < 5; ++ennemy_number) {
        size_t enemy = reg.spawn_entity();
        reg.add_component<Position>(enemy, Position_s{(float)1620 + ennemy_number * 50, (float)300 + ennemy_number * 25});
        reg.add_component<Velocity>(enemy, Velocity_s{-1.0f, 0.0f});
        reg.add_component<Type>(enemy, Type_s{EntityType::ENEMY});
        reg.add_component<Health>(enemy, Health_s{100, 100, false, false});
        reg.add_component<Size>(enemy, Size{50, 50});
        reg.add_component<Damage>(enemy, Damage{20});
        reg.add_component<Wave_pattern>(enemy, Wave_pattern{2.f, 0.02f * (float)(ennemy_number + 1), std::chrono::steady_clock::now()});
        reg.add_component<ShootPlayerPattern>(enemy, ShootPlayerPattern{2, 5, std::chrono::steady_clock::now()});
        networkSender->sendCreateEnemy(0x03, enemy, 1620, ennemy_number * 200);
    }
}

void Systems::wave_of_ennemy_from_boss3(Registry& reg, std::unique_ptr<NetworkSender>& networkSender)
{
    (void)reg;
    (void)networkSender;
}

void Systems::boss_system(Registry& reg, std::unique_ptr<NetworkSender>& networkSender)
{
    auto& patterns = reg.get_components<BossPatern>();
    auto& positions = reg.get_components<Position>();
    auto& velocitys = reg.get_components<Velocity>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& position = positions[i];
        auto& velocity = velocitys[i];
        if (pattern && position && velocity) {
            if (position->y >= 800) {
                pattern->up = false;
                pattern->down = true;
            }
            if (position->y <= 0) {
                pattern->up = true;
                pattern->down = false;
            }
            if (pattern->up) {
                velocity->y = -1 * pattern->speed;
            }
            if (pattern->down) {
                velocity->y = pattern->speed;
            }
            auto now                        = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->lastSpawnTime;
            float elapsed_seconds           = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

            if (elapsed_seconds >= pattern->spawnCooldown && pattern->spawnCooldown > 1) {
                if (rand() % 2 == 0) {
                    wave_of_ennemy_from_boss1(reg, networkSender);
                } else {
                    wave_of_ennemy_from_boss2(reg, networkSender);
                }
                pattern->lastSpawnTime = now;
            }
        }
    }
}

void Systems::Straight_line_pattern_system(Registry& reg) {
    auto& patterns  = reg.get_components<StraightLinePattern>();
    auto& positions = reg.get_components<Position>();
    auto& velocitys = reg.get_components<Velocity>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& position = positions[i];
        auto& velocity = velocitys[i];
        if (pattern && position && velocity) {
            velocity->x = pattern->speed;
        }
    }
}

void Systems::player_following_pattern_system(Registry& reg) {
    auto& patterns  = reg.get_components<PlayerFollowingPattern>();
    auto& velocitys = reg.get_components<Velocity>();
    auto& positions = reg.get_components<Position>();

    for (size_t i = 0; i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& velocity = velocitys[i];
        auto& position = positions[i];

        if (pattern && velocity && position) {
            std::array<float, 2> target_pos = this->find_closest_entity(reg, &(*position), EntityType::PLAYER);
            velocity->x                     = target_pos[0] - position->x;
            velocity->y                     = target_pos[1] - position->y;
            float magnitude = std::sqrt((velocity->x * velocity->x) + (velocity->y * velocity->y));

            if (magnitude > 0) {
                velocity->x = (velocity->x / magnitude) * pattern->speed;
                velocity->y = (velocity->y / magnitude) * pattern->speed;
            }
        }
    }
}

void Systems::shoot_straight_pattern_system(Registry& reg, std::unique_ptr<NetworkSender>& networkSender) {
    auto& patterns  = reg.get_components<ShootStraightPattern>();
    auto& positions = reg.get_components<Position>();
    auto& velocitys = reg.get_components<Velocity>();
    auto& sizes     = reg.get_components<Size>();

    for (size_t i = 0; i < positions.size() && i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& position = positions[i];
        auto& velocity = velocitys[i];
        auto& size     = sizes[i];

        if (pattern && position && velocity && size) {
            auto now                        = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->lastShotTime;
            float elapsed_seconds           = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

            if (elapsed_seconds >= pattern->shootCooldown && pattern->shootCooldown > 1) {
                pattern->lastShotTime = now;
                entity_t projectile   = reg.spawn_entity();
                reg.add_component<Position_s>(
                    projectile, Position_s{position->x, position->y + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile, Velocity_s{-1 * pattern->projectileSpeed, 0});
                reg.add_component<Type_s>(projectile, Type_s{EntityType::ENEMY_PROJECTILE});
                reg.add_component<Damage_s>(projectile, Damage_s{10});
                reg.add_component<Size>(projectile, Size{70, 30});
                networkSender->sendCreateProjectil(projectile, position->x, position->y, i);
            }
        }
    }
}

void Systems::shoot_player_pattern_system(Registry& reg, std::unique_ptr<NetworkSender>& networkSender) {
    auto& patterns  = reg.get_components<ShootPlayerPattern>();
    auto& velocitys = reg.get_components<Velocity>();
    auto& positions = reg.get_components<Position>();
    auto& sizes     = reg.get_components<Size>();

    for (size_t i = 0; i < patterns.size(); ++i) {
        auto& pattern  = patterns[i];
        auto& velocity = velocitys[i];
        auto& position = positions[i];
        auto& size     = sizes[i];

        if (pattern && velocity && position && size) {
            auto now                        = std::chrono::steady_clock::now();
            std::chrono::duration<float> fs = now - pattern->lastShotTime;
            float elapsed_seconds           = std::chrono::duration_cast<std::chrono::seconds>(fs).count();

            if (elapsed_seconds >= pattern->shootCooldown) {
                pattern->lastShotTime = now;

                std::array<float, 2> target_pos          = this->find_closest_entity(reg, &(*position), EntityType::PLAYER);
                std::array<float, 2> projectile_velocity = {target_pos[0] - position->x,
                                                            target_pos[1] - position->y};
                float magnitude = std::sqrt((projectile_velocity[0] * projectile_velocity[0])
                                            + (projectile_velocity[1] * projectile_velocity[1]));
                if (magnitude > 0) {
                    projectile_velocity[0] = (projectile_velocity[0] / magnitude) * pattern->projectileSpeed;
                    projectile_velocity[1] = (projectile_velocity[1] / magnitude) * pattern->projectileSpeed;
                }
                entity_t projectile = reg.spawn_entity();
                reg.add_component<Position_s>(
                    projectile, Position_s{position->x, position->y + (size->y / 2) - (30 / 2)});
                reg.add_component<Velocity_s>(projectile,
                                              Velocity_s{projectile_velocity[0], projectile_velocity[1]});
                reg.add_component<Type_s>(projectile, Type_s{EntityType::ENEMY_PROJECTILE});
                reg.add_component<Damage_s>(projectile, Damage_s{10});
                reg.add_component<Size>(projectile, Size{70, 30});
                networkSender->sendCreateProjectil(projectile, position->x, position->y, i);
            }
        }
    }
}

void Systems::clone_system(Registry& reg) {
    auto& clones  = reg.get_components<Clone>();
    auto& velocities = reg.get_components<Velocity>();

    for (size_t i = 0; i < clones.size(); ++i) {
        auto &clone = clones[i];
        if (clone) {
            auto &velocityClone = velocities[i];
            auto &velocityPlayer = velocities[clone->playerId];
            if (velocityClone && velocityPlayer) {
                velocityClone->x = velocityPlayer->x;
                velocityClone->y = velocityPlayer->y;
            }
        }
    }
}

std::array<float, 2> Systems::find_closest_entity(Registry& reg, Position* position_entity, EntityType type) {
    float min_target_distance = 1000000;
    float target_x            = 0;
    float target_y            = 0;
    auto& positions           = reg.get_components<Position>();
    auto& types               = reg.get_components<Type>();

    for (size_t j = 0; j < positions.size(); ++j) {
        auto& target_position = positions[j];
        auto& target_type     = types[j];
        if (target_position && target_type && target_type->type == type) {
            float target_distance =
                std::abs(target_position->x - position_entity->x) + std::abs(target_position->y - position_entity->y);
            if (target_distance < min_target_distance) {
                min_target_distance = target_distance;
                target_x            = target_position->x;
                target_y            = target_position->y;
            }
        }
    }
    return (std::array<float, 2>({target_x, target_y}));
}


void Systems::ping_client(Registry& reg, std::unique_ptr<NetworkSender>& networkSender) {
    (void)reg;
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* localtm = std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(localtm, "%d/%H/%M/%S");
    std::string formatted_time = oss.str();
    networkSender->sendPing(formatted_time);
}