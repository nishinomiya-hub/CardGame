#pragma once

#include <string>

/**
 * @brief 卡牌资源配置加载器
 * @details 负责从配置文件加载卡牌资源路径配置
 */
class CardResConfigLoader {
public:
    /**
     * @brief 加载卡牌资源配置
     * @param configFile 配置文件路径，默认为"configs/card_res_config.json"
     * @return 加载成功返回true，失败返回false
     */
    static bool loadConfig(const std::string& configFile = "configs/card_res_config.json");
    
private:
    /**
     * @brief 解析JSON配置内容
     * @param jsonContent JSON字符串内容
     * @return 解析成功返回true，失败返回false
     */
    static bool parseJson(const std::string& jsonContent);
};