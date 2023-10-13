#include "managers/museum_manager.hpp"
#include "domain/states/blue_state.hpp"
#include "domain/states/red_state.hpp"
#include "domain/states/yellow_state.hpp"
#include "domain/states/gray_state.hpp"

void MuseumManager::renderMuseum(SDL_Renderer* renderer, std::shared_ptr<Museum> museum, float scaleX, float scaleY) {
    std::unordered_map<char, std::shared_ptr<NodeType>> nodeTypeMap;
    for (auto type : museum->nodeTypes) {
        nodeTypeMap[type->tag] = type;
    }

    for (const auto& node : museum->nodes) {
        auto nodeTypeIt = nodeTypeMap.find(node->tag);

        if (nodeTypeIt != nodeTypeMap.end()) {
            SDL_SetRenderDrawColor(renderer, nodeTypeIt->second->red, nodeTypeIt->second->green, nodeTypeIt->second->blue, 255);
            if (node->tag == 'R') {
                node->state = std::make_unique<RedState>();
            }
            else if (node->tag == 'B') {
                node->state = std::make_unique<BlueState>();
            }
            else if (node->tag == 'Y') {
                node->state = std::make_unique<YellowState>();
            }
            else if (node->tag == 'G') {
                node->state = std::make_unique<GrayState>();
            }
        }
        else {
            SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
        }

        // Calculate the screen coordinates of the node
        SDL_Rect nodeRect;
        nodeRect.x = static_cast<int>(node->x * scaleX);
        nodeRect.y = static_cast<int>(node->y * scaleY);
        nodeRect.w = 14;
        nodeRect.h = 14;
        SDL_RenderFillRect(renderer, &nodeRect);

        // Draw edges
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (const auto& edge : node->edges) {
            SDL_RenderDrawLine(renderer,
                static_cast<int>(node->x * scaleX),
                static_cast<int>(node->y * scaleY),
                static_cast<int>(edge->x * scaleX),
                static_cast<int>(edge->y * scaleY)
            );
        }
    }
}
