#include "StackController.h"
#include "GameController.h"

USING_NS_CC;

StackController::StackController(GameController* gameController)
    : _gameController(gameController)
    , _gameModel(nullptr)
    , _stackView(nullptr)
    , _undoManager(nullptr)
{
}

StackController::~StackController() {
}

bool StackController::init() {
    CCLOG("StackController: Initializing");
    
    // 获取引用
    _gameModel = _gameController->getGameModel();
    _stackView = _gameController->getGameView()->getStackView();
    _undoManager = _gameController->getUndoManager();
    
    if (!_gameModel || !_stackView || !_undoManager) {
        CCLOGERROR("StackController: Failed to get required references");
        return false;
    }
    
    // 创建手牌区卡牌视图
    const auto& handCards = _gameModel->getHandAreaCards();
    for (auto card : handCards) {
        CardView* cardView = CardView::create();
        cardView->displayCard(card->getId(), card->getNumber(), 
                             static_cast<int>(card->getSuit()), card->isFaceUp());
        cardView->setPosition(card->getPosition());
        _stackView->addCardView(cardView);
    }
    
    // 设置触摸回调
    setupCardCallbacks();
    
    CCLOG("StackController: Initialized with %zu cards", handCards.size());
    return true;
}

void StackController::setupCardCallbacks() {
    const auto& handCards = _gameModel->getHandAreaCards();
    
    for (auto card : handCards) {
        CardView* cardView = _stackView->getCardViewById(card->getId());
        if (cardView) {
            cardView->setTouchCallback([this](int cardId) {
                this->handleCardClick(cardId);
            });
        }
    }
}

void StackController::handleCardClick(int cardId) {
    CCLOG("StackController: Card clicked - ID: %d", cardId);
    
    // 1. 验证点击
    if (!validateClick(cardId)) {
        CCLOG("StackController: Invalid click");
        return;
    }
    
    // 2. 记录操作
    CardModel* topCard = _gameModel->getTopHandCard();
    recordOperation(cardId, topCard->getId());
    
    // 3. 执行替换
    executeCardReplace(cardId);
}

bool StackController::validateClick(int cardId) {
    // 检查卡牌是否存在
    CardModel* card = _gameModel->getCardById(cardId);
    if (!card) {
        CCLOGERROR("StackController: Card not found - ID: %d", cardId);
        return false;
    }
    
    // 检查是否在手牌区
    if (!card->isInHandArea()) {
        CCLOG("StackController: Card is not in hand area");
        return false;
    }
    
    // 检查是否已经是顶部牌
    CardModel* topCard = _gameModel->getTopHandCard();
    if (topCard && topCard->getId() == cardId) {
        CCLOG("StackController: Card is already on top");
        return false;
    }
    
    return true;
}

void StackController::recordOperation(int sourceCardId, int targetCardId) {
    UndoRecord record;
    record.operationType = UndoRecord::OperationType::HAND_CARD_CLICK;
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
    CCLOG("StackController: Operation recorded");
}

void StackController::executeCardReplace(int cardId) {
    // 1. 更新数据模型
    CardModel* clickedCard = _gameModel->getCardById(cardId);
    CardModel* oldTopCard = _gameModel->getTopHandCard();
    
    if (!clickedCard || !oldTopCard) {
        CCLOGERROR("StackController: Failed to get cards for replace");
        return;
    }
    
    // 交换位置
    Vec2 clickedPos = clickedCard->getPosition();
    Vec2 topPos = oldTopCard->getPosition();
    
    clickedCard->setPosition(topPos);
    oldTopCard->setPosition(clickedPos);
    
    // 更新顶部牌引用
    _gameModel->setTopHandCard(clickedCard);
    
    // 2. 播放动画
    _stackView->playCardReplaceAnimation(cardId, [this]() {
        CCLOG("StackController: Card replace animation completed");
    });

    _gameController->updateUndoButtonState();
    
    CCLOG("StackController: Card replace executed - new top: %d", cardId);
}