/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Freeze
*/

#ifndef FREEZE_HPP_
#define FREEZE_HPP_

namespace Component {
    class Freeze {
        public:
            Freeze();
            ~Freeze();

        protected:
            bool _isFrozen;
            bool _isFreezeDamaging;
        private:
    };
}

#endif /* !FREEZE_HPP_ */
