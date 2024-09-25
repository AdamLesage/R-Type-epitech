/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"

RType::AudioEngine::AudioEngine()
{
}

RType::AudioEngine::~AudioEngine()
{
}

void RType::AudioEngine::run()
{
    std::cout << "AudioEngine is running" << std::endl;
}

extern "C" RType::AudioEngine *entryPointAudioEngine()
{
    return (new RType::AudioEngine());
}
