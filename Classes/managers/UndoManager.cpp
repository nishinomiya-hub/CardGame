#include "UndoManager.h"
#include "cocos2d.h"

USING_NS_CC;

UndoManager::UndoManager() 
    : _maxRecords(0)  // 0表示无限制
{
}

UndoManager::~UndoManager() {
    clear();
}

void UndoManager::recordOperation(const UndoRecord& record) {
    _records.push_back(record);
    
    // 如果超过最大记录数，移除最早的记录
    if (_maxRecords > 0 && _records.size() > static_cast<size_t>(_maxRecords)) {
        _records.erase(_records.begin());
    }
    
    CCLOG("UndoManager: Recorded operation, total records: %zu", _records.size());
}

bool UndoManager::undo(GameModel* gameModel) {
    if (!canUndo() || !gameModel) {
        CCLOG("UndoManager: Cannot undo - no records or invalid game model");
        return false;
    }
    
    // 获取最后一条记录
    UndoRecord record = _records.back();
    _records.pop_back();
    
    CCLOG("UndoManager: Undoing operation, remaining records: %zu", _records.size());
    
    // 恢复游戏状态
    restoreGameState(record, gameModel);
    
    // 触发回调
    if (_undoCallback) {
        _undoCallback(record);
    }
    
    return true;
}

bool UndoManager::canUndo() const {
    return !_records.empty();
}

void UndoManager::clear() {
    _records.clear();
    CCLOG("UndoManager: Cleared all records");
}

int UndoManager::getRecordCount() const {
    return static_cast<int>(_records.size());
}

void UndoManager::setUndoCallback(const std::function<void(const UndoRecord&)>& callback) {
    _undoCallback = callback;
}

void UndoManager::setMaxRecords(int maxRecords) {
    _maxRecords = maxRecords;
    
    // 如果当前记录数超过新的最大值，移除多余的记录
    if (_maxRecords > 0) {
        while (_records.size() > static_cast<size_t>(_maxRecords)) {
            _records.erase(_records.begin());
        }
    }
}

void UndoManager::restoreGameState(const UndoRecord& record, GameModel* gameModel) {
    switch (record.operationType) {
        case UndoRecord::OperationType::HAND_CARD_CLICK:
            undoHandCardClick(record, gameModel);
            break;
            
        case UndoRecord::OperationType::PLAY_FIELD_CLICK:
            undoPlayFieldClick(record, gameModel);
            break;
            
        default:
            CCLOGERROR("UndoManager: Unknown operation type");
            break;
    }
}

void UndoManager::undoHandCardClick(const UndoRecord& record, GameModel* gameModel) {
    // 手牌区点击操作的回退：
    // 1. 将点击的卡牌从顶部位置恢复到原位置
    // 2. 将原来的顶部牌恢复为顶部牌
    
    CardModel* sourceCard = gameModel->getCardById(record.sourceCardId);
    CardModel* targetCard = gameModel->getCardById(record.targetCardId);
    
    if (!sourceCard || !targetCard) {
        CCLOGERROR("UndoManager: Cannot find cards for undo hand card click");
        return;
    }
    
    // 恢复位置
    sourceCard->setPosition(record.sourceOriginalPos);
    targetCard->setPosition(record.targetOriginalPos);
    
    // 恢复顶部牌引用
    gameModel->setTopHandCard(targetCard);
    
    CCLOG("UndoManager: Restored hand card click - source: %d, target: %d", 
          record.sourceCardId, record.targetCardId);
}

void UndoManager::undoPlayFieldClick(const UndoRecord& record, GameModel* gameModel) {
    // 桌面牌点击操作的回退：
    // 1. 将移动到手牌区的卡牌恢复到桌面原位置
    // 2. 将原来的手牌顶部牌恢复为顶部牌
    
    CardModel* sourceCard = gameModel->getCardById(record.sourceCardId);
    CardModel* targetCard = gameModel->getCardById(record.targetCardId);
    
    if (!sourceCard || !targetCard) {
        CCLOGERROR("UndoManager: Cannot find cards for undo play field click");
        return;
    }
    
    // 恢复源卡牌到桌面
    sourceCard->setPosition(record.sourceOriginalPos);
    sourceCard->setInHandArea(false);
    gameModel->addCardToPlayField(sourceCard);
    
    // 恢复原手牌顶部牌
    targetCard->setPosition(record.targetOriginalPos);
    gameModel->setTopHandCard(targetCard);
    
    CCLOG("UndoManager: Restored play field click - source: %d back to field, target: %d as top", 
          record.sourceCardId, record.targetCardId);
}