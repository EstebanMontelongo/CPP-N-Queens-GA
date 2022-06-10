#include "piece.h"
#include "queen.h"
#include "chess.h"
#include "point.h"
#include "bishop.h"
#include "knight.h"
#include <vector>       // std::vector<T>
#include <algorithm>    // std::random_shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;


const vector<Point> MOVES = {
    Point(2, -1), Point(1, 2),
    Point(2, 1), Point(1, -2),
    Point(-2, -1), Point(-1, 2),
    Point(-2, 1), Point(-1, -2),
};

bool Knight::peiceLogic(const Point& p1, const Point& p2, const Chess* chess) {
    // If they are overlaping return 
    if (p1 == p2) {
        return true;
    }

    // Check knights attacking sqaures
    for (auto move : MOVES) {
        Point p1Shifted = p1 + move;
        //bool isInBounds = isCoordinatesInbound(p1Shifted, p2, chess);
        if (p1Shifted == p2) {
            return true;
        }
    }

    // No attacking spots hits anothe knight
    return false;
}


int Knight::findChromeSize(const int& tableSize) {
    // Maximum knights on board estimation
    int K = (int)((tableSize - 1) / 2);

    if (tableSize % 2 == 0) {
        return (int)((tableSize * tableSize) / 2);
    }
    return (int)(2 * (K * K + K) + 1);
}

char Knight::getLetter() const {
    return letter;
}