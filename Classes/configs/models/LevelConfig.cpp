#include "LevelConfig.h"

const std::vector<CardConfigData>& LevelConfig::getPlayfieldCards() const
{
    return _playfieldCards;
}

const std::vector<CardConfigData>& LevelConfig::getStackCards() const
{
    return _stackCards;
}

void LevelConfig::setPlayfieldCards(const std::vector<CardConfigData>& cards)
{
    _playfieldCards = cards;
}

void LevelConfig::setStackCards(const std::vector<CardConfigData>& cards)
{
    _stackCards = cards;
}

void LevelConfig::addPlayfieldCard(const CardConfigData& cardData)
{
    _playfieldCards.push_back(cardData);
}

void LevelConfig::addStackCard(const CardConfigData& cardData)
{
    _stackCards.push_back(cardData);
}

void LevelConfig::clear()
{
    _playfieldCards.clear();
    _stackCards.clear();
}