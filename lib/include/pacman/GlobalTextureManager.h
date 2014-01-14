#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

#include "FileManager.h"

namespace pacman {
class Game;
class Texture;
class GlobalTextureManager {
  public:
    GlobalTextureManager(Game& game): game_(game) {}

    std::shared_ptr<Texture> getTexture(const std::string& name);
  private:
    typedef std::unordered_map<std::string,std::weak_ptr<Texture>> Textures;

    Game& game_;
    Textures textures_;
};
}

#endif // TEXTUREMANAGER_H
