#ifndef ATLAS_H
#define ATLAS_H

#include <string>
#include <map>

#include "Sprite.h"

namespace pacman {
namespace Graphics {
class Atlas {
  public:
    Atlas();

    Sprite getSprite(const std::string& name) const;
  private:
    std::shared_ptr<Texture> texture_;
    std::map<std::string, bounds2d> sprites_;
};
} // namespace Graphics
} // namespace pacman

#endif // ATLAS_H
