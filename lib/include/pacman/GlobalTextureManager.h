#ifndef PACMAN_GLOBALTEXTUREMANAGER_H
#define PACMAN_GLOBALTEXTUREMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include "pacman/Config.h"
#include "CallbackConnection.h"

namespace pacman {
class Game;
class Texture;
class GlobalTextureManager {
  public:
    GlobalTextureManager(Game& game)
#if !EMSCRIPTEN
        : game_(game)
#endif
    {}

    std::shared_ptr<Texture> getTexture(const std::string& name);
  private:
#if !EMSCRIPTEN
    Game& game_;
    typedef std::unordered_map<std::string, ScopedCallbackConnection> LoadingCallbacks;

    LoadingCallbacks loadingCallbacks_;
#endif
    typedef std::unordered_map<std::string, std::weak_ptr<Texture>> Textures;
    Textures textures_;
};
} // namespace pacman

#endif // PACMAN_GLOBALTEXTUREMANAGER_H
