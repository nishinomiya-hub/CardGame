#pragma once

#include "CardView.h"
#include <vector>

/**
 * @brief 桌面牌区视图
 * @details 管理桌面牌区的卡牌显示和布局
 */
class PlayFieldView : public cocos2d::Node {
public:
    /**
     * @brief 创建桌面牌区视图
     * @return 桌面牌区视图指针
     */
    static PlayFieldView* create();
    
    /**
     * @brief 初始化桌面牌区视图
     * @return 初始化成功返回true
     */
    virtual bool init() override;
    
    /**
     * @brief 添加卡牌视图
     * @param cardView 卡牌视图指针
     * @param position 初始位置
     */
    void addCardView(CardView* cardView, const cocos2d::Vec2& position);
    
    /**
     * @brief 根据卡牌ID获取卡牌视图
     * @param cardId 卡牌ID
     * @return 卡牌视图指针，未找到返回nullptr
     */
    CardView* getCardViewById(int cardId);
    
    /**
     * @brief 移除卡牌视图
     * @param cardId 卡牌ID
     */
    void removeCardView(int cardId);
    
    /**
     * @brief 播放卡牌移动到手牌区动画
     * @param cardId 卡牌ID
     * @param targetPos 目标位置
     * @param callback 动画完成回调
     */
    void playCardToHandAnimation(int cardId, const cocos2d::Vec2& targetPos, 
                                 const std::function<void()>& callback = nullptr);
    
private:
    std::vector<CardView*> _cardViews;  // 所有卡牌视图
};
