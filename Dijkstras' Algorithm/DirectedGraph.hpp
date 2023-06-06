#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1

#include<algorithm>
#include<iostream>
#include<stack>
#include<vector>
#include "UFDS.hpp"
#include "AbstractGraph.hpp"
#include "AdjacencyMatrix.hpp"
#include "FibonacciHeap.hpp"
using namespace std;

/**
 * Using Fibonacci Heap as a utility for Dijkstras' Algorithm
 *  Fib_Heap_Decrease_key --> O(1)
 *  Extract_Min --> O(log(n))
*/
FibonacciHeap _FibonacciHeap;
Fibonacci_Heap* _FibonacciHeapObj = _FibonacciHeap.Make_Fib_Heap();

/*
 * A class to represent a directed graph.
 */
class DirectedGraph : AbstractGraph {
    private:
        char matrixType;
        int no_of_rows;
        int no_of_cols;
        int **adjacencyMatrix;
    public:
    /*
    * Constructor: DirectedGraph
    *
    * Parameters: mode
    * Used to decide which representation to use
    * 'm' for AdjacencyMatrix
    * 'l' for AdjacencyList
    */

    DirectedGraph(int numVertices, char mode){
        if(mode == 'm'){
            matrixType = mode;
            no_of_rows = no_of_cols = numVertices;
            adjacencyMatrix = new int*[numVertices];
            for(int i = 0; i < no_of_rows; i++){
                adjacencyMatrix[i] = new int[numVertices];
                for(int j = 0; j < no_of_cols; j++){
                    adjacencyMatrix[i][j] = 0;
                } 
            }
        }
    }

    /*
    * Function: edgeExists
    * Returns true if an edge exists between vertices i and j, false otherwise.
    */
    bool edgeExists(int i, int j){
        return adjacencyMatrix[i][j] != 0 ? true : false;
    }

