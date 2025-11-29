#pragma once

#include "cocos2d.h"
#include <functional>

/**
 * @brief 卡牌视图类
 * @details 负责单张卡牌的显示和交互，包括正面、背面、动画效果
 */
class CardView : public cocos2d::Sprite {
public:
    /**
     * @brief 创建卡牌视图
     * @return 卡牌视图指针
     */
    static CardView* create();
    
    /**
     * @brief 初始化卡牌视图
     * @return 初始化成功返回true
     */
    virtual bool init() override;
    
    /**
     * @brief 显示指定ID的卡牌
     * @param cardId 卡牌ID
     * @param number 点数(1-13)
     * @param suit 花色
     * @param isFaceUp 是否正面朝上
     */
    void displayCard(int cardId, int number, int suit, bool isFaceUp);
    
    /**
     * @brief 播放移动动画
     * @param targetPos 目标位置
     * @param duration 动画时长
     * @param callback 动画完成回调
     */
    void playMoveAnimation(const cocos2d::Vec2& targetPos, float duration, 
                          const std::function<void()>& callback = nullptr);
    
    /**
     * @brief 设置触摸回调
     * @param callback 触摸回调函数
     */
    void setTouchCallback(const std::function<void(int)>& callback);
    
    /**
     * @brief 获取卡牌ID
     * @return 卡牌ID
     */
    int getCardId() const { return _cardId; }
    
    /**
     * @brief 设置是否可触摸
     * @param enabled 是否可触摸
     */
    void setTouchEnabled(bool enabled);
    
private:
    int _cardId;                                    // 卡牌ID
    cocos2d::Sprite* _cardBase;                     // 卡牌底板
    cocos2d::Sprite* _suitSprite;                   // 花色图标
    cocos2d::Sprite* _bigNumberSprite;              // 大号数字
    cocos2d::Sprite* _smallNumberTopLeft;           // 左上角小号数字
    cocos2d::Sprite* _smallNumberBottomRight;       // 右下角小号数字
    cocos2d::Sprite* _cardBack;                     // 卡牌背面
    std::function<void(int)> _touchCallback;        // 触摸回调
    bool _touchEnabled;                             // 是否可触摸
    
    /**
     * @brief 设置触摸监听
     */
    void setupTouchListener();
    
    /**
     * @brief 显示正面
     */
    void showFrontFace(int number, int suit);
    
    /**
     * @brief 显示背面
     */
    void showBackFace();
};