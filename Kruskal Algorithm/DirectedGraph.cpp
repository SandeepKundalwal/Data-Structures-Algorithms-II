#include "DirectedGraph.hpp"
#include "UFDS.hpp"
#include<algorithm>
#include<iostream>
using namespace std;
using namespace cs514;

DirectedGraph :: DirectedGraph(int numVertices, char rep){
    if(rep == 'm'){
        matrixType = rep;
        no_of_rows = no_of_cols = numVertices;
        adjacencyMatrix = new int*[numVertices];
        for(int i = 0; i < numVertices; i++){
            adjacencyMatrix[i] = new int[numVertices];
            for(int j = 0; j < numVertices; j++){
                adjacencyMatrix[i][j] = 0;
            } 
        }
    }
}

bool DirectedGraph :: edgeExits(int i, int j){
    return adjacencyMatrix[i][j] != 0 ? true : false;
}

int DirectedGraph :: edges(){
    int no_of_edges = 0;
    for(int i = 0; i < no_of_rows; i++){
        for(int j = 0; j < no_of_cols; j++){
            if(adjacencyMatrix[i][j] != 0){
                no_of_edges++;
            }
        }
    }
    return no_of_edges;
}

int DirectedGraph :: vertices(){
    return (no_of_rows);
}

void DirectedGraph :: add(int i, int j, int wt){
    adjacencyMatrix[i][j] = wt;
}

void DirectedGraph :: remove(int i, int j){
    adjacencyMatrix[i][j] = 0;
}

int DirectedGraph :: indegree(int i){
    int in_degree = 0;
    for(int row = 0; row < no_of_rows; row++){
        if(adjacencyMatrix[row][i] != 0){
            in_degree++;
        }
    }
    return in_degree;

}

int DirectedGraph :: outdegree(int j){
    int out_degree = 0;
    for(int col = 0; col < no_of_cols; col++){
        if(adjacencyMatrix[j][col] != 0){
            out_degree++;
        }
    }
    return out_degree;
}

vector<vector<int>> DirectedGraph :: Kruskal(vector<Edge> E, int v){
    vector<vector<int>> MST;
    if(matrixType == 'm'){
        sort(E.begin(), E.end(), [](const Edge & E1, const Edge & E2) -> bool {
            return E1.wt < E2.wt; });
            
        UFDS _UFDS_ = UFDS(v);
        _UFDS_.make_set(v);

        for(auto edge : E){
            int src = edge.src;
            int des = edge.des;
            int wt = edge.wt;

            if(!_UFDS_.is_same_set(src, des)){
                if(--v == 0){
                    break;
                }
                _UFDS_.union_set(src, des);
                vector<int> include_in_MST {src, des, wt};
                MST.push_back(include_in_MST);
            }
        }
    }
    return MST;
}