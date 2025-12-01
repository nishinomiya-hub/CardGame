#pragma once

#include "cocos2d.h"

class LayoutConfig {
public:
    // ==============================
    // 设计分辨率相关
    // ==============================
    
    /// @brief 设计分辨率
    static const cocos2d::Size DESIGN_RESOLUTION;
    
    /// @brief 窗口大小
    static const cocos2d::Size WINDOW_SIZE;
    
    // ==============================
    // 游戏区域尺寸
    // ==============================
    
    /// @brief 主牌区尺寸 (1080x1500)
    static const cocos2d::Size MAIN_FIELD_SIZE;
    
    /// @brief 堆牌区尺寸 (1080x580)
    static const cocos2d::Size STACK_FIELD_SIZE;
    
    /// @brief 游戏区域总尺寸
    static const cocos2d::Size TOTAL_GAME_AREA_SIZE;
    
    

    
    // ==============================
    // UI元素尺寸
    // ==============================
    
    /// @brief 回退按钮尺寸
    static const cocos2d::Size UNDO_BUTTON_SIZE;
    
    /// @brief 重新开始按钮尺寸
    static const cocos2d::Size RESTART_BUTTON_SIZE;
    
    /// @brief 按钮间距
    static const float BUTTON_SPACING;
    
    // ==============================
    // 位置计算方法
    // ==============================
    
    /**
     * @brief 获取主牌区位置
     * @return 主牌区在屏幕中的中心位置
     */
    static cocos2d::Vec2 getMainFieldPosition();
    
    /**
     * @brief 获取堆牌区位置
     * @return 堆牌区在屏幕中的中心位置
     */
    static cocos2d::Vec2 getStackFieldPosition();
    
    
    /**
     * @brief 获取回退按钮位置
     * @return 回退按钮在屏幕中的位置
     */
    static cocos2d::Vec2 getUndoButtonPosition();
    
    /**
     * @brief 获取重新开始按钮位置
     * @return 重新开始按钮在屏幕中的位置
     */
    static cocos2d::Vec2 getRestartButtonPosition();
    
    
private:
    /// @brief 禁止实例化
    LayoutConfig() = delete;
    ~LayoutConfig() = delete;
};
