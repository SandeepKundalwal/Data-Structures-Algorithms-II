#include "UndirectedGraph.hpp"
#include "AbstractGraph.hpp"
#include "AdjacencyMatrix.hpp"
#include "UFDS.hpp"
#include<algorithm>
#include<iostream>
using namespace cs514;
using namespace std;

UndirectedGraph :: UndirectedGraph(int vertices, char mode){
    if(mode == 'm'){
        matrixType = mode;
        no_of_rows = no_of_cols = vertices;
        adjacencyMatrix = new int*[vertices];
        for(int i = 0; i < vertices; i++){
            adjacencyMatrix[i] = new int[vertices];
            for(int j = 0; j < vertices; j++){
                adjacencyMatrix[i][j] = 0;
            } 
        }
    }
}

void UndirectedGraph :: printMatrix(){
  for(int i = 0; i < no_of_rows; i++){
    for(int j = 0; j < no_of_cols; j++){
      cout<<adjacencyMatrix[i][j]<<" ";
    }
    cout<<endl;
  }
}

bool UndirectedGraph :: edgeExits(int i, int j){
    return adjacencyMatrix[i][j] != 0 ? true : false;
}


int UndirectedGraph :: edges(){
    int no_of_edges = 0;
    for(int i = 0; i < no_of_rows; i++){
        for(int j = 0; j < no_of_cols; j++){
            if(adjacencyMatrix[i][j] != 0){
                no_of_edges++;
            }
        }
    }
    return (no_of_edges / 2);
}

int UndirectedGraph :: vertices(){
    return no_of_rows;
}

void UndirectedGraph :: add(int i, int j, int wt){
    adjacencyMatrix[i][j] = wt;
    adjacencyMatrix[j][i] = wt;
}

void UndirectedGraph :: remove(int i, int j){
    adjacencyMatrix[i][j] = 0;
    adjacencyMatrix[j][i] = 0;
}

int UndirectedGraph :: degree(int i){
    int no_of_degree = 0;
    for(int col = 0; col < no_of_cols; col++){
        if(adjacencyMatrix[i][col] != 0){
            no_of_degree++;
        }
    }
    return no_of_degree;
}

/* Function Kruskal.
   *
   * Params:
   * 1. E : A vector of objects of type Edge.
   * 2. v : Number of vertices
   *
   * Returns Adjacency matrix representation of MST
  */
vector<vector<int>> UndirectedGraph :: Kruskal(vector<Edge> E, int v){
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
                if(--v != 0){
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

