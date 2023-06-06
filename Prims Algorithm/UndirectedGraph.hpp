#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH 1
#include<vector>
#include "UFDS.hpp"
#include "AdjacencyMatrix.hpp"
#include "FibonacciHeap.hpp"
/*
 * A class to represent an UndirectedGraph
 * Subclasses AbstractGraph
 */
#include "AbstractGraph.hpp"
class UndirectedGraph : AbstractGraph {
   private: 
      char matrix_type;
      int no_of_rows;
      int no_of_cols;
      int** adjacencyMatrix;
   public:
   /*
    * Constructor: UndirectedGraph
    *
    * Parameters: mode
    * Used to decide which representation to use
    * 'm' for AdjacencyMatrix
    * 'l' for AdjacencyList
   */
   UndirectedGraph(int vertices, char mode);

   /*
    * Function: edgeExists
    * Returns true if an edge exists between vertices i and j, false otherwise.
   */
   bool edgeExists(int i, int j);

   /*
    * Function: edges
    * Returns the number of edges in the adjacency structure.
   */
   int edges();

   /*
    * Function: vertices
    * Returns the number of vertices in the adjacency structure.
   */
   int vertices();

   /*
    * Function add:
    * Adds an edge between vertices i and j having weight wt.
   */
   void add(int i, int j, int wt);

   /*
    * Function: remove
    * Deleted the edge between vertices i and j
   */
   void remove(int i, int j);

   /*
    * Returns the degree of the vertex.
   */
   int degree(int i);

   /* Function Prim.
    *
    * Params:
    * 1. G : Adjacency matrix represeatation of a graph.
    * 2. v : Number of vertices
    *
    * Returns Adjacency matrix representation of MST
   */
   vector<vector<int>> Prim(vector<vector<int>> G, const int v);
};
#endif /* ifndef UNDIRECTED_GRAPH */