/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

    #include <libconfig.h++>
    #include <string>
    #include <iostream>
    #include <vector>
    #include <algorithm>

class Score {
    public:
        /**
         * @brief Default constructor.
         */
        Score() = default;

        /**
         * @brief Default constructor.
         */
        Score(const std::string& playerName, const std::string& configPath);

        /**
         * @brief Default destructors.
         */
        ~Score() = default;

        /**
         * @brief Add points to the score.
         * 
         * @param points number of points to add.
         */
        void addPoints(int points);

        /**
         * @brief Read score informations from the score config file.
         * 
         * @return boolean
         */
        bool readScoreFromFile();

        /**
         * @brief Update scores.
         */
        void updateScore();

        /**
         * @brief Write score informations updated into score config file.
         * 
         * @return boolean
         */
        bool writeScoresToFile();

        /**
         * @brief Get score value.
         * 
         * @return score
         */
        int getScore();
    private:
        libconfig::Config cfg;
        std::string playerName;
        int score;
        std::string configPath;
};

#endif /* !SCORE_HPP_ */
