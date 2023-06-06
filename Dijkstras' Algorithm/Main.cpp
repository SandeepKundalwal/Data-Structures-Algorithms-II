#include<iostream>
#include<vector>
using namespace std;

#include "DirectedGraph.hpp"
#include "AdjacencyMatrix.hpp"

int main(){
    int vertices = 5;

    vector<vector<int>> G
    {
        {0, 7, 1, 6, 0},
        {7, 0, 0, 0, 9},
        {1, 0, 0, 3, 2},
        {6, 0, 3, 0, 5},
        {0, 9, 2, 5, 0}
    };


    DirectedGraph *directedGraph = new DirectedGraph(vertices, 'm');
    vector<Edge> edges;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(G.at(i).at(j) != 0){
                directedGraph->add(i, j, G.at(i).at(j));
                edges.push_back(Edge(i, j, G.at(i).at(j)));
            }
        }
    }

    Shortest_Path_Tree *_shortestpathtree = directedGraph->Dijkstra(directedGraph, vertices, 0);
    directedGraph->Display_Shortest_Path_Tree(_shortestpathtree);
    return 0;
}

/**
 * OUTPUT: Vertex          Distance from Source
            0                  0
            1                  4
            2                  12
            3                  19
            4                  21
            5                  11
            6                  9
            7                  8
            8                  14
*/

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