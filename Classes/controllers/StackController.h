#pragma once

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"

// 前置声明
class GameController;

/**
 * @brief 手牌区控制器
 * @details 处理手牌区的所有交互逻辑
 */
class StackController {
public:
    /**
     * @brief 构造函数
     * @param gameController 游戏主控制器指针
     */
    StackController(GameController* gameController);
    
    /**
     * @brief 析构函数
     */
    ~StackController();
    
    /**
     * @brief 初始化手牌区
     * @return 初始化成功返回true
     */
    bool init();
    
    /**
     * @brief 处理卡牌点击事件
     * @param cardId 被点击的卡牌ID
     */
    void handleCardClick(int cardId);
    
private:
    GameController* _gameController;  // 游戏主控制器
    GameModel* _gameModel;            // 游戏数据模型
    StackView* _stackView;            // 手牌区视图
    UndoManager* _undoManager;        // 回退管理器
    
    /**
     * @brief 验证点击是否合法
     * @param cardId 卡牌ID
     * @return 合法返回true
     */
    bool validateClick(int cardId);
    
    /**
     * @brief 记录操作历史
     * @param sourceCardId 源卡牌ID
     * @param targetCardId 目标卡牌ID
     */
    void recordOperation(int sourceCardId, int targetCardId);
    
    /**
     * @brief 执行卡牌替换
     * @param cardId 要替换到顶部的卡牌ID
     */
    void executeCardReplace(int cardId);
    
    /**
     * @brief 设置所有手牌的触摸回调
     */
    void setupCardCallbacks();
};