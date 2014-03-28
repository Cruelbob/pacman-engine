#include "pacman/Sprite.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman::Graphics;

void Sprite::update(pacman::Time deltaTime) {
    if(texture_ && !boundsInitialized_ && texture_->isInitialized()) {
        textureBounds_.set(0, 0, texture_->getWidth(), texture_->getHeight());
        boundsInitialized_ = true;
    }
}

void Sprite::draw() {
    if(isInitialized()) {
        //draw
    }
}
