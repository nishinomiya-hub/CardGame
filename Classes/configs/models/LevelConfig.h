#pragma once

#include "cocos2d.h"
#include "CardTypes.h"
#include <vector>


/**
 * @struct CardConfigData
 * @brief 单张卡牌的配置数据
 */
struct CardConfigData
{
    CardFaceType cardFace;      // 卡牌点数
    CardSuitType cardSuit;      // 卡牌花色
    cocos2d::Vec2 position;     // 卡牌位置
    
    CardConfigData()
        : cardFace(CFT_NONE)
        , cardSuit(CST_NONE)
        , position(cocos2d::Vec2::ZERO)
    {}
    
    CardConfigData(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& pos)
        : cardFace(face)
        , cardSuit(suit)
        , position(pos)
    {}
};

/**
 * @class LevelConfig
 * @brief 关卡配置类,包含桌面牌区和手牌区的初始配置
 */
class LevelConfig
{
public:
    
    /**
     * @brief 获取桌面牌区配置列表
     * @return 桌面牌区卡牌配置列表
     */
    const std::vector<CardConfigData>& getPlayfieldCards() const;
    
    /**
     * @brief 获取手牌区配置列表
     * @return 手牌区卡牌配置列表
     */
    const std::vector<CardConfigData>& getStackCards() const;
    
    /**
     * @brief 设置桌面牌区配置列表
     * @param cards 桌面牌区卡牌配置列表
     */
    void setPlayfieldCards(const std::vector<CardConfigData>& cards);
    
    /**
     * @brief 设置手牌区配置列表
     * @param cards 手牌区卡牌配置列表
     */
    void setStackCards(const std::vector<CardConfigData>& cards);
    
    /**
     * @brief 添加桌面牌区卡牌
     * @param cardData 卡牌配置数据
     */
    void addPlayfieldCard(const CardConfigData& cardData);
    
    /**
     * @brief 添加手牌区卡牌
     * @param cardData 卡牌配置数据
     */
    void addStackCard(const CardConfigData& cardData);
    
    /**
     * @brief 清空所有配置
     */
    void clear();
    
private:
    std::vector<CardConfigData> _playfieldCards;  // 桌面牌区配置列表
    std::vector<CardConfigData> _stackCards;      // 手牌区配置列表
};