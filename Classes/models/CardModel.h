#pragma once

#include <string>

#include "cocos2d.h"

//存放卡片信息 点数 花色 位置

class CardModel {
public:
    enum class Suit {
        HEARTS,    // 红心
        DIAMONDS,  // 方块  
        CLUBS,     // 梅花
        SPADES     // 黑桃
    };

    CardModel(int id, int number, Suit suit, bool isFaceUp = true);
    
    // Getters
    int getId() const { return _id; }
    int getNumber() const { return _number; }
    Suit getSuit() const { return _suit; }
    bool isFaceUp() const { return _isFaceUp; }
    bool isInHandArea() const { return _isInHandArea; }
    
    // Setters
    void setFaceUp(bool faceUp) { _isFaceUp = faceUp; }
    void setInHandArea(bool inHandArea) { _isInHandArea = inHandArea; }
    void setPosition(const cocos2d::Vec2& position) { _position = position; }
    cocos2d::Vec2 getPosition() const { return _position; }

private:
    int _id;                    // 卡牌唯一ID
    int _number;                // 卡牌点数 (A=1, 2-10, J=11, Q=12, K=13)
    Suit _suit;                 // 花色
    bool _isFaceUp;             // 是否正面朝上
    bool _isInHandArea;         // 是否在手牌区
    cocos2d::Vec2 _position;    // 位置信息
};