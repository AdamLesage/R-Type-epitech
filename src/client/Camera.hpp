/*
** EPITECH PROJECT, 2024
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <SFML/Graphics.hpp>
#include "../shared/components/Size.hpp"
#include "../shared/components/Position.hpp"
#include "../shared/components/Direction.hpp"
#include "../shared/components/Rotation.hpp"
#include "../shared/components/Sprite.hpp"
#include "../shared/components/Health.hpp"
#include "../shared/components/Score.hpp"
#include <array>

typedef struct EntityRenderInfo_s {
        Size size;
        Position position;
        Rotation rotation;
        Direction direction;
        Sprite sprite;
        Health health;
        Score score;
} EntityRenderInfo;

/**
 * @struct Camera_s
 */
typedef struct Camera_s {
        /**
         * @brief Camera component, add a camera to an entity
         *
         */
        std::vector<EntityRenderInfo> listEntityToDisplay;
} Camera;

#endif /* !CAMERA_HPP_ */
