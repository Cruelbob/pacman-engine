#include <emscripten/emscripten.h>

#include "pacman/GlobalTextureManager.h"
#include "pacman/Texture.h"

#include <iostream>

using namespace pacman;
using namespace pacman::Graphics;

void onImageLoad(std::weak_ptr<Texture>* textureWeak, GLuint textureId, int width, int height) {
    std::cout << "onImageLoad" << std::endl;
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
        EM_ASM_INT(
            var img = new Image();
            img.onload = function() {
                console.log('loaded ' + img.src);
                var p_texName = _malloc(4);
                console.log(Module);
                _glGenTextures(1, p_texName);
                var textureId = getValue(p_texName, 'i32');
                _free(p_texName);
                var gl = Module.ctx;
                _glBindTexture(gl.TEXTURE_2D, textureId);
                gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
                Runtime.dynCall('viiii', $2, [$1, textureId, img.width, img.height]);
            };

            img.onlrror = function() {
                console.log('Error loading ' + img.src);
            };
            img.src = Pointer_stringify($0);
            return 0;
        , name.c_str(), textureWeak, &onImageLoad);
    }
    return texture;
}
