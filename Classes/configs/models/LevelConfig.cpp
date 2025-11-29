#include "LevelConfig.h"

LevelConfig::LevelConfig() {
}

void LevelConfig::addPlayFieldCard(const CardConfig& card) {
    _playFieldCards.push_back(card);
}

void LevelConfig::addStackCard(const CardConfig& card) {
    _stackCards.push_back(card);
}

CardModel::Suit LevelConfig::convertSuit(int suitType) {
    // CST_CLUBS = 0 -> CLUBS
    // CST_DIAMONDS = 1 -> DIAMONDS  
    // CST_HEARTS = 2 -> HEARTS
    // CST_SPADES = 3 -> SPADES
    
    switch (suitType) {
        case 0: return CardModel::Suit::CLUBS;
        case 1: return CardModel::Suit::DIAMONDS;
        case 2: return CardModel::Suit::HEARTS;
        case 3: return CardModel::Suit::SPADES;
        default: return CardModel::Suit::CLUBS;
    }
}