#ifndef ASTAR_H
#define ASTAR_H

#include "tilepuzzle.h"
#include "Heuristic.h"

#include <queue>
#include <unordered_set>
enum AlgorithmMode { ASTAR, GBFS };
void heuristic_solver(const TILE_size& initial_state, int blank_x, int blank_y, AlgorithmMode mode);

#endif