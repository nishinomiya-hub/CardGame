#pragma once

#include "configs/models/LevelConfig.h"
#include "json/document.h"
#include <string>

/**
 * @file LevelConfigLoader.h
 * @brief 关卡配置加载器,负责从JSON文件加载关卡配置
 */

/**
 * @class LevelConfigLoader
 * @brief 关卡配置加载器类,提供静态方法加载关卡配置
 */
class LevelConfigLoader
{
public:
    /**
     * @brief 从JSON文件加载关卡配置
     * @param filePath JSON配置文件路径
     * @param outConfig 输出的关卡配置对象
     * @return 加载是否成功
     */
    static bool loadFromFile(const std::string& filePath, LevelConfig& outConfig);
    
    /**
     * @brief 从JSON字符串加载关卡配置
     * @param jsonString JSON配置字符串
     * @param outConfig 输出的关卡配置对象
     * @return 解析是否成功
     */
    static bool loadFromString(const std::string& jsonString, LevelConfig& outConfig);
    
private:
    /**
     * @brief 解析单张卡牌配置
     * @param cardJson 卡牌JSON对象
     * @param outCardData 输出的卡牌配置数据
     * @return 解析是否成功
     */
    static bool parseCardData(const rapidjson::Value& cardJson, CardConfigData& outCardData);
    
    /**
     * @brief 将整数转换为CardFaceType
     * @param faceValue 点数整数值
     * @return 对应的CardFaceType枚举值
     */
    static CardFaceType intToCardFace(int faceValue);
    
    /**
     * @brief 将整数转换为CardSuitType
     * @param suitValue 花色整数值
     * @return 对应的CardSuitType枚举值
     */
    static CardSuitType intToCardSuit(int suitValue);
};