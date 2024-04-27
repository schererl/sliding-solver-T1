#include "tilepuzzle.h"
//#include "memcontrol.h"
#include "bfs.h"
#include "HeuristicSearch.h"
#include "iterativeDeepening.h"
#include "IdAstar.h"
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>


int main(int argc, char *argv[]){
    std::vector<std::vector<int>> puzzles;

    // vai pegar todos os números do argumento e por no vetor puzzle
    Method search_method = read_arguments(puzzles, argc, argv);

    
    auto init_time = std::chrono::high_resolution_clock::now();
    
    for(auto &puzzle:puzzles){
        configurePuzzle(puzzle.size());
        auto [state, blank_x, blank_y] = vectorToState(puzzle);
        auto start_solver_time = std::chrono::high_resolution_clock::now();
        
        switch (search_method)
        {
            case ASTAR_M:        
                heuristic_solver(state, blank_x, blank_y, ASTAR);
                break;
            case GBFS_M:
                heuristic_solver(state, blank_x, blank_y, GBFS);
                break;
            case IDFS_M:
                id_solver(state, blank_x, blank_y);
                break;
            case BFS_M:
                bfs_solver(state, blank_x, blank_y);
                break;
            case IDASTAR_M:
                idAstarSolver(state, blank_x, blank_y);
                break;
        }

    }
    std::chrono::duration<double> total_elapsed = std::chrono::high_resolution_clock::now() - init_time;
    std::cout << "Total time taken for all instances: "
              << total_elapsed.count() << " seconds." << std::endl;

    // file.close();
    return 0;
}
