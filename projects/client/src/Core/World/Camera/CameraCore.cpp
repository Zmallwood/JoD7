module;

#include <SDL2/SDL.h>

export module CameraCore;

import std;
import SDLDeleter;

export namespace jod {
class CameraCore {
  public:
    CameraCore() {
        
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
            return;
        }
        
        m_window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(
                "Hello World SDL",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                660,
                660,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED),
            SDLDeleter());
        
        m_renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED),
            SDLDeleter());
    }
    
    void ClearCanvas() {
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 150, 255, 255);
        
        SDL_RenderClear(m_renderer.get());
    }
    
    void PresentCanvas() {
        SDL_RenderPresent(m_renderer.get());
    }
    
    std::shared_ptr<SDL_Renderer> GetRenderer() {
        return m_renderer;
    }
    
  private:
    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
};
}