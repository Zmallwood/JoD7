export module CameraPosition;

import std;
import CameraCore;
import Point;
import Size;
import Entity;
import Box;
import Tile;
import PlayerPosition;
import Textures;

export namespace jod {
class CameraPosition : public Entity {
  public:
    CameraPosition(
        Size worldAreaSize,
        std::vector<CameraPosition>& cameraPositions,
        std::vector<Tile>& tiles,
        std::vector<PlayerPosition>& playerPositions) : Entity(worldAreaSize),
        m_cameraPositions(cameraPositions),
        m_tiles(tiles),
        m_playerPositions(playerPositions) {}
    
    void Activate() {
        m_cameraCore = std::make_unique<CameraCore>();
        m_textures = std::make_shared<Textures>(m_cameraCore->GetRenderer());
    }
    
    void Look() {
        m_cameraCore->ClearCanvas();
        
        auto viewRange = 5;
        
        auto center = GetCoord();
        
        for (auto y = 0; y <= 2*viewRange; y++) {
            for (auto x = 0; x <= 2*viewRange; x++) {
                auto coord = Point {center.x - viewRange + x,
                                    center.y - viewRange + y};
                auto tile = GetTile(coord);
                auto area = Box {x*60, y*60, 60, 60};
                tile->Render(m_cameraCore->GetRenderer(), m_textures, area);
                auto playerPosition = GetPlayerPosition(coord);
                playerPosition->Render(m_cameraCore->GetRenderer(), m_textures, area);
            }
        }
        
        m_cameraCore->PresentCanvas();
    }
    
  private:    
    Point GetCoord() {
        auto index = this - m_cameraPositions.data();
        return ConvertIndexToCoord(index);
    }
    
    Tile* GetTile(Point coord) {
        return m_tiles.data() + ConvertCoordToIndex(coord);
    }
    
    PlayerPosition* GetPlayerPosition(Point coord) {
        return m_playerPositions.data() + ConvertCoordToIndex(coord);
    }
    
    std::unique_ptr<CameraCore> m_cameraCore;
    std::shared_ptr<Textures> m_textures;
    std::vector<CameraPosition>& m_cameraPositions;
    std::vector<Tile>& m_tiles;
    std::vector<PlayerPosition>& m_playerPositions;
};
}