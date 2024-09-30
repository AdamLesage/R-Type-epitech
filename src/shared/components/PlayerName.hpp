/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PlayerName
*/

#ifndef PLAYERNAME_HPP_
    #define PLAYERNAME_HPP_

    #include <string>

    /**
    * @struct PlayerName_s
    */
    typedef struct PlayerName_s {
        /**
        * @brief PlayerName component, add a tag to an entity
        *
        */
        std::string player_name; //tag of the entity (ex: player, enemy, bullet)
    } Tag;

#endif /* !TAG_HPP_ */
