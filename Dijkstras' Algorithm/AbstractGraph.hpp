#ifndef ABSTRACT_GRAPH
#define ABSTRACT_GRAPH 1

#include<vector>
#include<iostream>
using namespace std;

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

// Shortest path tree node
class TreeNode {
    public:
        int distance;
        TreeNode* predecessor;
        int label;

        TreeNode(){}

        TreeNode(int distance, TreeNode* predecessor, int label) {
            this -> distance = distance;
            this -> predecessor = predecessor;
            this -> label = label;
        }
};

class Shortest_Path_Tree {
    public:
        vector<TreeNode *> treeNode;

        // Shortest_Path_Tree(int length){
        //     treeNode = new TreeNode*[length];
        // }

        Shortest_Path_Tree(){}
        ~Shortest_Path_Tree(){}
};

class DirectedGraph;

/*
 * An interface to represent any type of Graph
*/
class AbstractGraph {
    public:
    /* Destructor:
     * releases all resources acquired by the class
    */
    virtual ~AbstractGraph(){}
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
  
    /* Funcnction Kruskal.
     *
     * Params:
     * 1. E : A vector of objects of type Edge.
     * 2. v : Number of vertices
     *
     * Returns Adjacency matrix representation of MST
    */
    virtual vector<vector<int>> Kruskal(vector<Edge> E, int v) = 0;


    /* Function Prim.
     *
     * Params:
     * 1. G : Adjacency matrix represeatation of a graph.
     * 2. v : Number of vertices
     *
     * Returns Adjacency matrix representation of MST
    */
    virtual vector<vector<int>> Prim(vector<vector<int>> G, const int v) = 0;

    /* Function Dijkstra.
     *
     * Params:
     * 1. G : Object of the DirectedGraph.
     * 2. v : Number of vertices.
     * 3. src : Source node.
     *
     * Returns ShortestPathTree.
    */
    virtual Shortest_Path_Tree* Dijkstra(DirectedGraph* G, int v, int src) = 0;

    /* Function Display_Shortest_Path_Tree.
     *
     * Param:
     * 1. SPT : Object of Shortest_Path_Tree.
    */
    virtual void Display_Shortest_Path_Tree(Shortest_Path_Tree* SPT) = 0;
};
#endif /* ifndef ABSTRACT_GRAPH */


