#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include "TextureFrame.h"
#include "Node.h"

namespace pacman {
class GameScene;
class Sprite: public Node {
  public:
    Sprite(const TextureFrame& textureFrame): textureFrame_(textureFrame) {}

    bool isInitialized() const {
        return textureFrame_.isInitialized();
    }

    void update(Time deltaTime) override;
    void draw() override;
  private:
    TextureFrame textureFrame_;

};
} // namespace pacman

#endif // PACMAN_SPRITE_H
