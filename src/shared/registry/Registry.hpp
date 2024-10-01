/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

    #include <unordered_map>
    #include <typeindex>
    #include <any>
    #include <functional>
    #include <vector>
    #include <queue>
    #include "../sparse_array/SparseArray.hpp"

using entity_t = std::size_t;

class Registry {
    public:
        /**
         * @brief Creates a new entity, reusing a dead entity ID if available.
         *
         * @return entity_t The ID of the newly spawned entity.
         */
        entity_t spawn_entity();

        /**
         * @brief Retrieves an entity ID from its index.
         *
         * @param idx The index of the entity in the internal vector.
         * @return entity_t The entity ID corresponding to the given index.
         */
        entity_t entity_from_index(std::size_t idx) const;

        /**
         * @brief Marks an entity as dead, allowing its ID to be reused.
         *
         * @param e The ID of the entity to kill.
         */
        void kill_entity(entity_t const& e);

        /**
         * @brief Registers a component type by creating a new sparse array for it.
         *
         * @tparam Component The type of the component to register.
         * @return SparseArray<Component>& Reference to the newly created sparse array for the component type.
         */
        template <class Component>
        SparseArray<Component>& register_component() {
            std::type_index index(typeid(Component));
            if (_components_arrays.find(index) == _components_arrays.end()) {
                _components_arrays[index] = SparseArray<Component>();
                _component_erasers[index] = [this](Registry&, entity_t const& e) {
                    this->get_components<Component>().erase(e);
                };
            }
            return std::any_cast<SparseArray<Component>&>(_components_arrays[index]);
        }

        /**
         * @brief Retrieves the sparse array of a specific component type.
         *
         * @tparam Component The type of the component.
         * @return SparseArray<Component>& Reference to the sparse array of the specified component type.
         */
        template <class Component>
        SparseArray<Component>& get_components() {
            return std::any_cast<SparseArray<Component>&>(_components_arrays.at(std::type_index(typeid(Component))));
        }

        /**
         * @brief Retrieves the constant sparse array of a specific component type.
         *
         * @tparam Component The type of the component.
         * @return const SparseArray<Component>& Constant reference to the sparse array of the specified component type.
         */
        template <class Component>
        const SparseArray<Component>& get_components() const {
            return std::any_cast<const SparseArray<Component>&>(_components_arrays.at(std::type_index(typeid(Component))));
        }

        /**
         * @brief Adds a new component to a specific entity.
         *
         * @tparam Component The type of the component.
         * @param to The entity to which the component will be added.
         * @param c The component to be added.
         * @return typename SparseArray<Component>::reference_type Reference to the newly added component.
         */
        template <typename Component>
        typename SparseArray<Component>::reference_type add_component(entity_t const& to, Component&& c) {
            return register_component<Component>().insert_at(to, std::forward<Component>(c));
        }

        /**
         * @brief Constructs and adds a new component in-place for a specific entity.
         *
         * @tparam Component The type of the component.
         * @tparam Params Variadic template parameters for the component constructor.
         * @param to The entity to which the component will be added.
         * @param p The parameters to forward to the component constructor.
         * @return typename SparseArray<Component>::reference_type Reference to the newly emplaced component.
         */
        template <typename Component, typename... Params>
        typename SparseArray<Component>::reference_type emplace_component(entity_t const& to, Params&&... p) {
            return register_component<Component>().emplace_at(to, std::forward<Params>(p)...);
        }

        /**
         * @brief Removes a component from a specific entity.
         *
         * @tparam Component The type of the component.
         * @param from The entity from which the component will be removed.
         */
        template <typename Component>
        void remove_component(entity_t const& from) {
            get_components<Component>().erase(from);
        }

        template <class... Components, typename Function>
        void add_system(Function && f) {
            _systems.emplace_back([this, f = std::forward<Function>(f)]() {
                f(*this, get_components<Components>()...);
            });
        }

        void run_systems() {
            for (auto& system : _systems) {
                system();
            }
        }

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::unordered_map<std::type_index, std::function<void(Registry&, entity_t const&)>> _component_erasers;
        std::vector<entity_t> _entities;
        std::queue<entity_t> _dead_entities;
        entity_t _next_entity_id = 0;
        std::vector<std::function<void()>> _systems;
};

#endif /* !REGISTRY_HPP_ */
