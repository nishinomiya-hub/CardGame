#pragma once

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "managers/UndoManager.h"
#include "services/CardMatchService.h"

// 前置声明
class GameController;

/**
 * @brief 桌面牌区控制器
 * @details 处理桌面牌区的所有交互逻辑
 */
class PlayFieldController {
public:
    /**
     * @brief 构造函数
     * @param gameController 游戏主控制器指针
     */
    PlayFieldController(GameController* gameController);
    
    /**
     * @brief 析构函数
     */
    ~PlayFieldController();
    
    /**
     * @brief 初始化桌面牌区
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
    PlayFieldView* _playFieldView;    // 桌面牌区视图
    UndoManager* _undoManager;        // 回退管理器
    
    /**
     * @brief 验证点击是否合法
     * @param cardId 卡牌ID
     * @return 合法返回true
     */
    bool validateClick(int cardId);
    
    /**
     * @brief 检查卡牌是否与手牌顶部匹配
     * @param cardId 卡牌ID
     * @return 匹配返回true
     */
    bool checkMatch(int cardId);
    
    /**
     * @brief 记录操作历史
     * @param sourceCardId 源卡牌ID
     * @param targetCardId 目标卡牌ID
     */
    void recordOperation(int sourceCardId, int targetCardId);
    
    /**
     * @brief 执行卡牌移动到手牌区
     * @param cardId 要移动的卡牌ID
     */
    void executeCardMove(int cardId);
    
    /**
     * @brief 设置所有桌面牌的触摸回调
     */
    void setupCardCallbacks();
};