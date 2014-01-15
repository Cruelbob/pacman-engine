#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

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

    InputManager(): keyEventCallbacks_(std::make_shared<KeyEventCallbacks>()) {}

    CallbackConnection addOnKeyEvent(const KeyEventCallback& keyEventCallback) {
        auto keyEventCallbackIt = keyEventCallbacks_->insert(keyEventCallbacks_->end(), keyEventCallback);
        std::weak_ptr<KeyEventCallbacks> keyEventCallbacksWeak = keyEventCallbacks_;
        return CallbackConnection([keyEventCallbacksWeak, keyEventCallbackIt]() {
            auto keyEventCallbacks = keyEventCallbacksWeak.lock();
            if(keyEventCallbacks) {
                keyEventCallbacks->erase(keyEventCallbackIt);
            }
        });
    }

    void update();
  private:
    typedef std::list<KeyEventCallback> KeyEventCallbacks;
    std::shared_ptr<KeyEventCallbacks> keyEventCallbacks_;
};
} // namespace pacman

#endif // INPUT_MANAGER_H
