module;

#include <SDL2/SDL.h>

export module GameRunner;

import CameraPosition;
import PlayerPosition;
import Directions;

export namespace jod {
class GameRunner {
  public:
    GameRunner(CameraPosition* camera,
               PlayerPosition* player)
        : m_camera(camera), m_player(player) {}
    
    void Start() {
        while (m_running) {
            ProcessEvents();
            
            m_camera->Look();
        }
    }
    
  private:
    void ProcessEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                m_player = m_player->Move(Directions::North);
                break;
                case SDLK_RIGHT:
                m_player = m_player->Move(Directions::East);
                break;
                case SDLK_DOWN:
                m_player = m_player->Move(Directions::South);
                break;
                case SDLK_LEFT:
                m_player = m_player->Move(Directions::West);
                break;
            }
            break;
            }
        }
    }
    
    bool m_running {true};
    CameraPosition* m_camera;
    PlayerPosition* m_player;
};
}