#include "piece.h"
#include "queen.h"
#include "chess.h"
#include "point.h"
#include "bishop.h"
#include <vector>       // std::vector<T>
#include <algorithm>    // std::random_shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;


void Bishop::populationShuffler(vector<int>& xChromosome,
    vector<int>& yChromosome, vector<vector<Point>>& population, const int& populationLimit) {
    // Shuffle all parent genes in the population randomly
    for (int i = 0; i < populationLimit; i++) {
        // Create a seed
        unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();

        // shuffle x
        shuffle(xChromosome.begin(), xChromosome.end(), default_random_engine(rand() + seed));
        // shuffle y 
        shuffle(xChromosome.begin(), xChromosome.end(), default_random_engine(rand() + seed + seed));
        population.push_back(xChromosome + yChromosome);
    }
}

bool Bishop::peiceLogic(const Point& p1, const Point& p2, const Chess* chess) {
    // Check diagnols for attacking bishops
    return (abs(p1.x - p2.x) == abs(p1.y - p2.y));
}

void Bishop::mutateChildren(vector<vector<Point>>& children, const double& mutateProb, const int &tableSize) {
    double randomProb = (double)rand() / (double)RAND_MAX;

    unsigned int childSize = children[0].size();
    if (randomProb <= mutateProb) {
        for (auto& child : children) {
            int randGeneIndex = rand() % childSize;
            // Mutate x chromosome
            int xRandGeneMutation = rand() % tableSize;
            child[randGeneIndex].x = xRandGeneMutation;

            // Mutate y chromosome
            int yRandGeneMutation = rand() % tableSize;
            child[randGeneIndex].y = yRandGeneMutation;

        }
    }

}

int Bishop::findChromeSize(const int& tableSize) {
    return { 2 * tableSize - 2 };
}

char Bishop::getLetter() const {
    return letter;
}
