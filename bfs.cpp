#include "bfs.h"
#include "tilepuzzle.h"

#include <chrono>
using namespace std::chrono;
void bfs_solver(const TILE_size& initial_state, const int &blank_x, const int &blank_y) {
    auto overall_start = high_resolution_clock::now();
    Node *initial_node = new Node(initial_state, Move::NONE, 0, 0, 0, 0, blank_x, blank_y);
    size_t expanded_nodes = 0;
    
    std::queue<Node*> open;
    open.push(initial_node);
    std::unordered_set<TILE_size> visited;
    visited.insert(initial_state);

    
    while (!open.empty()) {
        Node* current = open.front();
        expanded_nodes+=1;
        open.pop();
        //std::cout << *current << std::endl;

        for (auto& [m, next_state, next_bx, next_by] : successors(current->state, current->blank_x, current->blank_y)){
            // Move m;
            // TILE_size next_state;
            // int next_bx, next_by;
            // std::tie(m, next_state, next_bx, next_by) = succ;
            if (visited.find(next_state) != visited.end()) continue;
        
            if (isGoal(next_state)) {
                //std::cout << "Goal reached after " << current->moves_count+1 << " moves.\nNodes expanded " << expanded_nodes << std::endl;
                auto total_solving_time = duration_cast<duration<double>>(high_resolution_clock::now() - overall_start);
                std::cout << expanded_nodes << ',' << current->moves_count+1 << ',' << total_solving_time.count() <<',' << 0 << ',' << 0 << std::endl;
                while (!open.empty()) {
                    delete open.front();
                    open.pop();
                }
                break;
            }

            Node* next_node = new Node(next_state, m, current->moves_count + 1, 0, 0, 0, next_bx, next_by);
            open.push(next_node);
            visited.insert(next_state);
        }
        delete current;
    }
    

    

}