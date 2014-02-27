#include <iostream>
#include <functional>

#include <pacman.h>
#include <pacman/GameScene.h>
#include <pacman/Game.h>

using namespace pacman;
using namespace pacman::FileIO;
using namespace std::placeholders;

const std::string TEST_FILE = "test.txt";
const std::string TEST_FILE_1 = "not_file.txt";

class DummyGameScene: public GameScene {
    void initialize() {
        getGame().getGlobalFileManager().loadFile(TEST_FILE, std::bind(&DummyGameScene::onFile, this, _1, _2, _3));
    }

    void onFile(const std::string& filename, LoadingStatus status, const array_view<uint8_t>& fileData) {
        switch (status) {
          case LoadingStatus::SUCCESS:
          {
            std::cout << "Content of " << filename << ": \"";
            std::cout.write((char*)fileData.data(), fileData.size()) << "\"\n";
            std::cout << "postExit from DummyGameScene\n";
            getGame().postExit();
            break;
          }
          case LoadingStatus::FAILURE:
            std::cout << "Loading of " << filename << " failed\n";
            if(filename == TEST_FILE_1) {
                getFileManager().loadFile(TEST_FILE, std::bind(&DummyGameScene::onFile, this, _1, _2, _3));
            } else {
                getGame().postExit();
            }
            break;
          case LoadingStatus::CANCELED:
            std::cout << "Loading of " << filename << " canceled\n";
            getFileManager().loadFile(TEST_FILE_1, std::bind(&DummyGameScene::onFile, this, _1, _2, _3));
            break;
          default:
            break;
        }
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
