/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** ScoresParser
*/

#ifndef RTYPE_SCORESPARSER_HPP
#define RTYPE_SCORESPARSER_HPP

    #include <string>
    #include <map>
    #include <libconfig.h++>
    #include <vector>

    #if defined(_WIN32) || defined(_WIN64)
        #define PATH_SEPARATOR "\\"
    #else
        #define PATH_SEPARATOR "/"
    #endif

namespace RType {
    class ScoresParser {
        public:
            /**
             * @brief Constructor that initializes the configuration file path.
             * @param filepath The path to the configuration file.
             * @author BxptisteM
             */
            ScoresParser();

            /**
             * @brief Retrieves the latest 10 scores from the config file.
             * @return A map of player names and their scores.
             * @author BxptisteM
             */
            std::map<std::string, size_t> getLatestScores();

            /**
             * @brief Retrieves the top 3 highscores from the config file.
             * @return A map of player names and their highscores.
             * @author BxptisteM
             */
            std::map<std::string, size_t> getHighscores();

            /**
             * @brief Saves a new score to the configuration file.
             * Updates the 10 latest scores and the highscores if applicable.
             * @param playerName The name of the player.
             * @param score The score to save.
             * @author BxptisteM
             */
            void saveScore(const std::string& playerName, size_t score);

        private:
            std::string _filepath; // The path to the configuration file.
            libconfig::Config _cfg; // The configuration object.

            /**
             * @brief Loads the configuration file.
             * @author BxptisteM
             */
            void loadConfig();

            /**
             * @brief Writes the updated configuration to the file.
             * @author BxptisteM
             */
            void writeConfig();

            /**
             * @brief Updates the highscores list if the new score qualifies.
             * @param playerName The name of the player.
             * @param score The new score to evaluate.
             * @author BxptisteM
             */
            void updateHighscores(const std::string& playerName, size_t score);
    };
} // namespace RType

#endif // RTYPE_SCORESPARSER_HPP
