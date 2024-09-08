module;

#include <SDL2/SDL.h>

export module Tile;

import std;
import Entity;
import Box;
import Point;
import Size;
import Textures;

export namespace jod {
class Tile : public Entity {
  public:
    Tile(Size worldAreaSize,
         std::vector<Tile>& tiles) : Entity(worldAreaSize),
        m_tiles(tiles) {}
    
    void Render(std::shared_ptr<SDL_Renderer> renderer,
                std::shared_ptr<Textures> textures, Box area) {
        auto rect = SDL_Rect {area.x, area.y, area.width, area.height};
        
        switch (m_ground) {
        case 0: {
            auto imgGrass = textures->GetTexture("GroundGrass");
            SDL_RenderCopy(renderer.get(), imgGrass.get(), nullptr, &rect);
            break;
        }
        case 1: {
            auto imgGrass = textures->GetTexture("GroundWater");
            SDL_RenderCopy(renderer.get(), imgGrass.get(), nullptr, &rect);
            break;
        }
        }
    }
    
    void CreateLake(int r) {
        auto coord = GetCoord();
        auto worldAreaSize = GetWorldAreaSize();
        
        for (auto y = coord.y - r; y <= coord.y + r; y++) {
            for (auto x = coord.x - r; x <= coord.x + r; x++) {
                if (x < 0 || y < 0 || x >= worldAreaSize.width ||
                    y >= worldAreaSize.height)
                    continue;
                
                auto dx = x - coord.x;
                auto dy = y - coord.y;
                if (dx*dx + dy*dy <= r*r) {
                    auto tile = GetTile({x,y});
                    tile->SetGround(1);
                }
            }
        }
    }
    
    void SetGround(int value) {
        m_ground = value;
    }
    
  private:
    Point GetCoord() {
        auto index = this - m_tiles.data();
        return ConvertIndexToCoord(index);
    }
    
    Tile* GetTile(Point coord) {
        return m_tiles.data() + ConvertCoordToIndex(coord);
    }
    
    int m_ground {0};
    std::vector<Tile>& m_tiles;
};
}