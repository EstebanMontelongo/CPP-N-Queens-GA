#include "point.h"
#include <vector>       // std::vector<T>
using namespace std;

Point::Point():x(-1), y(-1) {}

Point::Point(int x, int y): x(x), y(y) {}

bool operator==(const Point& lhs, const Point& rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

ostream& operator<<(ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

vector<Point> operator+(const vector<int>& xVec, const vector<int>& yVec) {
	vector<Point> result;
	unsigned int xSize = xVec.size();
	if (xSize != yVec.size()) {
		return vector<Point>();
	}
	result.reserve(xSize);
	for (unsigned int i = 0; i < xSize; i++) {
		result.push_back(Point(xVec[i], yVec[i]));
	}

	return result;
}

Point operator+(const Point& lhs, const Point& rhs) {
	return Point((lhs.x + rhs.x), (lhs.y + rhs.y));
}