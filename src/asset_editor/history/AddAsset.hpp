/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AddAsset
*/

#ifndef ADDASSET_HPP_
#define ADDASSET_HPP_

#include "ICommand.hpp"
#include "Asset.hpp"

#include <vector>

namespace Edition {

    /**
     * @brief Add Asset Command
     *
     * This command will be used to add an asset to the scene
     */
    class AddAsset : public ICommand {
        public:
            /**
             * @brief Construct a new Add Asset object
             *
             * @param assets The assets of the scene
             * @param asset The asset to add
             */
            AddAsset(std::vector<std::shared_ptr<Edition::Asset>> assets, std::shared_ptr<Asset> asset);

            /**
             * @brief Destroy the Add Asset object
             */
            ~AddAsset();

            /**
             * @brief Execute the command
             *
             * This will add the asset to the scene
             */
            void execute() override;

            /**
             * @brief Undo the command
             *
             * This will remove the asset from the scene
             */
            void undo() override;

            /**
             * @brief Redo the command
             */
            void redo() override;

            /**
             * @brief Get the asset
             *
             * @return std::shared_ptr<Asset> The asset
             */
            std::shared_ptr<Asset> getAsset() override {
                return _asset;
            }

        protected:
        private:
            /**
             * @brief The assets of the scene
             */
            std::vector<std::shared_ptr<Asset>> _assets;

            /**
             * @brief The asset to add
             */
            std::shared_ptr<Asset> _asset;
    };
} // namespace Edition

#endif /* !ADDASSET_HPP_ */
