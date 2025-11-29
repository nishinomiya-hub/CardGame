#include "configs/models/CardResConfig.h"
#include <string>


/**
 * @file CardResConfigLoader.h
 * @brief 卡牌资源配置加载器,负责初始化多层卡牌资源映射
 */

/**
 * @class CardResConfigLoader
 * @brief 卡牌资源配置加载器类,提供静态方法加载卡牌资源配置
 */
class CardResConfigLoader
{
public:
    /**
     * @brief 从JSON文件加载卡牌资源配置
     * @param filePath JSON配置文件路径
     * @param outConfig 输出的卡牌资源配置对象
     * @return 加载是否成功
     */
    static bool loadFromFile(const std::string& filePath, CardResConfig& outConfig);
    
    /**
     * @brief 从JSON字符串加载卡牌资源配置
     * @param jsonString JSON配置字符串
     * @param outConfig 输出的卡牌资源配置对象
     * @return 解析是否成功
     */
    static bool loadFromString(const std::string& jsonString, CardResConfig& outConfig);
    
    /**
     * @brief 使用默认规则初始化卡牌资源配置
     * @param outConfig 输出的卡牌资源配置对象
     * @param imageFolder 图片资源文件夹路径
     * 
     * 默认命名规则:
     * - 底层: card_general.png
     * - 花色: club.png, diamond.png, heart.png, spade.png
     * - 大数字: big_black_a.png, big_red_2.png 等
     * - 小数字: small_black_a.png, small_red_2.png 等
     */
    static void loadWithDefaultRules(CardResConfig& outConfig, const std::string& imageFolder = "res/");
    
private:
    /**
     * @brief 获取花色文件名
     * @param suit 花色类型
     * @return 花色文件名(不含扩展名)
     */
    static std::string getSuitFileName(CardSuitType suit);
    
    /**
     * @brief 获取点数文件名
     * @param face 点数类型
     * @return 点数文件名(不含扩展名)
     */
    static std::string getFaceFileName(CardFaceType face);
    
    /**
     * @brief 判断花色是否为红色
     * @param suit 花色类型
     * @return 是否为红色花色
     */
    static bool isRedSuit(CardSuitType suit);
};