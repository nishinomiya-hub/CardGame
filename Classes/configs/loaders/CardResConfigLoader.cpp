#include "CardResConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

bool CardResConfigLoader::loadFromFile(const std::string& filePath, CardResConfig& outConfig)
{
    // 读取文件内容
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    std::string jsonString = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (jsonString.empty())
    {
        CCLOG("CardResConfigLoader: Failed to read file: %s", filePath.c_str());
        return false;
    }
    
    return loadFromString(jsonString, outConfig);
}

bool CardResConfigLoader::loadFromString(const std::string& jsonString, CardResConfig& outConfig)
{
    // 解析JSON
    rapidjson::Document doc;
    doc.Parse(jsonString.c_str());
    
    if (doc.HasParseError())
    {
        CCLOG("CardResConfigLoader: JSON parse error at offset %zu: %d", 
              doc.GetErrorOffset(), doc.GetParseError());
        return false;
    }
    
    // 清空配置
    outConfig.clear();
    
    // 解析底层图片
    if (doc.HasMember("CardBase") && doc["CardBase"].IsString())
    {
        outConfig.setCardBaseImagePath(doc["CardBase"].GetString());
    }
    
    // 解析卡牌背面图片
    if (doc.HasMember("CardBack") && doc["CardBack"].IsString())
    {
        outConfig.setCardBackImagePath(doc["CardBack"].GetString());
    }
    
    // TODO: 根据实际JSON格式解析其他配置
    
    CCLOG("CardResConfigLoader: Successfully loaded card resource config");
    return true;
}

void CardResConfigLoader::loadWithDefaultRules(CardResConfig& outConfig, const std::string& imageFolder)
{
    outConfig.clear();
    
    // 设置通用底层图片
    outConfig.setCardBaseImagePath(imageFolder + "card_general.png");
    
    // 设置卡牌背面图片
    //outConfig.setCardBackImagePath(imageFolder + "card_back.png");
    
    // 设置花色图片
    std::string suitFolders = imageFolder + "suits/";
    outConfig.setSuitImagePath(CST_CLUBS, suitFolders + "club.png");
    outConfig.setSuitImagePath(CST_DIAMONDS, suitFolders + "diamond.png");
    outConfig.setSuitImagePath(CST_HEARTS, suitFolders + "heart.png");
    outConfig.setSuitImagePath(CST_SPADES, suitFolders + "spade.png");
    
    // 设置所有点数的大数字和小数字图片
    std::string numberFolders = imageFolder + "number/";
    for (int f = CFT_ACE; f < CFT_NUM_CARD_FACE_TYPES; ++f)
    {
        CardFaceType face = static_cast<CardFaceType>(f);
        std::string faceName = getFaceFileName(face);
        
        // 黑色数字(梅花、黑桃)
        outConfig.setBigNumberImagePath(face, false, 
            numberFolders + "big_black_" + faceName + ".png");
        outConfig.setSmallNumberImagePath(face, false, 
            numberFolders + "small_black_" + faceName + ".png");
        
        // 红色数字(红桃、方块)
        outConfig.setBigNumberImagePath(face, true, 
            numberFolders + "big_red_" + faceName + ".png");
        outConfig.setSmallNumberImagePath(face, true, 
            numberFolders + "small_red_" + faceName + ".png");
    }
    
    CCLOG("CardResConfigLoader: Initialized with default rules, folder: %s", imageFolder.c_str());
}

std::string CardResConfigLoader::getSuitFileName(CardSuitType suit)
{
    switch (suit)
    {
        case CST_CLUBS:    return "club";
        case CST_DIAMONDS: return "diamond";
        case CST_HEARTS:   return "heart";
        case CST_SPADES:   return "spade";
        default:           return "unknown";
    }
}

std::string CardResConfigLoader::getFaceFileName(CardFaceType face)
{
    switch (face)
    {
        case CFT_ACE:   return "A";
        case CFT_TWO:   return "2";
        case CFT_THREE: return "3";
        case CFT_FOUR:  return "4";
        case CFT_FIVE:  return "5";
        case CFT_SIX:   return "6";
        case CFT_SEVEN: return "7";
        case CFT_EIGHT: return "8";
        case CFT_NINE:  return "9";
        case CFT_TEN:   return "10";
        case CFT_JACK:  return "J";
        case CFT_QUEEN: return "Q";
        case CFT_KING:  return "K";
        default:        return "unknown";
    }
}

bool CardResConfigLoader::isRedSuit(CardSuitType suit)
{
    return (suit == CST_HEARTS || suit == CST_DIAMONDS);
}