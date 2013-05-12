#include <game_state.hpp>
#include <stdexcept>

namespace pacman {
game_state::game_state() {
}
game_state::~game_state() {
}
void game_state::initialize() {
}
void game_state::input(const std::vector<input_event_t>& in_events) {
}
void game_state::update(const time_type& delta) {
}
void game_state::pre_next_state() {
}
void game_state::set_state_change_callback(const state_change_t& state_change) {
	state_change_clbk = state_change;
}
void game_state::set_previous_state(std::unique_ptr<game_state>&& p_prev_state) {
	p_previous_state = std::move(p_prev_state);
}
void game_state::set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_ctx) {
	p_graphics_context = p_graphics_ctx;
}
void game_state::set_next_state(std::unique_ptr<game_state>&& p_state) {
	if(state_change_clbk) {
		state_change_clbk(p_state);
	} else {
		throw std::runtime_error("game_state::set_state_change_callback was not called");
	}
}
void game_state::exit() {
	set_next_state(std::unique_ptr<game_state>());
}
user_graphics_context& game_state::get_graphics_context() {
	if(p_graphics_context) {
		return *p_graphics_context;
	} else {
		throw std::runtime_error("graphics context has not set");
	}
}
}
