/*
** EPITECH PROJECT, 2024
** B-CPP-500-NAN-5-1-bsrtype-romain.chevallier
** File description:
** Registery
*/

#ifndef REGISTERY_HPP_
#define REGISTERY_HPP_

#include <unordered_map>
#include <typeindex>
#include <any>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "SparseArray.hpp"
#include "Entity.hpp"
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Registery {
    public:
        std::shared_ptr<sf::RenderWindow> window;

        Registery(std::shared_ptr<sf::RenderWindow> win) {
            window = win;
            max_entity = 0;
            
        }
        ~Registery() {
        }
        template <class Component>
        SparseArray<std::optional<Component>>& register_component()
        {
            this->_container[std::type_index(typeid(Component))] = SparseArray<std::optional<Component>>();
            return get_components<Component>();
        }

        template <class Component>
        SparseArray<std::optional<Component>>& get_components() {
            try {
                return std::any_cast<SparseArray<std::optional<Component>>&>(
                    _container.at(std::type_index(typeid(Component)))
                );
            } catch (const std::bad_any_cast& e) {
                throw std::runtime_error("Invalid cast to SparseArray<std::optional<Component>>");
            }
        }
        template <class Component>
        SparseArray<std::optional<Component>> const &get_components() const
        {
            try {
                return std::any_cast<SparseArray<std::optional<Component>>&>(
                    _container.at(std::type_index(typeid(Component)))
                );
            } catch (const std::bad_any_cast& e) {
                throw std::runtime_error("Invalid cast to SparseArray<std::optional<Component>>");
            }
        }
        Entity spawn_entity() {
            entity.push_back(Entity(max_entity));
            max_entity++;
            return entity.back();
        }
        Entity entity_from_index(std::size_t idx) {
            for (auto & element : entity) {
                if (element == idx) {
                    return element;
                }
            }
            return 0;
        }
        void kill_entity(Entity const & e) {
            auto it = std::find(entity.begin(), entity.end(), e);
            if (it != entity.end()) { 
                entity.erase(it); 
            }
        }
        template <typename Component>
        typename SparseArray<std::optional<Component>>::reference_type add_component(Entity const &to, Component && c )
        {
            return this->get_components<Component>().insert_at((std::size_t)to, c);
        }
        template <typename Component, typename ...Params>
        typename SparseArray<std::optional<Component>>::reference_type emplace_component (Entity const &to, Params &&... p)
        {
            return this->get_components<Component>().emplace_at((std::size_t)to, std::forward<Params>(p)...);
        }
        template <typename Component>
        void remove_component(Entity const &from)
        {
            this->get_components<Component>().erase((std::size_t)from);
        }
        template <class ...Components, typename Function>
        void add_system ( Function && f ) {
            systems.push_back(std::move(f));
        }
        template <class ...Components, typename Function>
        void add_system ( Function const & f ) {
            systems.push_back(f);
        }
        void run_systems() {
            for (auto & system : systems) {
                system(*this);
            }
        }
    protected:
    private:
        std::unordered_map<std::type_index, std::any> _container;
        std::vector<Entity> entity;
        using SystemFunction = std::function<void(Registery & r)>;
        std::vector<SystemFunction> systems;
        int max_entity;
};

#endif /* !REGISTERY_HPP_ */
