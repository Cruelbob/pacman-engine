#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

namespace pacman {
class GameScene;
class Texture;
namespace Graphics {
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
} // namespace Graphics
} // namespace pacman

#endif // TEXTUREMANAGER_H
