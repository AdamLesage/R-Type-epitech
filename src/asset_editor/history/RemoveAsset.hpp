/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RemoveAsset
*/

#ifndef REMOVEASSET_HPP_
#define REMOVEASSET_HPP_

#include "ICommand.hpp"
#include "Asset.hpp"

#include <vector>

namespace Edition {

    /**
     * @brief Remove Asset Command
     * 
     * This class will be used to remove an asset from the scene
     */
    class RemoveAsset : public ICommand {
        public:
            /**
             * @brief Construct a new Remove Asset object
             * 
             * @param assets The assets of the scene
             */
            RemoveAsset(std::vector<std::shared_ptr<Asset>>& assets);

            /**
             * @brief Destroy the Remove Asset object
             */
            ~RemoveAsset();

            /**
             * @brief Execute the command
             * 
             * This will store the asset to remove and then remove it asset vector
             */
            void execute() override;

            /**
             * @brief Undo the command
             * 
             * This will add the asset to the scene
             */
            void undo() override;

            /**
             * @brief Get the asset
             * 
             * @return std::shared_ptr<Asset> The asset
             */
            std::shared_ptr<Asset> getAsset() override { return _asset; }

        protected:
        private:
            /**
             * @brief The assets of the scene
             */
            std::vector<std::shared_ptr<Asset>> _assets;

            /**
             * @brief The asset to add or remove
             */
            std::shared_ptr<Asset> _asset;
    };
}

#endif /* !REMOVEASSET_HPP_ */
