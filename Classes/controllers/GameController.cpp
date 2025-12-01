#include "GameController.h"
#include "StackController.h"
#include "PlayFieldController.h"

#include "configs/loaders/LevelConfigLoader.h"
#include "configs/loaders/CardResConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"

USING_NS_CC;

GameController::GameController()
    : _gameModel(nullptr)
    , _gameView(nullptr)
    , _undoManager(nullptr)
    , _stackController(nullptr)
    , _playFieldController(nullptr)
{
}

GameController::~GameController() {
    CC_SAFE_DELETE(_gameModel);
    CC_SAFE_DELETE(_undoManager);
    CC_SAFE_DELETE(_stackController);
    CC_SAFE_DELETE(_playFieldController);
}

bool GameController::startGame(int levelId, cocos2d::Node* parentNode) {
    CCLOG("GameController: Starting game with level %d", levelId);
    
    // 1. 加载卡牌资源配置
    CardResConfigLoader::loadConfig();
    
    // 2. 初始化游戏数据
    if (!initGameData(levelId)) {
        CCLOGERROR("GameController: Failed to initialize game data");
        return false;
    }
    
    // 3. 初始化视图
    if (!initView(parentNode)) {
        CCLOGERROR("GameController: Failed to initialize view");
        return false;
    }
    
    // 4. 初始化子控制器
    if (!initControllers()) {
        CCLOGERROR("GameController: Failed to initialize controllers");
        return false;
    }
    
    // 5. 设置事件回调
    setupCallbacks();
    
    // 6. 更新UI状态
    updateUndoButtonState();
    
    CCLOG("GameController: Game started successfully");
    return true;
}

bool GameController::initGameData(int levelId) {
    // 加载关卡配置
    LevelConfig* levelConfig = LevelConfigLoader::loadLevel(levelId);
    if (!levelConfig) {
        CCLOGERROR("GameController: Failed to load level config");
        return false;
    }
    
    // 生成游戏数据模型
    _gameModel = GameModelFromLevelGenerator::generateFromLevel(levelConfig);
    delete levelConfig;
    
    if (!_gameModel) {
        CCLOGERROR("GameController: Failed to generate game model");
        return false;
    }
    
    // 创建回退管理器
    _undoManager = new UndoManager();
    _undoManager->setMaxRecords(50);  // 最多记录50步
    
    return true;
}

bool GameController::initView(cocos2d::Node* parentNode) {
    // 创建游戏视图
    _gameView = GameView::create();
    if (!_gameView) {
        CCLOGERROR("GameController: Failed to create game view");
        return false;
    }
    
    parentNode->addChild(_gameView);
    return true;
}

bool GameController::initControllers() {
    // 创建手牌区控制器
    _stackController = new StackController(this);
    if (!_stackController->init()) {
        CCLOGERROR("GameController: Failed to initialize stack controller");
        return false;
    }
    
    // 创建桌面牌区控制器
    _playFieldController = new PlayFieldController(this);
    if (!_playFieldController->init()) {
        CCLOGERROR("GameController: Failed to initialize play field controller");
        return false;
    }
    
    return true;
}

void GameController::setupCallbacks() {
    // 设置回退按钮回调
    _gameView->setUndoButtonCallback([this]() {
        this->handleUndo();
    });
    
    // 设置回退完成回调
    _undoManager->setUndoCallback([this](const UndoRecord& record) {
        this->onUndoComplete(record);
    });
}

void GameController::handleUndo() {
    if (!_undoManager->canUndo()) {
        CCLOG("GameController: No operations to undo");
        return;
    }
    
    CCLOG("GameController: Executing undo operation");
    _undoManager->undo(_gameModel);
    
    // 更新按钮状态
    updateUndoButtonState();
}

void GameController::onUndoComplete(const UndoRecord& record) {
    CCLOG("GameController: Undo completed");
    
    // 根据操作类型播放反向动画
    StackView* stackView = _gameView->getStackView();
    PlayFieldView* playFieldView = _gameView->getPlayFieldView();
    
    switch (record.operationType) {
        case UndoRecord::OperationType::HAND_CARD_CLICK: {
            // 手牌区点击的回退：播放卡牌位置恢复动画
            CardView* sourceCard = stackView->getCardViewById(record.sourceCardId);
            CardView* targetCard = stackView->getCardViewById(record.targetCardId);
            
            if (sourceCard && targetCard) {
                sourceCard->playMoveAnimation(record.sourceOriginalPos, 0.3f);
                targetCard->playMoveAnimation(record.targetOriginalPos, 0.3f);
            }
            break;
        }
        
        case UndoRecord::OperationType::PLAY_FIELD_CLICK: {
            // 桌面牌点击的回退：将卡牌从手牌区移回桌面
            CardView* sourceCard = playFieldView->getCardViewById(record.sourceCardId);
            if( ! sourceCard )
            {
                // 如果在PlayFieldView中找不到，可能需要重新创建
                sourceCard = CardView::create();
                CardModel* cardModel = _gameModel->getCardById(record.sourceCardId);
                if (cardModel) {
                    sourceCard->displayCard(cardModel->getId(), cardModel->getNumber(), 
                                          static_cast<int>(cardModel->getSuit()), cardModel->isFaceUp());
                    playFieldView->addCardView(sourceCard, record.sourceOriginalPos);
                }
            }
            CardView* targetCard = stackView->getCardViewById(record.targetCardId);
            
            if (sourceCard && targetCard) {
                // 源卡牌移回桌面原位置
                sourceCard->playMoveAnimation(record.sourceOriginalPos, 0.3f);
                // 目标卡牌恢复到原位置
                targetCard->playMoveAnimation(record.targetOriginalPos, 0.3f);
            }
            break;
        }
    }
}

void GameController::updateUndoButtonState() {
    bool canUndo = _undoManager->canUndo();
    _gameView->setUndoButtonEnabled(canUndo);
    CCLOG("GameController: Undo button state updated - %s", canUndo ? "enabled" : "disabled");
}

bool GameController::checkWinCondition() {
    // 检查桌面是否还有牌
    const auto& playFieldCards = _gameModel->getPlayFieldCards();
    
    if (playFieldCards.empty()) {
        CCLOG("GameController: Win condition met!");
        showWinMessage();
        return true;
    }
    
    return false;
}

void GameController::showWinMessage() {
    // 创建胜利提示标签
    auto label = Label::createWithSystemFont("You Win!", "Arial", 48);
    label->setPosition(_gameView->getContentSize() / 2);
    label->setTextColor(Color4B::YELLOW);
    _gameView->addChild(label, 100);
    
    // 添加淡入淡出动画
    auto fadeIn = FadeIn::create(0.5f);
    auto delay = DelayTime::create(2.0f);
    auto fadeOut = FadeOut::create(0.5f);
    auto remove = RemoveSelf::create();
    auto sequence = Sequence::create(fadeIn, delay, fadeOut, remove, nullptr);
    label->runAction(sequence);
}