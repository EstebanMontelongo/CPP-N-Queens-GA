#ifndef ROOK_H
#define ROOK_H

class Queen;
class Chess;
struct Point;

class Rook : public Queen {
	private:
		bool peiceLogic(const Point& p1, const Point& p2, const Chess* chess);
	public:
		Rook():Queen('R') { }
		Rook(char letter) :Queen(letter) { }
		~Rook() {}
		virtual char getLetter() const;
};

#endif 

