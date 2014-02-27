#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace pacman {
union Color {
    struct Components {
        Components(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
          red_(red), green_(green), blue_(blue), alpha_(alpha) {}

        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255):
      components(red, green, blue, alpha) {}
    Color(float red, float green, float blue, float alpha = 1.0f):
      components(red*255.0f, green*255.0f, blue*255.0f, alpha*255.0f) {}

    const Components& getComponents() const { return components; }

    uint32_t asUint() const { return uintValue; }
    void set(uint32_t uintValue) { this->uintValue = uintValue; }

    uint8_t redAsByte() const { return components.red; }
    uint8_t greenAsByte() const { return components.green; }
    uint8_t blueAsByte() const { return components.blue; }
    uint8_t alphaAsByte() const { return components.alpha; }

    float redAsFloat() const { return static_cast<float>(redAsByte())/255.0f; }
    float greenAsFloat() const { return static_cast<float>(greenAsByte())/255.0f; }
    float blueAsFloat() const { return static_cast<float>(blueAsByte())/255.0f; }
    float alphaAsFloat() const { return static_cast<float>(alphaAsByte())/255.0f; }
  private:
    Components components;
    uint32_t uintValue;
};
} // namespace pacman

#endif // COLOR_H
