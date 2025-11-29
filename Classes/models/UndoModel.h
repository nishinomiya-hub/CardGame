#pragma once
#include "CardModel.h"
#include <vector>

/**
 * @brief 回退操作的数据模型
 * @details 记录每次操作的信息，用于实现回退功能
 */
struct UndoRecord {
    enum class OperationType {
        HAND_CARD_CLICK,    // 手牌区点击
        PLAY_FIELD_CLICK    // 桌面牌点击
    };
    
    OperationType operationType;
    int sourceCardId;       // 操作的源卡牌ID
    int targetCardId;       // 操作的目标卡牌ID（被替换的卡牌）
    cocos2d::Vec2 sourceOriginalPos; // 源卡牌原始位置
    cocos2d::Vec2 targetOriginalPos; // 目标卡牌原始位置
};

class UndoModel {
public:
    void addRecord(const UndoRecord& record);
    UndoRecord popRecord();
    bool hasRecords() const { return !_records.empty(); }
    void clear() { _records.clear(); }
    
private:
    std::vector<UndoRecord> _records;
};