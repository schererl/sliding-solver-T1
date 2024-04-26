#pragma once

#include "tilepuzzle.h"
#include <stack>
#include <set>


#define MAX_F 80
#define MAX_H 50

typedef struct{
    std::stack<Node*> bucket[MAX_F*MAX_H];
    std::set<int> set_index; // stores all indices that contain nodes
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

        set_index.insert(f*MAX_H + h);
        count_elements++;
    };

    void pop(){
        int index_min = min_node.first*MAX_H + min_node.second;

        if (!bucket[index_min].empty()) {
            bucket[index_min].pop();
            count_elements--;
            
            
            if(bucket[index_min].empty()){
                set_index.erase(index_min);

                if(set_index.size()>0){
                    index_min = *(set_index.begin());
                    min_node.first = index_min / MAX_H;
                    min_node.second = index_min % MAX_H;
                } else {
                    min_node.first = MAX_F;
                    min_node.second = MAX_H;
                }
            }
           

        } else {
            std::cout << "popping an empty stack" << std::endl;
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
