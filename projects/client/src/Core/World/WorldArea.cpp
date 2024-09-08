module;

#include <stdlib.h>

export module WorldArea;

import std;
import Tile;
import Size;
import Point;
import CameraPosition;
import PlayerPosition;

export namespace jod {
class WorldArea {
  public:
    WorldArea(Size size)
        : m_size(size) {
        std::cout << "New world area\n";
        
        for (auto y = 0; y < m_size.height; y++) {
            for (auto x = 0; x < m_size.width; x++) {
                m_tiles.push_back(Tile(m_size, m_tiles));
                m_cameraPositions.push_back(
                    CameraPosition(
                        m_size,
                        m_cameraPositions, m_tiles, m_playerPositions));
                m_playerPositions.push_back(
                    PlayerPosition(
                        m_size,
                        m_playerPositions));
            }
        }
        std::cout << "m_cameraPositions.data(): " << m_cameraPositions.data() <<
            std::endl;
        GenerateContent();
    }
    
    CameraPosition* AddMainCamera(Point coord) {
        auto index = GetIndex(coord);
        m_cameraPositions[index].Activate();
        return &m_cameraPositions[index];
    }
    
    PlayerPosition* AddPlayer(Point coord) {
        auto index = GetIndex(coord);
        m_playerPositions[index].Activate();
        return &m_playerPositions[index];
    }
    
  private:
    void GenerateContent() {
        auto numLakes = 30;
        
        for (auto i = 0; i < numLakes; i++) {
            auto x = rand() % m_size.width;
            auto y = rand() % m_size.height;
            auto r = 3 + rand() % 6;
            auto tile = GetTile({x, y});
            tile->CreateLake(r);
        }
    }
    
    int GetIndex(Point coord) {
        return coord.y*m_size.width + coord.x;
    }
    
    Tile* GetTile(Point coord) {
        return m_tiles.data() + GetIndex(coord);
    }
    
    Size m_size;
    std::vector<Tile> m_tiles;
    std::vector<CameraPosition> m_cameraPositions;
    std::vector<PlayerPosition> m_playerPositions;
};
}