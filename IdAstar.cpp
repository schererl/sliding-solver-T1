#include "IdAstar.h"
#include "Heuristic.h"
#include <chrono>

using namespace std::chrono;

#define FAIL_VALUE -1

std::pair<int, uint32_t> idAstar(const TILE_size &state, Move last_move, const int &blank_x, const int &blank_y, const int &f_limit, int depth, int &expanded_nodes, Heuristic &heuristic){
    
    int h_value = heuristic.heuristic(state);
    int f = depth + h_value;

    if( f > f_limit ){
        return {f, FAIL_VALUE};
    }
    
    if(isGoal(state)){
        return {0, depth};
    }

    expanded_nodes+=1;

    int next_limit = INT32_MAX;

    for (auto& [m, next_state, next_bx, next_by] : successors(state, blank_x, blank_y)){
        if(opposite(last_move, m)) continue;

        std::pair<int, uint32_t> result = idAstar(next_state, m, next_bx, next_by, f_limit, depth+1, expanded_nodes, heuristic);
        
        if(result.second != FAIL_VALUE){
            return {f, result.second};
        }
        
        next_limit = std::min(next_limit, result.first);
    }

    return {next_limit, FAIL_VALUE};
}



void idAstarSolver(const TILE_size& initial_state, const int &blank_x, const int &blank_y){
    auto overall_start = high_resolution_clock::now();

    Heuristic h = Heuristic(initial_state);

    std::pair<int, uint32_t> solution;
    uint32_t result;
    int expanded_nodes = 0;

    int f_limit = h.init_h;

    while(f_limit != INT32_MAX){
        solution = idAstar(initial_state, Move::NONE, blank_x, blank_y, f_limit, 0, expanded_nodes, h);

        f_limit = solution.first;
        result = solution.second;
        if(result != FAIL_VALUE){
            break;
        }
    }
    auto total_solving_time = duration_cast<duration<double>>(high_resolution_clock::now() - overall_start);

    std::cout << expanded_nodes << ',' << solution.second << ',' << total_solving_time.count() << ',' << h.heuristic_acc/h.heuristic_count << ',' << h.init_h << std::endl;
}