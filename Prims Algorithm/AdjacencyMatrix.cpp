#include "AdjacencyMatrix.hpp"
#include<iostream>
using namespace std;

AdjacencyMatrix :: AdjacencyMatrix(){}

AdjacencyMatrix :: AdjacencyMatrix(int vertices){
    no_of_rows = no_of_cols = vertices;
    adjacencyMatrix = new int*[vertices];
    for(int i = 0; i < no_of_rows; i++){
        adjacencyMatrix[i] = new int[vertices];
        for(int j = 0; j < no_of_cols; j++){
            adjacencyMatrix[i][j] = 0;
        } 
    }
}

AdjacencyMatrix :: ~AdjacencyMatrix(){
    for(int i = 0; i < no_of_rows; i++){
        delete adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

void AdjacencyMatrix :: printMatrix(){
  for(int i = 0; i < no_of_rows; i++){
    for(int j = 0; j < no_of_cols; j++){
      cout<<adjacencyMatrix[i][j]<<" ";
    }
    cout<<endl;
  }
}

bool AdjacencyMatrix :: edgeExists(int i, int j){
    return adjacencyMatrix[i][j] != 0 ? true : false;
}

int AdjacencyMatrix :: edges(){
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

int AdjacencyMatrix :: vertices(){
    return no_of_rows;
}

void AdjacencyMatrix :: add(int i, int j, int wt){
    adjacencyMatrix[i][j] = wt;
    adjacencyMatrix[j][i] = wt;
}

void AdjacencyMatrix :: remove(int i, int j){
    adjacencyMatrix[i][j] = 0;
    adjacencyMatrix[j][i] = 0;
}

int AdjacencyMatrix :: degree(int i){
    int no_of_degree = 0;
    for(int col = 0; col < no_of_cols; col++){
        if(adjacencyMatrix[i][col] != 0){
            no_of_degree++;
        }
    }
    return no_of_degree;
}
