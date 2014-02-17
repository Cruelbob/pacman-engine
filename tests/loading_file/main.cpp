#include <iostream>
#include <functional>

#include <pacman.h>
#include <pacman/Game.h>
#include <pacman/GameScene.h>

using namespace pacman;
using namespace std::placeholders;

const std::string TEST_FILE = "test.txt";

class DummyGameScene: public GameScene
{
    void initialize() {
        std::cout << "loadFile from DummyGameScene\n";
        getFileManager().loadFile(TEST_FILE, std::bind(&DummyGameScene::onFile, this, _1, _2, _3));
    }

    void onFile(const std::string& filename, FileIO::LoadingStatus status, const array_view<uint8_t>& fileData) {
        if(status == FileIO::LoadingStatus::SUCCESS) {
            std::string content(fileData.begin(), fileData.end());
            std::cout << "Content of " << filename << ":\"" << content << "\"\n";
        }  else {
            std::cout << "Loading of " << filename << " failed\n";
        }
        std::cout << "postExit from DummyGameScene\n";
        getGame().postExit();
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
