#ifndef ABSTRACT_GRAPH
#define ABSTRACT_GRAPH 1
#include<vector>
using namespace std;
/* 
 * A class to represent an edge of the graph.
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
  virtual bool edgeExits(int i, int j) = 0;
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
   
  /* Function Kruskal.
   *
   * Params:
   * 1. E : A vector of objects of type Edge.
   * 2. v : Number of vertices
   *
   * Returns Adjacency matrix representation of MST
  */
  virtual vector<vector<int>> Kruskal(vector<Edge> E, int v) = 0;
};
#endif /* ifndef ABSTRACT_GRAPH */
