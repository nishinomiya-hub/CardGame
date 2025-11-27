#include "CardModel.h"

CardModel::CardModel(int id, int number, Suit suit, bool isFaceUp)
    : _id(id)
    , _number(number)
    , _suit(suit)
    , _isFaceUp(isFaceUp)
    , _isInHandArea(false)
{
}