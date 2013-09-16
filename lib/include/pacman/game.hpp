#pragma once

#include <memory>

#include "pacman_defs.hpp"
#include "graphics_context.hpp"
#include "game_state.hpp"

namespace pacman {
class game: public non_copyable {
  public:
    /**
    Sets first state as next state for game loop.
    */
    game(std::unique_ptr<game_state>&& p_first_state);
    /**
    Sets next state as current state. Runs game loop from current state.
    After starting the control is carried out from the current state.
    First, it calls game_state::initialize.
    Next it calls game_state::input and game_state::update from loop.
    It calls game_state::pre_next_state before running next state.
    */
    void operator()();
  private:
    std::unique_ptr<game_state> p_next_state_;
    std::unique_ptr<game_state> p_current_state_;
    /**
    Sets next state or terminate game loop.
    */
    void set_next_state(std::unique_ptr<game_state>& p_next_state);
    void setup_current_state();

    std::shared_ptr<graphics_context> p_graphics_ctx;

    static std::shared_ptr<graphics_context> create_graphics_context();
};
} // namespace pacman
