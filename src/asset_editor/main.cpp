/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** main
*/

#include "AssetEditor/AssetEditor.hpp"

int main()
{
    Edition::AssetEditor assetEditor;

    try  {
        assetEditor.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}
