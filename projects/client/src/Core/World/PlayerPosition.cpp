module;

#include <SDL2/SDL.h>

export module PlayerPosition;

import std;
import Entity;
import Box;
import Directions;
import Size;
import Point;
import Textures;

export namespace jod {
class PlayerPosition : public Entity {
  public:
    PlayerPosition(
        Size worldAreaSize,
        std::vector<PlayerPosition>& playerPositions) : Entity(worldAreaSize),
        m_playerPositions(playerPositions) {}
    
    void Activate() {
        m_active = true;
    }
    
    void Deactivate() {
        m_active = false;
    }
    
    void Render(std::shared_ptr<SDL_Renderer> renderer,
                std::shared_ptr<Textures> textures, Box area) {
        if (!m_active)
            return;
        
        auto rect = SDL_Rect {area.x, area.y, area.width, area.height};
        
        auto imgPlayer = textures->GetTexture("Player");
        SDL_RenderCopy(renderer.get(), imgPlayer.get(), nullptr, &rect);
    }
    
    
    PlayerPosition* Move(Directions direction) {
        auto coord = GetCoord();
        Point newCoord;
        switch (direction) {
        case Directions::North:
            newCoord = coord.Translate(0, -1);
            break;
        case Directions::East:
            newCoord = coord.Translate(1, 0);
            break;
        case Directions::South:
            newCoord = coord.Translate(0, 1);
            break;
        case Directions::West:
            newCoord = coord.Translate(-1, 0);
            break;
        }
        auto newPos = GetPlayerPosition(newCoord);
        auto index = this - m_playerPositions.data();
        auto newIndex = newPos - m_playerPositions.data();
        m_playerPositions[newIndex].Activate();
        m_playerPositions[index].Deactivate();
        return &m_playerPositions[newIndex];
    }
    
  private:
    Point GetCoord() {
        auto index = this - m_playerPositions.data();
        return ConvertIndexToCoord(index);
    }
    
    PlayerPosition* GetPlayerPosition(Point coord) {
        return m_playerPositions.data() + ConvertCoordToIndex(coord);
    }
    
    bool m_active {false};
    std::vector<PlayerPosition>& m_playerPositions;
};
}