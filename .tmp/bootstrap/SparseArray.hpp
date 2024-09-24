/*
** EPITECH PROJECT, 2024
** B-CPP-500-NAN-5-1-bsrtype-romain.chevallier
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <vector>
#include <optional>

template <typename Component>

class SparseArray {
    public :
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<std::optional<Component>>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;
        SparseArray() {} // You can add more constructors .
        SparseArray(SparseArray const &other) {*this = other;} // copy constructor
        SparseArray(SparseArray &&other) noexcept {this->_data = std::move(other._data);} // move constructor
        ~SparseArray() {};
        SparseArray & operator =(SparseArray const &) {
            return *this;
        } // copy assignment operator
        SparseArray & operator =(SparseArray &&) noexcept {
            return *this;
        } // move assignment operator
        reference_type operator [](std::size_t idx) {
            return this->_data[idx];
        }
        const_reference_type operator [](std::size_t idx) const {
            return this->_data[idx];
        }
        iterator begin () {
            return this->_data.begin();
        }
        const_iterator begin () const {
            return this->_data.begin();
        }
        const_iterator cbegin () const {
            return this->_data.cbegin();
        }
        iterator end() {
            return this->_data.end();
        }
        const_iterator end() const {
            return this->_data.end();
        }
        const_iterator cend() const {
            return this->_data.cend();
        }
        size_type size() const {
            return this->_data.size();
        }
        reference_type insert_at(size_type pos, Component const &other) {
            if (pos > this->_data.size()) {
                this->_data.resize(pos + 1);
            }
            this->_data[pos] = other;
            return this->_data[pos];
        }
        reference_type insert_at( size_type pos, Component &&other) {
            if (pos + 1 > this->_data.size()) {
                this->_data.resize(pos + 1);
            }
            this->_data[pos] = other;
            return this->_data[pos];
        }
        template <class ...Params>
        reference_type emplace_at(size_type pos, Params &&...params) {
            if (pos > this->_data.size()) {
                this->_data.resize(pos + 1);
            }
            this->_data = Component(std::forward<Params>(params)...);
            return this->_data[pos];
        } // optional
        void erase(size_type pos) {
            this->_data.erase(this->begin() + pos);
        }
        size_type get_index(value_type const &value) const {
            for (std::size_t i = 0; i != _data.size(); i++) {
                if (_data[i] == value) {
                    return (i);
                }
            }
            return 0;
        }
    private:
        container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
