#pragma once
#include "CardModel.h"
#include <vector>
#include <unordered_map>

/**
 * @brief 游戏数据模型，管理整个游戏的状态和数据
 * @details 包含桌面牌区、手牌区、当前顶部牌等游戏状态
 */
class GameModel {
public:
    GameModel();
    
    // 卡牌管理
    void addCardToPlayField(CardModel* card);
    void addCardToHandArea(CardModel* card);
    CardModel* getTopHandCard() const;
    CardModel* getCardById(int cardId) const;
    
    // 游戏状态
    void setTopHandCard(CardModel* card);
    void removeCardFromPlayField(int cardId);
    
    // 获取数据
    const std::vector<CardModel*>& getPlayFieldCards() const { return _playFieldCards; }
    const std::vector<CardModel*>& getHandAreaCards() const { return _handAreaCards; }
    
private:
    std::vector<CardModel*> _playFieldCards;    // 桌面牌区的卡牌
    std::vector<CardModel*> _handAreaCards;     // 手牌区的卡牌
    CardModel* _topHandCard;                    // 手牌区顶部牌
    std::unordered_map<int, CardModel*> _allCards; // 所有卡牌的映射
};