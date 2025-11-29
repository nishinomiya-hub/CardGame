#pragma once


#include "StackView.h"
#include "PlayFieldView.h"

/**
 * @brief 游戏主视图
 * @details 整合所有UI元素，管理游戏界面
 */
class GameView : public cocos2d::Layer {
public:
    /**
     * @brief 创建游戏视图
     * @return 游戏视图指针
     */
    static GameView* create();
    
    /**
     * @brief 初始化游戏视图
     * @return 初始化成功返回true
     */
    virtual bool init() override;
    
    /**
     * @brief 获取手牌区视图
     * @return 手牌区视图指针
     */
    StackView* getStackView() { return _stackView; }
    
    /**
     * @brief 获取桌面牌区视图
     * @return 桌面牌区视图指针
     */
    PlayFieldView* getPlayFieldView() { return _playFieldView; }
    
    /**
     * @brief 创建UI按钮
     */
    void createButtons();
    
    /**
     * @brief 设置回退按钮回调
     * @param callback 回调函数
     */
    void setUndoButtonCallback(const std::function<void()>& callback);
    
    /**
     * @brief 设置回退按钮启用状态
     * @param enabled 是否启用
     */
    void setUndoButtonEnabled(bool enabled);

    void setRestartButtonCallback(const std::function<void()>& callback);
    
private:
    StackView* _stackView;              // 手牌区视图
    PlayFieldView* _playFieldView;      // 桌面牌区视图
    cocos2d::ui::Button* _undoButton;   // 回退按钮
    cocos2d::ui::Button* _restartButton;
    std::function<void()> _undoCallback; // 回退回调
    std::function<void()> _restartCallback;
    
    /**
     * @brief 创建背景
     */
    void createBackground();
};