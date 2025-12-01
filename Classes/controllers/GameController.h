#pragma once

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"


// 前置声明
class StackController;
class PlayFieldController;

/**
 * @brief 游戏主控制器
 * @details 管理游戏生命周期，协调各个子控制器
 */
class GameController {
public:
    /**
     * @brief 构造函数
     */
    GameController();
    
    /**
     * @brief 析构函数
     */
    ~GameController();
    
    /**
     * @brief 开始游戏
     * @param levelId 关卡ID
     * @param parentNode 父节点，用于添加视图
     * @return 启动成功返回true
     */
    bool startGame(int levelId, cocos2d::Node* parentNode);
    
    /**
     * @brief 处理回退操作
     */
    void handleUndo();
    
    /**
     * @brief 检查游戏是否获胜
     * @return 获胜返回true
     */
    bool checkWinCondition();
    
    /**
     * @brief 获取游戏数据模型
     * @return 游戏数据模型指针
     */
    GameModel* getGameModel() { return _gameModel; }
    
    /**
     * @brief 获取游戏视图
     * @return 游戏视图指针
     */
    GameView* getGameView() { return _gameView; }
    
    /**
     * @brief 获取回退管理器
     * @return 回退管理器指针
     */
    UndoManager* getUndoManager() { return _undoManager; }

    /**
     * @brief 更新回退按钮状态
     */
    void updateUndoButtonState();
    
private:
    GameModel* _gameModel;                      // 游戏数据模型
    GameView* _gameView;                        // 游戏视图
    UndoManager* _undoManager;                  // 回退管理器
    StackController* _stackController;          // 手牌区控制器
    PlayFieldController* _playFieldController;  // 桌面牌区控制器
    
    /**
     * @brief 初始化游戏数据
     * @param levelId 关卡ID
     * @return 初始化成功返回true
     */
    bool initGameData(int levelId);
    
    /**
     * @brief 初始化视图
     * @param parentNode 父节点
     * @return 初始化成功返回true
     */
    bool initView(cocos2d::Node* parentNode);
    
    /**
     * @brief 初始化子控制器
     * @return 初始化成功返回true
     */
    bool initControllers();
    
    /**
     * @brief 设置事件回调
     */
    void setupCallbacks();
    
    /**
     * @brief 处理回退完成事件
     * @param record 回退记录
     */
    void onUndoComplete(const UndoRecord& record);
    
    
    /**
     * @brief 显示胜利提示
     */
    void showWinMessage();
};