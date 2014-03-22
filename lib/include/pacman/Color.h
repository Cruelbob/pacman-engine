#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace pacman {
union Color {
    struct Components {
        Components(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
          red(red), green(green), blue(blue), alpha(alpha) {}

        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255):
      components(red, green, blue, alpha) {}
    Color(float red, float green, float blue, float alpha = 1.0f):
      components(red*255.0f, green*255.0f, blue*255.0f, alpha*255.0f) {}
    Color(uint32_t uintValue): uintValue(uintValue) {}

    void set(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255) {
        components.red = red;
        components.green = green;
        components.blue = blue;
        components.alpha = alpha;
    }

    float redAsFloat() const { return static_cast<float>(components.red)/255.0f; }
    float greenAsFloat() const { return static_cast<float>(components.green)/255.0f; }
    float blueAsFloat() const { return static_cast<float>(components.blue)/255.0f; }
    float alphaAsFloat() const { return static_cast<float>(components.alpha)/255.0f; }

    Components components;
    uint32_t uintValue;
};
} // namespace pacman

#endif // COLOR_H
