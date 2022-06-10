#include "piece.h"
#include "chess.h"
#include "point.h"

#include <string>   // std::string
#include <iostream> // std::cout, std::endl

using namespace std;

Chess::Chess(): chess_piece(nullptr), game_state(vector<Point>()), table_size(0){}

Chess::Chess(Piece* chess_piece, const int& chrom_size, const int& table_size): 
    chess_piece(chess_piece),
    game_state(vector<Point>(chrom_size, Point{ -1, -1 })),
    table_size(table_size){}

ostream& operator<<(ostream& os, const Chess& c){
    os << "[";
    unsigned int chromSize = c.game_state.size();
    for (unsigned int i = 0; i < chromSize; ++i) {
        os << "(" << c.game_state[i].x << ", " << c.game_state[i].y << ")";
        if (i != chromSize - 1)
            os << ", ";
    }
    os << "]" << endl;
    return os;
}

void Chess::solve(const int &initialPopSize, const int &populationLimit,
 const int &generationLimit, const int &numMatingParents, const double &mutateProb){
  chess_piece->genetic_algorithm(initialPopSize, populationLimit, generationLimit, numMatingParents, mutateProb, this);
}

// Ugly printing fucntion...
void Chess::printState(Piece* chess_piece) const{
    vector<Point> copy = game_state;
    string line = "|";
    for (int x = 0; x < table_size; x++) {
        for (int y = 0; y < table_size; y++) {
            bool found = false;
            if (y == 0 && x != 0) {
                line += "|";
            }
            for (auto& state : copy) {
                if (state == Point(x, y)) {
                    line += chess_piece->getLetter();
                    state = Point(-1, -1);
                    found = true;
                }
            }
            if (!found) {
                line += " ";
            }
            line += '|';
        }
        unsigned int lineSize = line.size();

        for (unsigned int i = 0; i < lineSize; i++) {
            if (i != 0) {
                cout << "_" << line[i];
            }
            else {
                cout << line[i];
            }
        }
        cout << endl;
        line = "";
   }
    cout << endl;
}