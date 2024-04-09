#include "iterativeDeepening.h"
#include "tilepuzzle.h"

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
    int expanded_nodes = 0;
    for(size_t depth_limit =0;;depth_limit++){
        int goal_reached = DFLS(initial_state, Move::NONE, blank_x, blank_y, depth_limit, 0, expanded_nodes);
        if(goal_reached >= 0){
            std::cout << "Goal reached after " << goal_reached << " moves.\nNodes expanded " << expanded_nodes << std::endl;
            break;
        }
    }
}