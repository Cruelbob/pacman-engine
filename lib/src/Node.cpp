#include "pacman/Node.h"

using namespace pacman;

void Node::addChild(const std::shared_ptr<Node> &child) {
    childs_.push_back(child);
    child->setTransformIsDirty();
}

void Node::visit(pacman::Time deltaTime) {
    update(deltaTime);
    assert(!transformIsDirty_);
    draw();
    for(const auto& child : childs_) {
        child->visit(deltaTime);
    }
}

void Node::update(pacman::Time deltaTime) {
    if(transformIsDirty_) {
        updateTransform();
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
        transform_ = parent->getTransform();
    } else {
        transform_.setIdentity();
    }
    transform_.scale(scale_);
    transform_.rotate(rotation_);
    transform_.scale(size_);
    transform_.translate(-pivot_);
    transformIsDirty_ = false;
}
