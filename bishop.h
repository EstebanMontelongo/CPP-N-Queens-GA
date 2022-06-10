#ifndef BISHOP_H
#define BISHOP_H

#include <vector>   // std::vector<T>

using namespace std;

class Queen;
class Chess;
struct Point;

class Bishop : public Queen {
	protected:
		void populationShuffler(vector<int>& xChromosome,
			vector<int>& yChromosome, vector<vector<Point>>& population, const int& populationLimit);
		void mutateChildren(vector<vector<Point>>& children, const double& mutateProb, const int &tableSize);
		virtual bool peiceLogic(const Point& p1, const Point& p2, const Chess* chess);

	public:
		Bishop():Queen('B') { }
		Bishop(char letter):Queen(letter) { }
		~Bishop() { }
		
		virtual int findChromeSize(const int& tableSize);
		virtual char getLetter() const;
		
};

#endif 
