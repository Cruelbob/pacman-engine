#pragma once

#include <memory>
#include <functional>

#include <user_graphics_context.hpp>
#include <audio_context.hpp>

namespace pacman {
class game_state {
    game_state(const game_state&);
    game_state& operator=(const game_state&);
  public:
    game_state() {}
    virtual ~game_state() {}
    typedef std::function<void (std::unique_ptr<game_state>&)> state_change_t;

    virtual void initialize() = 0;
    virtual void input(const std::vector<input_event_t>& in_events) = 0;
    virtual void update(const time_type& delta) = 0;
    virtual void pre_next_state() = 0;
  protected:
    virtual void set_state_change_callback(const state_change_t& state_change) = 0;
    virtual void set_previous_state(std::unique_ptr<game_state>&& p_prev_state) = 0;
    virtual void set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_ctx) = 0;
    virtual void set_audio_context(const std::shared_ptr<user_audio_context>& p_audio_ctx) = 0;

    friend class game;
};
}