#ifndef PACMAN_TEXTUREMANAGER_H
#define PACMAN_TEXTUREMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

namespace pacman {
class GameScene;
class Texture;
class TextureManager {
  public:
    TextureManager(GameScene& gameScene): gameScene_(gameScene) {}

    std::shared_ptr<Texture> getTexture(const std::string& name);
    void preloadTexture(const std::string& name);
    void removePreloadedTexture(const std::string& name);
  private:
    typedef std::unordered_map<std::string,std::shared_ptr<Texture>> PreloadedTextures;

    GameScene& gameScene_;
    PreloadedTextures preloadedTextures_;
};
} // namespace pacman

#endif // PACMAN_TEXTUREMANAGER_H
