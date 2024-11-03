# Game Menu Documentation

## Menu Structure

The game menu is structured into several sections (`Start`, `Lobby`, `Game`, `EndMenu`), with each section representing a distinct scene with its own properties and configurations.

---

### 1. `Menu.Start`

Represents the game’s starting scene.

- **SceneNumber**: The scene number (here, `1` for Start).
- **background**: Path to the scene’s background image (`assets/background/back.png`).
- **image**: Main image of the scene, often representing a key visual element.
  - `path`: Image file path.
  - `posX`, `posY`: Position of the image on the screen.
- **option**: List of navigation options, each defined with:
  - `text`: Text displayed on the button.
  - `posX`, `posY`: Position of the button.
  - `to`: Scene number of the target scene when the button is selected (`2` for Lobby, `0` for settings, `-1` to quit).

---

### 2. `Menu.Lobby`

Represents the game’s Lobby scene.

- **SceneNumber**: Scene number (`2`).
- **background**: Path to the background image (same as `Start`).
- **option**: List of navigation options available in the lobby, with the same structure as `Start`.

---

### 3. `Menu.Game`

Represents the main gameplay scene, containing different levels.

- **SceneNumber**: Scene number (`3`).
- **level**: List of levels, with each level having its own background, sounds, and settings.
  - **levelId**: Unique identifier for the level (0, 1, 2, etc.).
  - **backgrounds**: List of background images for the level.
    - `path`: Background image file path.
    - `transparency`: Image transparency level (0 to 255, where 128 is half-transparent).
    - `movingSpeedX`, `movingSpeedY`: Image movement speed (e.g., `movingSpeedX = -2`).
  - **sounds**: Sounds associated with the level.
    - `launchSound`: Sound played when the level starts.
    - `shootSound`: Sound played during shooting actions.
  - **sceneConfig**: Path to the specific configuration file for the level.

Each level in `Menu.Game.level` is configured to offer a unique visual and auditory experience, with parallax effects.

---

### 4. `Menu.EndMenu`

Represents the game’s end screen or victory screen.

- **SceneNumber**: Scene number (`4`).
- **background**: Path to the background image of this scene.
- **option**: Navigation options that allow replaying, accessing settings, or exiting the game, with the same structure as `Start` and `Lobby`.

---

## Example of Adding a New Level to `Game`

To add a new level in `Game`, define a new entry in `Menu.Game.level` with the necessary keys:

```lua
{
    levelId = 8,
    backgrounds = (
        { path = "assets/background/new_background.png", transparency = 128, movingSpeedX = -1, movingSpeedY = 0 }
    ),
    sounds = {
        launchSound = "assets/Sounds/new_launch.ogg",
        shootSound = "assets/Sounds/new_shoot.wav"
    },
    sceneConfig = "config/scenes/Level_6.cfg"
}
