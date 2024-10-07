/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    _menu = std::make_unique<Menu>(window);
    try {
        games = std::make_shared<Game>(window);
        settings = std::make_shared<Settings>(window);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    // _renderMediator = std::make_unique<RenderMediator>(_menu, std::shared_ptr<RenderingEngine>(this));
}

RType::RenderingEngine::~RenderingEngine()
{
}

void RType::RenderingEngine::run()
{
    window->setFramerateLimit(360);
    window->clear();
    while (window->isOpen()) {
        int scene = _menu->displayMenu();
        if (scene == 1) {
            games->displayGame();
        } else if (scene == 2) {
            settings->displaySettings();
        } else if (scene == 3) {
            window->close();
        }
        window->display();
    }
}

void RType::RenderingEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

extern "C" RType::RenderingEngine *entryPointRenderingEngine()
{
    return (new RType::RenderingEngine());
}
