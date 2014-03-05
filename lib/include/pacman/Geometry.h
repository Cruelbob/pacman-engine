#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>

namespace pacman {
class point2d {
  public:
    typedef float size_type;

    point2d(size_type x = 0, size_type y = 0): x_(x), y_(y) {}

    void setX(size_type x) { x_ = x; }
    size_type getX() const { return x_; }
    void setY(size_type y) { y_ = y; }
    size_type getY() const { return y_; }
  private:
    size_type x_;
    size_type y_;
};

class size2d {
  public:
    typedef point2d::size_type size_type;

    size2d(size_type width = 0, size_type height = 0): width_(width), height_(height) {}

    void set(size_type width = 0, size_type height = 0) {
        width_ = width;
        height_ = height;
    }

    void setWidth(size_type width) { width_ = width; }
    size_type getWidth() const { return width_; }
    void setHeight(size_type height) { height_ = height; }
    size_type getHeight() const { return height_; }
  private:
    size_type width_;
    size_type height_;
};

class bounds2d {
  public:
    typedef point2d::size_type size_type;

    bounds2d(size_type left = 0, size_type top = 0, size_type right = 0, size_type bottom = 0):
        left_(left), top_(top), right_(right), bottom_(bottom) {}

    void setLeft(size_type left) { left_ = left; }
    size_type getLeft() const { return left_; }
    void setTop(size_type top) { top_ = top; }
    size_type getTop() const { return top_; }
    void setRight(size_type right) { right_ = right; }
    size_type getRight() const { return right_; }
    void setBottom(size_type bottom) { bottom_ = bottom; }
    size_type getBottom() const { return bottom_; }

    size2d getSize() const { return size2d(right_ - left_, bottom_ - top_); }
    bool isContains(const point2d& point) {
        return  point.getX() >= left_ && point.getX() <= right_ &&
                point.getY() >= top_ && point.getY() <= bottom_;
    }
  private:
    size_type left_;
    size_type top_;
    size_type right_;
    size_type bottom_;
};
}

#endif // GEOMETRY_H
