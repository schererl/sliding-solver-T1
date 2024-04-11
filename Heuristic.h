#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "tilepuzzle.h"

class Heuristic {
public:
    float heuristic_acc;
    int heuristic_count;
    int init_h;
    Heuristic(const TILE_size &state);
    int heuristic(const TILE_size &state);
    int optimized_heuristic(const TILE_size& state, Move last_move, int last_heuristic, int blank_x, int blank_y);
    double getAvgH();
    void initH();
};

#endif // HEURISTIC_H
