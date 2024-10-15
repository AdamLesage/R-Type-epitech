/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RightSidebar
*/

#ifndef RIGHTSIDEBAR_HPP_
#define RIGHTSIDEBAR_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>


namespace Edition {
    /**
     * @brief Right Sidebar of the Asset Editor
     * 
     * This sidebar will be used to display different assets and components that can be added to the scene
     * 
     * Components will be given to different entities in the scene
     */
    class RightSidebar {
        public:
            /**
             * @brief Construct a new Right Sidebar object
             * 
             * @param window  The window of the Asset Editor
             */
            RightSidebar(sf::RenderWindow &window);

            /**
             * @brief Destroy the Right Sidebar object
             */
            ~RightSidebar();

            void draw();

        protected:
        private:
            sf::RenderWindow &_window;
            bool my_tool_active;
            float *_color;
    };
}

#endif /* !RIGHTSIDEBAR_HPP_ */
