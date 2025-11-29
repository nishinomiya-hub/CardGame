#include "GameModelFromLevelGenerator.h"
#include "models/GameModel.h"


GameModel* GameModelFromLevelGenerator::generateFromLevel(const LevelConfig* levelConfig) {
    GameModel* gameModel = new GameModel();
    
    // 创建桌面牌区卡牌
    int cardId = 1;
    const auto& playFieldCards = levelConfig->getPlayFieldCards();
    for (const auto& cardConfig : playFieldCards) {
        CardModel* cardModel = createCardModel(cardConfig, cardId++);
        cardModel->setPosition(cardConfig.position);
        gameModel->addCardToPlayField(cardModel);
    }
    
    // 创建手牌区卡牌
    const auto& stackCards = levelConfig->getStackCards();
    for (const auto& cardConfig : stackCards) {
        CardModel* cardModel = createCardModel(cardConfig, cardId++);
        cardModel->setPosition(cardConfig.position);
        gameModel->addCardToHandArea(cardModel);
    }
    
    return gameModel;
}

CardModel* GameModelFromLevelGenerator::createCardModel(const CardConfig& cardConfig, int id) {
    CardModel::Suit suit = LevelConfig::convertSuit(cardConfig.cardSuit);
    CardModel* cardModel = new CardModel(id, cardConfig.cardFace, suit);
    return cardModel;
}