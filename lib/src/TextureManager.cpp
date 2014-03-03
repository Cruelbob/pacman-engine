#include "pacman/TextureManager.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;
using namespace pacman::Graphics;

std::shared_ptr<Texture> TextureManager::getTexture(const std::string &name) {
    auto textureIt = preloadedTextures_.find(name);
    if(textureIt != preloadedTextures_.end()) {
        return textureIt->second;
    } else {
        return gameScene_.getGame().getGlobalTextureManager().getTexture(name);
    }
}

void TextureManager::preloadTexture(const std::string &name) {
    preloadedTextures_.emplace(name, gameScene_.getGame().getGlobalTextureManager().getTexture(name));
}

void TextureManager::removePreloadedTexture(const std::string &name) {
    preloadedTextures_.erase(name);
}
