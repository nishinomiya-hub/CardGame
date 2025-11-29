#pragma once

#include <vector>
#include "cocos2d.h"
#include "models/CardModel.h"

/**
 * @brief 单张卡牌的配置信息
 */
struct CardConfig {
    int cardFace;           // 卡牌点数 (1-13, 对应A-K)
    int cardSuit;           // 花色 (0-3, 对应枚举CardSuitType)
    cocos2d::Vec2 position; // 位置坐标
    
    CardConfig() : cardFace(0), cardSuit(0), position(0, 0) {}
    CardConfig(int face, int suit, float x, float y) 
        : cardFace(face), cardSuit(suit), position(x, y) {}
};

/**
 * @brief 关卡配置数据模型
 * @details 定义关卡的初始布局，包括桌面牌区和手牌区的卡牌配置
 */
class LevelConfig {
public:
    LevelConfig();
    
    // 添加卡牌配置
    void addPlayFieldCard(const CardConfig& card);
    void addStackCard(const CardConfig& card);
    
    // 获取配置数据
    const std::vector<CardConfig>& getPlayFieldCards() const { return _playFieldCards; }
    const std::vector<CardConfig>& getStackCards() const { return _stackCards; }
    
    // 转换花色枚举
    static CardModel::Suit convertSuit(int suitType);
    
private:
    std::vector<CardConfig> _playFieldCards;  // 桌面牌区卡牌配置
    std::vector<CardConfig> _stackCards;      // 手牌区卡牌配置
};