    int getEdge(int i, int j){
        return adjacencyMatrix[i][j];
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
    * Function: vertices
    * Returns the number of vertices in the adjacency structure.
    */
    int vertices(){
        return no_of_rows;
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

    /*
    * Function: indegree
    * Returns the indegree of a vertex
    */
    int indegree(int i){
        int in_degree = 0;
        for(int row = 0; row < no_of_rows; row++){
            if(adjacencyMatrix[row][i]){
                in_degree++;
            }
        }
        return in_degree;
    }

    /*
    * Function: outdegree
    * Returns the outdegree of a vertex.
    */
    int outdegree(int j){
        int out_degree = 0;
        for(int col = 0; col < no_of_cols; col++){
            if(adjacencyMatrix[j][col]){
                out_degree++;
            }
        }
        return out_degree;
    }


    /* Function Kruskal.
    *
    * Params:
    * 1. E : A vector of objects of type Edge.
    * 2. v : Number of vertices
    *
    * Returns Adjacency matrix representation of MST
    */
    vector<vector<int>> Kruskal(vector<Edge> E, int v){
        vector<vector<int>> MST;
        if(matrixType == 'm'){
            sort(E.begin(), E.end(), [](const Edge & E1, const Edge & E2) -> bool {
                return E1.wt < E2.wt; });
            
            cs514 :: UFDS _UFDS_ = cs514 :: UFDS(v);
            _UFDS_.make_set(v);
            for(auto edge : E){
                int src = edge.src;
                int des = edge.des;
                int wt = edge.wt;

                if(!_UFDS_.is_same_set(src, des)){
                    if(--v == 0){
                        break;
                    }
                    _UFDS_.union_set(src, des);
                    vector<int> include_in_MST {src, des, wt};
                    MST.push_back(include_in_MST);
                }
            }
        }
        return MST;
    }



    /**
    * returns true if we have already added the current edge into the MST;
    * otherwise, false
    */
    bool _AlreadyInMST(vector<vector<int>> MST, int src, int des){
        for(auto edge : MST){
            /**
             * Checks if the unidirectional edge is already added into the resultant MST
            */
            if((edge[0] == src && edge[1] == des) || (edge[0] == des && edge[1] == src)){
                return true;
            }
        }
        return false;
    }

    /**
     * Traverse every edge of a particular vertex and adds it to the Fibonacci Heap in case:
     * if it is not already present in the MST constructed so far or if we already not already 
     * rejected the edge(found a better one!)
    */
    void _AddOutGoingEdges(int vertex, vector<vector<int>> G, vector<vector<int>> MST, bool *visited){
        for(int i = 0; i < G.size(); i++){
            if(G[vertex][i] != 0){
                /**
                 * if -> check if the edge we are trying to add is already present in the resultant MST,
                 *       or whether we have already visited the edge
                 *                        ⬇️
                 *                       Y E S 
                 *                        ⬇️ 
                 *          Add the edge into the Fibonacci Heap;
                 *          otherwise, continue onto the next edge 
                 *   
                */
                if((_AlreadyInMST(MST, vertex, i)) || (visited[vertex] && visited[i])){
                    continue;
                }

                /**
                 * Inserting the edge in Fibonacci Heap
                */
                _FibonacciHeap.Fib_Heap_Insert(_FibonacciHeapObj, G[vertex][i], 0, vertex, i);
            }
        }
    }

    vector<vector<int>> Prim(vector<vector<int>> G, const int vertices){
        /**
         * stores the resultant MST
        */
        vector<vector<int>> MST;

        /**
         * If the Graph is Empty, we return an empty MST
        */
        if(G.size() == 0){
            return MST;
        }

        /**
         * Boolean array to keep track of the visited nodes of the Graph
        */ 
        bool *visited = new bool[vertices];
        for(int i = 0; i < vertices; i++){
            visited[i] = false;
        }

        /**
         * initializing the first node, to jump-start the MST finding algorithm
        */
        int start_node = 0;
        visited[start_node] = true;

        /**
         * adds all the outgoing edges from a particular vertex 
        */
        _AddOutGoingEdges(start_node, G, MST, visited);    

        /**
         * Traverses the edges V - 1 times to find the MST
        */
        int i = 0;
        while(i < vertices - 1){
            /**
             * Extracts the minimum node for the Fibonacci Heap in -> O(log(n)) amortized cost
            */
            node *node = _FibonacciHeap.Extract_Min(_FibonacciHeapObj);
            int wt = node->key;
            int src = node->src;
            int des = node->des;

            /**
             * if -> check if the edge we are trying to add is already present in the resultant MST,
             *       or whether we have already visited the edge
             * else -> we add this edge to the MST
            */
            if((_AlreadyInMST(MST, src, des)) || (visited[src] && visited[des])){
                continue;
            } else {
                i++;
                visited[src] = true;
                visited[des] = true;
                MST.push_back({src, des, wt});
            }

            /**
             * adds all the outgoing edges from a particular vertex 
            */
            _AddOutGoingEdges(des, G, MST, visited);
        }  
        return MST;
    }
  
    /* Function Dijkstra.
     *
     * Params:
     * 1. G : Object of the DirectedGraph.
     * 2. v : Number of vertices.
     * 3. src : Source node.
     *
     * Returns ShortestPathTree.
    */
    Shortest_Path_Tree* Dijkstra(DirectedGraph* G, int vertices, int src){
        /**
         * To keep track of predecessor in order to determine the path
        */
        vector<TreeNode *> _TreeNodes;

        /**
         * To keep track of already visited nodes
        */
        bool* visited = new bool[vertices];   

        /**
         * Initialization phase
        */
        for(int i = 0; i < vertices; i++){
            visited[i] = false;
            _TreeNodes.push_back(new TreeNode(INT_MAX, NULL, i));
            _FibonacciHeap.Fib_Heap_Insert(_FibonacciHeapObj, INT_MAX, i, 0, 0);
        }

        /**
         * To kick-start the Dijkstras' Algorithm
        */
        _TreeNodes.at(src)->distance = 0;
        _FibonacciHeap.Fib_Heap_Decrease_key(_FibonacciHeapObj, src, _FibonacciHeap.Fib_Heap_Find(_FibonacciHeapObj, src)->key, _TreeNodes.at(src)->distance);

        /**
         * Running the algorithm till there are nodes in the Fibonacci Heap .i.e (V - 1) times
        */
        while(_FibonacciHeap.get_number_of_nodes(_FibonacciHeapObj) != 0){
            /**
             * Extracting the vertex node with minimum edge weight from the Fibonacci Heap
            */
            node *u = _FibonacciHeap.Extract_Min(_FibonacciHeapObj);
            visited[u->label] = true;

            /**
             * Visiting the neighbours of the extracted vertex node
            */
            for(int v = 0; v < vertices; v++){
                if(G->edgeExists(u->label, v)){
                    int _edgeWeight = G->getEdge(u->label, v);
                    if((u->key + _edgeWeight) < _TreeNodes.at(v)->distance){
                        /**
                         * Relaxing the edge u->v
                        */
                        _TreeNodes.at(v)->distance = u->key + _edgeWeight;
                        _TreeNodes.at(v)->predecessor = _TreeNodes.at(u->label);
                        if(!visited[v]){
                            _FibonacciHeap.Fib_Heap_Decrease_key(_FibonacciHeapObj, v, _FibonacciHeap.Fib_Heap_Find(_FibonacciHeapObj, v)->key, _TreeNodes.at(v)->distance);
                        }
                    }
                }
            }
        }

        Shortest_Path_Tree *_shortestpathtree = new Shortest_Path_Tree();
        for(int i = 0; i < vertices; i++){
            _shortestpathtree->treeNode.push_back(_TreeNodes.at(i));
        }
        return _shortestpathtree;
    }

    /* Function Display_Shortest_Path_Tree.
     *
     * Param:
     * 1. SPT : Object of Shortest_Path_Tree.
    */
    void Display_Shortest_Path_Tree(Shortest_Path_Tree* SPT){
        for(auto _path : SPT->treeNode){
            TreeNode *_current = _path;
            stack<TreeNode *> _Stack;
            while(_path != NULL){
                _Stack.push(_path);
                _path = _path->predecessor;
            }

            while(!_Stack.empty()){
                cout << _Stack.top()->label;
                _Stack.pop();
                cout << (!_Stack.empty() ? "->" : "");
            }
            cout << " -----> distance: " << _current->distance << endl;
        }
    }
};
#endif /* ifndef DIRECTED_GRAPH */