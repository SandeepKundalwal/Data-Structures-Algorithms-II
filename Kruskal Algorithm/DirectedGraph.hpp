#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1
#include "AbstractGraph.hpp"
/*
 * A class to represent a directed graph.
 */
class DirectedGraph : AbstractGraph {
 private:
    char matrixType;
    int no_of_rows;
    int no_of_cols;
    int** adjacencyMatrix;
 public:
  /*
   * Constructor: DirectedGraph
   *
   * Parameters: mode
   * Used to decide which representation to use
   * 'm' for AdjacencyMatrix
   * 'l' for AdjacencyList 
   */
  DirectedGraph(int numVertices, char rep);

  bool edgeExits(int i, int j);

  int edges();

  int vertices();

  void add(int i, int j, int wt);

  void remove(int i, int j);
  /*
   * Function: indegree
   * Returns the indegree of a vertex
   */
  int indegree(int i);
  /*
   * Function: outdegree
   * Returns the outdegree of a vertex.
   */
  int outdegree(int j);

  /* Function Kruskal.
   *
   * Params:
   * 1. E : A vector of objects of type Edge.
   * 2. v : Number of vertices
   *
   * Returns Adjacency matrix representation of MST
  */
  vector<vector<int>> Kruskal(vector<Edge> E, int v);
};
#endif /* ifndef DIRECTED_GRAPH */