module;

#include <SDL2/SDL_image.h>

export module Textures;

import std;
import SDLDeleter;
import Hash;
import FileUtilities;

export namespace jod {
class Textures {
  public:
    Textures(std::shared_ptr<SDL_Renderer> renderer) {
        
        using iterator = std::filesystem::recursive_directory_iterator;
        
        auto allImagesPath = (std::string(SDL_GetBasePath()) +
                              "/Resources/Images/");
        
        for (auto &entry : iterator(allImagesPath)) {
            auto absPath = entry.path().string();
            
            if (GetFileExtension(absPath) != "png")
                continue;
            
            auto texture = std::shared_ptr<SDL_Texture>(
                IMG_LoadTexture(
                    renderer.get(),
                    absPath.c_str()),
                SDLDeleter());
            auto textureName = GetFilenameNoExtension(absPath);
            
            m_textures.insert({Hash(textureName), texture});
        }
    }
    
    std::shared_ptr<SDL_Texture> GetTexture(std::string_view textureName) {
        auto hash = Hash(textureName);
        if (m_textures.contains(hash))
            return m_textures.at(hash);
        return nullptr;
    }
    
  private:
    std::map<int, std::shared_ptr<SDL_Texture>> m_textures;
};
}