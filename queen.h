#ifndef QUEEN_H
#define QUEEN_H   

#include <vector>   // std::vector<T>

using namespace std;

class Piece;
struct Point;

class Queen : public Piece{
  protected:
    // Genetic Algorithm helper functions
      vector<vector<Point>> createPopulation(const int& populationLimit, const int& chromSize, const int& tableSize) override;
    vector<int> calculatePopulationFitness(const vector<vector<Point>> &population, const Chess* chess) override;
    vector<vector<Point>> findBestParents(const vector<vector<Point>> &population, const vector<int> &fitness, int numMatingParents) override;
    vector<vector<Point>> crossOver(const vector<vector<Point>> &parents, const int &numOffsprng) override;
    virtual void mutateChildren(vector<vector<Point>> &children, const double &mutateProb, const int & tableSize) override;

    // Queen functions
    virtual void populationShuffler(vector<int>& xChromosome,
        vector<int>& yChromosome, vector<vector<Point>>& population, const int& populationLimit);
    virtual bool peiceLogic(const Point& p1, const Point& p2, const Chess* chess) override;
    int countSafePieces(const vector<Point> &parent, const Chess * chess) override;
    virtual void removeAttackingPieces(vector<Point> &parent, const Chess * chess) override;

  public:
    Queen():Piece('Q') { }
    Queen(char letter):Piece(letter) { }
    ~Queen() { }
    virtual int findChromeSize(const int& tableSize);
    virtual char getLetter() const;
};

#endif