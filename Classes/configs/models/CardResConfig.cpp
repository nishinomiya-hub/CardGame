#include "CardResConfig.h"

std::string CardResConfig::_cardGeneralImage = "cards/card_general.png";
std::string CardResConfig::_cardBackImage = "cards/card_back.png";
std::unordered_map<int, std::string> CardResConfig::_suitImageMap;
std::unordered_map<std::string, std::string> CardResConfig::_numberImageMap;

void CardResConfig::init() {
    // 初始化花色图片映射
    _suitImageMap[static_cast<int>(CardModel::Suit::CLUBS)] = "cards/suits/club.png";
    _suitImageMap[static_cast<int>(CardModel::Suit::DIAMONDS)] = "cards/suits/diamond.png";
    _suitImageMap[static_cast<int>(CardModel::Suit::HEARTS)] = "cards/suits/heart.png";
    _suitImageMap[static_cast<int>(CardModel::Suit::SPADES)] = "cards/suits/spade.png";
    
    // 初始化数字图片映射
    const char* numbers[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    for (int i = 0; i < 13; ++i) {
        int number = i + 1;
        
        // 黑色大号数字
        std::string keyBlackBig = generateNumberKey(number, false, true);
        _numberImageMap[keyBlackBig] = "cards/numbers/big_black_" + std::string(numbers[i]) + ".png";
        
        // 黑色小号数字
        std::string keyBlackSmall = generateNumberKey(number, false, false);
        _numberImageMap[keyBlackSmall] = "cards/numbers/small_black_" + std::string(numbers[i]) + ".png";
        
        // 红色大号数字
        std::string keyRedBig = generateNumberKey(number, true, true);
        _numberImageMap[keyRedBig] = "cards/numbers/big_red_" + std::string(numbers[i]) + ".png";
        
        // 红色小号数字
        std::string keyRedSmall = generateNumberKey(number, true, false);
        _numberImageMap[keyRedSmall] = "cards/numbers/small_red_" + std::string(numbers[i]) + ".png";
    }
}

std::string CardResConfig::getCardGeneralImage() {
    return _cardGeneralImage;
}

std::string CardResConfig::getSuitImage(CardModel::Suit suit) {
    int suitIndex = static_cast<int>(suit);
    auto it = _suitImageMap.find(suitIndex);
    if (it != _suitImageMap.end()) {
        return it->second;
    }
    return "";
}

std::string CardResConfig::getBigNumberImage(int number, CardModel::Suit suit) {
    bool isRed = isRedSuit(suit);
    std::string key = generateNumberKey(number, isRed, true);
    auto it = _numberImageMap.find(key);
    if (it != _numberImageMap.end()) {
        return it->second;
    }
    return "";
}

std::string CardResConfig::getSmallNumberImage(int number, CardModel::Suit suit) {
    bool isRed = isRedSuit(suit);
    std::string key = generateNumberKey(number, isRed, false);
    auto it = _numberImageMap.find(key);
    if (it != _numberImageMap.end()) {
        return it->second;
    }
    return "";
}

std::string CardResConfig::getCardBackImage() {
    return _cardBackImage;
}

bool CardResConfig::isRedSuit(CardModel::Suit suit) {
    return suit == CardModel::Suit::HEARTS || suit == CardModel::Suit::DIAMONDS;
}

std::string CardResConfig::generateNumberKey(int number, bool isRed, bool isBig) {
    std::string key = "";
    key += (isBig ? "big_" : "small_");
    key += (isRed ? "red_" : "black_");
    key += std::to_string(number);
    return key;
}