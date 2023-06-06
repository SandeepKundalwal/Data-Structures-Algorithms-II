#ifndef Utility
#define Utility
#include <climits>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include "FibonacciHeap.hpp"

/**
 * Internal functions that help to implement the Standard Operations
*/
class Utilities {
    public: 
        /**
         * Inserts node x into the Fibonacci Heap
        */
        void _AddToRootList(Fibonacci_Heap* obj, node* x);
        
        /**
         * Swaps the node x and y
        */
        void _Exchange(node* &x, node* &y);

        /**
         * The node y is removed from the root list and becomes a subtree of node x.
        */
        void _Link(node* y, node*x);

        /**
         * Finds the node with key x in the Fibonacci Heap
        */
        node* _Find(Fibonacci_Heap* obj, node* traverse_heap, int x);

        /**
         * Remove node x from the child list of its parent node y
        */
        void _Cut(Fibonacci_Heap* obj, node* x, node* y);

        /**
        * Cuts each node in parent list, putting successive ancestor nodes on the
        * root list until we either arrive at the root list or until we find an
        * ancestor that is unmarked.  When a mark is set (which only happens during
        * a cascading cut), it means that one child subtree has been lost; if a
        * second subtree is lost later during another cascading cut, then we move
        * the node to the root list so that it can be re-balanced on the next
        * consolidate.
        */
        void _CascadeCut(Fibonacci_Heap* obj, node* y);

        /**
         * Get the childrens of a node
        */
        vector<node *> _GetAllChildren(node *node);

        /**
         * Prints the nodes of the Fibonacci Heap
        */
        void _PrintHeap(node *root);   

        /**
         * 
        */
        vector<int> _Split(const string row, const char delim);

        /**
         * generate Matrix Via Terminal
        */
        vector<vector<int>> _GenerateMatrixViaTerminal(int no_of_vertices);

        /**
         * generate Matrix Via File
        */
        vector<vector<int>> _GenerateMatrixViaFile(const string _FilePath, int no_of_vertices);

        /**
         * Perform various operations on Undirected Graph
        */
        void _PerformOperation(vector<vector<int>> matrix, int no_of_vertices, char mode);
};

#endif