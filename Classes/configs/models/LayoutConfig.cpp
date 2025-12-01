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
// 卡牌相关尺寸
// ==============================

const cocos2d::Size LayoutConfig::CARD_SIZE = cocos2d::Size(150, 210);
const float LayoutConfig::CARD_SELECTED_SCALE = 1.1f;
const float LayoutConfig::CARD_NORMAL_SCALE = 1.0f;

// ==============================
// 间距和边距配置
// ==============================

const float LayoutConfig::CARD_HORIZONTAL_SPACING = 20.0f;
const float LayoutConfig::CARD_VERTICAL_SPACING = 25.0f;
const float LayoutConfig::FIELD_INNER_MARGIN = 30.0f;
const float LayoutConfig::SCREEN_SAFE_MARGIN = 50.0f;

// ==============================
// 动画相关配置
// ==============================

const float LayoutConfig::CARD_MOVE_DURATION = 0.3f;
const float LayoutConfig::CARD_FLIP_DURATION = 0.5f;
const float LayoutConfig::MATCH_ANIMATION_DURATION = 0.8f;

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

cocos2d::Vec2 LayoutConfig::getCardPositionInStack(int index, int totalCards) {
    cocos2d::Vec2 stackPosition = getStackFieldPosition();
    
    // 手牌区卡牌层叠显示，稍微偏移
    float offsetX = (index - totalCards / 2.0f) * 5.0f; // 轻微水平偏移
    float offsetY = index * 3.0f; // 轻微垂直偏移
    
    return cocos2d::Vec2(stackPosition.x + offsetX, stackPosition.y + offsetY);
}

cocos2d::Vec2 LayoutConfig::getCardPositionInPlayField(int row, int column, int totalRows, int totalColumns) {
    cocos2d::Vec2 mainFieldPosition = getMainFieldPosition();
    cocos2d::Size mainFieldSize = MAIN_FIELD_SIZE;
    
    // 计算可用区域（减去边距）
    float usableWidth = mainFieldSize.width - 2 * FIELD_INNER_MARGIN;
    float usableHeight = mainFieldSize.height - 2 * FIELD_INNER_MARGIN;
    
    // 计算卡牌网格布局
    float cellWidth = usableWidth / totalColumns;
    float cellHeight = usableHeight / totalRows;
    
    // 计算卡牌位置
    float x = mainFieldPosition.x - usableWidth / 2 + cellWidth * (column + 0.5f);
    float y = mainFieldPosition.y + usableHeight / 2 - cellHeight * (row + 0.5f);
    
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

cocos2d::Vec2 LayoutConfig::getScreenCenter() {
    return cocos2d::Vec2(DESIGN_RESOLUTION.width / 2, DESIGN_RESOLUTION.height / 2);
}

cocos2d::Vec2 LayoutConfig::getScreenTopLeft() {
    return cocos2d::Vec2(SCREEN_SAFE_MARGIN, 
                DESIGN_RESOLUTION.height - SCREEN_SAFE_MARGIN);
}

cocos2d::Vec2 LayoutConfig::getScreenTopRight() {
    return cocos2d::Vec2(DESIGN_RESOLUTION.width - SCREEN_SAFE_MARGIN,
                DESIGN_RESOLUTION.height - SCREEN_SAFE_MARGIN);
}

cocos2d::Vec2 LayoutConfig::getScreenBottomLeft() {
    return cocos2d::Vec2(SCREEN_SAFE_MARGIN, SCREEN_SAFE_MARGIN);
}

cocos2d::Vec2 LayoutConfig::getScreenBottomRight() {
    return cocos2d::Vec2(DESIGN_RESOLUTION.width - SCREEN_SAFE_MARGIN,
                SCREEN_SAFE_MARGIN);
}

// ==============================
// 适配相关方法实现
// ==============================

float LayoutConfig::getScaleFactor() {
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    cocos2d::Size frameSize = glView->getFrameSize();
    
    // 计算基于宽度的缩放因子
    float scaleX = frameSize.width / DESIGN_RESOLUTION.width;
    float scaleY = frameSize.height / DESIGN_RESOLUTION.height;
    
    // 取较小值确保内容完全显示
    return MIN(scaleX, scaleY);
}

cocos2d::Size LayoutConfig::getAdaptedSize(const cocos2d::Size& designSize) {
    float scale = getScaleFactor();
    return cocos2d::Size(designSize.width * scale, designSize.height * scale);
}

cocos2d::Vec2 LayoutConfig::getAdaptedPosition(const cocos2d::Vec2& designPosition) {
    float scale = getScaleFactor();
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    cocos2d::Size frameSize = glView->getFrameSize();
    
    // 计算居中偏移
    float offsetX = (frameSize.width - DESIGN_RESOLUTION.width * scale) / 2;
    float offsetY = (frameSize.height - DESIGN_RESOLUTION.height * scale) / 2;
    
    return cocos2d::Vec2(designPosition.x * scale + offsetX, 
                designPosition.y * scale + offsetY);
}

cocos2d::Size LayoutConfig::getAdaptedCardSize() {
    return getAdaptedSize(CARD_SIZE);
}

// ==============================
// 布局验证方法实现
// ==============================

bool LayoutConfig::validateLayoutConfig() {
    // 验证分辨率设置
    if (DESIGN_RESOLUTION.width <= 0 || DESIGN_RESOLUTION.height <= 0) {
        CCLOGERROR("Invalid design resolution");
        return false;
    }
    
    // 验证区域尺寸
    if (MAIN_FIELD_SIZE.width <= 0 || MAIN_FIELD_SIZE.height <= 0 ||
        STACK_FIELD_SIZE.width <= 0 || STACK_FIELD_SIZE.height <= 0) {
        CCLOGERROR("Invalid field sizes");
        return false;
    }
    
    // 验证卡牌尺寸
    if (CARD_SIZE.width <= 0 || CARD_SIZE.height <= 0) {
        CCLOGERROR("Invalid card size");
        return false;
    }
    
    // 验证区域是否超出设计分辨率
    if (MAIN_FIELD_SIZE.height + STACK_FIELD_SIZE.height > DESIGN_RESOLUTION.height) {
        CCLOGERROR("Field heights exceed design resolution");
        return false;
    }
    
    if (MAIN_FIELD_SIZE.width > DESIGN_RESOLUTION.width || 
        STACK_FIELD_SIZE.width > DESIGN_RESOLUTION.width) {
        CCLOGERROR("Field widths exceed design resolution");
        return false;
    }
    
    CCLOG("Layout configuration validation passed");
    return true;
}

void LayoutConfig::printLayoutInfo() {
    CCLOG("=== Layout Configuration Info ===");
    CCLOG("Design Resolution: %.0fx%.0f", DESIGN_RESOLUTION.width, DESIGN_RESOLUTION.height);
    CCLOG("Main Field: %.0fx%.0f at (%.1f, %.1f)", 
          MAIN_FIELD_SIZE.width, MAIN_FIELD_SIZE.height,
          getMainFieldPosition().x, getMainFieldPosition().y);
    CCLOG("Stack Field: %.0fx%.0f at (%.1f, %.1f)",
          STACK_FIELD_SIZE.width, STACK_FIELD_SIZE.height,
          getStackFieldPosition().x, getStackFieldPosition().y);
    CCLOG("Card Size: %.0fx%.0f", CARD_SIZE.width, CARD_SIZE.height);
    CCLOG("Scale Factor: %.2f", getScaleFactor());
    CCLOG("Adapted Card Size: %.1fx%.1f", 
          getAdaptedCardSize().width, getAdaptedCardSize().height);
    CCLOG("==================================");
}