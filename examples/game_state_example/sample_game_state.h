#pragma once

#include <pacman/game_state.hpp>
#include <pacman/image.hpp>

class sample_game_state: public pacman::game_state {
    std::shared_ptr<pacman::image> loading_image;
    std::shared_ptr<pacman::image> loading_text;
    void initialize() override;
    void update(const pacman::time_type& delta) override;
};
