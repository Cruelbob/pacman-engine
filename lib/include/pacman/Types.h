#ifndef PACMAN_TYPES_H
#define PACMAN_TYPES_H

#include <cstdint>
#include <cmath>
#include <ostream>
#include <chrono>

#include <Eigen/Geometry>

namespace pacman {
typedef std::chrono::duration<float> Time;

union Color {
    struct Components {
        Components(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
          red(red), green(green), blue(blue), alpha(alpha) {}

        float redAsFloat() const { return static_cast<float>(red)/255.0f; }
        float greenAsFloat() const { return static_cast<float>(green)/255.0f; }
        float blueAsFloat() const { return static_cast<float>(blue)/255.0f; }
        float alphaAsFloat() const { return static_cast<float>(alpha)/255.0f; }

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

inline std::ostream& operator<<(std::ostream& out, const Color& color)
{
    out << "r: " << std::hex << static_cast<int>(color.components.red)
        << " g: " << std::hex << static_cast<int>(color.components.green)
        << " b: " << std::hex << static_cast<int>(color.components.blue)
        << " a: " << std::hex << static_cast<int>(color.components.alpha);
    return out;
}

typedef Eigen::Vector2f vec2;

class size2d {
  public:
    typedef float size_type;

    size2d(const size2d& other) = default;
    size2d& operator=(const size2d& other) = default;
    size2d(size_type width = 0, size_type height = 0): width_(width), height_(height) {}

    void set(size_type width = 0, size_type height = 0) {
        width_ = width;
        height_ = height;
    }

    void setWidth(size_type width) { width_ = width; }
    size_type getWidth() const { return width_; }
    void setHeight(size_type height) { height_ = height; }
    size_type getHeight() const { return height_; }
    size_type getArea() const { return width_ * height_; }
  private:
    size_type width_;
    size_type height_;
};

class bounds2d {
  public:
    typedef float size_type;

    bounds2d(const bounds2d& other) = default;
    bounds2d& operator=(const bounds2d& other) = default;
    bounds2d(size_type left = 0, size_type bottom = 0, size_type right = 0, size_type top = 0):
        left_(left), bottom_(bottom), right_(right), top_(top) {}
    bounds2d(const size2d& size, const vec2& pos = vec2(0.0f, 0.0f)):
        left_(pos[0]), bottom_(pos[1]), right_(left_ + size.getWidth()), top_(bottom_ + size.getHeight()) {}

    void set(size_type left = 0, size_type bottom = 0, size_type right = 0, size_type top = 0) {
        left_ = left;
        bottom_ = bottom;
        right_ = right;
        top_ = top;
    }

    void setLeft(size_type left) { left_ = left; }
    size_type getLeft() const { return left_; }
    void setTop(size_type top) { top_ = top; }
    size_type getTop() const { return top_; }
    void setRight(size_type right) { right_ = right; }
    size_type getRight() const { return right_; }
    void setBottom(size_type bottom) { bottom_ = bottom; }
    size_type getBottom() const { return bottom_; }

    vec2 getPosition() const {
        return vec2(left_, bottom_);
    }
    void setPosition(const vec2& pos) {
        right_ = right_ - left_ + pos[0];
        top_ = top_ - bottom_ + pos[1];
        left_ = pos[0];
        bottom_ = pos[1];
    }

    size2d getSize() const { return size2d(right_ - left_, top_ - bottom_); }
    void setSize(const size2d& size) {
        right_ = left_ + size.getWidth();
        top_ = bottom_ + size.getHeight();
    }

    bool contains(const vec2& point) const {
        return  point[0] >= left_ && point[0] <= right_ &&
                point[1] >= top_ && point[1] <= bottom_;
    }

    bounds2d getAbsoluteBounds(const bounds2d& relative) const {
        return bounds2d(left_ + relative.left_,
                        bottom_ + relative.bottom_,
                        right_ + relative.right_,
                        top_ + relative.top_);
    }

  private:
    size_type left_;
    size_type bottom_;
    size_type right_;
    size_type top_;
};

} // namespace pacman

#endif // PACMAN_TYPES_H
