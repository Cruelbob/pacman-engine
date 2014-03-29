#include "pacman/Sprite.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;

void Sprite::update(pacman::Time deltaTime) {
    if(isInitialized()) {
        Node::update(deltaTime);
    }
}

void Sprite::draw() {
    if(isInitialized()) {
        //draw
    }
}
