#ifndef CHESS_H
#define CHESS_H   

#include <vector>   // std::vector<T>
#include <iostream> // std::ostream

using namespace std;

class Piece;
struct Point;

class Chess{
    Piece *chess_piece;
    vector<Point> game_state;
    const int table_size;
    
  public:
    Chess(); 
    Chess(Piece *chess_piece, const int &chrom_size, const int &table_size);

    void solve(const int &initialPopSize, const int &populationLimit,
     const int &generationLimit, const int &numMatingParents, const double &mutateProb);
    void printState(Piece* chess_piece) const;
    
    friend ostream& operator<<(ostream& os, const Chess& c);
    friend Piece;

  private:
    void setGameState(vector<Point> &game_state){this->game_state = game_state;}
};
#endif
