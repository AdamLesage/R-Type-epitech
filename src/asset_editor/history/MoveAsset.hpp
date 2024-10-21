/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** MoveAsset
*/

#ifndef MOVEASSET_HPP_
#define MOVEASSET_HPP_

#include "ICommand.hpp"
#include "Asset.hpp"

#include <vector>

namespace Edition {

    /**
     * @brief Move Asset Command
     * 
     * This command will be used to move an asset in the scene
     */
    class MoveAsset : public ICommand {
        public:
            /**
             * @brief Construct a new Move Asset object
             * 
             * @param asset The asset to move
             * @param dx The x offset
             * @param dy The y offset
             */
            MoveAsset(std::shared_ptr<Asset> asset, int dx, int dy);

            /**
             * @brief Destroy the Move Asset object
             */
            ~MoveAsset();

            /**
             * @brief Execute the command
             * 
             * This will move the asset
             */
            void execute() override;

            /**
             * @brief Undo the command
             * 
             * This will move the asset back
             */
            void undo() override;

        protected:
        private:
            /**
             * @brief The asset to move
             */
            std::shared_ptr<Asset> _asset;

            /**
             * @brief The x offset
             */
            int _dx;

            /**
             * @brief The y offset
             */
            int _dy;
    };
}

#endif /* !MOVEASSET_HPP_ */
