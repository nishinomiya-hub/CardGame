#pragma once

#include <string>
#include <unordered_map>
#include "models/CardModel.h"

/**
 * @brief 卡牌资源配置类
 * @details 管理每张卡牌对应的图片资源路径，卡牌由card_general.png+花色+数字组成
 */
class CardResConfig {
public:
    /**
     * @brief 获取卡牌底板图片路径
     * @return 图片资源路径
     */
    static std::string getCardGeneralImage();
    
    /**
     * @brief 获取花色图片路径
     * @param suit 花色
     * @return 图片资源路径
     */
    static std::string getSuitImage(CardModel::Suit suit);
    
    /**
     * @brief 获取大号数字图片路径
     * @param number 点数 (1-13)
     * @param suit 花色 (用于判断黑色/红色)
     * @return 图片资源路径
     */
    static std::string getBigNumberImage(int number, CardModel::Suit suit);
    
    /**
     * @brief 获取小号数字图片路径
     * @param number 点数 (1-13)
     * @param suit 花色 (用于判断黑色/红色)
     * @return 图片资源路径
     */
    static std::string getSmallNumberImage(int number, CardModel::Suit suit);
    
    /**
     * @brief 获取卡牌背面图片路径
     * @return 图片资源路径
     */
    static std::string getCardBackImage();
    
    /**
     * @brief 初始化资源配置
     */
    static void init();
    
private:
    static std::string _cardGeneralImage;
    static std::string _cardBackImage;
    static std::unordered_map<int, std::string> _suitImageMap;
    static std::unordered_map<std::string, std::string> _numberImageMap;
    
    /**
     * @brief 判断花色是否为红色
     * @param suit 花色
     * @return true表示红色，false表示黑色
     */
    static bool isRedSuit(CardModel::Suit suit);
    
    /**
     * @brief 生成数字资源key
     * @param number 点数
     * @param isRed 是否红色
     * @param isBig 是否大号
     * @return 资源key
     */
    static std::string generateNumberKey(int number, bool isRed, bool isBig);
};