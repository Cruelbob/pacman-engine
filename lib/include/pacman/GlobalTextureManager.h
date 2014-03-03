#ifndef GLOBALTEXTUREMANAGER_H
#define GLOBALTEXTUREMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include "CallbackConnection.h"

namespace pacman {
class Game;
class Texture;
namespace Graphics {
class GlobalTextureManager {
  public:
    GlobalTextureManager(Game& game): game_(game) {}

    std::shared_ptr<Texture> getTexture(const std::string& name);
  private:
    Game& game_;

    typedef std::unordered_map<std::string, std::weak_ptr<Texture>> Textures;
    Textures textures_;

#if EMSCRIPTEN
#else
    typedef std::unordered_map<std::string, ScopedCallbackConnection> LoadingCallbacks;

    LoadingCallbacks loadingCallbacks_;
#endif
};
} // Graphics
} // namespace pacman

#endif // GLOBALTEXTUREMANAGER_H
