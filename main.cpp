#include "tilepuzzle.h"
//#include "memcontrol.h"
#include "bfs.h"
#include "HeuristicSearch.h"
#include "iterativeDeepening.h"
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>



int main(int argc, char *argv[]){
    if (argc != 2)
    {
        std::cout << "Usage:  <file_name>" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];

    std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return 1;
    }

    std::string line;
    auto init_time = std::chrono::high_resolution_clock::now();
    while (std::getline(file, line))
    {
        
        std::istringstream iss(line);
        std::vector<int> tiles;
        int tile;
        while (iss >> tile)
        {
            tiles.push_back(tile);
        }

        auto [state, blank_x, blank_y] = vectorToState(tiles);
        auto start_solver_time = std::chrono::high_resolution_clock::now();
        //heuristic_solver(state, blank_x, blank_y, ASTAR);
        id_solver(state, blank_x, blank_y);
        //bfs_solver(state, blank_x, blank_y);
    }

    std::chrono::duration<double> total_elapsed = std::chrono::high_resolution_clock::now() - init_time;
    std::cout << "Total time taken for all instances: "
              << total_elapsed.count() << " seconds." << std::endl;

    file.close();
    return 0;
}
