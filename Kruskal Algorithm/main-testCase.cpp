// Purpose: To test Kruskal's algorithm for MST
// Author: MD Arshad Jamal (S20013)
// Date of Creation: 29 Sept 2022
/* ---------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"
#include "DirectedGraph.hpp"

int main() {

    /*
     * Input taken from terminal.
     * First line of input contains a non negavtive integer N representing number of vertices
     * in the adjacency matrix representation of the graph.
     * Next N lines contains N non negative integers separated by a single space representing
     * weight of edges.
     */
     

	int vertices = 5;
	
	vector<vector<int>> mat
    {
        {0, 2, 0, 0},
        {2, 0, 6, 5},
        {0, 6, 0, 2},
        {0, 5, 2, 0}
    };

    vector<vector<int>> matrix
    {
        {0, 7, 1, 6, 0},
        {7, 0, 0, 0, 9},
        {1, 0, 0, 3, 2},
        {6, 0, 3, 0, 5},
        {0, 9, 2, 5, 0}
    };


    /*
     * Build the matrix using appropriate interface(s).
     */

    // AdjacencyMatrix adjacencyMatrix(vertices);

    // for(int i=0; i<vertices; i++) {
    // 	for(int j=0; j<vertices; j++) {
    // 		adjacencyMatrix.add(i, j, mat[i][j]);
    // 	}
    // }

    UndirectedGraph undirectedGraph(vertices, 'm');

    vector<Edge> edges;

    for(int i=0; i<vertices; i++) {
    	for(int j=0; j<vertices; j++) {
    		if(matrix[i][j] != 0) {
                undirectedGraph.add(i, j, matrix[i][j]);
    			edges.push_back(Edge(i, j, matrix[i][j]));
    		}
    	}
    }

    // cout<<"Edge Exists: [3][2] -> "<<directedGraph.edgeExits(3, 2);
    // cout<<endl;
    // cout<<"Edge Exists: [2][1] -> "<<directedGraph.edgeExits(2, 1);
    // cout<<endl;
    // cout<<"No of vertices: "<<directedGraph.vertices();
    // cout<<endl;
    // cout<<"No of edges: "<<directedGraph.edges();
    // cout<<endl;
    // directedGraph.remove(3, 2);
    // cout<<"Edge Exists: [3][2] -> "<<directedGraph.edgeExits(3, 2);
    // cout<<endl;
    // cout<<"InDegree: "<<directedGraph.indegree(4)<<endl;
    // cout<<endl;
    // cout<<"OutDegree: "<<directedGraph.outdegree(4)<<endl;

    vector<vector<int>> MST = undirectedGraph.Kruskal(edges, vertices);
    /*
     * Display the output as per the problem statement.
     */
    for(auto row : MST){
        for(auto col : row){
            cout<<col<<" ";
        }
        cout<<endl;
    }
	return 0;

}

/*
 * For the current input following is the output. (s)
 *
 * 0 2 1
 * 2 4 2
 * 2 3 3
 * 0 1 7
 *
 * Here, ouput is of the format "src des wt".
 * where, src and des are the vertices of the edge which is included in MST and whose weight is wt.
 */

