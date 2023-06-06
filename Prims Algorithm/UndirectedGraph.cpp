#include <map>
#include <vector>
#include "seqLinearList.hpp"
#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"

/**
 * Fibonacci Heap to minimize the cost of certain operations like 
 * extract_min -> (O(log(n)))
 * decrease_key_operation -> (O(1))
*/
FibonacciHeap fibonacci_heap;
Fibonacci_Heap* heap_obj = fibonacci_heap.Make_Fib_Heap();

/*
* Constructor: UndirectedGraph
*
* Parameters: mode
* Used to decide which representation to use
* 'm' for AdjacencyMatrix
* 'l' for AdjacencyList
*/
UndirectedGraph :: UndirectedGraph(int vertices, char mode){
    if(mode == 'm'){
        matrix_type = mode;
        no_of_rows = no_of_cols = vertices;
        adjacencyMatrix = new int*[vertices];
        for(int i = 0; i < vertices; i++){
            adjacencyMatrix[i] = new int[vertices];
            for(int j = 0; j < vertices; j++){
                adjacencyMatrix[i][j] = 0;
            } 
        }
    }
}

/*
* Function: edgeExists
* Returns true if an edge exists between vertices i and j, false otherwise.
*/
bool UndirectedGraph :: edgeExists(int i, int j){
    return adjacencyMatrix[i][j] != 0 ? true : false;
}

/*
* Function: edges
* Returns the number of edges in the adjacency structure.
*/
int UndirectedGraph :: edges(){
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
int UndirectedGraph :: vertices(){
    return no_of_rows;
}

/*
* Function add:
* Adds an edge between vertices i and j having weight wt.
*/
void UndirectedGraph :: add(int i, int j, int wt){
    adjacencyMatrix[i][j] = wt;
    adjacencyMatrix[j][i] = wt;
}

/*
* Function: remove
* Deleted the edge between vertices i and j
*/
void UndirectedGraph :: remove(int i, int j){
    adjacencyMatrix[i][j] = 0;
    adjacencyMatrix[j][i] = 0;
}

/*
* Returns the degree of the vertex.
*/
int UndirectedGraph :: degree(int i){
    int no_of_degree = 0;
    for(int col = 0; col < no_of_cols; col++){
        if(adjacencyMatrix[i][col] != 0){
            no_of_degree++;
        }
    }
    return no_of_degree;
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
            fibonacci_heap.Fib_Heap_Insert(heap_obj, G[vertex][i], vertex, i);
        }
    }
}

vector<vector<int>> UndirectedGraph :: Prim(vector<vector<int>> G, const int vertices){
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
        node *node = fibonacci_heap.Extract_Min(heap_obj);
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

