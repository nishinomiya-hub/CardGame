#include "CardView.h"
#include "configs/models/CardResConfig.h"
#include "models/CardModel.h"

USING_NS_CC;

CardView* CardView::create() {
    CardView* ret = new CardView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init() {
    if (!Sprite::init()) {
        return false;
    }
    
    _cardId = -1;
    _touchEnabled = true;
    
    // 创建卡牌底板
    _cardBase = Sprite::create(CardResConfig::getCardGeneralImage());
    if (_cardBase) {
        this->addChild(_cardBase);
        this->setContentSize(_cardBase->getContentSize());
    }
    
    // 创建花色精灵
    _suitSprite = Sprite::create();
    _suitSprite->setVisible(false);
    this->addChild(_suitSprite);
    
    // 创建数字精灵
    _bigNumberSprite = Sprite::create();
    _bigNumberSprite->setVisible(false);
    this->addChild(_bigNumberSprite);
    
    _smallNumberTopLeft = Sprite::create();
    _smallNumberTopLeft->setVisible(false);
    this->addChild(_smallNumberTopLeft);
    
    _smallNumberBottomRight = Sprite::create();
    _smallNumberBottomRight->setVisible(false);
    this->addChild(_smallNumberBottomRight);
    
    // 创建卡牌背面
    _cardBack = Sprite::create(CardResConfig::getCardBackImage());
    if (_cardBack) {
        _cardBack->setVisible(false);
        this->addChild(_cardBack);
    }
    
    setupTouchListener();
    
    return true;
}

void CardView::displayCard(int cardId, int number, int suit, bool isFaceUp) {
    _cardId = cardId;
    
    if (isFaceUp) {
        showFrontFace(number, suit);
    } else {
        showBackFace();
    }
}

void CardView::showFrontFace(int number, int suit) {
    // 隐藏背面
    if (_cardBack) {
        _cardBack->setVisible(false);
    }
    
    // 显示底板
    if (_cardBase) {
        _cardBase->setVisible(true);
    }
    
    // 转换花色枚举
    CardModel::Suit cardSuit = static_cast<CardModel::Suit>(suit);
    
    // 设置花色图标
    std::string suitImage = CardResConfig::getSuitImage(cardSuit);
    if (!suitImage.empty() && _suitSprite) {
        _suitSprite->setTexture(suitImage);
        _suitSprite->setVisible(true);
        // 居中显示
        Size cardSize = this->getContentSize();
        _suitSprite->setPosition(Vec2(cardSize.width / 2, cardSize.height / 2));
    }
    
    // 设置大号数字（中央）
    std::string bigNumberImage = CardResConfig::getBigNumberImage(number, cardSuit);
    if (!bigNumberImage.empty() && _bigNumberSprite) {
        _bigNumberSprite->setTexture(bigNumberImage);
        _bigNumberSprite->setVisible(true);
        Size cardSize = this->getContentSize();
        _bigNumberSprite->setPosition(Vec2(cardSize.width / 2, cardSize.height * 0.3f));
    }
    
    // 设置左上角小号数字
    std::string smallNumberImage = CardResConfig::getSmallNumberImage(number, cardSuit);
    if (!smallNumberImage.empty() && _smallNumberTopLeft) {
        _smallNumberTopLeft->setTexture(smallNumberImage);
        _smallNumberTopLeft->setVisible(true);
        Size cardSize = this->getContentSize();
        _smallNumberTopLeft->setPosition(Vec2(cardSize.width * 0.15f, cardSize.height * 0.85f));
    }
    
    // 设置右下角小号数字（旋转180度）
    if (!smallNumberImage.empty() && _smallNumberBottomRight) {
        _smallNumberBottomRight->setTexture(smallNumberImage);
        _smallNumberBottomRight->setVisible(true);
        _smallNumberBottomRight->setRotation(180);
        Size cardSize = this->getContentSize();
        _smallNumberBottomRight->setPosition(Vec2(cardSize.width * 0.85f, cardSize.height * 0.15f));
    }
}

void CardView::showBackFace() {
    // 隐藏正面所有元素
    if (_cardBase) _cardBase->setVisible(false);
    if (_suitSprite) _suitSprite->setVisible(false);
    if (_bigNumberSprite) _bigNumberSprite->setVisible(false);
    if (_smallNumberTopLeft) _smallNumberTopLeft->setVisible(false);
    if (_smallNumberBottomRight) _smallNumberBottomRight->setVisible(false);
    
    // 显示背面
    if (_cardBack) {
        _cardBack->setVisible(true);
        Size cardSize = this->getContentSize();
        _cardBack->setPosition(Vec2(cardSize.width / 2, cardSize.height / 2));
    }
}

void CardView::playMoveAnimation(const Vec2& targetPos, float duration, 
                                 const std::function<void()>& callback) {
    auto moveTo = MoveTo::create(duration, targetPos);
    
    if (callback) {
        auto callbackAction = CallFunc::create(callback);
        auto sequence = Sequence::create(moveTo, callbackAction, nullptr);
        this->runAction(sequence);
    } else {
        this->runAction(moveTo);
    }
}

void CardView::setupTouchListener() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!_touchEnabled) {
            return false;
        }
        
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size size = this->getContentSize();
        Rect rect = Rect(0, 0, size.width, size.height);
        
        if (rect.containsPoint(locationInNode)) {
            return true;
        }
        return false;
    };
    
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        if (_touchCallback && _touchEnabled) {
            _touchCallback(_cardId);
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CardView::setTouchCallback(const std::function<void(int)>& callback) {
    _touchCallback = callback;
}

void CardView::setTouchEnabled(bool enabled) {
    _touchEnabled = enabled;
}