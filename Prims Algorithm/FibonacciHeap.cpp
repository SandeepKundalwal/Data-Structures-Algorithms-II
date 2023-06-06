#include<iostream>
#include<vector>
#include "FibonacciHeap.hpp"
#include "Utilities.hpp"
using namespace std;

Utilities utility;
/**
 * Constructor
 */
FibonacciHeap :: FibonacciHeap(){
    obj = new Fibonacci_Heap();
    node* newNode = NULL;

    obj -> minNode = newNode;
    obj -> numberOfNodes = 0;
}

/**
 * Destructor
 */
FibonacciHeap :: ~FibonacciHeap(){
    delete obj;
}

/**
 * Function Make_Fib_Heap.
 * Returns an instance of Fibonacci_Heap.
 */
Fibonacci_Heap* FibonacciHeap :: Make_Fib_Heap(){
    return obj;
}

/**
 * Function Fib_Heap_Insert.
 * Inserts a given integer x into Fibonacci_Heap.
 * Returns object of the Fibonacci_Heap after insertion.
 * 
 * Fib_Heap_Insert() - O(1) actual; O(2) amortized for clean up process
 */
Fibonacci_Heap* FibonacciHeap :: Fib_Heap_Insert(Fibonacci_Heap* obj, int x, int src, int des){
    node* new_node = new node();
    new_node -> label = 0;
    new_node -> key = x;
    new_node -> src = src;
    new_node -> des = des;
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
     * If minNode is NULL, then Fibonacci Heap is empty
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
Fibonacci_Heap* FibonacciHeap :: Fib_Heap_Union(Fibonacci_Heap* obj1, Fibonacci_Heap* obj2){
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
node* FibonacciHeap :: Extract_Min(Fibonacci_Heap* obj){
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
             * Consolidate heap to find new minimum and do reorganize work
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
 * Function Consolidate.
 * Rearranges the Fibonacci_Heap.
 */
Fibonacci_Heap* FibonacciHeap :: Consolidate(Fibonacci_Heap* obj){
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
                utility._Exchange(x, y);
            }

            if(z == y){
                z = y->right;
            }

            /**
             * We need to link the tree with higher key to the tree with lower key
            */
            utility._Link(y, x);

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
            utility._AddToRootList(obj, A[iterator]);
            if((NULL == obj->minNode) || ((A[iterator]->key < (obj->minNode)->key))){
                obj->minNode = A[iterator];
            }
        }
    }
    return obj;
}


/**
 * Function Fib_Heap_Display.
 * Prints the Fibonacci_Heap.
 */
void FibonacciHeap:: Fib_Heap_Display(Fibonacci_Heap* obj){
    node *start = obj->minNode;
    cout << "(";
    while (start->right != obj->minNode)
    {
        utility._PrintHeap(start);
        start = start->right;
    }
    utility._PrintHeap(start);
    cout << ")\n";
}


/**
 * Function Fib_Heap_Find.
 * Finds the value x in the Fibonacci_Heap.
 * Returns the node containing value x, otherwise null.
 */
node* FibonacciHeap :: Fib_Heap_Find(Fibonacci_Heap* obj, int x){  
    return utility._Find(obj, obj->minNode, x);
}


/**
 * Function Fib_Heap_Decrease_key.
 * Decreases the value x to new value k.
 * If operation is successful returns true otherwise false.
 */
bool FibonacciHeap :: Fib_Heap_Decrease_key(Fibonacci_Heap* obj, int label, int x, int k){
    node *theParent;

    if(obj == NULL || obj->minNode == NULL){
        cout << "The Fibonacci Heap is empty.\n";
        return false;
    }

    if(x < k){
        cout << "The new key is greater than the old key.\n";
        return false;
    }
    node* _key = Fib_Heap_Find(obj, x);

    if(NULL == _key){
        cout << "Node with key " << k << " not found in Fibonacci Heap.\n";
        return false;
    }

    _key->key = k;
    theParent = _key->parent;
    if((theParent != NULL) && (_key->key < theParent->key)){
        utility._Cut(obj, _key, theParent);
        utility._CascadeCut(obj, theParent);
    } 
    
    if(_key->key < (obj->minNode)->key){
        obj->minNode = _key;
    }
    return true;
}


/**
 * Function Fib_Heap_Delete_key.
 * Deletes the given value k from the Fibonacci_Heap.
 * If operation is successful returns true otherwise false.
 */
bool FibonacciHeap :: Fib_Heap_Delete_key(Fibonacci_Heap* obj, int k){
    node *_key = Fib_Heap_Find(obj, k);

    if(_key == NULL){
        cout << "Node with key " << k << "not found in the Fibonacci Heap.\n";
        return false;
    }

    if(Fib_Heap_Decrease_key(obj, _key->label, k, INT_MIN)){
        if(Extract_Min(obj) == NULL){
            cout << "Encountered some issue while deleting the node with key " << k << endl;
            return false;
        }
    }
    return true;
}


/**
 * Function get_number_of_nodes.
 * Returns total number of nodes present in the Fibonacci_Heap.
 */
int FibonacciHeap :: get_number_of_nodes(Fibonacci_Heap* obj){
    return obj->numberOfNodes;
}