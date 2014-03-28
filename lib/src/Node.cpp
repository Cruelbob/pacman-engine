#include "pacman/Node.h"

using namespace pacman::Graphics;

void Node::addChild(const std::shared_ptr<Node> &child) {
    childs_.push_back(child);
    child->setTransformIsDirty();
}

void Node::visit(pacman::Time deltaTime) {
    update(deltaTime);
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
    assert(parent);
    transform_ = parent->getTransform();
    transform.scale(scale);
    transform.rotate(rotation);
    transform.scale(size);
    transform.translate(-pivot);
    transformIsDirty_ = false;
}
