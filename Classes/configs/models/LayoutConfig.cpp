#include "LayoutConfig.h"


// ==============================
// 设计分辨率相关
// ==============================

const cocos2d::Size LayoutConfig::DESIGN_RESOLUTION = cocos2d::Size(1080, 2080);
const cocos2d::Size LayoutConfig::WINDOW_SIZE = cocos2d:: Size(1080, 2080);

// ==============================
// 游戏区域尺寸
// ==============================

const cocos2d::Size LayoutConfig::MAIN_FIELD_SIZE = cocos2d::Size(1080, 1500);
const cocos2d::Size LayoutConfig::STACK_FIELD_SIZE = cocos2d::Size(1080, 580);
const cocos2d::Size LayoutConfig::TOTAL_GAME_AREA_SIZE = cocos2d::Size(1080, 2080);



// ==============================
// UI元素尺寸
// ==============================

const cocos2d::Size LayoutConfig::UNDO_BUTTON_SIZE = cocos2d::Size(120, 60);
const cocos2d::Size LayoutConfig::RESTART_BUTTON_SIZE = cocos2d::Size(120, 60);
const float LayoutConfig::BUTTON_SPACING = 20.0f;

// ==============================
// 位置计算方法实现
// ==============================

cocos2d::Vec2 LayoutConfig::getMainFieldPosition() {
    float x = 0 ;
    float y = STACK_FIELD_SIZE.height ;
    return cocos2d::Vec2(x, y);
}

cocos2d::Vec2 LayoutConfig::getStackFieldPosition() {
    float x = 0 ;
    float y = 0 ;
    return cocos2d::Vec2(x, y);
}


cocos2d::Vec2 LayoutConfig::getUndoButtonPosition() {
    return cocos2d::Vec2(DESIGN_RESOLUTION.width - UNDO_BUTTON_SIZE.width  ,
                STACK_FIELD_SIZE.height / 2 - UNDO_BUTTON_SIZE.height / 2 );
}

cocos2d::Vec2 LayoutConfig::getRestartButtonPosition() {
    cocos2d::Vec2 undoPos = getUndoButtonPosition();
    return cocos2d::Vec2(undoPos.x - UNDO_BUTTON_SIZE.width - BUTTON_SPACING,
                undoPos.y);
}
