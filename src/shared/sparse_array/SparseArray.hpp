/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <vector>
#include <optional>

template <typename Component> class SparseArray {
    public:
        /**
         * @typedef value_type
         * @brief Alias for the optional component type.
         */
        using value_type = std::optional<Component>;

        /**
         * @typedef reference_type
         * @brief Alias for a reference to the component type.
         */
        using reference_type = value_type&;

        /**
         * @typedef const_reference_type
         * @brief Alias for a constant reference to the component type.
         */
        using const_reference_type = const value_type&;

        /**
         * @typedef container_t
         * @brief Alias for the underlying container type, a constant reference to std::vector.
         */
        using container_t = std::vector<value_type>;

        /**
         * @typedef size_type
         * @brief Alias for the size type of the container.
         */
        using size_type = typename container_t::size_type;

        /**
         * @typedef iterator
         * @brief Alias for the iterator type of the container.
         */
        using iterator = typename container_t::iterator;

        /**
         * @typedef const_iterator
         * @brief Alias for the constant iterator type of the container.
         */
        using const_iterator = typename container_t::const_iterator;

    public:
        /**
         * @brief Default constructor for SparseArray.
         */
        SparseArray() = default;

        /**
         * @brief Copy constructor for SparseArray.
         *
         * @param other The SparseArray instance to copy from.
         */
        SparseArray(SparseArray const& other) {
            _data = other._data;
        }

        /**
         * @brief Move constructor for SparseArray.
         *
         * @param other The SparseArray instance to move from.
         */
        SparseArray(SparseArray&& other) noexcept {
            _data = std::move(other._data);
        }

        /**
         * @brief Destructor for SparseArray.
         */
        ~SparseArray() {
        }

        /**
         * @brief Copy assignment operator.
         *
         * @param other The SparseArray instance to copy from.
         * @return Reference to the current object.
         */
        SparseArray& operator=(SparseArray const& other) {
            _data = other._data;
            return *this;
        }

        /**
         * @brief Move assignment operator.
         *
         * @param other The SparseArray instance to move from.
         * @return Reference to the current object.
         */
        SparseArray& operator=(SparseArray&& other) noexcept {
            _data = std::move(other._data);
            return *this;
        }

        /**
         * @brief Access operator for modifying an element.
         *
         * @param index The index of the element to access.
         * @return Reference to the element at the specified index.
         */
        reference_type operator[](size_t index) {
            return _data[index];
        }

        /**
         * @brief Access operator for reading an element.
         *
         * @param index The index of the element to access.
         * @return Constant reference to the element at the specified index.
         */
        const_reference_type operator[](size_t index) const {
            return _data[index];
        }

        /**
         * @brief Returns an iterator to the beginning of the array.
         * @return An iterator to the beginning.
         */
        iterator begin() {
            return _data.begin();
        }

        /**
         * @brief Returns a constant iterator to the beginning of the array.
         * @return A constant iterator to the beginning.
         */
        const_iterator begin() const {
            return _data.begin();
        }

        /**
         * @brief Returns a constant iterator to the beginning of the array.
         * @return A constant iterator to the beginning.
         */
        const_iterator cbegin() const {
            return _data.cbegin();
        }

        /**
         * @brief Returns an iterator to the end of the array.
         * @return An iterator to the end.
         */
        iterator end() {
            return _data.end();
        }

        /**
         * @brief Returns a constant iterator to the end of the array.
         * @return A constant iterator to the end.
         */
        const_iterator end() const {
            return _data.end();
        }

        /**
         * @brief Returns a constant iterator to the end of the array.
         * @return A constant iterator to the end.
         */
        const_iterator cend() const {
            return _data.cend();
        }

        /**
         * @brief Returns the size of the sparse array.
         * @return The size of the array.
         */
        size_type size() const {
            return _data.size();
        }

        /**
         * @brief Inserts a component at the specified position.
         *
         * @param pos The position to insert the component at.
         * @param component The component to insert.
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, Component const& component) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(component);
            return _data[pos];
        }

        /**
         * @brief Inserts a component at the specified position using move semantics.
         *
         * @param pos The position to insert the component at.
         * @param component The component to insert.
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, Component&& component) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(component);
            return _data[pos];
        }

        /**
         * @brief Constructs a component in-place at the specified position.
         *
         * @tparam Params Parameter pack for the constructor of the component.
         * @param pos The position to emplace the component at.
         * @param params Parameters for constructing the component.
         * @return Reference to the emplaced component.
         */
        template <class... Params> reference_type emplace_at(size_type pos, Params&&... params) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = Component(std::forward<Params>(params)...);
            return _data[pos];
        }

        /**
         * @brief Erases the component at the specified position.
         *
         * @param pos The position of the component to erase.
         */
        void erase(size_type pos) {
            if (pos < _data.size()) {
                _data[pos].reset();
            }
        }

        /**
         * @brief Retrieves the index of a specific component.
         *
         * @param component The component to search for.
         * @return The index of the component.
         */
        size_type getIndex(value_type const& component) const {
            for (size_type i = 0; i < _data.size(); i++) {
                if (_data[i] == component) {
                    return i;
                }
            }
            return -1;
        }

    private:
        container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
