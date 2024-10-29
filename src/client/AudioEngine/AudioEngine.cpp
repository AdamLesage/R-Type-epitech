/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"

RType::AudioEngine::AudioEngine() {
    std::string soundPath =
        std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "game_launch.ogg";
    if (!game_launch_sound.loadFromFile(soundPath)) {
        throw std::runtime_error("Error loading game launch sound");
    }
    game_launch_music.setBuffer(game_launch_sound);
    std::string shootPath =
        std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "shootsounds.wav";
    if (!shoot_sound.loadFromFile(shootPath)) {
        throw std::runtime_error("Error loading shoot sound");
    }
    shoot_music.setBuffer(shoot_sound);
    std::string shootPath2 = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "Piou.wav";
    if (!shoot_sound2.loadFromFile(shootPath2)) {
        throw std::runtime_error("Error loading shoot sound 2");
    }
    shoot_music2.setBuffer(shoot_sound2);
    std::string lobbyogg = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "lobby.wav";
    if (!backgroundBuffer.loadFromFile(lobbyogg)) {
        throw std::runtime_error("Error loading background music");
    }
    backgroundMusic2.setBuffer(backgroundBuffer);
    std::string select = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "selectsound.wav";
    if (!selectBuffer.loadFromFile(select)) {
        throw std::runtime_error("Error loading select sound");
    }
    selectSound.setBuffer(selectBuffer);
    soundPath = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "menu.ogg";
    if (!backgroundBuffer2.loadFromFile(soundPath)) {
        throw std::runtime_error("Error loading select sound");
    }
    backgroundMusic.setBuffer(backgroundBuffer2);
}

RType::AudioEngine::~AudioEngine() {
}

void RType::AudioEngine::run() {
}

void RType::AudioEngine::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
}

extern "C" RType::AudioEngine* entryPointAudioEngine() {
    return (new RType::AudioEngine());
}

void RType::AudioEngine::ShootSound() {
    int random = rand() % 10;
    if (random == 9) {
        shoot_music2.setVolume(200);
        shoot_music2.play();
    } else {
        shoot_music2.play();
    }
}

void RType::AudioEngine::launch_music_play() {
    game_launch_music.play();
}

void RType::AudioEngine::launch_music_stop() {
    game_launch_music.stop();
}

void RType::AudioEngine::selectSoundPlay() {
    selectSound.play();
}

void RType::AudioEngine::adjustVolume(bool increase) {
    float currentVolume = backgroundMusic.getVolume();
    if (increase) {
        currentVolume = std::min(100.0f, currentVolume + 10.0f);
    } else {
        currentVolume = std::max(0.0f, currentVolume - 10.0f);
    }
    backgroundMusic.setVolume(currentVolume);
}

void RType::AudioEngine::BackgroundMusicGetVolume() {
    float value = backgroundMusic.getVolume();
    _mediator->notify("AudioEngine", "volume =" + std::to_string(value));
}

void RType::AudioEngine::backgroundMusicPlay() {
    backgroundMusic.play();
    backgroundMusic.setLoop(true);
}

void RType::AudioEngine::backgroundMusicStop() {
    backgroundMusic.stop();
}

void RType::AudioEngine::adjustVolume2(bool increase) {
    float currentVolume = backgroundMusic2.getVolume();
    if (increase) {
        currentVolume = std::min(100.0f, currentVolume + 10.0f);
    } else {
        currentVolume = std::max(0.0f, currentVolume - 10.0f);
    }
    backgroundMusic2.setVolume(currentVolume);
}

void RType::AudioEngine::BackgroundMusicGetVolume2() {
    float value = backgroundMusic2.getVolume();
    _mediator->notify("AudioEngine", "volume =" + std::to_string(value));
}

void RType::AudioEngine::backgroundMusicPlay2() {
    backgroundMusic2.play();
    backgroundMusic2.setLoop(true);
}

void RType::AudioEngine::backgroundMusicStop2() {
    backgroundMusic2.stop();
}
