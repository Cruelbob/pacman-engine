#ifndef PACMAN_NODE_H
#define PACMAN_NODE_H

#include <vector>
#include <memory>

#include <Eigen/Geometry>

#include "Types.h"

namespace pacman {
class Node: public std::enable_shared_from_this<Node> {
  public:
    typedef Eigen::Transform<float, 2, Eigen::Affine> Transform;

    Node(const size2d<uint32_t>& sizeInPoints = size2d<uint32_t>());

    virtual ~Node() {}

    virtual void addChild(const std::shared_ptr<Node>& child);
    virtual void removeFromParent();
    virtual void visit(Time deltaTime);

    void setsizeInPoints(const size2d<uint32_t>& sizeInPoints);
    const size2d<uint32_t>& getsizeInPoints() const { return sizeInPoints_; }

    void setPosition(const point2d<float>& position);
    const point2d<float>& getPosition() const { return position_; }

    void setScale(const scale2d<float>& scale);
    void setScale(float scale) { setScale(scale2d<float>(scale, scale)); }
    const scale2d<float>& getScale() const { return scale_; }

    void setPivot(const point2d<float>& pivot);
    const point2d<float>& getPivot() const { return pivot_; }

    void setRotation(float angle);
    float getRotation() const { return rotationAngle_; }
  protected:
    virtual void update(Time deltaTime);
    virtual void draw() {}

    void setTransformIsDirty();
    void updateTransform();
  protected:
    size2d<uint32_t> sizeInPoints_;
    scale2d<float> sizeInParent_;
    point2d<float> position_;
    scale2d<float> scale_;
    point2d<float> pivot_;
    float rotationAngle_;
    Transform transform_;
    bool transformIsDirty_;
    std::vector<std::shared_ptr<Node>> childs_;
    std::weak_ptr<Node> parent_;
};
} // namespace pacman

#endif // PACMAN_NODE_H
