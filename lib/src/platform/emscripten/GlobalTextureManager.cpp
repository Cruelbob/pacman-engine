#include <emscripten/emscripten.h>

#include "pacman/GlobalTextureManager.h"
#include "pacman/Texture.h"

#include <iostream>

using namespace pacman;
using namespace pacman::Graphics;

GLuint createAndBindTexture() {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    return texture;
}

void onImageLoad(std::weak_ptr<Texture>* textureWeak, GLuint textureId, int width, int height) {
    auto texture = textureWeak->lock();
    if(texture) {
        texture->init(textureId, size2d(width, height));
    }
    delete textureWeak;
}

std::shared_ptr<Texture> GlobalTextureManager::getTexture(const std::string &name) {
    std::shared_ptr<Texture> texture;
    auto texturIt = textures_.find(name);
    if(texturIt != textures_.end()) {
        texture = texturIt->second.lock();
    } else {
        texture.reset(new Texture(),[this, name](Texture * texture){
           textures_.erase(name);
           delete texture;
        });

        auto textureWeak = new std::weak_ptr<Texture>(texture);
        EM_ASM_INT({
            var img = new Image();
            img.onload = function() {
                var textureId = Runtime.dynCall('i', $2, []);
                var gl = Module.ctx;
                gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
                Runtime.dynCall('viiii', $3, [$1, textureId, img.width, img.height]);
            };

            img.onerror = function() {
                console.log('Error loading ' + img.src);
            };
            img.src = Pointer_stringify($0);
            return 0;
        }, name.c_str(), textureWeak, &createAndBindTexture, &onImageLoad);
    }
    return texture;
}
