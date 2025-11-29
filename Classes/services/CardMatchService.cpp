#include "CardMatchService.h"
#include <cmath>

bool CardMatchService::isMatch(const CardModel* card1, const CardModel* card2) {
    if (!card1 || !card2) {
        return false;
    }
    
    return isNumberMatch(card1->getNumber(), card2->getNumber());
}

bool CardMatchService::isNumberMatch(int number1, int number2) {
    return std::abs(number1 - number2) == 1;
}