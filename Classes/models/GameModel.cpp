#include "GameModel.h"

GameModel::GameModel() : _topHandCard(nullptr) {
}

void GameModel::addCardToPlayField(CardModel* card) {
    _playFieldCards.push_back(card);
    _allCards[card->getId()] = card;
}

void GameModel::addCardToHandArea(CardModel* card) {
    card->setInHandArea(true);
    _handAreaCards.push_back(card);
    _allCards[card->getId()] = card;
    
    // 设置顶部牌
    if (!_topHandCard) {
        _topHandCard = card;
    }
}

CardModel* GameModel::getTopHandCard() const {
    return _topHandCard;
}

CardModel* GameModel::getCardById(int cardId) const {
    auto it = _allCards.find(cardId);
    return it != _allCards.end() ? it->second : nullptr;
}

void GameModel::setTopHandCard(CardModel* card) {
    _topHandCard = card;
    if (card) {
        card->setInHandArea(true);
    }
}

void GameModel::removeCardFromPlayField(int cardId) {
    for (auto it = _playFieldCards.begin(); it != _playFieldCards.end(); ++it) {
        if ((*it)->getId() == cardId) {
            _playFieldCards.erase(it);
            break;
        }
    }
}