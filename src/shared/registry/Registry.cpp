/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Registry
*/

#include "Registry.hpp"

entity_t Registry::spawn_entity() {
    if (!_dead_entities.empty()) {
        entity_t reused_id = _dead_entities.front();
        _dead_entities.pop();
        return reused_id;
    }
    _entities.push_back(_next_entity_id);
    return _next_entity_id++;
}

entity_t Registry::entity_from_index(std::size_t idx) const {
    return _entities.at(idx);
}

void Registry::kill_entity(entity_t const& e) {
    _dead_entities.push(e);
    for (auto& [type, eraser] : _component_erasers) {
        eraser(*this, e);
    }
}
