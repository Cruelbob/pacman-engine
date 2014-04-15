#ifndef PACMAN_ATLAS_H
#define PACMAN_ATLAS_H

#include <string>
#include <map>

#include "TextureFrame.h"

namespace pacman {
class TextureAtlas {
  public:
    TextureAtlas();

    TextureFrame getFrame(const std::string& name) const;
  private:
    std::shared_ptr<Texture> texture_;
    std::map<std::string, Frame> sprites_;
};
} // namespace pacman

#endif // PACMAN_ATLAS_H
