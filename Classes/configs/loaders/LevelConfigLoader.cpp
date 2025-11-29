#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

LevelConfig* LevelConfigLoader::loadLevel(int levelId) {
    std::string filePath = getLevelFilePath(levelId);
    return loadFromFile(filePath);
}

LevelConfig* LevelConfigLoader::loadFromFile(const std::string& filePath) {
    // 读取文件内容
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    std::string jsonContent = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (jsonContent.empty()) {
        CCLOG("Failed to load level config file: %s", filePath.c_str());
        return nullptr;
    }
    
    return parseJson(jsonContent);
}

LevelConfig* LevelConfigLoader::parseJson(const std::string& jsonContent) {
    // 使用RapidJSON解析
    rapidjson::Document document;
    document.Parse(jsonContent.c_str());
    
    if (document.HasParseError()) {
        CCLOG("JSON parse error");
        return nullptr;
    }
    
    LevelConfig* config = new LevelConfig();
    
    // 解析Playfield数组
    if (document.HasMember("Playfield") && document["Playfield"].IsArray()) {
        const rapidjson::Value& playfield = document["Playfield"];
        
        for (rapidjson::SizeType i = 0; i < playfield.Size(); ++i) {
            const rapidjson::Value& card = playfield[i];
            
            if (card.HasMember("CardFace") && card.HasMember("CardSuit") && card.HasMember("Position")) {
                int face = card["CardFace"].GetInt();
                int suit = card["CardSuit"].GetInt();
                
                const rapidjson::Value& pos = card["Position"];
                float x = pos["x"].GetFloat();
                float y = pos["y"].GetFloat();
                
                CardConfig cardConfig(face, suit, x, y);
                config->addPlayFieldCard(cardConfig);
            }
        }
    }
    
    // 解析Stack数组
    if (document.HasMember("Stack") && document["Stack"].IsArray()) {
        const rapidjson::Value& stack = document["Stack"];
        
        for (rapidjson::SizeType i = 0; i < stack.Size(); ++i) {
            const rapidjson::Value& card = stack[i];
            
            if (card.HasMember("CardFace") && card.HasMember("CardSuit") && card.HasMember("Position")) {
                int face = card["CardFace"].GetInt();
                int suit = card["CardSuit"].GetInt();
                
                const rapidjson::Value& pos = card["Position"];
                float x = pos["x"].GetFloat();
                float y = pos["y"].GetFloat();
                
                CardConfig cardConfig(face, suit, x, y);
                config->addStackCard(cardConfig);
            }
        }
    }
    
    return config;
}

std::string LevelConfigLoader::getLevelFilePath(int levelId) {
    return "configs/level_" + std::to_string(levelId) + ".json";
}