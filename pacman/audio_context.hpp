#pragma once

namespace pacman {
class user_audio_context {
	user_audio_context(const user_audio_context& other);
	user_audio_context& operator=(const user_audio_context& other);
  public:
	virtual ~user_audio_context() {};
};
}