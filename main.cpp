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

Method search_method(std::string method_name){
    // switch does not work with std::string (?)
    if (method_name == "-bfs") {
        return BFS_M;
    } else if (method_name == "-idfs") {
        return IDFS_M;
    } else if (method_name == "-astar") {
        return ASTAR_M;
    } else if (method_name == "-idastar") {
        return IDASTAR_M;
    } else if (method_name == "-gbfs") {
        return GBFS_M;
    }
    
    return INVALID_M;
    
}

Method read_arguments(std::vector<int>& puzzle, int argc, char* argv[]){
    // if (argc < 11){
    //     std::cerr << "ERROR: The number of arguments are lesser than required." << std::endl;
    // }

    std::string method_name = argv[1]; 
    Method method = search_method(method_name);

    int count = 0;
    std::string s;
    for (int i = 2; i < argc; i++) {
        count++;
        s = argv[i];
        std::stringstream ss(s);
        std::string num;

        while (ss >> num) {
            if(num.find(',') != -1){
                count = 0;
            }
            puzzle.push_back(stoi(num));
            
        }
    }

    configurePuzzle(count);

    return method;

}

int main(int argc, char *argv[]){
    // if (argc != 2)
    // {
    //     std::cout << "Usage:  <file_name>" << std::endl;
    //     return 1;
    // }

    std::vector<int> puzzle;

    Method search_method = read_arguments(puzzle, argc, argv);

    // std::string file_name = argv[1];

    // std::ifstream file(file_name);
    // if (!file.is_open())
    // {
    //     std::cerr << "Unable to open file: " << file_name << std::endl;
    //     return 1;
    // }
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
