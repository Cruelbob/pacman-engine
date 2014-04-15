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

template <typename T>
using Vec2 = Eigen::Matrix<T, 2, 1>;

template<typename SizeType>
class point2d {
  public:
    point2d(SizeType x = SizeType(), SizeType y = SizeType()): x_(x), y_(y) {}
    point2d(const Vec2<SizeType>& vec2): x_(vec2[0]), y_(vec2[1]) {}

    SizeType getX() const { return x_; }
    SizeType getY() const { return y_; }

    Vec2<SizeType> toVec2() const {
        return Vec2<SizeType>(x_, y_);
    }
  private:
    SizeType x_;
    SizeType y_;
};

template<typename SizeType>
class scale2d {
  public:
    scale2d(SizeType xFactor = 1, SizeType yFactor = 1): xFactor_(xFactor), yFactor_(yFactor) {}

    void set(SizeType xFactor, SizeType yFactor) {
        xFactor_ = xFactor;
        yFactor_ = yFactor;
    }

    SizeType getXFactor() const { return xFactor_; }
    SizeType getYFactor() const { return yFactor_; }

    scale2d<SizeType> operator*(const scale2d<SizeType>& other) const {
        return scale2d<SizeType>(xFactor_ * other.xFactor_, yFactor_ * other.yFactor_);
    }

    Vec2<SizeType> toVec2() const {
        return Vec2<SizeType>(xFactor_, yFactor_);
    }
  private:
    SizeType xFactor_;
    SizeType yFactor_;
};

template<typename SizeType>
class size2d {
  public:
    size2d(const size2d& other) = default;
    size2d& operator=(const size2d& other) = default;
    size2d(SizeType width = SizeType(), SizeType height = SizeType()): width_(width), height_(height) {}
    size2d(const Vec2<SizeType>& vec2): width_(vec2[0]), height_(vec2[1]) {}

    void set(SizeType width, SizeType height) {
        width_ = width;
        height_ = height;
    }

    void setWidth(SizeType width) { width_ = width; }
    SizeType getWidth() const { return width_; }
    void setHeight(SizeType height) { height_ = height; }
    SizeType getHeight() const { return height_; }

    scale2d<float> operator/(const size2d<SizeType>& other) const {
        return scale2d<float>(float(width_)/other.width_, float(height_)/other.height_);
    }

    size2d<float> operator*(const scale2d<float>& scale) const {
        return size2d<SizeType>(width_ * scale.getXFactor(), height_ * scale.getYFactor());
    }

    Vec2<SizeType> toVec2() const {
        return Vec2<SizeType>(width_, height_);
    }
  private:
    SizeType width_;
    SizeType height_;
};

template<typename SizeType>
class bounds2d {
  public:
    bounds2d(SizeType left = SizeType(),
             SizeType bottom = SizeType(),
             SizeType right = SizeType(),
             SizeType top = SizeType()):
      left_(left),
      bottom_(bottom),
      right_(right),
      top_(top) {}
    bounds2d(const size2d<SizeType>& size, const point2d<SizeType>& pos = point2d<SizeType>()):
        left_(pos.getX()), bottom_(pos.getY()), right_(left_ + size.getWidth()), top_(bottom_ + size.getHeight()) {}

    void set(SizeType left, SizeType bottom, SizeType right, SizeType top) {
        left_ = left;
        bottom_ = bottom;
        right_ = right;
        top_ = top;
    }

    void setLeft(SizeType left) { left_ = left; }
    SizeType getLeft() const { return left_; }
    void setTop(SizeType top) { top_ = top; }
    SizeType getTop() const { return top_; }
    void setRight(SizeType right) { right_ = right; }
    SizeType getRight() const { return right_; }
    void setBottom(SizeType bottom) { bottom_ = bottom; }
    SizeType getBottom() const { return bottom_; }

    point2d<SizeType> getPosition() const {
        return point2d<SizeType>(left_, bottom_);
    }
    void setPosition(const point2d<SizeType>& pos) {
        size2d<SizeType> size = getSize();
        left_ = pos.getX();
        bottom_ = pos.getY();
        right_ = pos.getX() + size.getWidth();
        top_ = pos.getY() + size.getHeight();
    }

    size2d<SizeType> getSize() const { return size2d<SizeType>(right_ - left_, top_ - bottom_); }
    void setSize(const size2d<SizeType>& size) {
        right_ = left_ + size.getWidth();
        top_ = bottom_ + size.getHeight();
    }

    bool contains(const point2d<SizeType>& point) const {
        return  point.getX() >= left_ && point.getX() <= right_ &&
                point.getY() >= top_ && point.getY() <= bottom_;
    }

    bounds2d getAbsoluteBounds(const bounds2d& relative) const {
        return bounds2d(left_ + relative.left_,
                        bottom_ + relative.bottom_,
                        right_ + relative.right_,
                        top_ + relative.top_);
    }

  private:
    SizeType left_;
    SizeType bottom_;
    SizeType right_;
    SizeType top_;
};

class Frame {
  public:
    Frame(const bounds2d<float>& bounds, bool rotated = false): bounds_(bounds), rotated_(rotated) {}

    const bounds2d<float>& getBounds() const { return bounds_; }
    bool isRotated() const { return rotated_; }
  private:
    bounds2d<float> bounds_;
    bool rotated_;
};

struct V2F_C4B_T2F {
    V2F_C4B_T2F(const Vec2<float>& coords, const Vec2<float>& texCoords, const Color& colors = Color(1.0f, 1.0f, 1.0f, 1.0f)):
      coords(coords), texCoords(texCoords), colors(colors) {}

    Vec2<float> coords;
    Vec2<float> texCoords;
    Color colors;
};

struct V2F_C4B_T2F_Quad {
    V2F_C4B_T2F_Quad(const Frame& frame):
      bottomLeft(Vec2<float>(0.0f, 0.0f),
                 frame.isRotated() ? Vec2<float>(frame.getBounds().getLeft(), frame.getBounds().getTop())
                                   : Vec2<float>(frame.getBounds().getLeft(), frame.getBounds().getBottom())),
      bottomRight(Vec2<float>(1.0f, 0.0f),
                  frame.isRotated() ? Vec2<float>(frame.getBounds().getLeft(), frame.getBounds().getBottom())
                                    : Vec2<float>(frame.getBounds().getRight(), frame.getBounds().getBottom())),
      topLeft(Vec2<float>(0.0f, 1.0f),
              frame.isRotated() ? Vec2<float>(frame.getBounds().getRight(), frame.getBounds().getTop())
                                : Vec2<float>(frame.getBounds().getLeft(), frame.getBounds().getTop())),
      topRight(Vec2<float>(0.0f, 1.0f),
               frame.isRotated() ? Vec2<float>(frame.getBounds().getRight(), frame.getBounds().getBottom())
                                 : Vec2<float>(frame.getBounds().getRight(), frame.getBounds().getTop())) {}

    V2F_C4B_T2F bottomLeft;
    V2F_C4B_T2F bottomRight;
    V2F_C4B_T2F topLeft;
    V2F_C4B_T2F topRight;
};
} // namespace pacman

#endif // PACMAN_TYPES_H
