#include "GameView.h"
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
        this->addChild(_stackView, 1);
    }
    
    // 创建桌面牌区视图
    _playFieldView = PlayFieldView::create();
    if (_playFieldView) {
        this->addChild(_playFieldView, 0);
    }
    
    // 创建UI按钮
    createButtons();
    
    return true;
}

void GameView::createBackground() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 创建绿色背景
    auto background = LayerColor::create(Color4B(34, 139, 34, 255));
    this->addChild(background, -1);
}

void GameView::createButtons() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 创建回退按钮
    _undoButton = ui::Button::create();
    _undoButton->setTitleText("Undo");
    _undoButton->setTitleFontSize(24);
    _undoButton->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, 
                                   origin.y + visibleSize.height * 0.9f));
    
    _undoButton->addClickEventListener([this](Ref* sender) {
        if (_undoCallback) {
            _undoCallback();
        }
    });
    
    this->addChild(_undoButton, 10);
}

void GameView::setUndoButtonCallback(const std::function<void()>& callback) {
    _undoCallback = callback;
}

void GameView::setUndoButtonEnabled(bool enabled) {
    if (_undoButton) {
        _undoButton->setEnabled(enabled);
        _undoButton->setBright(enabled);
    }
}