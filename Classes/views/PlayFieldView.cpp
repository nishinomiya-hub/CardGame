#include "PlayFieldView.h"

USING_NS_CC;

PlayFieldView* PlayFieldView::create() {
    PlayFieldView* ret = new PlayFieldView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool PlayFieldView::init() {
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void PlayFieldView::addCardView(CardView* cardView, const Vec2& position) {
    if (cardView) {
        _cardViews.push_back(cardView);
        cardView->setPosition(position);
        this->addChild(cardView);
    }
}

CardView* PlayFieldView::getCardViewById(int cardId) {
    for (auto cardView : _cardViews) {
        if (cardView->getCardId() == cardId) {
            return cardView;
        }
    }
    return nullptr;
}

void PlayFieldView::removeCardView(int cardId) {
    for (auto it = _cardViews.begin(); it != _cardViews.end(); ++it) {
        if ((*it)->getCardId() == cardId) {
            (*it)->removeFromParent();
            _cardViews.erase(it);
            break;
        }
    }
}

void PlayFieldView::playCardToHandAnimation(int cardId, const Vec2& targetPos, 
                                           const std::function<void()>& callback) {
    CardView* cardView = getCardViewById(cardId);
    if (cardView) {
        // 播放移动动画
        cardView->playMoveAnimation(targetPos, 0.3f, [this, cardId, callback]() {
            // 动画完成后从桌面移除
            removeCardView(cardId);
            if (callback) {
                callback();
            }
        });
    }
}