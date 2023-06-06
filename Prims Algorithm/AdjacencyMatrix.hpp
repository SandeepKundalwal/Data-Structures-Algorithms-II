#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1
#include "GraphAdjacencyBase.hpp"
class AdjacencyMatrix : public GraphAdjacencyBase {
  private:
	  int no_of_rows;
	  int no_of_cols;
    int** adjacencyMatrix;

  public:
	AdjacencyMatrix();
    AdjacencyMatrix(int vertices);

	  ~AdjacencyMatrix();

	  void printMatrix();

  /*
	 * Function: edgeExists
	 * Returns true if an edge exists between vertices i and j, false otherwise.
	 */
    bool edgeExists(int i, int j);
  /*
	 * Function: vertices 
	 * Returns the number of vertices in the adjacency structure.
	 */
    int vertices();
  /*
	 * Function: edges
	 * Returns the number of edges in the adjacency structure.
	 */
    int edges();
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
	 * Function: degree
	 * Returns the degree of the vertex i
	 */
    int degree(int i);
};
#endif /* ifndef ADJACENCY_MATRIX */