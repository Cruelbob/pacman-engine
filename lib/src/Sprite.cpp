#include "pacman/Sprite.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;

Sprite::Sprite(const TextureFrame &textureFrame):
  Node(textureFrame.getSizeInPoints()), textureFrame_(textureFrame), quad_(textureFrame.getFrame())
{
}

bool Sprite::isInitialized() const { return textureFrame_.getTexture()->isInitialized(); }

void Sprite::update(Time deltaTime) {
    if(isInitialized()) {
        if(transformIsDirty_) {
            updateTransform();
            transformIsDirty_ = false;
            updateQuadVertices();
        }
    }
}

void Sprite::draw() {
    if(isInitialized()) {
        //draw
    }
}

void Sprite::updateQuadVertices() {
    Vec2<float> bottomLeft = transform_ * Vec2<float>(0.0f, 0.0f);
    Vec2<float> topRight = transform_ * Vec2<float>(1.0f, 1.0f);
    quad_.bottomLeft.coords = bottomLeft;
    quad_.bottomRight.coords = Vec2<float>(topRight[0], bottomLeft[1]);
    quad_.topLeft.coords = Vec2<float>(bottomLeft[0], topRight[1]);
    quad_.topRight.coords = topRight;
}
