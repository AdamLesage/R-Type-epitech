#ifndef CAMERAHPP
#define CAMERAHPP

#include <SFML/Graphics.hpp>
#include "../shared/components/Size.hpp"
#include "../shared/components/Position.hpp"
#include "../shared/components/Direction.hpp"

typedef struct EntityRenderInfos {
    Size size;
    Position position;
    Direction direction;
    std::string texturePath;
} EntityRenderInfo;

typedef struct Camera_s {
    std::vector<EntityRenderInfo> listEntityToDisplay;
} Camera;

#endif /* !CAMERA_HPP */