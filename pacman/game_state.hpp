#pragma once

#include <memory>
#include <vector>

#include <pacman_defs.hpp>
#include <base_game_state.hpp>

namespace pacman {
class game_state: private base_game_state {
  public:
    game_state() {}
    ~game_state() override {}

    using base_game_state::to_be_shutdown;
  protected:
    using base_game_state::set_next_state;
    using base_game_state::exit;
    using base_game_state::get_graphics_context;
    using base_game_state::get_audio_contxt;

    friend class game;
};
} // namespace pacman
