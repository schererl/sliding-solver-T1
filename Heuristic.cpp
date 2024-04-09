#include "Heuristic.h"
#include <cmath>

#include "tilepuzzle.h"

Heuristic::Heuristic(const TILE_size &state){
    heuristic_count = 0;
    heuristic_acc = 0;
    init_h = heuristic(state);
}

int Heuristic::heuristic(const TILE_size &state) {
    int h_value = 0;
    for(int i = 0; i < ROW_COL_SIZE; i++){
        for(int j = 0; j < ROW_COL_SIZE; j++){
            int goal_x = i;
            int goal_y = j;
            
            int tile_pos = (TILE_BIT_SIZE) * (i * ROW_COL_SIZE + j);
            int tile_val = (state >> tile_pos) & 0xF;
            if(tile_val == 0) continue;

            int tile_x = tile_val/ROW_COL_SIZE;
            int tile_y = tile_val%ROW_COL_SIZE;
            h_value+=std::abs(goal_x-tile_x) + std::abs(goal_y-tile_y);

        }
    }
    heuristic_count++;
    heuristic_acc += h_value;
    return h_value;
}

int Heuristic::optimized_heuristic(const TILE_size& state, Move last_move, int last_heuristic, int blank_x, int blank_y) {
    int dx = 0, dy = 0;
    // get the moved tile last position (opposite dir of the last move)
    switch (last_move) {
        case UP:    dx = 1;  break; 
        case DOWN:  dx = -1; break; 
        case LEFT:  dy = 1;  break; 
        case RIGHT: dy = -1; break; 
        default: return heuristic(state);
    }
    
    // moved tile last position
    int moved_tile_x = blank_x + dx;
    int moved_tile_y = blank_y + dy;

    int tile_pos = TILE_BIT_SIZE * (moved_tile_x * ROW_COL_SIZE + moved_tile_y);
    int moved_tile_val = (state >> tile_pos) & 0xF;

    // calculate goal position for the moved tile
    int goal_x = moved_tile_val / ROW_COL_SIZE;
    int goal_y = moved_tile_val % ROW_COL_SIZE;

    // compute the old and new distances
    int new_dist = std::abs(goal_x - moved_tile_x) + std::abs(goal_y - moved_tile_y);
    int old_dist = std::abs(goal_x - blank_x) + std::abs(goal_y - blank_y);

    int h_value=last_heuristic - old_dist + new_dist;
    heuristic_count++;
    heuristic_acc += h_value;
    return h_value;
    
}

double Heuristic::getAvgH() {
    if (heuristic_count == 0) return 0; // Prevent division by zero
    return static_cast<double>(heuristic_acc) / heuristic_count;
}

void Heuristic::initH() {
    heuristic_count = 0;
    heuristic_acc = 0;
}
