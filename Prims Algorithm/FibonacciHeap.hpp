// Purpose: 
// Author: 
// Date of Creation: 20 October 2022
// Bugs:
// Date of Modification: 26 October 2022

#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include <iostream>
#include <cmath>
using namespace std;

#include "seqLinearList.hpp"

class node {
	public : 
		int label; //Label for the node
  		int key; // Value stored in the node.
		int src;
		int des;
  		int degree; // Number of children.
  		node *parent;
  		node *child;
  		node *left; // Left sibling
  		node *right; // Right sibling
  		char mark;

		node(){}
  		~node(){}
};


/**
 * Represents head of the fibonacci heap.
 * It should always point to the node containing minimum value.
 */
class Fibonacci_Heap {
	public:
  		int numberOfNodes;
 		node* minNode;

		Fibonacci_Heap(){}
 		~Fibonacci_Heap(){}
};


class FibonacciHeap {

	public:
		Fibonacci_Heap* obj;

		/**
		 * Constructor
		 */
		FibonacciHeap();

		/**
		 * Destructor
		 */
		~FibonacciHeap();

		/**
		 * Function Make_Fib_Heap.
		 * Returns an instance of Fibonacci_Heap.
		 */
		Fibonacci_Heap* Make_Fib_Heap();

		/**
		 * Function Fib_Heap_Insert.
		 * Inserts a given integer x into Fibonacci_Heap.
		 * Returns object of the Fibonacci_Heap after insertion.
		 */
		Fibonacci_Heap* Fib_Heap_Insert(Fibonacci_Heap* obj, int x, int src, int des);

		/**
		 * Function Fib_Heap_Union.
		 * Combines two fibonacci heaps with objects obj1 and obj2.
		 * Returns object of the combined Fibonacci_Heap.
		 */
		Fibonacci_Heap* Fib_Heap_Union(Fibonacci_Heap* obj1, Fibonacci_Heap* obj2); 

		/**
		 * Function Extract_Min.
		 * Deletes node containing minimum value from the Fibonacci_Heap.
		 * Returns this node containing minimun value.
		 */
		node* Extract_Min(Fibonacci_Heap* obj);

		/**
		 * Function Fib_Heap_Display.
		 * Prints the Fibonacci_Heap.
		 */
		void Fib_Heap_Display(Fibonacci_Heap* obj);

		/**
		 * Function Fib_Heap_Find.
		 * Finds the value x in the Fibonacci_Heap.
		 * Returns the node containing value x, otherwise null.
		 */
		node* Fib_Heap_Find(Fibonacci_Heap* obj, int x);

		/**
		 * Function Consolidate.
		 * Rearranges the Fibonacci_Heap.
		 */
		Fibonacci_Heap* Consolidate(Fibonacci_Heap* obj);

		/**
		 * Function Fib_Heap_Decrease_key.
		 * Decreases the value x to new value k.
		 * If operation is successful returns true otherwise false.
		 */
		bool Fib_Heap_Decrease_key(Fibonacci_Heap* obj, int label, int x, int k);
		
		/**
		 * Function Fib_Heap_Delete_key.
		 * Deletes the given value k from the Fibonacci_Heap.
		 * If operation is successful returns true otherwise false.
		 */
		bool Fib_Heap_Delete_key(Fibonacci_Heap* obj, int k);

		/**
		 * Function get_number_of_nodes.
		 * Returns total number of nodes present in the Fibonacci_Heap.
		 */
    	int get_number_of_nodes(Fibonacci_Heap* obj);
};

#endif