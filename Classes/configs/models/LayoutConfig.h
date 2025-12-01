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
    // 卡牌相关尺寸
    // ==============================
    
    /// @brief 卡牌尺寸 (宽x高)
    static const cocos2d::Size CARD_SIZE;
    
    /// @brief 卡牌选中状态放大比例
    static const float CARD_SELECTED_SCALE;
    
    /// @brief 卡牌正常状态比例
    static const float CARD_NORMAL_SCALE;
    
    // ==============================
    // 间距和边距配置
    // ==============================
    
    /// @brief 卡牌之间的水平间距
    static const float CARD_HORIZONTAL_SPACING;
    
    /// @brief 卡牌之间的垂直间距
    static const float CARD_VERTICAL_SPACING;
    
    /// @brief 区域内部边距
    static const float FIELD_INNER_MARGIN;
    
    /// @brief 屏幕安全边距（避免刘海屏等遮挡）
    static const float SCREEN_SAFE_MARGIN;
    
    // ==============================
    // 动画相关配置
    // ==============================
    
    /// @brief 卡牌移动动画时长（秒）
    static const float CARD_MOVE_DURATION;
    
    /// @brief 卡牌翻转动画时长（秒）
    static const float CARD_FLIP_DURATION;
    
    /// @brief 匹配成功动画时长（秒）
    static const float MATCH_ANIMATION_DURATION;
    
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
     * @brief 获取手牌区中指定索引卡牌的位置
     * @param index 卡牌索引（0为顶部牌）
     * @param totalCards 总卡牌数量
     * @return 卡牌在堆牌区中的位置
     */
    static cocos2d::Vec2 getCardPositionInStack(int index, int totalCards);
    
    /**
     * @brief 获取桌面牌区中指定行列的卡牌位置
     * @param row 行索引
     * @param column 列索引
     * @param totalRows 总行数
     * @param totalColumns 总列数
     * @return 卡牌在桌面牌区中的位置
     */
    static cocos2d::Vec2 getCardPositionInPlayField(int row, int column, int totalRows, int totalColumns);
    
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
    
    /**
     * @brief 获取屏幕中心位置
     * @return 屏幕中心坐标
     */
    static cocos2d::Vec2 getScreenCenter();
    
    /**
     * @brief 获取屏幕左上角位置（考虑安全区域）
     * @return 屏幕左上角坐标
     */
    static cocos2d::Vec2 getScreenTopLeft();
    
    /**
     * @brief 获取屏幕右上角位置（考虑安全区域）
     * @return 屏幕右上角坐标
     */
    static cocos2d::Vec2 getScreenTopRight();
    
    /**
     * @brief 获取屏幕左下角位置（考虑安全区域）
     * @return 屏幕左下角坐标
     */
    static cocos2d::Vec2 getScreenBottomLeft();
    
    /**
     * @brief 获取屏幕右下角位置（考虑安全区域）
     * @return 屏幕右下角坐标
     */
    static cocos2d::Vec2 getScreenBottomRight();
    
    // ==============================
    // 适配相关方法
    // ==============================
    
    /**
     * @brief 获取设计分辨率到实际屏幕的缩放因子
     * @return 缩放比例
     */
    static float getScaleFactor();
    
    /**
     * @brief 将设计分辨率尺寸适配到当前屏幕
     * @param designSize 设计分辨率下的尺寸
     * @return 适配后的尺寸
     */
    static cocos2d::Size getAdaptedSize(const cocos2d::Size& designSize);
    
    /**
     * @brief 将设计分辨率位置适配到当前屏幕
     * @param designPosition 设计分辨率下的位置
     * @return 适配后的位置
     */
    static cocos2d::Vec2 getAdaptedPosition(const cocos2d::Vec2& designPosition);
    
    /**
     * @brief 获取适配后的卡牌尺寸
     * @return 根据屏幕适配的卡牌尺寸
     */
    static cocos2d::Size getAdaptedCardSize();
    
    // ==============================
    // 布局验证方法
    // ==============================
    
    /**
     * @brief 验证布局配置是否有效
     * @return 配置有效返回true，否则返回false
     */
    static bool validateLayoutConfig();
    
    /**
     * @brief 打印当前布局配置信息（调试用）
     */
    static void printLayoutInfo();
    
private:
    /// @brief 禁止实例化
    LayoutConfig() = delete;
    ~LayoutConfig() = delete;
};
