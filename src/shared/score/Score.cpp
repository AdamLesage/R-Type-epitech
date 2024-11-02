/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** Score
*/

#include "Score.hpp"

Score::Score(const std::string& playerName, const std::string& configPath)
    : playerName(playerName), score(0), configPath(configPath)
{
}

bool Score::readScoreFromFile()
{
    try {
        cfg.readFile(configPath.c_str());
        return true;
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while reading file." << std::endl;
        return false;
    } catch (const libconfig::ParseException& parserError) {
        std::cerr << "Parse error at " << parserError.getFile() << ":"
            << parserError.getLine() << " - " << parserError.getError() << std::endl;
            return false;
    }
}

void Score::addPoints(int points)
{
    score += points;
}

void Score::updateScore()
{
    libconfig::Setting& root = cfg.getRoot();
    libconfig::Setting& lastScores = root["scores"];
    libconfig::Setting& highScores = root["highscore"];
    std::vector<std::pair<std::string, int>> lastTenScores;
    std::vector<std::pair<std::string, int>> bestScores;

    for (int i = 0; i < lastScores.getLength(); i += 1) {
        lastTenScores.emplace_back(lastScores[i]["name"], lastScores[i]["value"]);
    }

    lastTenScores.emplace_back(playerName, score);
    if (lastTenScores.size() > 10) {
        lastTenScores.erase(lastTenScores.begin());
    }

    for (size_t i = 0; i < lastTenScores.size(); i += 1) {
        lastScores.add("name", libconfig::Setting::TypeString) = lastTenScores[i].first;
        lastScores.add("value", libconfig::Setting::TypeString) = lastTenScores[i].second;
    }

    for (int i = 0; i < highScores.getLength(); i += 1) {
        bestScores.emplace_back(highScores[i]["name"], highScores[i]["value"]);
    }

    bestScores.emplace_back(playerName,score);
    std::sort(bestScores.begin(), bestScores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });
    bestScores.resize(3);

    for (size_t i = 0; i < bestScores.size(); i += 1) {
        highScores[i].add("name", libconfig::Setting::TypeString) = bestScores[i].first;
        highScores[i].add("value", libconfig::Setting::TypeInt) = bestScores[i].second;
    }
}

bool Score::writeScoresToFile()
{
    try {
        cfg.writeFile(configPath.c_str());
        std::cout << "Scores successfully written to:" << configPath << std::endl;
        return true;
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "Error while writing file: " << configPath << std::endl;
        return false;
    }
}

int Score::getScore()
{
    return score;
}
