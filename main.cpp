#include "chess.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "point.h"
#include <iostream>

int main(int argc, const char * argv[]){
  Queen q;
  Bishop b;
  Rook r;
  Knight k;
  vector<Piece*> pieces = { &q, &b, &r, &k };

  for (auto piece : pieces){
      int tableSize = 25;
      int chromosomeSize = piece->findChromeSize(tableSize);
      int populationLimit = 100;
      int initialPopSize = 1000;
      int generationLimit = 1000;
      int numMatingParents = 3;
      double mutateProb = 0.95;

      Chess c(piece, chromosomeSize, tableSize);
      c.solve(initialPopSize, populationLimit, generationLimit, numMatingParents, mutateProb);
      c.printState(piece);
      std::cin.get();
  }
  
  
  std::cin.get();
}