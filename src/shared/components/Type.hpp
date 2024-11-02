/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Type
*/

#ifndef TYPE_HPP_
#define TYPE_HPP_

enum EntityType { PLAYER, ENEMY, PLAYER_PROJECTILE, ENEMY_PROJECTILE, BACKGROUND, OBSTACLE, POWERUP, BOSS };

typedef struct Type_s {
        EntityType type;
} Type;

#endif /* !TYPE_HPP_ */
