#ifndef TILEPUZZLE_H
#define TILEPUZZLE_H

#include <iostream>
#include <bitset>
#include <vector>
#include <tuple>
#include <string>
#define TILE_BIT_SIZE 4

extern int ROW_COL_SIZE;
extern uint64_t GOAL_STATE;

void configurePuzzle(int size);

typedef uint64_t TILE_size; 

enum Move { LEFT, RIGHT, UP, DOWN, NONE};

class Node {
public:
    TILE_size state;
    Move last_move;
    int moves_count;
    int g_value;
    int h_value;
    int order_count;
    int blank_x;
    int blank_y;

    Node(TILE_size s, Move m, int count, int g_val, int h_val, int ord_count, int b_x, int b_y) : state(s), last_move(m), moves_count(count), g_value(g_val), h_value(h_val), order_count(ord_count), blank_x(b_x), blank_y(b_y) {}
    //Node(){}
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    bool operator>(const Node& other) const;
};


std::string MoveToString(Move m);

std::string StateToString(const TILE_size &state);

std::tuple<TILE_size, int, int> vectorToState(const std::vector<int>& tiles);

TILE_size swap_bits(const TILE_size &state, const int &blank_x, const int &blank_y, const int &swap_x, const int &swap_y);

bool opposite(Move parentMove, Move nextMove);

std::vector<std::tuple<Move, TILE_size, int, int>> successors(const TILE_size &state, int blank_x, int blank_y);

int isGoal(const TILE_size &state);
#endif

