#include <game.hpp>

namespace pacman {
game::game(std::unique_ptr<game_state>&& p_first_state):
  p_graphics_ctx(create_graphics_context()) {
	set_next_state(p_first_state);
}

void game::operator()() {
	setup_current_state();
	auto begin = std::chrono::system_clock::now();
	while(p_current_state_ && !p_current_state_->to_be_shutdown()) {
		auto now = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<time_type>(now-begin);
		begin = now;
		p_current_state_->input(std::vector<input_event_t>());
		p_current_state_->update(delta);
        p_graphics_ctx->render();
		if(p_next_state_) {
			p_current_state_->pre_next_state();
			setup_current_state();
		}
	}
    p_current_state_.reset();
    p_next_state_.reset();
}
void game::set_next_state(std::unique_ptr<game_state>& p_next_state) {
	p_next_state_ = std::move(p_next_state);
}

void game::setup_current_state() {
    p_next_state_->set_previous_state(std::move(p_current_state_));
    p_current_state_ = std::move(p_next_state_);
    game_state::state_change_t state_change_clbk = std::bind(&game::set_next_state,
                                                             this,
                                                             std::placeholders::_1);
    p_current_state_->set_state_change_callback(state_change_clbk);
    p_current_state_->set_graphics_contex(p_graphics_ctx);
    p_current_state_->initialize();
}
}
