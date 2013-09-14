#pragma once

#include <memory>
#include <functional>

#include <user_graphics_context.hpp>
#include <audio_context.hpp>

namespace pacman {
class game_state;
class base_game_state {
    base_game_state(const base_game_state&);
    base_game_state& operator=(const base_game_state&);
  public:
    base_game_state() {}
    virtual ~base_game_state() {}

    bool to_be_shutdown();
  protected:
    typedef std::function<void (std::unique_ptr<game_state>&)> state_change_t;

    virtual void initialize() = 0;
    virtual void input(const std::vector<input_event_t>& in_events) {}
    virtual void update(const time_type& delta) = 0;
    virtual void pre_next_state() {}

    void set_next_state(std::unique_ptr<game_state>& p_state);
    void exit();
    user_graphics_context& get_graphics_context();
    user_audio_context& get_audio_contxt();

    void set_state_change_callback(const state_change_t& state_change);
    void set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_context);
    void set_audio_context(const std::shared_ptr<user_audio_context>& p_audio_context);
  private:
    state_change_t state_change_clbk;
    std::shared_ptr<user_graphics_context> p_graphics_context_;
    std::shared_ptr<user_audio_context> p_audio_context_;
    bool to_be_shutdown_;
};
} // namespace pacman
