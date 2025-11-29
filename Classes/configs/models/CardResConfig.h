#pragma once
#include "CardTypes.h"
#include <string>
#include <map>

/**
 * @file CardResConfig.h
 * @brief 卡牌资源配置,管理卡牌多层图片资源路径
 * 
 * 卡牌由4层图片组成:
 * 1. 底层: card_general.png (通用卡牌背景)
 * 2. 花色层: club.png / diamond.png / heart.png / spade.png
 * 3. 大数字层: big_black_2.png / big_red_2.png
 * 4. 小数字层: small_black_2.png / small_red_2.png
 * 5. 底色层: card_back.png (卡牌背面) (没用美术资源，先留好接口)
 */

/**
 * @struct CardLayerImages
 * @brief 卡牌各层图片路径
 */
struct CardLayerImages
{
    std::string baseImage;          // 底层通用背景
    std::string suitImage;          // 花色图片
    std::string bigNumberImage;     // 大数字图片
    std::string smallNumberImage;   // 小数字图片
    
    CardLayerImages()
        : baseImage("")
        , suitImage("")
        , bigNumberImage("")
        , smallNumberImage("")
    {}
};

/**
 * @class CardResConfig
 * @brief 卡牌资源配置类,提供卡牌多层图片路径管理
 */
class CardResConfig
{
public:
    /**
     * @brief 构造函数
     */
    CardResConfig();
    
    /**
     * @brief 析构函数
     */
    ~CardResConfig();
    
    /**
     * @brief 根据花色和点数获取卡牌各层图片
     * @param suit 卡牌花色
     * @param face 卡牌点数
     * @return 卡牌各层图片路径结构
     */
    CardLayerImages getCardLayerImages(CardSuitType suit, CardFaceType face) const;
    
    /**
     * @brief 获取卡牌背面图片路径
     * @return 卡牌背面图片资源路径
     */
    std::string getCardBackImagePath() const;
    
    /**
     * @brief 设置通用卡牌底层图片
     * @param imagePath 图片资源路径
     */
    void setCardBaseImagePath(const std::string& imagePath);
    
    /**
     * @brief 设置花色图片
     * @param suit 花色类型
     * @param imagePath 图片资源路径
     */
    void setSuitImagePath(CardSuitType suit, const std::string& imagePath);
    
    /**
     * @brief 设置大数字图片
     * @param face 点数类型
     * @param isRed 是否红色(红桃方块为红色,梅花黑桃为黑色)
     * @param imagePath 图片资源路径
     */
    void setBigNumberImagePath(CardFaceType face, bool isRed, const std::string& imagePath);
    
    /**
     * @brief 设置小数字图片
     * @param face 点数类型
     * @param isRed 是否红色
     * @param imagePath 图片资源路径
     */
    void setSmallNumberImagePath(CardFaceType face, bool isRed, const std::string& imagePath);
    
    /**
     * @brief 设置卡牌背面图片路径
     * @param imagePath 图片资源路径
     */
    void setCardBackImagePath(const std::string& imagePath);
    
    /**
     * @brief 清空所有配置
     */
    void clear();
    
private:
    /**
     * @brief 判断花色是否为红色
     * @param suit 花色类型
     * @return 是否为红色花色(红桃或方块)
     */
    bool isRedSuit(CardSuitType suit) const;
    
    /**
     * @brief 生成数字图片的键
     * @param face 点数类型
     * @param isRed 是否红色
     * @return 唯一键
     */
    int generateNumberKey(CardFaceType face, bool isRed) const;
    
    std::string _cardBaseImage;                        // 通用卡牌底层图片
    std::map<CardSuitType, std::string> _suitImages;   // 花色图片映射
    std::map<int, std::string> _bigNumberImages;       // 大数字图片映射
    std::map<int, std::string> _smallNumberImages;     // 小数字图片映射
    std::string _cardBackImagePath;                    // 卡牌背面图片路径
};