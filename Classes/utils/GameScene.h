#pragma once

#include "cocos2d.h"
#include "controllers/GameController.h"

/**
 * @brief 游戏场景类
 * @details 负责管理游戏主场景，包含游戏控制器
 */
class GameScene : public cocos2d::Scene {
public:
    /**
     * @brief 创建游戏场景
     * @param levelId 关卡ID
     * @return 游戏场景指针
     */
    static GameScene* create(int levelId = 1);
    
    /**
     * @brief 初始化游戏场景
     * @param levelId 关卡ID
     * @return 初始化成功返回true
     */
    bool init(int levelId);
    
    /**
     * @brief 获取游戏控制器
     * @return 游戏控制器指针
     */
    GameController* getGameController() { return _gameController; }

private:
    GameController* _gameController;  // 游戏控制器
};
