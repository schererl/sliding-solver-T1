#ifndef BFS_H
#define BFS_H
#include "tilepuzzle.h"
#include <memory>
#include <queue>
#include <unordered_set>

void bfs_solver(const TILE_size& initial_state, const int &blank_x, const int &blank_y);

#endif