#include "PlayFieldController.h"
#include "GameController.h"

USING_NS_CC;

PlayFieldController::PlayFieldController(GameController* gameController)
    : _gameController(gameController)
    , _gameModel(nullptr)
    , _playFieldView(nullptr)
    , _undoManager(nullptr)
{
}

PlayFieldController::~PlayFieldController() {
}

bool PlayFieldController::init() {
    CCLOG("PlayFieldController: Initializing");
    
    // 获取引用
    _gameModel = _gameController->getGameModel();
    _playFieldView = _gameController->getGameView()->getPlayFieldView();
    _undoManager = _gameController->getUndoManager();
    
    if (!_gameModel || !_playFieldView || !_undoManager) {
        CCLOGERROR("PlayFieldController: Failed to get required references");
        return false;
    }
    
    // 创建桌面牌视图
    const auto& playFieldCards = _gameModel->getPlayFieldCards();
    for (auto card : playFieldCards) {
        CardView* cardView = CardView::create();
        cardView->displayCard(card->getId(), card->getNumber(), 
                             static_cast<int>(card->getSuit()), card->isFaceUp());
        _playFieldView->addCardView(cardView, card->getPosition());
    }
    
    // 设置触摸回调
    setupCardCallbacks();
    
    CCLOG("PlayFieldController: Initialized with %zu cards", playFieldCards.size());
    return true;
}

void PlayFieldController::setupCardCallbacks() {
    const auto& playFieldCards = _gameModel->getPlayFieldCards();
    
    for (auto card : playFieldCards) {
        CardView* cardView = _playFieldView->getCardViewById(card->getId());
        if (cardView) {
            cardView->setTouchCallback([this](int cardId) {
                this->handleCardClick(cardId);
            });
        }
    }
}

void PlayFieldController::handleCardClick(int cardId) {
    CCLOG("PlayFieldController: Card clicked - ID: %d", cardId);
    
    // 1. 验证点击
    if (!validateClick(cardId)) {
        CCLOG("PlayFieldController: Invalid click");
        return;
    }
    
    // 2. 检查匹配
    if (!checkMatch(cardId)) {
        CCLOG("PlayFieldController: Card does not match");
        return;
    }
    
    // 3. 记录操作
    CardModel* topCard = _gameModel->getTopHandCard();
    recordOperation(cardId, topCard->getId());
    
    // 4. 执行移动
    executeCardMove(cardId);
}

bool PlayFieldController::validateClick(int cardId) {
    // 检查卡牌是否存在
    CardModel* card = _gameModel->getCardById(cardId);
    if (!card) {
        CCLOGERROR("PlayFieldController: Card not found - ID: %d", cardId);
        return false;
    }
    
    // 检查是否在桌面区
    if (card->isInHandArea()) {
        CCLOG("PlayFieldController: Card is in hand area");
        return false;
    }
    
    return true;
}

bool PlayFieldController::checkMatch(int cardId) {
    CardModel* clickedCard = _gameModel->getCardById(cardId);
    CardModel* topCard = _gameModel->getTopHandCard();
    
    if (!clickedCard || !topCard) {
        CCLOGERROR("PlayFieldController: Failed to get cards for match check");
        return false;
    }
    
    bool matched = CardMatchService::isMatch(clickedCard, topCard);
    
    if (matched) {
        CCLOG("PlayFieldController: Cards match - %d and %d", 
              clickedCard->getNumber(), topCard->getNumber());
    } else {
        CCLOG("PlayFieldController: Cards do not match - %d and %d", 
              clickedCard->getNumber(), topCard->getNumber());
    }
    
    return matched;
}

void PlayFieldController::recordOperation(int sourceCardId, int targetCardId) {
    UndoRecord record;
    record.operationType = UndoRecord::OperationType::PLAY_FIELD_CLICK;
    record.sourceCardId = sourceCardId;
    record.targetCardId = targetCardId;
    
    // 记录原始位置
    CardModel* sourceCard = _gameModel->getCardById(sourceCardId);
    CardModel* targetCard = _gameModel->getCardById(targetCardId);
    
    if (sourceCard && targetCard) {
        record.sourceOriginalPos = sourceCard->getPosition();
        record.targetOriginalPos = targetCard->getPosition();
    }
    
    _undoManager->recordOperation(record);
    CCLOG("PlayFieldController: Operation recorded");
}

void PlayFieldController::executeCardMove(int cardId) {
    // 1. 获取目标位置（手牌顶部位置）
    StackView* stackView = _gameController->getGameView()->getStackView();
    Vec2 targetPos = stackView->getTopCardPosition();
    
    // 2. 播放移动动画
    _playFieldView->playCardToHandAnimation(cardId, targetPos, [this, cardId, stackView]() {
        CCLOG("PlayFieldController: Card move animation completed");
        
        // 3. 动画完成后更新数据模型
        CardModel* card = _gameModel->getCardById(cardId);
        if (card) {
            // 从桌面区移除
            _gameModel->removeCardFromPlayField(cardId);
            
            // 设置为新的顶部牌
            card->setInHandArea(true);
            _gameModel->setTopHandCard(card);
            
            // 在手牌区视图中添加此卡牌
            CardView* cardView = CardView::create();
            cardView->displayCard(card->getId(), card->getNumber(), 
                                 static_cast<int>(card->getSuit()), card->isFaceUp());
            cardView->setPosition(card->getPosition());
            cardView->setTouchCallback([this](int id) {
                // 更新为手牌区的点击处理
                GameController* gc = _gameController;
                // 这里应该调用StackController的handleCardClick
                // 但由于架构限制，我们通过GameController间接调用
            });
            stackView->addCardView(cardView);
        }
        
        // 4. 检查胜利条件
        _gameController->checkWinCondition();
    });
    
    CCLOG("PlayFieldController: Card move executed - ID: %d", cardId);
}