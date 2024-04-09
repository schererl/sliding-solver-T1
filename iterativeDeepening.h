#ifndef IDS_H
#define IDS_H
#include "tilepuzzle.h"

void id_solver(const TILE_size& initial_state, int blank_x, int blank_y);

int DFLS(const TILE_size &state, Move last_move, const int &blank_x, const int &blank_y, const int &d_limit, int depth, int &expanded_nodes);
#endif