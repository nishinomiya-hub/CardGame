#pragma once

#include "CardView.h"
#include <vector>

/**
 * @brief 手牌区视图
 * @details 管理手牌区的卡牌显示和布局
 */
class StackView : public cocos2d::Node {
public:
    /**
     * @brief 创建手牌区视图
     * @return 手牌区视图指针
     */
    static StackView* create();
    
    /**
     * @brief 初始化手牌区视图
     * @return 初始化成功返回true
     */
    virtual bool init() override;
    
    /**
     * @brief 添加卡牌视图
     * @param cardView 卡牌视图指针
     */
    void addCardView(CardView* cardView);
    
    /**
     * @brief 根据卡牌ID获取卡牌视图
     * @param cardId 卡牌ID
     * @return 卡牌视图指针，未找到返回nullptr
     */
    CardView* getCardViewById(int cardId);
    
    /**
     * @brief 更新手牌区布局
     */
    void updateLayout();
    
    /**
     * @brief 播放卡牌替换动画
     * @param cardId 要替换的卡牌ID
     * @param callback 动画完成回调
     */
    void playCardReplaceAnimation(int cardId, const std::function<void()>& callback = nullptr);
    
    /**
     * @brief 获取顶部卡牌位置
     * @return 顶部卡牌位置
     */
    cocos2d::Vec2 getTopCardPosition() const;
    
private:
    std::vector<CardView*> _cardViews;  // 所有卡牌视图
    float _cardOffsetX;                 // 卡牌偏移量
    float _topCardGap;                  // 顶牌和手牌堆的间距
    cocos2d::Vec2 _stackBasePos;        // 手牌堆基准位置
    
    /**
     * @brief 计算卡牌位置
     * @param index 卡牌索引
     * @return 卡牌位置
     */
    cocos2d::Vec2 calculateCardPosition(int index) const;
};