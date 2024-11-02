/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** ScoresParser
*/

#include "ScoresParser.hpp"
#include <iostream>
#include <algorithm>

using namespace RType;

ScoresParser::ScoresParser() {
    this->_filepath = std::string("config") + PATH_SEPARATOR + "scores.cfg";
    loadConfig();
}

std::map<std::string, size_t> ScoresParser::getLatestScores() {
    std::map<std::string, size_t> scores;
    try {
        const libconfig::Setting& root = _cfg.getRoot();
        const libconfig::Setting& scoresSetting = root["scores"];

        for (int i = 0; i < scoresSetting.getLength(); ++i) {
            std::string name = scoresSetting[i]["name"];
            int value = scoresSetting[i]["value"];
            scores[name] = value;
        }
    } catch (const libconfig::SettingNotFoundException& e) {
        std::cerr << "Scores setting not found: " << e.what() << '\n';
    }
    return scores;
}

std::map<std::string, size_t> ScoresParser::getHighscores() {
    std::map<std::string, size_t> highscores;
    try {
        const libconfig::Setting& root = _cfg.getRoot();
        const libconfig::Setting& highscoresSetting = root["highscores"];

        for (int i = 0; i < highscoresSetting.getLength(); ++i) {
            std::string name = highscoresSetting[i]["name"];
            int value = highscoresSetting[i]["value"];
            highscores[name] = value;
        }
    } catch (const libconfig::SettingNotFoundException& e) {
        std::cerr << "Highscores setting not found: " << e.what() << '\n';
    }
    return highscores;
}

void ScoresParser::saveScore(const std::string& playerName, size_t score) {
    std::map<std::string, size_t> latestScores = getLatestScores();

    latestScores.insert(latestScores.begin(), {playerName, score});
    if (latestScores.size() > 10) latestScores.erase(--latestScores.end());

    libconfig::Setting& root = _cfg.getRoot();

    if (root.exists("scores")) {
        root.remove("scores");
    }
    libconfig::Setting& scoresSetting = root.add("scores", libconfig::Setting::TypeList);
    for (const auto& [name, value] : latestScores) {
        libconfig::Setting& scoreSetting = scoresSetting.add(libconfig::Setting::TypeGroup);
        scoreSetting.add("name", libconfig::Setting::TypeString) = name;
        scoreSetting.add("value", libconfig::Setting::TypeInt) = static_cast<int>(value);
    }

    updateHighscores(playerName, score);
    writeConfig();
}

void ScoresParser::updateHighscores(const std::string& playerName, size_t score) {
    std::map<std::string, size_t> highscores = getHighscores();

    highscores[playerName] = score;

    std::vector<std::pair<std::string, size_t>> sortedHighscores(highscores.begin(), highscores.end());
    std::sort(sortedHighscores.begin(), sortedHighscores.end(),
              [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    if (sortedHighscores.size() > 3) {
        sortedHighscores.resize(3);
    }

    libconfig::Setting& root = _cfg.getRoot();
    if (root.exists("highscores")) {
        root.remove("highscores");
    }
    libconfig::Setting& highscoresSetting = root.add("highscores", libconfig::Setting::TypeList);
    for (const auto& [name, value] : sortedHighscores) {
        libconfig::Setting& highscoreSetting = highscoresSetting.add(libconfig::Setting::TypeGroup);
        highscoreSetting.add("name", libconfig::Setting::TypeString) = name;
        highscoreSetting.add("value", libconfig::Setting::TypeInt) = static_cast<int>(value);
    }
}

void ScoresParser::loadConfig() {
    try {
        _cfg.readFile(_filepath.c_str());
    } catch (const libconfig::FileIOException& e) {
        std::cerr << "Error reading file: " << _filepath << '\n';
    } catch (const libconfig::ParseException& e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine()
                  << " - " << e.getError() << '\n';
    }
}

void ScoresParser::writeConfig() {
    try {
        _cfg.writeFile(_filepath.c_str());
    } catch (const libconfig::FileIOException& e) {
        std::cerr << "Error writing to file: " << _filepath << '\n';
    }
}
