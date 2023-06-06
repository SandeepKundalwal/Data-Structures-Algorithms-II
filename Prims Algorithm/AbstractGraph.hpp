#ifndef ABSTRACT_GRAPH
#define ABSTRACT_GRAPH 1

#include "seqLinearList.hpp"

/*
 * Class to represent an edge of the graph.
 * src : Source vertex
 * des : Destination vertex
 * wt : Weight of the corresponding edge.
 */
class Edge {
    public:
        int src;
        int des;
        int wt;
    
        Edge(int src, int des, int wt) {
            this -> src = src;
            this -> des = des;
            this -> wt = wt;
        }
};


/*
 * An interface to represent any type of Graph
 */
class AbstractGraph {
 public:
  /* Destructor:
   * releases all resources acquired by the class
   */
  virtual ~AbstractGraph(){};
  /*
   * Function: edgeExists
   * Returns true if an edge exists between vertices i and j, false otherwise.
   */
  virtual bool edgeExists(int i, int j) = 0;
  /*
   * Function: edges
   * Returns the number of edges in the adjacency structure.
   */
  virtual int edges() = 0;
  /*
   * Function: vertices
   * Returns the number of vertices in the adjacency structure.
   */
  virtual int vertices() = 0;
  /*
   * Function add:
   * Adds an edge between vertices i and j having weight wt.
   */
  virtual void add(int i, int j, int wt) = 0;
  /*
   * Function: remove
   * Deleted the edge between vertices i and j
   */
  virtual void remove(int i, int j) = 0;

  /* Function Prim.
   *
   * Params:
   * 1. G : Adjacency matrix represeatation of a graph.
   * 2. v : Number of vertices
   *
   * Returns Adjacency matrix representation of MST
  */
  virtual vector<vector<int>> Prim(vector<vector<int>> G, const int v) = 0;
};
#endif /* ifndef ABSTRACT_GRAPH */
