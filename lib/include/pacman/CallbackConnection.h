#ifndef CALLBACK_CONNECTION_H
#define CALLBACK_CONNECTION_H

#include <functional>

namespace pacman {
class CallbackConnection {
  public:
    typedef std::function<void ()> DisconnectCallback;

    CallbackConnection() = default;
    CallbackConnection(const CallbackConnection&) = delete;
    CallbackConnection(const DisconnectCallback& disconnectCallback):
        disconnectCallback_(disconnectCallback) {}

    CallbackConnection(CallbackConnection&& other):
        disconnectCallback_(std::move(other.disconnectCallback_))
    {
        other.disconnectCallback_ = nullptr;
    }

    CallbackConnection& operator=(CallbackConnection&& other) {
        disconnectCallback_ = std::move(other.disconnectCallback_);
        other.disconnectCallback_ = nullptr;
        return *this;
    }

    void disconnect() {
        if(disconnectCallback_) {
            disconnectCallback_();
            disconnectCallback_ = nullptr;
        }
    }
  private:
    DisconnectCallback disconnectCallback_;
};

class ScopedCallbackConnection {
  public:
    ScopedCallbackConnection() = default;
    ScopedCallbackConnection(ScopedCallbackConnection&&) = default;
    ScopedCallbackConnection(CallbackConnection&& callbackConnection):
        callbackConnection_(std::move(callbackConnection)) {}
    ~ScopedCallbackConnection() {
        disconnect();
    }

    ScopedCallbackConnection& operator=(ScopedCallbackConnection&&) = default;

    void disconnect() { callbackConnection_.disconnect(); }
  private:
    CallbackConnection callbackConnection_;
};
} // namespace pacman


#endif // CALLBACK_CONNECTION_H
