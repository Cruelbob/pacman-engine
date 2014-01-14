#include <iostream>

#include <pacman.h>
#include <pacman/Game.h>
#include <pacman/GameScene.h>

using namespace pacman;

class DummyGameScene: public GameScene
{
    void initialize() {
        std::cout << "loadFile from DummyGameScene\n";
        getFileManager().loadFile("test.txt",[this](const FileManager::LoadingFile& file) {
            if(file.getStatus() == FileManager::LoadingStatus::SUCCESS) {
                std::string content(file.getBufferView().begin(), file.getBufferView().end());
                std::cout << "Content of " << file.getFilename() << ":\"" << content << "\"\n";
            }  else {
                std::cout << "Loading of " << file.getFilename() << " failed\n";
            }
            std::cout << "postExit from DummyGameScene\n";
            getGame().postExit();
        });
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
