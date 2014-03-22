#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

#include <Eigen/Geometry>

#include "Geometry.h"

namespace pacman {
namespace Graphics {
class Node {
  public:
    typedef Eigen::Transform<float, 2, Eigen::Affine> Transform;

    Node():
      pivot_(0.5f, 0.5f),
      position_(0.0f, 0.0f),
      scale_(1.0f, 1.0f),
      rotation_(0.0f),
      transform_(Transform::Identity()),
      transformIsDirty_(false) {}
    virtual ~Node() {}
  protected:
    Eigen::Vector2f pivot_;
    Eigen::Vector2f position_;
    Eigen::Vector2f scale_;
    float rotation_;
    Transform transform_;
    bool transformIsDirty_;
    std::vector<std::shared_ptr<Node>> childs_;
    std::weak_ptr<Node> parent_;
};
} // namespace Graphics
} // namespace pacman

#endif // NODE_H
