#include "CardResConfig.h"

CardResConfig::CardResConfig()
    : _cardBaseImage("")
    , _cardBackImagePath("")
{
}

CardResConfig::~CardResConfig()
{
}

CardLayerImages CardResConfig::getCardLayerImages(CardSuitType suit, CardFaceType face) const
{
    CardLayerImages layers;
    
    // 设置底层图片
    layers.baseImage = _cardBaseImage;
    
    // 设置花色图片
    auto suitIt = _suitImages.find(suit);
    if (suitIt != _suitImages.end())
    {
        layers.suitImage = suitIt->second;
    }
    
    // 判断是否红色花色
    bool isRed = isRedSuit(suit);
    int numberKey = generateNumberKey(face, isRed);
    
    // 设置大数字图片
    auto bigIt = _bigNumberImages.find(numberKey);
    if (bigIt != _bigNumberImages.end())
    {
        layers.bigNumberImage = bigIt->second;
    }
    
    // 设置小数字图片
    auto smallIt = _smallNumberImages.find(numberKey);
    if (smallIt != _smallNumberImages.end())
    {
        layers.smallNumberImage = smallIt->second;
    }
    
    return layers;
}

std::string CardResConfig::getCardBackImagePath() const
{
    return _cardBackImagePath;
}

void CardResConfig::setCardBaseImagePath(const std::string& imagePath)
{
    _cardBaseImage = imagePath;
}

void CardResConfig::setSuitImagePath(CardSuitType suit, const std::string& imagePath)
{
    _suitImages[suit] = imagePath;
}

void CardResConfig::setBigNumberImagePath(CardFaceType face, bool isRed, const std::string& imagePath)
{
    int key = generateNumberKey(face, isRed);
    _bigNumberImages[key] = imagePath;
}

void CardResConfig::setSmallNumberImagePath(CardFaceType face, bool isRed, const std::string& imagePath)
{
    int key = generateNumberKey(face, isRed);
    _smallNumberImages[key] = imagePath;
}

void CardResConfig::setCardBackImagePath(const std::string& imagePath)
{
    _cardBackImagePath = imagePath;
}

void CardResConfig::clear()
{
    _cardBaseImage = "";
    _suitImages.clear();
    _bigNumberImages.clear();
    _smallNumberImages.clear();
    _cardBackImagePath = "";
}

bool CardResConfig::isRedSuit(CardSuitType suit) const
{
    return (suit == CST_HEARTS || suit == CST_DIAMONDS);
}

int CardResConfig::generateNumberKey(CardFaceType face, bool isRed) const
{
    // 使用公式: face * 10 + (isRed ? 1 : 0)
    return static_cast<int>(face) * 10 + (isRed ? 1 : 0);
}