#ifndef GLOBALTEXTUREMANAGER_H
#define GLOBALTEXTUREMANAGER_H

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
    typedef std::unordered_map<std::string, std::weak_ptr<Texture>> Textures;
    typedef std::unordered_map<std::string, CallbackConnection> Callbacks;

    Game& game_;
    Textures textures_;
    Callbacks callbacks;
};
} // namespace pacman

#endif // GLOBALTEXTUREMANAGER_H
