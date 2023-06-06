// Purpose: 
// Author: 
// Date of Creation: 20 October 2022
// Bugs:
// Date of Modification: 26 October 2022

#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include <iostream>
#include <cmath>
#include<vector>
using namespace std;

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
		FibonacciHeap(){
			obj = new Fibonacci_Heap();
    		node* newNode = NULL;

    		obj -> minNode = newNode;
    		obj -> numberOfNodes = 0;
		}

		/**
		 * Destructor
		 */
		~FibonacciHeap(){}

		/**
		 * Function Make_Fib_Heap.
		 * Returns an instance of Fibonacci_Heap.
		 */
		Fibonacci_Heap* Make_Fib_Heap(){
			return obj;
		}

		/**
		 * Function Fib_Heap_Insert.
		 * Inserts a given integer x into Fibonacci_Heap.
		 * Returns object of the Fibonacci_Heap after insertion.
		 */
		Fibonacci_Heap* Fib_Heap_Insert(Fibonacci_Heap* obj, int x, int label, int src, int des){
			node* new_node = new node();
    		new_node -> key = x;
			new_node -> label = label;
			new_node->src = src;
			new_node->des = des;
    		new_node -> degree = 0;
    		new_node -> parent = NULL;
    		new_node -> child = NULL;
    		new_node -> left = new_node;
    		new_node -> right = new_node;
    		/**
    		 * M -> for marked nodes
    		 * U -> for unmarked nodes
    		*/
    		new_node -> mark = 'U';
    		/**
    		 * If minNode is NULL, then Fibonacci Heap is empty and we make the newly created node
			 * as the minNode
    		*/
    		if(obj -> minNode != NULL){
        		/**
        		 * Inserting the new node to the left of the min node
        		*/
				(obj -> minNode -> left) -> right = new_node;
        		new_node -> right = obj -> minNode;
        		new_node -> left = obj -> minNode -> left;
        		obj -> minNode -> left = new_node;

        		/**
        		 * Adjusting the minimum node in case new_node is the minimum
        		*/
        		if(new_node -> key < obj -> minNode -> key){
            		obj -> minNode = new_node;
        		} 
    		} else {
        		obj -> minNode = new_node;
    		}
    		obj -> numberOfNodes++;
    		return obj;
		}

		/**
		 * Function Fib_Heap_Union.
		 * Combines two fibonacci heaps with objects obj1 and obj2.
		 * Returns object of the combined Fibonacci_Heap.
		 */
		Fibonacci_Heap* Fib_Heap_Union(Fibonacci_Heap* obj1, Fibonacci_Heap* obj2){
			node *Min1, *Min2, *Next1, *Next2;
    		Fibonacci_Heap* heap_obj = Make_Fib_Heap();

    		if((obj1 == NULL && obj1->minNode == NULL) && (obj2 == NULL && obj2->minNode == NULL)){
        		return heap_obj;
    		} else if(obj1 == NULL && obj1->minNode == NULL){
        		heap_obj->minNode = obj2->minNode;
        		return heap_obj;
    		} else if(obj2 == NULL && obj2->minNode == NULL){
        		heap_obj->minNode = obj1->minNode;
        		return heap_obj;
    		}

    		/**
    		 * We join the two circular lists by cutting each list between its
    		 * min node and the node after the min.  This code just pulls those
    		 * nodes into temporary variables so we don't get lost as changes
    		 * are made.
    		*/
    		Min1 = obj1->minNode;
    		Min2 = obj2->minNode;
    		Next1 = Min1->right;
    		Next2 = Min2->right;

    		/**
    		 * To join the two circles, we join the minimum nodes to the next
    		 * nodes on the opposite chains.
    		*/
    		Min1->right = Next2;
    		Next2->left = Min1;
    		Min2->right = Next1;
    		Next1->left = Min2;

    		/**
    		 * Minimum node after union
    		*/
    		heap_obj->minNode = ((Min2->key < Min1->key) ? Min2 : Min1);
    
    		/**
    		 * Number of nodes afer union
    		*/
    		heap_obj -> numberOfNodes = (obj1 -> numberOfNodes) + (obj2 -> numberOfNodes);    
    		return heap_obj;
		} 

		/**
		 * Function Extract_Min.
		 * Deletes node containing minimum value from the Fibonacci_Heap.
		 * Returns this node containing minimun value.
		 */
		node* Extract_Min(Fibonacci_Heap* obj){
			node* z = obj->minNode;
    		node* child_node = NULL;
    		node* child_node_traverse_right = NULL;
    		if(NULL != z){
        		/**
        		 * Attach child list of Minimum node to the root list of the heap
        		 * If there is no child list, then do no work
        		*/
        		child_node = z->child;
        		if(NULL != child_node){  
            		do{
                		child_node_traverse_right = child_node->right;
                		(obj->minNode->left)->right = child_node;
                		child_node->right = obj->minNode;
                		child_node->left = obj->minNode->left;
                		obj->minNode->left = child_node;
                		child_node->parent = NULL;
                		child_node = child_node_traverse_right;
            		} while(child_node_traverse_right != z->child);
        		}  
          
        		/**
        		 * Remove minimum node and set MinRoot to next node
        		*/
        		(z->left)->right = z->right;
        		(z->right)->left = z->left;

        		/**
        		 * if --> In case Fibonacci Heap had only one node, then after Extract_Min
        		 *        the Fibonacci Heap will become empty.
        		 * else --> Go for consolidation
       			*/
        		if(z == z->right){
        		    obj->minNode = NULL;
        		} else {
        		    obj->minNode = z->right;

        		    /**
        		     * Consolidate heap to find new minimum and do reorganize work ie. re-balance the heap
        		    */
        		    Consolidate(obj);
        		}
        		obj->numberOfNodes--;

        		/**
        		 * Return the minimum node, which is now disassociated with the heap
        		 * It has Left, Right, Parent, Child, Mark and Degree cleared.
        		*/
        		return z;      
    		} else {
        		cout << "Fibonacci Heap is empty." << endl;
        		return NULL;
    		}
		}

		/**
		 * Function Fib_Heap_Display.
		 * Prints the Fibonacci_Heap.
		 */
		void Fib_Heap_Display(Fibonacci_Heap* obj){
			node *start = obj->minNode;
    		cout << "(";
    		while (start->right != obj->minNode)
    		{
    		    _PrintHeap(start);
    		    start = start->right;
    		}
    		_PrintHeap(start);
    		cout << ")\n";
		}

		/**
		 * Function Fib_Heap_Find.
		 * Finds the value x in the Fibonacci_Heap.
		 * Returns the node containing value x, otherwise null.
		 */
		node* Fib_Heap_Find(Fibonacci_Heap* obj, int label){
			return _FindNode(obj->minNode, label);
		}

		node* Fib_Find_Prim(Fibonacci_Heap* obj, int key){
			return _FindNodePrim(obj->minNode, key);
		}

		/**
		 * Utilty for Fib_Heap_Find
		*/
        node* _FindNodePrim(node *root, int key){
            if(root == NULL){
                return NULL;
            }

            node *_node = root;

            /**
             * traversing the current rootlist by moving towards right
            */
            do {
                if(_node->key == key){
                    return _node;
                }
                _node = _node->right;
            } while(_node != root);

            /**
             * if the key is not in this rootlist, 
             * we move to the current node's child and recursively traverse the rootlist again
            */
            _node = root;
            node *_result = NULL;
            do{
                if(_node->child != NULL){
                    if(_result == NULL){
                        _result = _FindNode(_node->child, key);
                    }
                }
                _node = _node->right;
            } while(_node != root);

            return _result;
        }

		/**
		 * Function Consolidate.
		 * Rearranges the Fibonacci_Heap.
		 */
		Fibonacci_Heap* Consolidate(Fibonacci_Heap* obj){
			int degree;
    		int Dn = ceil(log(obj->numberOfNodes)) / (log(2)) + 1;
    		node *x, *y, *z;
    		node *A[Dn];
    
    		/**
    		 * Initialize the consolidation detection array
    		*/
    		for(int iterator = 0; iterator < Dn; iterator++){
    		    A[iterator] = NULL;
    		}
    
    		/**
    		 * The Fibonacci Heap is not circular anymore
    		*/
    		(obj->minNode->left)->right = NULL;
    		obj->minNode->left = NULL;
    		z = obj->minNode;

    		do{
    		    x = z;
    		    degree = x->degree;
    		    z = z->right;

    		    /**
    		     * We need another loop here because the consolidated result
    		     * may collide with another large tree on the root list.
    		    */
    		    while(NULL != A[degree]){
    		        y = A[degree];

    		        if(x->key > y->key){
    	            	_Exchange(x, y);
    		        }

    		        if(z == y){
   		             z = y->right;
    		        }

    		        /**
    		         * We need to link the tree with higher key to the tree with lower key
    		        */
    		        _Link(y, x);
         		    A[degree] = NULL;
        		    degree++;   
        		}
        		A[degree] = x;  
    		} while (z != NULL);
    
    	/**
    	 * Now we rebuild the root list, find the new minimum,set all root 
    	 * list nodes' parent pointers to NULL and count the number of subtrees.
    	*/
    	obj->minNode = NULL;
    	for(int iterator = 0; iterator < Dn; iterator++){
    	    if(NULL != A[iterator]){
        	    A[iterator]->left = A[iterator];
        	    A[iterator]->right = A[iterator];  
        	    _AddToRootList(obj, A[iterator]);
       		    if((NULL == obj->minNode) || ((A[iterator]->key < (obj->minNode)->key))){
        	        obj->minNode = A[iterator];
        	    }
        	}
    	}
    	return obj;
		}

		/**
		 * Function Fib_Heap_Decrease_key.
		 * Decreases the value x to new value k.
		 * If operation is successful returns true otherwise false.
		 */
		bool Fib_Heap_Decrease_key(Fibonacci_Heap* obj, int label, int x, int k){
			node *theParent;

    		if(obj == NULL || obj->minNode == NULL){
    		    cout << "The Fibonacci Heap is empty.\n";
    		    return false;
    		}

    		if(x < k){
    		    cout << "The new key is greater than the old key.\n";
    		    return false;
    		}

    		/**
    		 * Finding the node whose key we need to decrease
    		*/
    		node* _label = Fib_Heap_Find(obj, label);

    		if(NULL == _label){
    		    cout << "Node with label " << k << " not found in Fibonacci Heap.\n";
    		    return false;
    		}

    		_label->key = k;
    		theParent = _label->parent;
    		if((theParent != NULL) && (_label->key < theParent->key)){
    		    /**
    		     * Cutting _key from it's parent
    		    */
    		    _Cut(obj, _label, theParent);

    		    /**
    		     * recursively cutting edge if parent edge is marked 
    		     * and theParent->key > _key->key
    		    */
    		    _CascadeCut(obj, theParent);
    		} 

    		if(_label->key < obj->minNode->key){
    		    obj->minNode = _label;
    		}
    		return true;
		}
		
		/**
		 * Function Fib_Heap_Delete_key.
		 * Deletes the given value k from the Fibonacci_Heap.
		 * If operation is successful returns true otherwise false.
		 */
		bool Fib_Heap_Delete_key(Fibonacci_Heap* obj, int k){
			node *_key = Fib_Heap_Find(obj, k);

    		if(_key == NULL){
        		cout << "Node with key " << k << "not found in the Fibonacci Heap.\n";
        		return false;
    		}

    		if(Fib_Heap_Decrease_key(obj, k, k, INT_MIN)){
    		    if(Extract_Min(obj) == NULL){
    		        cout << "Encountered some issue while deleting the node with key " << k << endl;
    		        return false;
    		    }
				return true;
    		}
    		return false;
		}

		/**
		 * Function get_number_of_nodes.
		 * Returns total number of nodes present in the Fibonacci_Heap.
		 */
    	int get_number_of_nodes(Fibonacci_Heap* obj){
			return obj->numberOfNodes;
		}

		/**
         * Inserts node x into the Fibonacci Heap
        */
        void _AddToRootList(Fibonacci_Heap* obj, node* x){
            if(x->mark == 'M'){
                x->mark = 'U';
            }

			/**
			 * Disconnecting the node x from its parent
			*/
            x->parent = NULL;

            if(obj->minNode != NULL){
                /**
                 * Inserting the new node to the left of the min node
                */
                obj -> minNode -> left -> right = x;
                x -> right = obj -> minNode;
                x -> left = obj -> minNode -> left;
                obj -> minNode -> left = x;
            } else {
                obj -> minNode = x;
            }
        }


        /**
		 * Utilty for Fib_Heap_Find
		*/
        node* _FindNode(node *root, int label){
            if(root == NULL){
                return NULL;
            }

            node *_node = root;

            /**
             * traversing the current rootlist by moving towards right
            */
            do {
                if(_node->label == label){
                    return _node;
                }
                _node = _node->right;
            } while(_node != root);

            /**
             * if the key is not in this rootlist, 
             * we move to the current node's child and recursively traverse the rootlist again
            */
            _node = root;
            node *_result = NULL;
            do{
                if(_node->child != NULL){
                    if(_result == NULL){
                        _result = _FindNode(_node->child, label);
                    }
                }
                _node = _node->right;
            } while(_node != root);

            return _result;
        }
        
        /**
         * Swaps the node x and y
        */
        void _Exchange(node* &x, node* &y){
            node *temp = x;
            x = y;
            y = temp;
        }

        /**
         * The node y is removed from the root list and becomes a subtree of node x.
        */
        void _Link(node* y, node*x){
            /**
            * Remove node y from root list
            */
            if(NULL != y->right){
                y->right->left = y->left;
            }
            if(NULL != y->left){
                y->left->right = y->right;
            }

            /**
             * Make node y a singleton circular list with a parent of x
            */
            y->left = y->right = y;
            y->parent = x;

            /**
             * If node x has no children, then list y is its new child list
             * Otherwise, node y must be added to node x's child list
            */
            if(NULL == x->child){
                x->child = y;
            } else {
                y->left = x->child;
                y->right = x->child->right;
                x->child->right = y;
                y->right->left = y;
            }

            /**
             * Increase the degree of node x because it's now a bigger tree
            */
            x->degree++;

            /**
             * Node y has just been made a child, so clear its mark
            */
            if(y->mark == 'M'){
                y->mark = 'U';
            }
        }

        /**
         * Remove node x from the child list of its parent node y
        */
        void _Cut(Fibonacci_Heap* obj, node* x, node* y){
			/**
			 * If x is the only child of y, then we make the child pointer of y as NULL
			*/
			if(x->right == x){
				y->child = NULL;
			}

			/**
			 * If y has multiple childrens, then we make the next node of x as it's child
			*/
            if(y->child == x && x->right != x){
                y->child = x->right;
            }

			/**
			 * Isolating the node that is to be cut from the rest of the nodes of the Fibonacci Heap
			*/
			x->left->right = x->right;
            x->right->left = x->left; 

			/**
			 * Since x is being removed from the child list of y,
			 * we decrease it's degree by 1
			*/
            y->degree--;

            

			/**
			 * Adding x to the root list
			*/
            _AddToRootList(obj, x);
        }

        /**
        * Cuts each node in parent list, putting successive ancestor nodes on the
        * root list until we either arrive at the root list or until we find an
        * ancestor that is unmarked.  When a mark is set (which only happens during
        * a cascading cut), it means that one child subtree has been lost; if a
        * second subtree is lost later during another cascading cut, then we move
        * the node to the root list so that it can be re-balanced on the next
        * consolidate.
        */
        void _CascadeCut(Fibonacci_Heap* obj, node* y){
            node* z = y->parent;

			/**
			 * if --> If y->mark is 'U', then we know that we have reached a point 
			 * 		  where we have to stop the cut as all the marked nodes have already
			 * 		  been moved to the root list, so that they can be-balanced on the next 
			 * 		  consolidate
			 * else --> the node is marked, so we have to perform the cut and move the node
			 * 		    to the root list
			*/
			if(y->mark == 'U'){
                    y->mark = 'M';
                    z = NULL;
            } else {
                    _Cut(obj, y, z);
                    _CascadeCut(obj, z);
            }
        }

        /**
         * Get the childrens of a node
        */
        vector<node *> _GetAllChildren(node *root){
            node *child = root->child;
            if (child == nullptr){
                return vector<node *>();
            }
        
            vector<node *> allChildren = vector<node *>();
            allChildren.push_back(child);
            node *temp = child->right;
            while (temp != child)
            {
                allChildren.push_back(temp);
                temp = temp->right;
            }
            return allChildren;
        }

        /**
         * Prints the nodes of the Fibonacci Heap
        */
       void _PrintHeap(node *root){
            vector<node *> childs = _GetAllChildren(root);
            cout << root->key << "(";
            for (auto n : childs)
            {
                _PrintHeap(n);
            }
            cout << ")->";
            return;
       }
};

#endif