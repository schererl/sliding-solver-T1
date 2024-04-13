#include "tilepuzzle.h"
//#include "bfs.h"
#include "HeuristicSearch.h"
#include <cmath>

int ROW_COL_SIZE;
uint64_t GOAL_STATE;
void configurePuzzle(int size) {
    if (size == 16) {
        ROW_COL_SIZE = 4;
        GOAL_STATE = 0xFEDCBA9876543210ULL;
    } else if (size == 9) {
        ROW_COL_SIZE = 3;
        GOAL_STATE = 0x876543210ULL;
    } else {
        std::cerr << "Unsupported puzzle size" << std::endl;
    }
}

std::string MoveToString(Move m) {
    switch (m) {
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case UP: return "UP";
        case DOWN: return "DOWN";
        default: return "Unknown Move";
    }
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "State: " << StateToString(node.state) << "\n Last Move: " << MoveToString(node.last_move) << "\n Move Count: " << node.moves_count;
    return os;
}

std::string StateToString(const TILE_size &state) {
    std::string output = "STATE: \n";
    int blank_x = -1, blank_y = -1;
    for (int i = 0; i < ROW_COL_SIZE; i++) {
        for (int j = 0; j < ROW_COL_SIZE; j++) {
            int tileValue = (state >> (TILE_BIT_SIZE * (i * ROW_COL_SIZE + j))) & 0xF;
            if (tileValue == 0) {
                blank_x = i;
                blank_y = j;
            }
            output += std::to_string(tileValue) + " ";
        }
        output += '\n';
    }
    output += "blank at (" + std::to_string(blank_x) + ", " + std::to_string(blank_y) + ")";
    return output;
}


TILE_size swap_bits(const TILE_size &state, const int &blank_x, const int &blank_y, const int &swap_x, const int &swap_y) {
    int blank_pos = (TILE_BIT_SIZE) * (blank_x * ROW_COL_SIZE + blank_y);
    int swap_pos = (TILE_BIT_SIZE) * (swap_x * ROW_COL_SIZE + swap_y);
    int swap_val = (state >> swap_pos) & 0xF;
    int blank_val = (state >> blank_pos) & 0xF;

    TILE_size new_state = state;
    new_state = (new_state & ~(0xFULL << blank_pos)) | (static_cast<TILE_size>(swap_val) << blank_pos);
    new_state = (new_state & ~(0xFULL << swap_pos)) | (static_cast<TILE_size>(blank_val) << swap_pos);

    return new_state;
}


std::tuple<TILE_size, int, int> vectorToState(const std::vector<int>& tiles) {
    TILE_size state = 0;
    int blank_x = -1, blank_y = -1;
    for (size_t i = 0; i < tiles.size(); ++i) {
        if (tiles[i] == 0) {
            blank_x = i / ROW_COL_SIZE;
            blank_y = i % ROW_COL_SIZE;
        }
        state |= (static_cast<TILE_size>(tiles[i]) << (TILE_BIT_SIZE * i));
    }
    return std::make_tuple(state, blank_x, blank_y);
}



bool opposite(Move parentMove, Move nextMove){
    return (parentMove == UP && nextMove == DOWN) || (parentMove == DOWN && nextMove == UP) || (parentMove == LEFT && nextMove == RIGHT) || (parentMove == RIGHT && nextMove == LEFT);
}

std::vector<std::tuple<Move, TILE_size, int, int>> successors(const TILE_size &state, int blank_x, int blank_y){
    // int blank_pos = (state >> BLANK_BIT_POS) & 0xF;
    // int blank_x = blank_pos/ROW_COL_SIZE;
    // int blank_y = blank_pos%ROW_COL_SIZE;
    //std::vector<std::tuple<Move, TILE_size>> moves;   
    std::vector<std::tuple<Move, TILE_size, int, int>> moves;
    if (blank_x > 0) {
        //moves.push_back(std::make_tuple(UP, swap_bits(state, blank_x, blank_y, blank_x - 1, blank_y)));
        auto result = swap_bits(state, blank_x, blank_y, blank_x - 1, blank_y);
        moves.push_back(std::make_tuple(UP, result, blank_x - 1, blank_y));
    }

    if (blank_y > 0) {
        //moves.push_back(std::make_tuple(LEFT, swap_bits(state, blank_x, blank_y, blank_x, blank_y - 1)));
        auto result = swap_bits(state, blank_x, blank_y, blank_x, blank_y-1);
        moves.push_back(std::make_tuple(LEFT, result, blank_x, blank_y-1));
    }

    if (blank_y < ROW_COL_SIZE - 1) {
        //moves.push_back(std::make_tuple(RIGHT, swap_bits(state, blank_x, blank_y, blank_x, blank_y + 1)));
        auto result = swap_bits(state, blank_x, blank_y, blank_x, blank_y+1);
        moves.push_back(std::make_tuple(RIGHT, result, blank_x, blank_y+1));
    }

    if (blank_x < ROW_COL_SIZE - 1) {
        //moves.push_back(std::make_tuple(DOWN, swap_bits(state, blank_x, blank_y, blank_x + 1, blank_y)));
        auto result = swap_bits(state, blank_x, blank_y, blank_x + 1, blank_y);
        moves.push_back(std::make_tuple(DOWN, result, blank_x + 1, blank_y));
    }

    return moves;
}

int isGoal(const TILE_size &state){
    return state == GOAL_STATE;
}