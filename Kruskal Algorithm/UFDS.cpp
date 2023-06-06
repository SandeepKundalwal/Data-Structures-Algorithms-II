#include "UFDS.hpp"
#include "seqLinearList.cpp"
#include<vector>
using namespace std;
using namespace cs514;

UFDS :: UFDS(const unsigned int& N){
    vertex.reserve(N);
} 

UFDS :: ~UFDS(){
}

void UFDS :: make_set(const unsigned int& N){
    for(int i = 0; i < N; i++){
        node new_node = node();
        new_node.rank = i;
        new_node.parent = i;
        vertex.push_back(new_node);
    }
}

int UFDS :: find_set(const unsigned int& x){
    int representativeSet = vertex.at(x).parent;
    return representativeSet;
}

void UFDS :: union_set(const unsigned int& x, const unsigned int& y){
    for(int i = 0; i < vertex.size(); i++){
        if(vertex.at(i).parent == y){
            vertex.at(i).parent = vertex.at(x).parent;
        }
    }
}

bool UFDS :: is_same_set(const unsigned int& x, const unsigned int& y){
    int representativeX = find_set(x);
    int representativeY = find_set(y);
    return (representativeX == representativeY);
}

int UFDS :: num_disjoint_sets(){
    int frequency[vertex.size()];
    for(int i = 0; i < vertex.size(); i++){
        frequency[i] = 0;
    }

    int representativeSet;
    for(int i = 0; i < vertex.size(); i++){
        representativeSet = vertex.at(i).parent;
        frequency[representativeSet]++;
    }

    int countDisjointSet = 0;
    for(int i = 0; i < vertex.size(); i++){
        if(frequency[i] != 0){
            countDisjointSet++;
        }
    }
    return countDisjointSet;
}

int UFDS :: size_set(const unsigned int& x){
    int setSize = 0;
    int representativeSet = vertex.at(x).parent;
    for(int i = 0; i < vertex.size(); i++){
        if(vertex.at(i).parent == representativeSet){
            setSize++;
        }
    }
    return setSize;
}