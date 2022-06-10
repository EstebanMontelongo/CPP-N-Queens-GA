#include "piece.h"
#include "queen.h"
#include "point.h"
#include <iostream>     // std::cout, std::endl
#include <vector>       // std::vector<T>
#include <algorithm>    // std::random_shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

void Queen::populationShuffler(vector<int>& xChromosome,
    vector<int>& yChromosome, vector<vector<Point>>& population, const int& populationLimit) {
    // Shuffle all parent genes in the population randomly
    for (int i = 0; i < populationLimit; i++) {
        // Create a seed
        unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
        shuffle(yChromosome.begin(), yChromosome.end(), default_random_engine(rand() + seed));
        population.push_back(xChromosome + yChromosome);
    }
}
// Create a population with each parent having N random genes
vector<vector<Point>> Queen::createPopulation(const int& populationLimit, const int& chromSize, const int& tableSize) {
  // Create a parent with 0 - (N - 1) Genes
  vector<int> xChromosome;
  vector<int> yChromosome;
  xChromosome.reserve(chromSize);
  yChromosome.reserve(chromSize);
  for(unsigned int i = 0; i < (unsigned int)chromSize; i++){
      xChromosome.push_back(i%(tableSize));
      yChromosome.push_back(i%(tableSize));
  }

  vector<vector<Point>> population;
  population.reserve(populationLimit);
  populationShuffler(xChromosome, yChromosome, population, populationLimit);
  
  return population;
}

// Returns true if two pieces are attacking each
// This causes the most cpu overhead
bool Queen::peiceLogic(const Point& p1, const Point& p2, const Chess* chess){
  // If coordinates in bound, check if they attack each other, else return false.
  return (p1.x == p2.x) || (p1.y == p2.y) || (abs(p1.x - p2.x) == abs(p1.y - p2.y));
}

// Counts the number of safe pieces
int Queen::countSafePieces(const vector<Point> &parent, const Chess * chess){
  unsigned int parentSize = parent.size();
  int safePieces = parentSize;
  for(unsigned int p1 = 0; p1 < parentSize; p1++){
    bool isAttacked = false;
    const Point &point1 = parent[p1];
    for(unsigned int p2 = p1 + 1; p2 < parentSize; p2++){
      const Point &point2 = parent[p2];
      if (peiceLogic(point1, point2, chess)){
        isAttacked = true;
        break;
      }     
    }
    if(isAttacked){
      safePieces--;
    }
  } 

  return safePieces;
}

// Sets all attacked pieces to negative as indicator to remove
void Queen::removeAttackingPieces(vector<Point> &parent, const Chess * chess){
 // vector<Point> parentCopy = parent;
  unsigned int parentSize = parent.size();

  for (unsigned int p1 = 0; p1 < parentSize; p1++) {
      Point& point1 = parent[p1];
      for (unsigned int p2 = p1 + 1; p2 < parentSize; p2++) {
          Point& point2 = parent[p2];
          if (peiceLogic(point1, point2, chess)) {
              point1.x = -1;
              point1.y = -1;
              break;
          }
      }
  }
}

// Calculating the fitness score for all the current parents in the population
vector<int> Queen::calculatePopulationFitness(const vector<vector<Point>> &population, const Chess* chess){
  vector<int> fitness;
  fitness.reserve(population.size());

  for(auto &parent : population){
    fitness.push_back(countSafePieces(parent, chess));
  }

  return fitness;
}

// Find N best parents, return their indices within the population
vector<vector<Point>> Queen::findBestParents(const vector<vector<Point>> &population, const vector<int> &fitness, int numParents = 1){
  if (population.size() < (unsigned int)numParents){
    cout << "The number of parents must be smaller or equal to the population size" << endl;
    exit(0);
  }
  
  vector<vector<Point>> bestParents;
  bestParents.reserve(numParents);
  vector<int> fitnessCopy = fitness;

    for (int i = 0;  i < numParents; i++){
      // find current max value
      int max_value = *max_element(fitnessCopy.begin(), fitnessCopy.end());
      // find its index in original fitness list and save it
      vector<int> v = {max_value};
      vector<int>::iterator it = find_first_of(fitnessCopy.begin(), fitnessCopy.end(), v.begin(), v.end());
      int max_index = int(it - fitnessCopy.begin());
      bestParents.push_back(population[max_index]);
      // remove the max value from tmp list to find the next largest fitness score
      fitnessCopy[max_index] = -1;
    }
        

  return bestParents;
}

// Randomly selected parents to create off spring by crossover of their genes randomly 
vector<vector<Point>> Queen::crossOver(const vector<vector<Point>> &parents,const int &numOffsprng){
    unsigned int chromosomeSize = parents[0].size();
    unsigned int currPopulation = parents.size();

    // Return original parents since no crossover is possible
    if (chromosomeSize == 1 || currPopulation == 1){
        return parents;
    }

    vector<Point> chromosomes;
    chromosomes.reserve(chromosomeSize);
    vector<vector<Point>> children(numOffsprng, chromosomes);

    for(auto &child : children){
      int rand_idx1 = rand()%currPopulation;
      int rand_idx2 = rand()%currPopulation;
      // Same idex catch
      while(rand_idx1 == rand_idx2){
        rand_idx2 = rand()%currPopulation;
      }
      unsigned int geneIndex = rand()%chromosomeSize;

      while(geneIndex == 0 || geneIndex == chromosomeSize - 1){
          geneIndex = rand()%chromosomeSize;
      }

      for (unsigned int c = 0; c < chromosomeSize; c++) {
          if (c <= geneIndex){
              child.push_back(parents[rand_idx1][c]);
          }
          else {
              child.push_back(parents[rand_idx2][c]);
          }
      }
    }
    return children;
}

// Randomly mutate a single gene from the each offspring if mutation prob is met
void Queen::mutateChildren(vector<vector<Point>> &children, const double &mutateProb, const int &tableSize){
  double randomProb = (double)rand() / (double)RAND_MAX;
  
  unsigned int childSize = children[0].size();
  if(randomProb <= mutateProb){
    for(auto &child : children){
      int randGeneIndex = rand()%childSize;
      int yRandGeneMutation = rand()%tableSize;
      child[randGeneIndex].y = yRandGeneMutation;

    }
  }
}

int Queen::findChromeSize(const int& tableSize) {
    return tableSize;
}

char Queen::getLetter() const {
    return letter;
}

