#ifndef PACMAN_NODE_H
#define PACMAN_NODE_H

#include <vector>
#include <memory>

#include <Eigen/Geometry>

#include "Types.h"

namespace pacman {
class Node {
  public:
    typedef Eigen::Transform<float, 2, Eigen::Affine> Transform;

    Node():
      position_(0.0f, 0.0f),
      size_(1.0f, 1.0f),
      pivot_(0.5f, 0.5f),
      scale_(1.0f, 1.0f),
      rotation_(0.0f),
      transform_(Transform::Identity()),
      transformIsDirty_(false) {}
    virtual ~Node() {}

    virtual void addChild(const std::shared_ptr<Node>& child);
    virtual void visit(Time deltaTime);
  protected:
    virtual void update(Time deltaTime);
    virtual void draw() {}

    void setTransformIsDirty();
    void updateTransform();
    const Transform& getTransform() const { return transform_; }
  protected:
    Eigen::Vector2f position_;
    Eigen::Vector2f size_;
    Eigen::Vector2f pivot_;
    Eigen::Vector2f scale_;
    float rotation_;
    Transform transform_;
    bool transformIsDirty_;
    std::vector<std::shared_ptr<Node>> childs_;
    std::weak_ptr<Node> parent_;
};
} // namespace pacman

#endif // PACMAN_NODE_H
