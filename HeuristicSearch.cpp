#include "HeuristicSearch.h"
#include "Memcontrol.h"
#include "tilepuzzle.h"
#include "Heuristic.h"
#include <functional>
#include <chrono>
#include <stack>

#define MAX_F 120
#define MAX_H 60

static size_t solved_count = 0;
static size_t problems_count = 0;

typedef struct{
    std::stack<Node*> bucket[MAX_F*MAX_H];
    std::pair<int, int> min_node = {MAX_F, MAX_H};
    int count_elements = 0;

    void push(Node* node){
        int f = node->h_value + node->g_value;
        int h = node->h_value;

        if(f < min_node.first){
            min_node = {f, h};
        } else if (f == min_node.first){
            if(h < min_node.second){
                min_node = {f, h};
            }
        }
        
        bucket[f*MAX_H + h].push(node);        
        count_elements++;
    };

    void pop(){
        int index_min = min_node.first*MAX_H + min_node.second;

        if (!bucket[index_min].empty()) {
            bucket[index_min].pop();
            count_elements--;
            
            while(bucket[index_min].empty() && (index_min < MAX_F*MAX_H)){
                index_min++;
            }

            min_node.first = index_min / MAX_H;
            min_node.second = index_min % MAX_H;           

        } else {
            std::cout << "pop an empty stack" << std::endl;
            // exit(-1);
        }
    };

    Node * top(){
        Node * node;
        int index_min = min_node.first*MAX_H + min_node.second;

        if(!bucket[index_min].empty())
            return bucket[index_min].top();
            
        return NULL;
    };

    bool empty(){
        if(count_elements > 0){
            return false;
        } 

        return true;
    };

} bucket_t;

    

