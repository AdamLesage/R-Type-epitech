/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Type
*/

#ifndef TYPE_HPP_
    #define TYPE_HPP_

    enum EntityType {
        PLAYER,
        ENEMY,
        PROJECTILE,
        BACKGROUND,
        OBSTACLE,
        POWERUP
    };

    typedef struct Type_s {
        EntityType type;
    } Type;

#endif /* !TYPE_HPP_ */