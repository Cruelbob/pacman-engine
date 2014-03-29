#ifndef PACMAN_INPUT_MANAGER_H
#define PACMAN_INPUT_MANAGER_H

#include <functional>
#include <memory>
#include <list>

#include "CallbackConnection.h"

namespace pacman {
class KeyEvent {
  public:
    enum class Type {
        UP,
        DOWN
    };
    enum class Key {
        ESC
    };

    KeyEvent(Type type, Key key): type_(type), key_(key) {}

    Type getType() const { return type_; }
    Key getKey() const { return key_; }
  private:
    Type type_;
    Key key_;
};
class InputManager {
  public:
    typedef std::function<void (const KeyEvent&)> KeyEventCallback;

    CallbackConnection addOnKeyEvent(const KeyEventCallback& keyEventCallback) {
        auto keyEventCallbackIt = keyEventCallbacks_.emplace(keyEventCallbacks_.end(), keyEventCallback);
        return CallbackConnection([this, keyEventCallbackIt]() {
            keyEventCallbacks_.erase(keyEventCallbackIt);
        });
    }

    void update();
  private:
    typedef std::list<KeyEventCallback> KeyEventCallbacks;
    KeyEventCallbacks keyEventCallbacks_;
};
} // namespace pacman

#endif // PACMAN_INPUT_MANAGER_H
