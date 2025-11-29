#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"

USING_NS_CC;

bool LevelConfigLoader::loadFromFile(const std::string& filePath, LevelConfig& outConfig)
{
    // 读取文件内容
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    std::string jsonString = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (jsonString.empty())
    {
        CCLOG("LevelConfigLoader: Failed to read file: %s", filePath.c_str());
        return false;
    }
    
    return loadFromString(jsonString, outConfig);
}

bool LevelConfigLoader::loadFromString(const std::string& jsonString, LevelConfig& outConfig)
{
    // 解析JSON
    rapidjson::Document doc;
    doc.Parse(jsonString.c_str());
    
    if (doc.HasParseError())
    {
        CCLOG("LevelConfigLoader: JSON parse error at offset %zu: %d", 
              doc.GetErrorOffset(), doc.GetParseError());
        return false;
    }
    
    // 清空配置
    outConfig.clear();
    
    // 解析Playfield数组
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfieldArray = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); i++)
        {
            CardConfigData cardData;
            if (parseCardData(playfieldArray[i], cardData))
            {
                outConfig.addPlayfieldCard(cardData);
            }
            else
            {
                CCLOG("LevelConfigLoader: Failed to parse Playfield card at index %u", i);
            }
        }
    }
    
    // 解析Stack数组
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stackArray = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stackArray.Size(); i++)
        {
            CardConfigData cardData;
            if (parseCardData(stackArray[i], cardData))
            {
                outConfig.addStackCard(cardData);
            }
            else
            {
                CCLOG("LevelConfigLoader: Failed to parse Stack card at index %u", i);
            }
        }
    }
    
    CCLOG("LevelConfigLoader: Successfully loaded config with %zu playfield cards and %zu stack cards",
          outConfig.getPlayfieldCards().size(), outConfig.getStackCards().size());
    
    return true;
}

bool LevelConfigLoader::parseCardData(const rapidjson::Value& cardJson, CardConfigData& outCardData)
{
    if (!cardJson.IsObject())
    {
        return false;
    }
    
    // 解析CardFace
    if (cardJson.HasMember("CardFace") && cardJson["CardFace"].IsInt())
    {
        int faceValue = cardJson["CardFace"].GetInt();
        outCardData.cardFace = intToCardFace(faceValue);
    }
    else
    {
        CCLOG("LevelConfigLoader: Missing or invalid CardFace");
        return false;
    }
    
    // 解析CardSuit
    if (cardJson.HasMember("CardSuit") && cardJson["CardSuit"].IsInt())
    {
        int suitValue = cardJson["CardSuit"].GetInt();
        outCardData.cardSuit = intToCardSuit(suitValue);
    }
    else
    {
        CCLOG("LevelConfigLoader: Missing or invalid CardSuit");
        return false;
    }
    
    // 解析Position
    if (cardJson.HasMember("Position") && cardJson["Position"].IsObject())
    {
        const rapidjson::Value& posJson = cardJson["Position"];
        if (posJson.HasMember("x") && posJson.HasMember("y") &&
            posJson["x"].IsNumber() && posJson["y"].IsNumber())
        {
            float x = posJson["x"].GetFloat();
            float y = posJson["y"].GetFloat();
            outCardData.position = Vec2(x, y);
        }
        else
        {
            CCLOG("LevelConfigLoader: Invalid Position object");
            return false;
        }
    }
    else
    {
        CCLOG("LevelConfigLoader: Missing or invalid Position");
        return false;
    }
    
    return true;
}

CardFaceType LevelConfigLoader::intToCardFace(int faceValue)
{
    if (faceValue >= 0 && faceValue < CFT_NUM_CARD_FACE_TYPES)
    {
        return static_cast<CardFaceType>(faceValue);
    }
    
    CCLOG("LevelConfigLoader: Invalid CardFace value: %d", faceValue);
    return CFT_NONE;
}

CardSuitType LevelConfigLoader::intToCardSuit(int suitValue)
{
    if (suitValue >= 0 && suitValue < CST_NUM_CARD_SUIT_TYPES)
    {
        return static_cast<CardSuitType>(suitValue);
    }
    
    CCLOG("LevelConfigLoader: Invalid CardSuit value: %d", suitValue);
    return CST_NONE;
}