#pragma once

#include <memory>
#include <functional>
#include <vector>

#include <pacman_defs.hpp>
#include <user_graphics_context.hpp>
#include <audio_context.hpp>

namespace pacman {
class game_state {
    game_state(const game_state& other);
    game_state& operator=(const game_state& other);
  public:
	typedef std::function<void (std::unique_ptr<game_state>&)> state_change_t;

	game_state();
    virtual ~game_state() = 0;

	virtual void initialize();
    virtual void input(const std::vector<input_event_t>& in_events);
	virtual void update(const time_type& delta);
	virtual void pre_next_state();

	void set_state_change_callback(const state_change_t& state_change);
	void set_previous_state(std::unique_ptr<game_state>&& p_prev_state);
	void set_graphics_contex(const std::shared_ptr<user_graphics_context>& p_graphics_ctx);
	void set_audio_context(const std::shared_ptr<user_audio_context>& p_audio_ctx);
  protected:
	std::unique_ptr<game_state> p_previous_state;
    /**
    Gets next state and previous current.
    */
    void set_next_state(std::unique_ptr<game_state>&& p_state);
	void exit();
	user_graphics_context& get_graphics_context();
	user_audio_context& get_audio_contxt();
  private:
	state_change_t state_change_clbk;
	std::shared_ptr<user_graphics_context> p_graphics_context;
	std::shared_ptr<user_audio_context> p_audio_context;
};
}