void heuristic_solver(const TILE_size& initial_state, int blank_x, int blank_y, AlgorithmMode mode) {
    using namespace std::chrono;
    duration<double> time_successors(0), time_visited(0), time_heuristic(0), time_pushing(0), time_popping(0);
    auto overall_start = high_resolution_clock::now();
    //auto cmp = [](Node* a, Node* b) { return *a > *b; };
    auto cmp = [mode](Node* a, Node* b) -> bool {
    switch(mode) {
        case GBFS:
            if(a->h_value == b->h_value){
                if(a->g_value == b->g_value){
                    return a->order_count < b->order_count; // Tie-breaking
                }
                return a->g_value < b->g_value;
            }
                
            return a->h_value > b->h_value;
            
            
        case ASTAR:
        default:
            if (a->h_value + a->g_value == b->h_value + b->g_value) {
                if(a->h_value == b->h_value)
                    return a->order_count < b->order_count; // Tie-breaking
                return a->h_value > b->h_value;
            }
            return a->h_value + a->g_value > b->h_value + b->g_value;
        }
    };

    bucket_t open;
    // std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> open(cmp);
    std::unordered_set<TILE_size> visited;
    
    problems_count+=1;
    int order_count = 0;
    size_t expanded_nodes = 0;
    Heuristic h = Heuristic(initial_state);
    //int h_value =heuristic(initial_state);
    int init_h = h.init_h;
    
    Node *initial_node = new Node(initial_state, Move::NONE, 0, 0, init_h, 0, blank_x, blank_y);
    bool solved = false;    
    open.push(initial_node); 
    Node* goal_node;
    while (!open.empty()) {
        auto start_popping = high_resolution_clock::now();
        Node* current = open.top();
        open.pop();
        time_popping += duration_cast<duration<double>>(high_resolution_clock::now() - start_popping);

        auto start_visited = high_resolution_clock::now();
        if (visited.find(current->state) == visited.end()) {
            visited.insert(current->state);
            time_visited += duration_cast<duration<double>>(high_resolution_clock::now() - start_visited);

            if (isGoal(current->state)) {
                solved = true;
                solved_count++;
                goal_node=current;
                break;
            }

            if (duration_cast<duration<double>>(high_resolution_clock::now() - overall_start).count() > 30) {
                break;
            }

            if (IsMemoryLimitExceeded()) {
                break;
            }

            expanded_nodes += 1;
            auto start_successors = high_resolution_clock::now();
            auto successors_list = successors(current->state, current->blank_x, current->blank_y);
            time_successors += duration_cast<duration<double>>(high_resolution_clock::now() - start_successors);

            for (auto& [m, next_state, next_bx, next_by] : successors_list) {
                if(opposite(current->last_move, m)) continue;
                order_count += 1;

                auto start_heuristic = high_resolution_clock::now();
                int h_value = h.optimized_heuristic(next_state, m, current->h_value, next_bx, next_by);
                //int h_value = h.heuristic(next_state);
                time_heuristic += duration_cast<duration<double>>(high_resolution_clock::now() - start_heuristic);

                Node* next_node = new Node(next_state, m, current->moves_count + 1, current->g_value + 1, h_value, order_count + 1, next_bx, next_by);
                
                auto start_pushing = high_resolution_clock::now();
                open.push(next_node);
                time_pushing += duration_cast<duration<double>>(high_resolution_clock::now() - start_pushing);
            }
        }
        delete current;
    }

    auto total_solving_time = duration_cast<duration<double>>(high_resolution_clock::now() - overall_start);

#ifdef VERBOSE
        // profilling stuff
        std::cout << "Total solving time " << total_solving_time.count()  << " seconds\n";
        std::cout << "Total time for computing successors: " << time_successors.count() << " seconds\n";
        std::cout << "Total time for checking visited states: " << time_visited.count() << " seconds\n";
        std::cout << "Total time for computing heuristic: " << time_heuristic.count() << " seconds\n";
        std::cout << "Total time for inserting into open: " << time_pushing.count() << " seconds\n";
        std::cout << "Total time for removing from open: " << time_popping.count() << " seconds\n";
        PrintMemoryUsage();
        // Print final status
        if (solved) {
            std::cout << "H-INIT: " << std::to_string(init_h) << std::endl;
            std::cout << "H-AVG: " << h.getAvgH() << std::endl;
            std::cout << "Expanded nodes: " << std::to_string(expanded_nodes) << std::endl;
            std::cout << "Path lenght: "  << std::to_string(goal_node->g_value) << std::endl;
            delete goal_node;
            std::cout << "Solved\n";
        } else if (duration_cast<duration<double>>(high_resolution_clock::now() - overall_start).count() > 30) {
            std::cout << "Unsolved (Out of Time)\n";
        } else if (IsMemoryLimitExceeded()){
            std::cout << "Unsolved (Out of Memory)\n";
        }
        else {
            std::cout << "Unsolved\n";
        }
        std::cout << "Total puzzles solved: " << solved_count << "/" << problems_count << std::endl;
#endif

#ifndef VERBOSE
        std::cout << expanded_nodes << ',' << goal_node->g_value << ',' << total_solving_time.count() << ',' << h.heuristic_acc/h.heuristic_count << ',' << init_h << std::endl;
#endif

    while (!open.empty()) {
        delete open.top();
        open.pop();
    }
}


