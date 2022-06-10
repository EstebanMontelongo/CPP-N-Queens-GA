#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>   // std::vector<T>

using namespace std;

class Queen;
class Chess;
class Bishop;
struct Point;

class Knight : public Bishop {
private:
	bool peiceLogic(const Point& p1, const Point& p2, const Chess* chess);

public:
	Knight():Bishop('K') { }
	Knight(char letter):Bishop(letter) { }
	~Knight() { }
	int findChromeSize(const int& tableSize);
	virtual char getLetter() const;
	
};

#endif 
