#include <iostream>
#include <game.hpp>
#include <sample_game_state.h>
#include <memory>
#include <future>

#include <Windows.h>

int CALLBACK WinMain(
    _In_  HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow
    )
//int main()
{
	try {
		pacman::game game(std::unique_ptr<pacman::game_state>(new sample_game_state));
        game();
	} catch (const std::exception& ex) {
        MessageBoxA(0,ex.what(),"",0);
	}
	return 0;
}

