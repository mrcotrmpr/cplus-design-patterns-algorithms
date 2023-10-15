#include "presentation/commands/go_back_command.hpp"
#include "presentation/sdl_facade.hpp"
#include "managers/museum_manager.hpp"
#include "managers/artist_manager.hpp"
#include "presentation/game.hpp"
#include <iostream>

void GoBackCommand::execute(std::shared_ptr<Game> game, std::shared_ptr<MuseumManager> museumManager, std::shared_ptr<ArtistManager> artistManager) {
    game->atPresent = false;

    if (game->currentMementoIndex == -1) {
        game->currentMementoIndex = game->sdl->mementoManager->getMementosCount() - 1;
    }

    int currentMementoIndex = game->currentMementoIndex;
    if (currentMementoIndex > 0) {
        auto memento = game->sdl->mementoManager->getMemento(currentMementoIndex - 1);
        game->currentMementoIndex = currentMementoIndex - 1;
        std::cout << "Current index: " << game->currentMementoIndex << "/" << game->sdl->mementoManager->getMementosCount() - 1 << std::endl;
        game->restoreMemento(memento);
        game->sdl->render();
    }
    else {
        std::cout << "No more states to go back to." << std::endl;
    }
}