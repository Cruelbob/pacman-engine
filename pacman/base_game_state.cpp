#include <base_game_state.hpp>
#include <stdexcept>

namespace pacman {
bool base_game_state::to_be_shutdown() {
    return to_be_shutdown_;
}
void base_game_state::set_state_change_callback(const state_change_t& state_change) {
    state_change_clbk = state_change;
}
void base_game_state::set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_context) {
    p_graphics_context_ = p_graphics_context;
}
void base_game_state::set_audio_context(const std::shared_ptr<user_audio_context>& p_audio_context) {
    p_audio_context_ = p_audio_context;
}
void base_game_state::set_next_state(std::unique_ptr<game_state>& p_state) {
    state_change_clbk(p_state);
}
void base_game_state::exit() {
    to_be_shutdown_ = true;
}
user_graphics_context& base_game_state::get_graphics_context() {
    return *p_graphics_context_;
}
} // namespace pacman