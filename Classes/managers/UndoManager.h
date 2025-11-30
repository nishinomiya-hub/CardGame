#pragma once

#include "models/UndoModel.h"
#include "models/GameModel.h"
#include <vector>
#include <functional>

/**
 * @brief 回退管理器
 * @details 管理游戏操作历史，支持回退功能
 * - 维护操作历史栈
 * - 提供记录和回退操作接口
 * - 通过回调通知外部状态变化
 */
class UndoManager {
public:
    /**
     * @brief 构造函数
     */
    UndoManager();
    
    /**
     * @brief 析构函数
     */
    ~UndoManager();
    
    /**
     * @brief 记录一次操作
     * @param record 操作记录
     */
    void recordOperation(const UndoRecord& record);
    
    /**
     * @brief 执行回退操作
     * @param gameModel 游戏数据模型（用于恢复状态）
     * @return 回退成功返回true，无可回退操作返回false
     */
    bool undo(GameModel* gameModel);
    
    /**
     * @brief 判断是否有可回退的操作
     * @return 有可回退操作返回true
     */
    bool canUndo() const;
    
    /**
     * @brief 清空所有历史记录
     */
    void clear();
    
    /**
     * @brief 获取历史记录数量
     * @return 历史记录数量
     */
    int getRecordCount() const;
    
    /**
     * @brief 设置回退完成回调
     * @param callback 回调函数，参数为回退的记录
     */
    void setUndoCallback(const std::function<void(const UndoRecord&)>& callback);
    
    /**
     * @brief 设置最大历史记录数
     * @param maxRecords 最大记录数，0表示无限制
     */
    void setMaxRecords(int maxRecords);
    
private:
    std::vector<UndoRecord> _records;                       // 操作历史栈
    std::function<void(const UndoRecord&)> _undoCallback;   // 回退完成回调
    int _maxRecords;                                        // 最大记录数
    
    /**
     * @brief 根据操作记录恢复游戏状态
     * @param record 操作记录
     * @param gameModel 游戏数据模型
     */
    void restoreGameState(const UndoRecord& record, GameModel* gameModel);
    
    /**
     * @brief 处理手牌区点击操作的回退
     * @param record 操作记录
     * @param gameModel 游戏数据模型
     */
    void undoHandCardClick(const UndoRecord& record, GameModel* gameModel);
    
    /**
     * @brief 处理桌面牌点击操作的回退
     * @param record 操作记录
     * @param gameModel 游戏数据模型
     */
    void undoPlayFieldClick(const UndoRecord& record, GameModel* gameModel);
};