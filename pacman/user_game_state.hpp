#pragma once

#include <memory>
#include <vector>

#include <pacman_defs.hpp>
#include <game_state.hpp>

namespace pacman {
class user_game_state: public game_state {
    user_game_state(const user_game_state& other);
    user_game_state& operator=(const user_game_state& other);
  public:
	user_game_state() {};
    ~user_game_state() override {};

    bool to_be_shutdown() override final;
  protected:
    void initialize() override {};
    void input(const std::vector<input_event_t>& in_events) override {};
    void update(const time_type& delta) override {};
    void pre_next_state() override {};

    void set_next_state(std::unique_ptr<game_state>& p_state);
	void exit();
	user_graphics_context& get_graphics_context();
	user_audio_context& get_audio_contxt();

    std::unique_ptr<game_state> p_previous_state;
  private:
    void set_state_change_callback(const state_change_t& state_change) override final;
    void set_previous_state(std::unique_ptr<game_state>& p_prev_state) override final;
    void set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_context) override final;
    void set_audio_context(const std::shared_ptr<user_audio_context>& p_audio_context) override final;

	state_change_t state_change_clbk;
	std::shared_ptr<user_graphics_context> p_graphics_context_;
	std::shared_ptr<user_audio_context> p_audio_context_;
    bool to_be_shutdown_;
};
}