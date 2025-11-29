#include "UndoModel.h"

void UndoModel::addRecord(const UndoRecord& record) {
    _records.push_back(record);
}

UndoRecord UndoModel::popRecord() {
    if (_records.empty()) {
        return UndoRecord();
    }
    
    UndoRecord record = _records.back();
    _records.pop_back();
    return record;
}