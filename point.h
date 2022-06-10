#ifndef POINT_H
#define POINT_H

#include <vector>		// std::vector<T>
#include <iostream>		// std::ostream

using namespace std;

struct Point {
	int x;
	int y;
	Point();
	explicit Point(int x, int y);
	
	friend ostream& operator<<(ostream& os, const Point& p);
	Point(const Point& p) { x = p.x; y = p.y; }
};

bool operator==(const Point& lhs, const Point& rhs);

vector<Point> operator+(const vector<int>& xVec, const vector<int>& yVec);

Point operator+(const Point& lhs, const Point& rhs);
#endif

