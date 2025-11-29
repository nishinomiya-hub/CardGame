#pragma once

#include "configs/models/LevelConfig.h"
#include <string>

/**
 * @brief 关卡配置加载器
 * @details 负责从JSON文件加载关卡配置数据
 */
class LevelConfigLoader {
public:
    /**
     * @brief 从JSON文件加载关卡配置
     * @param levelId 关卡ID
     * @return 关卡配置对象指针，失败返回nullptr
     */
    static LevelConfig* loadLevel(int levelId);
    
    /**
     * @brief 从JSON文件路径加载关卡配置
     * @param filePath JSON文件路径
     * @return 关卡配置对象指针，失败返回nullptr
     */
    static LevelConfig* loadFromFile(const std::string& filePath);
    
private:
    /**
     * @brief 解析JSON内容
     * @param jsonContent JSON字符串内容
     * @return 关卡配置对象指针，失败返回nullptr
     */
    static LevelConfig* parseJson(const std::string& jsonContent);
    
    /**
     * @brief 获取关卡文件路径
     * @param levelId 关卡ID
     * @return 文件路径
     */
    static std::string getLevelFilePath(int levelId);
};