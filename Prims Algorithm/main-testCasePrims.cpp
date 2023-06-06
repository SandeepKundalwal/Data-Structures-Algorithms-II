// Purpose: To test Prim's algorithm for MST
// Author: Md Arshad Jamal (S20013)
// Date of Creation: 28 Oct 2022
/* ---------------------------------------------- */
#include <iostream>
#include <algorithm>
using namespace std;

#include "seqLinearList.cpp"
#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"

    /*
     * INPUT FORMAT:
     * Input taken from terminal.
     * First line of input contains a non negavtive integer N representing number of vertices
     * in the adjacency matrix representation of the graph.
     * Next N lines contains N non negative integers separated by a single space representing
     * weight of edges.
     */
    

int main() {

    /**
     * Below is the hard coded form of input for your reference. You are supposed to 
     * store the input in a 2-D LinearList.
     * Here it is named as mat. 
     */

	int vertices = 5;
	
	vector<vector<int>> mat
    {
        {0, 7, 1, 6, 0},
        {7, 0, 0, 0, 9},
        {1, 0, 0, 3, 2},
        {6, 0, 3, 0, 5},
        {0, 9, 2, 5, 0}
    };

    vector<vector<int>> matrix
    {   
        { 0, 2, 0, 6, 0 },
        { 2, 0, 3, 8, 5 },
        { 0, 3, 0, 0, 7 },
        { 6, 8, 0, 0, 9 },
        { 0, 5, 7, 9, 0 } 
    };

    vector<vector<int>> matrix1
    {
        {0, 2, 0, 0},
        {2, 0, 6, 5},
        {0, 6, 0, 2},
        {0, 5, 2, 0},
    };


    /*
     * Build the matrix using appropriate interface(s).
     */

    AdjacencyMatrix adjacencyMatrix(vertices);

    /**
     * Buid Adjacency Matrix using functions given in AdjacencyMatrix.hpp. Note that AdjacencyMatrix.hpp 
     * inherits functons from GraphAdjacencyBase.hpp.
     */

    UndirectedGraph undirectedGraph(vertices, 'm');

    vector<vector<int>> MSTPrims = undirectedGraph.Prim(matrix, 5);

    /*
     * Traverse the obtained MST and display the output. See the required output format at the end.
     */
    for(auto edge : MSTPrims){
        cout << edge[0] << " " << edge[1] << " " << edge[2] << endl;
    }
}

/*
 * OUTPUT FORMAT
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

