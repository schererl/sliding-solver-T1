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
    std::vector<int> puzzle;

    // vai pegar todos os números do argumento e por no vetor puzzle
    Method search_method = read_arguments(puzzle, argc, argv);

    
    auto init_time = std::chrono::high_resolution_clock::now();
    int offset = 0;
    while(offset < puzzle.size()){
        std::vector<int> tiles(puzzle.begin()+offset, puzzle.begin()+offset+PuzzleSize());

        auto [state, blank_x, blank_y] = vectorToState(tiles);
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

        offset += PuzzleSize();
    }
    std::chrono::duration<double> total_elapsed = std::chrono::high_resolution_clock::now() - init_time;
    std::cout << "Total time taken for all instances: "
              << total_elapsed.count() << " seconds." << std::endl;

    // file.close();
    return 0;
}
