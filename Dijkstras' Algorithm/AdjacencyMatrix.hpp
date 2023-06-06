#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1

#include<iostream>
#include "GraphAdjacencyBase.hpp"
using namespace std;

class AdjacencyMatrix : public GraphAdjacencyBase {
    private:
	    int no_of_rows;
	    int no_of_cols;
        int** adjacencyMatrix;
  
    public:
        AdjacencyMatrix(){}

        AdjacencyMatrix(int vertices){
            no_of_rows = no_of_cols = vertices;
            adjacencyMatrix = new int*[vertices];
            for(int i = 0; i < no_of_rows; i++){
                adjacencyMatrix[i] = new int[vertices];
                for(int j = 0; j < no_of_cols; j++){
                    adjacencyMatrix[i][j] = 0;
                } 
            }
        }

	    ~AdjacencyMatrix(){
            for(int i = 0; i < no_of_rows; i++){
                delete adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;
        }

	    void printMatrix(){
            for(int i = 0; i < no_of_rows; i++){
                for(int j = 0; j < no_of_cols; j++){
                    std :: cout<<adjacencyMatrix[i][j]<<" ";
                }
            std :: cout<<endl;
            }
        }

        /*
	     * Function: edgeExists
	     * Returns true if an edge exists between vertices i and j, false otherwise.
	    */
        bool edgeExists(int i, int j){
            return adjacencyMatrix[i][j] != 0 ? true : false;
        }

        /*
	     * Function: vertices 
	     * Returns the number of vertices in the adjacency structure.
	    */
        int vertices(){
            return no_of_rows;
        }

        /*
	     * Function: edges
	     * Returns the number of edges in the adjacency structure.
	    */
        int edges(){
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

        /*
	     * Function add:
	     * Adds an edge between vertices i and j having weight wt.
	    */
        void add(int i, int j, int wt){
            adjacencyMatrix[i][j] = wt;
        }

        /*
	     * Function: remove
	     * Deleted the edge between vertices i and j
	    */
        void remove(int i, int j){
            adjacencyMatrix[i][j] = 0;
        }

        int degree(int i){
            int no_of_degree = 0;
            for(int col = 0; col < no_of_cols; col++){
                if(adjacencyMatrix[i][col] != 0){
                    no_of_degree++;
                }
            }
            return no_of_degree;
        }
};
#endif /* ifndef ADJACENCY_MATRIX */