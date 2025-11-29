#include "StackView.h"

USING_NS_CC;

StackView* StackView::create() {
    StackView* ret = new StackView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool StackView::init() {
    if (!Node::init()) {
        return false;
    }
    
    _cardOffsetY = 30.0f;  // 卡牌之间的垂直偏移
    
    // 设置手牌堆基准位置（屏幕右下角）
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _stackBasePos = Vec2(origin.x + visibleSize.width * 0.85f, 
                         origin.y + visibleSize.height * 0.2f);
    
    return true;
}

void StackView::addCardView(CardView* cardView) {
    if (cardView) {
        _cardViews.push_back(cardView);
        this->addChild(cardView);
        updateLayout();
    }
}

CardView* StackView::getCardViewById(int cardId) {
    for (auto cardView : _cardViews) {
        if (cardView->getCardId() == cardId) {
            return cardView;
        }
    }
    return nullptr;
}

void StackView::updateLayout() {
    for (size_t i = 0; i < _cardViews.size(); ++i) {
        Vec2 pos = calculateCardPosition(i);
        _cardViews[i]->setPosition(pos);
        _cardViews[i]->setLocalZOrder(i);
    }
}

Vec2 StackView::calculateCardPosition(int index) const {
    return Vec2(_stackBasePos.x, _stackBasePos.y + index * _cardOffsetY);
}

void StackView::playCardReplaceAnimation(int cardId, const std::function<void()>& callback) {
    CardView* clickedCard = getCardViewById(cardId);
    if (!clickedCard) {
        if (callback) callback();
        return;
    }
    
    // 找到被点击卡牌的索引
    int clickedIndex = -1;
    for (size_t i = 0; i < _cardViews.size(); ++i) {
        if (_cardViews[i]->getCardId() == cardId) {
            clickedIndex = i;
            break;
        }
    }
    
    if (clickedIndex == -1 || clickedIndex == 0) {
        if (callback) callback();
        return;
    }
    
    // 被点击的卡牌移动到顶部位置
    Vec2 topPos = calculateCardPosition(0);
    clickedCard->playMoveAnimation(topPos, 0.3f, callback);
    
    // 其他卡牌依次下移
    for (int i = 0; i < clickedIndex; ++i) {
        Vec2 newPos = calculateCardPosition(i + 1);
        _cardViews[i]->playMoveAnimation(newPos, 0.3f);
    }
    
    // 更新_cardViews顺序
    auto tempCard = _cardViews[clickedIndex];
    _cardViews.erase(_cardViews.begin() + clickedIndex);
    _cardViews.insert(_cardViews.begin(), tempCard);
    
    // 更新Z顺序
    for (size_t i = 0; i < _cardViews.size(); ++i) {
        _cardViews[i]->setLocalZOrder(i);
    }
}

Vec2 StackView::getTopCardPosition() const {
    return calculateCardPosition(0);
}