#include "GameView.h"

#include "configs/models/LayoutConfig.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

GameView* GameView::create() {
    GameView* ret = new GameView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GameView::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 创建背景
    createBackground();
    
    // 创建手牌区视图
    _stackView = StackView::create();
    if (_stackView) {
        _stackView->setPosition(LayoutConfig::getStackFieldPosition());
        this->addChild(_stackView, 1);
    }
    
    // 创建桌面牌区视图
    _playFieldView = PlayFieldView::create();
    if (_playFieldView) 
    {
        _playFieldView->setPosition(LayoutConfig::getMainFieldPosition());
        this->addChild(_playFieldView, 0);
    }
    
    // 创建UI按钮
    createButtons();
    
    return true;
}

void GameView::createBackground() {
    auto bgSize = LayoutConfig::DESIGN_RESOLUTION;

    auto background = LayerColor::create(Color4B(34, 139, 34, 255));
    background->setContentSize(bgSize);
    background->setPosition(Vec2::ZERO);

    this->addChild(background, -1);
}

void GameView::createButtons() {
    // Undo 按钮
    _undoButton = ui::Button::create();
    _undoButton->setTitleText("Undo");
    _undoButton->setTitleFontSize(24);
    _undoButton->setContentSize(LayoutConfig::UNDO_BUTTON_SIZE);
    _undoButton->setPosition(LayoutConfig::getUndoButtonPosition());

    _undoButton->addClickEventListener([this](Ref* sender) {
        if (_undoCallback) _undoCallback();
    });

    this->addChild(_undoButton, 10);

    // Restart 按钮（可选）
    _restartButton = ui::Button::create();
    _restartButton->setTitleText("Restart");
    _restartButton->setTitleFontSize(24);
    _restartButton->setContentSize(LayoutConfig::RESTART_BUTTON_SIZE);
    _restartButton->setPosition(LayoutConfig::getRestartButtonPosition());
    this->addChild(_restartButton, 10);
}

void GameView::setUndoButtonCallback(const std::function<void()>& callback) {
    _undoCallback = callback;
}

void GameView::setRestartButtonCallback(const std::function<void()>& callback) {
    _restartCallback = callback;
}

void GameView::setUndoButtonEnabled(bool enabled) {
    if (_undoButton) {
        _undoButton->setEnabled(enabled);
        _undoButton->setBright(enabled);
    }
}