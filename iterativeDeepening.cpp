#include "iterativeDeepening.h"
#include "tilepuzzle.h"
#include "Heuristic.h"
#include <chrono>
using namespace std::chrono;
#define FAIL_VALUE -1
int DFLS(const TILE_size &state, Move last_move, const int &blank_x, const int &blank_y, const int &d_limit, int depth, int &expanded_nodes){
    if(isGoal(state)){
        return depth;
    }

    if(d_limit>depth){
        expanded_nodes+=1;
        for (auto& [m, next_state, next_bx, next_by] : successors(state, blank_x, blank_y)){
            if(opposite(last_move, m)) continue;
            int returnValue = DFLS(next_state, m, next_bx, next_by, d_limit, depth+1, expanded_nodes);
            if (returnValue != FAIL_VALUE){
                return returnValue;
            }
        }
    }

    return FAIL_VALUE;
}

void id_solver(const TILE_size& initial_state, const int &blank_x, const int &blank_y) {
    auto overall_start = high_resolution_clock::now();
    int expanded_nodes = 0;
    int goal_reached=FAIL_VALUE;
    for(size_t depth_limit =0;;depth_limit++){
        goal_reached = DFLS(initial_state, Move::NONE, blank_x, blank_y, depth_limit, 0, expanded_nodes);
        if(goal_reached >= 0){
            break;
        }
    }
    auto total_solving_time = duration_cast<duration<double>>(high_resolution_clock::now() - overall_start).count();
    if(total_solving_time < 30){
        std::cout << expanded_nodes << ',' << goal_reached << ',' << total_solving_time << ',' << 0 << ',' << Heuristic(initial_state).init_h << std::endl;
    } else {
        std::cout << "-,-,-,-,-" << std::endl;
    }
    
}