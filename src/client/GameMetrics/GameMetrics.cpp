/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** GameMetrics
*/

#include "GameMetrics.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

GameMetrics::GameMetrics()
{
#ifdef _WIN32
    if (PdhOpenQuery(NULL, NULL, &cpuQuery) != ERROR_SUCCESS) {
        std::cerr << "Failed to open PDH query." << std::endl;
    }
    
    if (PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal) != ERROR_SUCCESS) {
        std::cerr << "Failed to add PDH counter." << std::endl;
    }

    if (PdhCollectQueryData(cpuQuery) != ERROR_SUCCESS) {
        std::cerr << "Failed to collect PDH query data." << std::endl;
    }
#endif
}

GameMetrics::~GameMetrics()
{
#ifdef _WIN32
    PdhCloseQuery(cpuQuery);
#endif
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
    text.setPosition(0, 60);
    window.draw(text);

#elif __linux__
    GpuInfo gpuInfo = getGpuInfo();

    std::string gpuText = "GPU Model: " + gpuInfo.model + "\n"
                        + "VRAM Used: " + std::to_string(gpuInfo.vramUsed) + " MB\n"
                        + "GPU Temp: " + std::to_string(gpuInfo.temperature) + " C";

    text.setString(gpuText);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 60);
    window.draw(text);
#endif
}

void GameMetrics::displayCPU(sf::RenderWindow& window)
{
    sf::Text text;
    static sf::Font font;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    text.setFont(font);

#ifdef _WIN32
    PDH_FMT_COUNTERVALUE counterVal;

    if (PdhCollectQueryData(cpuQuery) == ERROR_SUCCESS) {
        if (PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal) == ERROR_SUCCESS) {
             std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << counterVal.doubleValue;
            std::string cpuUsage = "CPU Usage: " + ss.str() + " %";
            text.setString(cpuUSage);
        }
    } else {
        text.setString("Failed to retrieve CPU usage.");
    }

#elif __linux__
    FILE* fp = fopen("/proc/stat", "r");
    if (fp) {
        long user, nice, system, idle;
        fscanf(fp, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);
        fclose(fp);

        static long prevUser = 0, prevNice = 0, prevSystem = 0, prevIdle = 0;
        long deltaUser = user - prevUser;
        long deltaNice = nice - prevNice;
        long deltaSystem = system - prevSystem;
        long deltaIdle = idle - prevIdle;
        long total = deltaUser + deltaNice + deltaSystem + deltaIdle;
        float cpuUsage = 100.0f * (deltaUser + deltaNice + deltaSystem) / total;
        prevUser = user;
        prevNice = nice;
        prevSystem = system;
        prevIdle = idle;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << cpuUsage;
        std::string cpuText = "CPU Usage: " + ss.str() + " %";
        text.setString(cpuText);
    } else {
        text.setString("Failed to retrieve CPU usage.");
    }
#endif

    text.setFillColor(sf::Color::White);
    text.setPosition(0, 40);
    window.draw(text);
}

void GameMetrics::displayLatency(sf::RenderWindow& window, float& latency)
{
    sf::Text text;
    static sf::Font font;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    text.setFont(font);

    text.setString("Latency: " + std::to_string(latency) + " ms");
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 130);
    window.draw(text);
}

void GameMetrics::displayPlayerPosition(sf::RenderWindow& window, sf::Vector2f pos)
{
    sf::Text text;
    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    text.setFont(font);
    text.setString("Player Position: (" +
        std::to_string(static_cast<int>(pos.x)) + ", " +
        std::to_string(static_cast<int>(pos.y)) + ")");
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 150);
    window.draw(text);
}
