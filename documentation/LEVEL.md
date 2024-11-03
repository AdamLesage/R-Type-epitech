# Scene Configuration Documentation

This document provides an overview of the structure and components used to configure each entity within the game scene.

---

## Scene Structure

Each `scene` contains multiple `entities`, each represented by an object with specific properties and configurations. Below are the details of each entity attribute and component.

### 1. `code`
- **Description**: Unique hexadecimal code identifier for the entity type (e.g., `0x50`, `0x51`).
  
### 2. `number`
- **Description**: Number of instances of this entity type that will be spawned within the scene.

### 3. `components`
- **Description**: Contains all attributes defining the entity's behavior, appearance, and interactions. The components include:

#### 3.1. `position`
  - **x**: X-axis coordinate of the entity's position.
  - **y**: Y-axis coordinate of the entity's position.

#### 3.2. `size`
  - **x**: Width of the entity.
  - **y**: Height of the entity.

#### 3.3. `rotation`
  - **Description**: Specifies the initial rotation of the entity in degrees.

#### 3.4. `damage`
  - **value**: Amount of damage inflicted by this entity on impact.

#### 3.5. `health`
  - **health**: Maximum health of the entity.
  - **isRegenerating**: Specifies if the entity regenerates health (`0` for no, `1` for yes).
  - **isDamageable**: Defines if the entity can take damage (`0` for no, `1` for yes).

#### 3.6. `sprite`
  - **path**: File path to the entity's sprite image.
  - **rectPos**: Starting position of the sprite within the sprite sheet (`x`, `y`).
  - **rectSize**: Size of the sprite within the sprite sheet (`width`, `height`).

#### 3.7. `shootStraightPattern` (optional)
  - **shootCooldown**: Delay (in seconds) between each shot.
  - **projectileSpeed**: Speed of the projectiles fired by the entity in a straight line.

#### 3.8. `shootPlayerPattern` (optional)
  - **shootCooldown**: Delay between each shot directed towards the player.
  - **projectileSpeed**: Speed of the projectiles when targeting the player.

#### 3.9. `straightLinePattern` (optional)
  - **speed**: Speed at which the entity moves in a straight line.

#### 3.10. `playerFollowingPattern` (optional)
  - **speed**: Speed at which the entity follows the player.

#### 3.11. `animation`  (optional)
  - **animationSpeed**: Frame rate of the animation (time in seconds between frames).
  - **steps**: List of frames in the animation, each frame represented by `[x, y, width, height]`, defining its position and size within the sprite sheet.

---

## Entity Examples

### Example 1: Enemy with Straight Shooting
```lua
{
    code = 0x50,
    number = 5,
    components = {
        position = {x = 5001, y = 389},
        size = {x = 64, y = 64},
        rotation = 0,
        damage = { value = 10 },
        health = { health = 100, isRegenerating = 0, isDamageable = 1 },
        sprite = {
            path = "assets/enemy/enemy_1_easy.png",
            rectPos = (0, 0),
            rectSize = (171, 180)
        },
        shootStraightPattern = {
            shootCooldown = 1.0,
            projectileSpeed = 3.0
        },
        straightLinePattern = {speed = -2.0},
        animation = {
            animationSpeed = 0.2,
            steps = {
                [0, 0, 171, 180],
                [171, 0, 171, 180],
                // Additional frames here
            }
        }
    }
}
