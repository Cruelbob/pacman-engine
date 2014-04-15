#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include "TextureFrame.h"
#include "Node.h"
#include "Types.h"

namespace pacman {
class GameScene;
class Sprite: public Node {
  public:
    Sprite(const TextureFrame &textureFrame, const size2d<uint32_t>& sizeInPoints);
    Sprite(const TextureFrame& textureFrame);

    bool isInitialized() const;

    void update(Time deltaTime) override;
    void draw() override;
  private:
    void updateQuadVertices();

    TextureFrame textureFrame_;
    V2F_C4B_T2F_Quad quad_;
};
} // namespace pacman

#endif // PACMAN_SPRITE_H
