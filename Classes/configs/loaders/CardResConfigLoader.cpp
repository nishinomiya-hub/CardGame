#include "CardResConfigLoader.h"
#include "configs/models/CardResConfig.h"
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

bool CardResConfigLoader::loadConfig(const std::string& configFile) {
    // 读取配置文件
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(configFile);
    std::string jsonContent = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (jsonContent.empty()) {
        CCLOG("Failed to load card resource config file: %s", configFile.c_str());
        // 如果配置文件不存在，使用默认配置
        CardResConfig::init();
        return true;
    }
    
    bool result = parseJson(jsonContent);
    
    // 如果解析失败，使用默认配置
    if (!result) {
        CCLOG("Failed to parse card resource config, using default config");
        CardResConfig::init();
    }
    
    return result;
}

bool CardResConfigLoader::parseJson(const std::string& jsonContent) {
    rapidjson::Document document;
    document.Parse(jsonContent.c_str());
    
    if (document.HasParseError()) {
        CCLOG("JSON parse error in card resource config");
        return false;
    }
    
    // 这里可以根据JSON配置自定义资源路径
    // 目前使用硬编码的默认路径，如果需要可扩展
    
    CardResConfig::init();
    return true;
}