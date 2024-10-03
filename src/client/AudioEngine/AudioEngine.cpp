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

void RType::AudioEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

extern "C" RType::AudioEngine *entryPointAudioEngine()
{
    return (new RType::AudioEngine());
}
