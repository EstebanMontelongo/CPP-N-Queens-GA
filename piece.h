#ifndef PIECE_H
#define PIECE_H   

#include <vector>   // std::vector<T>

using namespace std;

class Chess;
struct Point;

class Piece {
    protected:
        // GA functions
        virtual vector<vector<Point>> createPopulation(const int& populationLimit, const int& chromSize, const int & tableSize) = 0;
        virtual vector<int> calculatePopulationFitness(const vector<vector<Point>>& population, const Chess* chess) = 0;
        virtual vector<vector<Point>> findBestParents(const vector<vector<Point>>& population, const vector<int>& fitness, int numParents = 1) = 0;
        virtual vector<vector<Point>> crossOver(const vector<vector<Point>>& parents, const int& numOffsprng) = 0;
        virtual void mutateChildren(vector<vector<Point>>& children, const double& mutateProb, const int &tableSize) = 0;
        void genetic_algorithm(const int& initialPopSize, const int& populationLimit,
            const int& generationLimit, const int& numMatingParents, const double& mutateProb, Chess* chess);

    // Piece functions
    virtual bool peiceLogic(const Point& p1, const Point& p2, const Chess* chess) = 0;
    bool isCoordinatesInbound(const Point& p1, const Point& p2, const Chess* chess);
    virtual int countSafePieces(const vector<Point>& parent, const Chess* chess) = 0;
    virtual void removeAttackingPieces(vector<Point>& parent, const Chess* chess) = 0;
    void setGameState(Chess* chess, vector<Point> game_state);

    char letter;

public:
    Piece():letter(' ') { }
    Piece(char letter):letter(letter) { }
    ~Piece() { }
    virtual int findChromeSize(const int& tableSize) = 0;
    virtual char getLetter() const = 0;
    friend Chess;
};

#endif