#include "pacman/Node.h"

using namespace pacman;

Node::Node(const size2d<uint32_t> &sizeInPoints):
  sizeInPoints_(sizeInPoints),
  sizeInParent_(sizeInPoints.getWidth() ? 1.0f : 0.0f, sizeInPoints.getHeight() ? 1.0f : 0.0f),
  pivot_(0.5f, 0.5f),
  rotationAngle_(0.0f),
  transform_(Transform::Identity()),
  transformIsDirty_(false) {}

void Node::addChild(const std::shared_ptr<Node> &child) {
    childs_.push_back(child);
    child->sizeInParent_ = child->sizeInPoints_ / sizeInPoints_;
    child->setTransformIsDirty();
}

void Node::removeFromParent() {
    auto parent = parent_.lock();
    if(parent) {
        parent->childs_.erase(std::find(parent->childs_.begin(), parent->childs_.end(), shared_from_this()));
        parent_.reset();
        sizeInParent_.set(sizeInPoints_.getWidth() ? 1.0f : 0.0f, sizeInPoints_.getHeight() ? 1.0f : 0.0f);
        setTransformIsDirty();
    }
}

void Node::visit(pacman::Time deltaTime) {
    update(deltaTime);
    draw();
    for(const auto& child : childs_) {
        child->visit(deltaTime);
    }
}

void Node::setsizeInPoints(const size2d<uint32_t> &sizeInPoints) {
    if(parent_.expired()) {
        sizeInPoints_ = sizeInPoints;
        sizeInParent_.set(sizeInPoints.getWidth() ? 1.0f : 0.0f, sizeInPoints.getHeight() ? 1.0f : 0.0f);
    } else {
        sizeInPoints_ = sizeInPoints;
        sizeInParent_ = sizeInParent_ * (sizeInPoints / sizeInPoints_);
    }
    setTransformIsDirty();
}

void Node::setPosition(const point2d<float> &position) {
    position_ = position;
    setTransformIsDirty();
}

void Node::setScale(const scale2d<float> &scale) {
    scale_ = scale;
    setTransformIsDirty();
}

void Node::setPivot(const point2d<float> &pivot) {
    pivot_ = pivot;
    setTransformIsDirty();
}

void Node::setRotation(float angle) {
    rotationAngle_ = angle;
    setTransformIsDirty();
}

void Node::update(pacman::Time deltaTime) {
    if(transformIsDirty_) {
        updateTransform();
        transformIsDirty_ = false;
    }
}

void Node::setTransformIsDirty() {
    if(!transformIsDirty_) {
        transformIsDirty_ = true;
        for(const auto& child : childs_) {
            child->setTransformIsDirty();
        }
    }
}

void Node::updateTransform() {
    auto parent = parent_.lock();
    if(parent) {
        transform_ = parent->transform_;
    } else {
        transform_.setIdentity();
    }
    transform_.translate(position_.toVec2());
    transform_.scale((sizeInParent_ * scale_).toVec2());
    transform_.rotate(rotationAngle_);
    transform_.translate(-pivot_.toVec2());
}
