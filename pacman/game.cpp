#include <game.hpp>

namespace pacman {
game::game(std::unique_ptr<game_state>&& p_first_state):
  p_graphics_ctx(create_graphics_context()) {
	set_next_state(p_first_state);
}
game::~game() {
}
void game::operator()() {
	p_current_state_ = std::move(p_next_state_);
	p_current_state_->initialize();
	auto begin = std::chrono::system_clock::now();
	while(p_current_state_) {
		auto now = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<time_type>(now-begin);
		begin = now;
		p_current_state_->input(std::vector<input_event_t>());
		p_current_state_->update(delta);
        p_graphics_ctx->render();
		if(p_next_state_) {
			p_current_state_->pre_next_state();
			p_next_state_->set_previous_state(std::move(p_current_state_));
			p_current_state_ = std::move(p_next_state_);
			p_current_state_->initialize();
		}
	}
	p_last_state_.reset();
}
void game::set_next_state(std::unique_ptr<game_state>& p_next_state) {
	// If p_next_state hasn't value then terminate loop.
	if(p_next_state) {
		// If loop isn't running then set previous state here.
		if(!p_current_state_) {
			p_next_state->set_previous_state(std::move(p_next_state_));
		}
		p_next_state_ = std::move(p_next_state);
		game_state::state_change_t state_change_clbk = std::bind(&game::set_next_state,this,std::placeholders::_1);
		p_next_state_->set_state_change_callback(state_change_clbk);
        p_next_state_->set_graphics_contex(p_graphics_ctx);
	} else {
		p_next_state_.reset();
		p_last_state_ = std::move(p_current_state_);
	}
}
}