/* NODE POOL VERSION
std::stack<Node*> nodePool;

void initializeNodePool() {
    for (int i = 0; i < MAX_NODES; i++) {
        nodePool.push(new Node()); // Pre-create Node objects
    }
}

Node* allocateNode() {
    if (nodePool.empty()) {
        return nullptr;
    }
    Node* node = nodePool.top();
    nodePool.pop();
    return node;
}

void deallocateNode(Node* node) {
    nodePool.push(node);
}



void solver(const TILE_size& initial_state, int blank_x, int blank_y) {

    std::cout << "\nSTART SOLVING:" << std::endl;
    using namespace std::chrono;
    auto overall_start = high_resolution_clock::now();
    problems_count+=1;
    int order_count = 0;
    size_t expanded_nodes = 0;
    auto cmp = [](Node* a, Node* b) { return *a > *b; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> open(cmp);

    // profiling
    duration<double> time_successors(0), time_visited(0), time_heuristic(0), time_pushing(0), time_popping(0);
    
    bool solved = false;

    //Node *initial_node = new Node(initial_state, Move::NONE, 0, 0, optimized_heuristic(initial_state, Move::NONE, 0, blank_x, blank_y), 0, blank_x, blank_y);
    Node* initial_node = allocateNode();
    if (!initial_node) throw std::bad_alloc();
    initial_node->state = initial_state;
    initial_node->last_move = Move::NONE;
    initial_node->moves_count = 0;
    initial_node->g_value = 0;
    initial_node->h_value = optimized_heuristic(initial_state, Move::NONE, 0, blank_x, blank_y);
    initial_node->order_count = 0;
    initial_node->blank_x = blank_x;
    initial_node->blank_y = blank_y;
    
    open.push(initial_node);

    std::unordered_set<TILE_size> visited;

    while (!open.empty()) {
        auto start_popping = high_resolution_clock::now();
        Node* current = open.top();
        open.pop();
        time_popping += duration_cast<duration<double>>(high_resolution_clock::now() - start_popping);

        auto start_visited = high_resolution_clock::now();
        if (visited.find(current->state) == visited.end()) {
            visited.insert(current->state);
            time_visited += duration_cast<duration<double>>(high_resolution_clock::now() - start_visited);

            if (isGoal(current->state)) {
                solved = true;
                solved_count++;
                break;
            }

            if (duration_cast<duration<double>>(high_resolution_clock::now() - overall_start).count() > 30) {
                break;
            }

            if (IsMemoryLimitExceeded()) {
                break;
            }

            expanded_nodes += 1;
            auto start_successors = high_resolution_clock::now();
            auto successors_list = successors(current->state, current->blank_x, current->blank_y);
            time_successors += duration_cast<duration<double>>(high_resolution_clock::now() - start_successors);

            for (auto& [m, next_state, next_bx, next_by] : successors_list) {
                if(opposite(current->last_move, m)) continue;
                order_count += 1;

                auto start_heuristic = high_resolution_clock::now();
                int h_value = optimized_heuristic(next_state, m, current->h_value, next_bx, next_by);
                time_heuristic += duration_cast<duration<double>>(high_resolution_clock::now() - start_heuristic);

                //Node* next_node = new Node(next_state, m, current->moves_count + 1, current->g_value + 1, h_value, order_count + 1, next_bx, next_by);
                Node* next_node = allocateNode();
                if (!next_node) throw std::bad_alloc(); // or handle it appropriately
                next_node->state = next_state;
                next_node->last_move = m;
                next_node->moves_count = current->moves_count + 1;
                next_node->g_value = current->g_value + 1;
                next_node->h_value = optimized_heuristic(next_state, m, current->h_value, next_bx, next_by);
                next_node->order_count = order_count + 1;
                next_node->blank_x = next_bx;
                next_node->blank_y = next_by;
                
                auto start_pushing = high_resolution_clock::now();
                open.push(next_node);
                time_pushing += duration_cast<duration<double>>(high_resolution_clock::now() - start_pushing);
            }
        }
        delete current;
        //deallocateNode(current);
    }

    auto total_solving_time = duration_cast<duration<double>>(high_resolution_clock::now() - overall_start);
    // Print profiling results
    
    std::cout << "Total solving time " << total_solving_time.count()  << " seconds\n";
    std::cout << "Total time for computing successors: " << time_successors.count() << " seconds\n";
    std::cout << "Total time for checking visited states: " << time_visited.count() << " seconds\n";
    std::cout << "Total time for computing heuristic: " << time_heuristic.count() << " seconds\n";
    std::cout << "Total time for inserting into open: " << time_pushing.count() << " seconds\n";
    std::cout << "Total time for removing from open: " << time_popping.count() << " seconds\n";
    PrintMemoryUsage();
    // Print final status
    if (solved) {
        std::cout << "Solved\n";
    } else if (duration_cast<duration<double>>(high_resolution_clock::now() - overall_start).count() > 30) {
        std::cout << "Unsolved (Out of Time)\n";
    } else if (IsMemoryLimitExceeded()){
         std::cout << "Unsolved (Out of Memory)\n";
    }
    else {
        std::cout << "Unsolved\n";
    }
    std::cout << "Total puzzles solved: " << solved_count << "/" << problems_count << std::endl;
    // Clean up remaining nodes
    while (!open.empty()) {
        // delete open.top();
        // open.pop();
        deallocateNode(open.top());
        open.pop();
    }
    
}

*/
