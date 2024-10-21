/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#include "ComponentsEditor.hpp"

Edition::ComponentsEditor::ComponentsEditor()
{
}

Edition::ComponentsEditor::~ComponentsEditor()
{
}

void Edition::ComponentsEditor::display(std::shared_ptr<sf::RenderWindow> window)
{

}

void Edition::ComponentsEditor::updateSelectedEntity(std::shared_ptr<Edition::Asset> asset)
{
    _asset = asset;
}
