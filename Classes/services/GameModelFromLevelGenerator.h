#pragma once

#include "configs/models/LevelConfig.h"

// 前置声明解决循环依赖
class GameModel;
class CardModel;

/**
 * @brief 游戏数据生成服务
 * @details 根据LevelConfig生成初始GameModel，处理卡牌随机生成逻辑
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 根据关卡配置生成游戏数据模型
     * @param levelConfig 关卡配置
     * @return 生成的游戏数据模型
     */
    static GameModel* generateFromLevel(const LevelConfig* levelConfig);
    
private:
    /**
     * @brief 创建卡牌模型
     * @param cardConfig 卡牌配置
     * @param id 卡牌ID
     * @return 卡牌模型
     */
    static CardModel* createCardModel(const CardConfig& cardConfig, int id);
};