#include "GameScene.h"
#include "configs/models/LayoutConfig.h"

USING_NS_CC;

GameScene* GameScene::create(int levelId) {
    GameScene* ret = new GameScene();
    if (ret && ret->init(levelId)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GameScene::init(int levelId) {
    if (!Scene::init()) {
        return false;
    }
    
    // 创建游戏控制器
    _gameController = new GameController();
    
    // 启动游戏
    if (!_gameController->startGame(levelId, this)) {
        CCLOGERROR("Failed to start game with level %d", levelId);
        return false;
    }
    
    return true;
}
