module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

export module SDLDeleter;

export namespace jod {
class SDLDeleter {
  public:
    void operator()(SDL_Window *window) const {
        SDL_DestroyWindow(window);
    }
    
    void operator()(SDL_Renderer *renderer) const {
        SDL_DestroyRenderer(renderer);
    }
    
    void operator()(SDL_Surface *surface) const {
        SDL_FreeSurface(surface);
    }
    
    void operator()(SDL_Texture *texture) const {
        SDL_DestroyTexture(texture);
    }
    
    void operator()(TTF_Font *font) const {
        TTF_CloseFont(font);
    }
};
}