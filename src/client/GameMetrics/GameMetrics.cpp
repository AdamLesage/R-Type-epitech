/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** GameMetrics
*/

#include "GameMetrics.hpp"
#include <iostream>

GameMetrics::GameMetrics()
{
}

GameMetrics::~GameMetrics()
{
}

void GameMetrics::displayFPS(sf::RenderWindow& window)
{
    static sf::Clock clock;
    static int frameCnt = 0;
    static int fps = 0;
    sf::Text text;
    static sf::Font font;

    frameCnt += 1;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }
    if (clock.getElapsedTime().asSeconds() >= 1.0f) {
        fps = frameCnt / clock.getElapsedTime().asSeconds();
        frameCnt = 0;
        clock.restart();
    }
    text.setFont(font);
    text.setString("FPS: " + std::to_string(fps));
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    window.draw(text);
}

void GameMetrics::displayMemory(sf::RenderWindow& window)
{
    sf::Text text;
    static sf::Font font;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    text.setFont(font);

    std::size_t memoryUsed = this->getMemoryUsage();

    text.setString("Memory used: " + std::to_string(memoryUsed) + " MB");

    text.setFillColor(sf::Color::White);
    text.setPosition(0, 20);
    window.draw(text);
}

std::size_t GameMetrics::getMemoryUsage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        return memCounter.WorkingSetSize / (1024 * 1024);
    }
#elif __linux__
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss / 1024;
    }
#endif
    return 0;
}

GameMetrics::GpuInfo getGpuInfo() {
    GameMetrics::GpuInfo gpuInfo = {"Unknown", 0, 0, 0.0f};

#ifdef _WIN32
    // Under Windows, NVIDIA API is not available on chocolatey
#elif __linux__
    FILE* fp = popen("nvidia-smi --query-gpu=temperature.gpu,memory.used,memory.total,name --format=csv,noheader,nounits", "r");
    if (fp) {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), fp)) {
            std::sscanf(buffer, "%f,%zu,%zu,%127[^\n]", &gpuInfo.temperature, &gpuInfo.vramUsed, &gpuInfo.vramTotal, buffer);
            gpuInfo.model = std::string(buffer);
        }
        pclose(fp);
    } else {
        return gpuInfo;
    }
#endif
    return gpuInfo;
}

void GameMetrics::displayGpuUsage(sf::RenderWindow& window) {
    sf::Text text;
    static sf::Font font;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    text.setFont(font);

#ifdef _WIN32
    text.setString("GPU information is not available on Windows.");
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 100);
    window.draw(text);

#elif __linux__
    GpuInfo gpuInfo = getGpuInfo();

    std::string gpuText = "GPU Model: " + gpuInfo.model + "\n"
                        + "VRAM Used: " + std::to_string(gpuInfo.vramUsed) + " MB\n"
                        + "GPU Temp: " + std::to_string(gpuInfo.temperature) + " C";

    text.setString(gpuText);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 100);
    window.draw(text);
#endif
}