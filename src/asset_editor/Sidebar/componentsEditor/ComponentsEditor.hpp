/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#ifndef COMPONENTSEDITOR_HPP_
#define COMPONENTSEDITOR_HPP_

#include "../../history/Asset.hpp"
#include <memory>
#include "Input.hpp"
#include "InputNumber.hpp"
#include "SelectButton.hpp"
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    typedef struct HealthDisplay_s {
        std::unique_ptr<InputNumber> health;

        void initialize(int healthValue) {
            this->health = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "hp: ");
            this->health->setInput(std::to_string(healthValue));
        }
    } HealthDisplay;

    typedef struct ShootStraightPatternDisplay_s {
        std::unique_ptr<InputNumber> projectileSpeed;
        std::unique_ptr<InputNumber> shootCooldown;
        void initialize(int speed, int cooldown) {
            this->projectileSpeed = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Speed: ");
            this->projectileSpeed->setInput(std::to_string(speed));
            this->shootCooldown = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Cooldown: ");
            this->shootCooldown->setInput(std::to_string(cooldown));
        }
    } ShootStraightPatternDisplay;

    typedef struct ShootPlayerPatternDisplay_s {
        std::unique_ptr<InputNumber> projectileSpeed;
        std::unique_ptr<InputNumber> shootCooldown;
        void initialize(int speed, int cooldown) {
            this->projectileSpeed = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Speed: ");
            this->projectileSpeed->setInput(std::to_string(speed));
            this->shootCooldown = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Cooldown: ");
            this->shootCooldown->setInput(std::to_string(cooldown));
        }
    } ShootPlayerPatternDisplay;

    typedef struct PlayerFollowingPatternDisplay_s {
        std::unique_ptr<InputNumber> speed;
        void initialize(int speedValue) {
            this->speed = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Speed: ");
            this->speed->setInput(std::to_string(speedValue));
        }
    } PlayerFollowingPatternDisplay;

    typedef struct StraightLinePatternDisplay_s {
        std::unique_ptr<InputNumber> speed;
        void initialize(int speedValue) {
            this->speed = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "Speed: ");
            this->speed->setInput(std::to_string(speedValue));
        }
    } StraightLinePatternDisplay;

    typedef struct Wave_patternDisplay_s {
        std::unique_ptr<InputNumber> amplitude;
        std::unique_ptr<InputNumber> frequency;
        void initialize(float amp, float freq) {
            this->amplitude = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "amplitude: ");
            this->amplitude->setInput(std::to_string(amp));
            this->frequency = std::make_unique<InputNumber>(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "fequency: ");
            this->frequency->setInput(std::to_string(freq));
        }
    } Wave_patternDisplay;
    typedef struct TypeDisplay_s {
        std::unique_ptr<SelectButton> type;

        void initialize() {
            std::vector<std::string> option({"PLAYER", "ENEMY", "PLAYER_PROJECTILE", "ENEMY_PROJECTILE", "BACKGROUND", "OBSTACLE", "POWERUP"});
            this->type = std::make_unique<SelectButton>(sf::Vector2f(1460, 400), sf::Vector2f(300, 50), option);
        }
    } TypeDisplay;
    /**
     * @brief A class used for editing the attributes of assets.
     * 
     * The ComponentsEditor class provides functionality to modify 
     * various properties of an asset, such as size, position, and pattern. 
     * It interacts with the user to update the selected entity and renders 
     * the necessary UI components for asset editing.
     */
    class ComponentsEditor {
        public:
            ComponentsEditor();
            ~ComponentsEditor();

            /**
             * @brief Updates the currently selected asset with new attributes.
             * 
             * @param asset The asset to be modified.
             */
            void updateSelectedEntity(std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Displays the editor UI on the provided window.
             * 
             * @param window The render window where the UI is displayed.
             */
            void display(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Handles user input events for the editor.
             * 
             * @param event The event to handle, typically user input such as keyboard or mouse actions.
             */
            void handleInput(const sf::Event &event);

            private:
            /**
             * @brief Displays the title of a category in the specified position.
             * 
             * @param window The render window where the title is displayed.
             * @param title The title text to be displayed.
             * @param posX The X coordinate for the position of the title.
             * @param posY The Y coordinate for the position of the title.
             */
            void displayCategoryTitle(std::shared_ptr<sf::RenderWindow> window, std::string title, float posX, float posY);
            /**
             * @brief Displays the health information in the specified position.
             * 
             * @param window The render window where the health information is displayed.
             * @param posY The reference to the Y coordinate where the health will be displayed and updated after rendering.
             */
            void displayHealth(std::shared_ptr<sf::RenderWindow> window, int &posY);

            /**
             * @brief Displays a UI option to add a component at a specified position.
             * 
             * @param window The render window where the "Add Component" option is displayed.
             * @param posY The Y coordinate where the option will be displayed.
             */
            void displayAddComponent(std::shared_ptr<sf::RenderWindow> window, int posY);

            /**
             * @brief Adds a new component to the entity or object.
             */
            void addComponent();
            /**
             * @brief Handles user input for updating health values.
             * 
             * @param event The SFML event object representing user input events such as key presses or mouse actions.
             */
            void handleHealthInput(const sf::Event &event);

            std::shared_ptr<Edition::Asset> _asset;
            sf::Font font;
            std::unique_ptr<Input> label;
            std::unique_ptr<InputNumber> posX;
            std::unique_ptr<InputNumber> posY;
            std::unique_ptr<InputNumber> sizeX;
            std::unique_ptr<InputNumber> sizeY;
            std::unique_ptr<InputNumber> rotation;
            int currentPosY;
            std::unique_ptr<SelectButton> componentSelection;
            sf::RectangleShape addButton;
            std::vector<std::string> options = { "Health", "ShootStraightPattern", "ShootPlayerPattern", "PlayerFollowingPattern" , "StraightLinePattern", "Wave_pattern" ,"Type"};

            std::unique_ptr<HealthDisplay> healthDisplay;
            std::unique_ptr<ShootStraightPatternDisplay> shootStraightPatternDisplay;
            std::unique_ptr<ShootPlayerPatternDisplay> shootPlayerPatternDisplay;
            std::unique_ptr<PlayerFollowingPatternDisplay> playerFollowingPatternDisplay;
            std::unique_ptr<StraightLinePatternDisplay> straightLinePatternDisplay;
            std::unique_ptr<Wave_patternDisplay> wavePatternDisplay;
            std::unique_ptr<TypeDisplay> typeDisplay;
    };
}

#endif /* !COMPONENTSEDITOR_HPP_ */
