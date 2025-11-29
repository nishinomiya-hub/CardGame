#pragma once

#include "models/CardModel.h"

/**
 * @brief 卡牌匹配服务
 * @details 提供静态方法验证两张牌是否匹配（点数差1），纯逻辑判断，不持有数据
 */
class CardMatchService {
public:
    /**
     * @brief 判断两张卡牌是否匹配
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 是否匹配（点数相差1）
     */
    static bool isMatch(const CardModel* card1, const CardModel* card2);
    
    /**
     * @brief 判断两个点数是否匹配
     * @param number1 第一个点数
     * @param number2 第二个点数
     * @return 是否匹配（点数相差1）
     */
    static bool isNumberMatch(int number1, int number2);
};