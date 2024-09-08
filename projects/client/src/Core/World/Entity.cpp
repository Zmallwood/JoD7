export module Entity;

import Size;
import Point;

export namespace jod {
class Entity {
  public:
    Entity(Size worldAreaSize) : m_worldAreaSize(worldAreaSize) {}
    
  protected:
    Point ConvertIndexToCoord(int index) {
        auto x = index % m_worldAreaSize.width;
        auto y = index / m_worldAreaSize.width;
        
        return {x, y};
    }
    
    int ConvertCoordToIndex(Point coord) {
        return coord.y * m_worldAreaSize.width + coord.x;
    }

    Size GetWorldAreaSize() {
        return m_worldAreaSize;
    }
    
  private:
    Size m_worldAreaSize;
};
}