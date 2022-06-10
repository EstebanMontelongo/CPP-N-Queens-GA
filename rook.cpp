#include "piece.h"
#include "queen.h"
#include "point.h"
#include "rook.h"

bool Rook::peiceLogic(const Point & p1, const Point & p2, const Chess * chess) {
    // Only check vertical attacks because we never set any two horizontal the same.
    return (p1.y == p2.y);
}

char Rook::getLetter() const {
    return letter;
}