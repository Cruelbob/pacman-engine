#pragma once

#include <game_state.hpp>
#include <user_image.hpp>

class sample_game_state: public pacman::game_state {
	std::shared_ptr<pacman::user_image> loading_image;
    std::shared_ptr<pacman::user_image> loading_image2;
	void initialize() override;
	void update(const pacman::time_type& delta) override;
};