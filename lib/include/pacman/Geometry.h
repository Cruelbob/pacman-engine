#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>

namespace pacman {
class size2d {
  public:
    typedef uint16_t size_type;
  private:
    size_type width_;
    size_type height;
};
}

#endif // GEOMETRY_H
