#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include "Utilities.hpp"
#include "UndirectedGraph.hpp"
using namespace std;

/**
 * Inserts node x into the Fibonacci Heap
*/
void Utilities :: _AddToRootList(Fibonacci_Heap* obj, node* x){
    if(x->mark = 'M'){
        x->mark = 'U';
    }
    x->parent = NULL;
    if(obj->minNode != NULL){
        /**
         * Inserting the new node to the left of the min node
        */
        (obj -> minNode -> left) -> right = x;
        x -> right = obj -> minNode;
        x -> left = obj -> minNode -> left;
        obj -> minNode -> left = x;
    } else {
        obj -> minNode = x;
    }
}


/**
 * Swaps the node x and y
*/
void Utilities :: _Exchange(node* &x, node* &y){
    node *temp = x;
    x = y;
    y = temp;
}


/**
 * The node y is removed from the root list and becomes a subtree of node x.
*/
void Utilities ::_Link(node* y, node*x){
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
 * Finds the node with key x in the Fibonacci Heap
*/
node* Utilities :: _Find(Fibonacci_Heap* obj, node* traverse_heap, int x){
    if(traverse_heap->key == x){
        return traverse_heap;
    } else if(NULL != traverse_heap->child && obj->minNode != traverse_heap->child){
        return _Find(obj, traverse_heap->child, x);
    } else if (NULL != traverse_heap->right && obj->minNode != traverse_heap->right) {
        return _Find(obj, traverse_heap->right, x);
    } 
    return NULL;
}


/**
 * Remove node x from the child list of its parent node y
*/
void Utilities :: _Cut(Fibonacci_Heap* obj, node* x, node* y){
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
void Utilities :: _CascadeCut(Fibonacci_Heap* obj, node* y){
    node* z = y->parent;

    while (z != NULL){
        if(y->mark == 'U'){
            y->mark = 'M';
            z = NULL;
        } else {
            _Cut(obj, y, z);
            _CascadeCut(obj, z);
        }
    }
}

/**
 * Gets all the childrens of a rootlist node
*/
vector<node *> Utilities :: _GetAllChildren(node *root){
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
 * Prints all the childrens from one of the rootlist node
*/
void Utilities :: _PrintHeap(node *root){
    vector<node *> childs = _GetAllChildren(root);
    cout << root->key << "(";
    for (auto n : childs)
    {
        _PrintHeap(n);
    }
    cout << ")->";
    return;
}

/**
 * Generates the Graph Via Terminal
*/
vector<vector<int>> Utilities :: _GenerateMatrixViaTerminal(int no_of_vertices){
    int wt;
    vector<vector<int>> matrix;
    for(int i = 0; i < no_of_vertices; i++){
        vector<int> row;
        for(int j = 0; j < no_of_vertices; j++){
            cin >> wt;
            row.push_back(wt);
        }
        matrix.push_back(row);
    }
    return matrix;
}

/**
 * Splits the _InputFile into rows
*/
vector<int> Utilities :: _Split(const string row, const char delim){
    string element;
    vector<int> elements_of_row;
    stringstream ss(row);
    while(getline(ss, element, delim)){
        elements_of_row.push_back(stoi(element));
    }
    return elements_of_row;
}

/**
 * Generates the Graph Via File
*/
vector<vector<int>> Utilities :: _GenerateMatrixViaFile(const string _FilePath, int no_of_vertices){
    vector<vector<int>> matrix;
    fstream _InputFile;
    _InputFile.open(_FilePath, ios :: in);
    if(_InputFile.is_open()){
        string row;
        while(getline(_InputFile, row)){
            matrix.push_back(_Split(row, ' '));
        }
        _InputFile.close();
    }
    return matrix;
}

/**
 * Menu for the operations available in Undirected Graph that can be performed
*/
void Utilities :: _PerformOperation(vector<vector<int>> matrix, int no_of_vertices, char mode){
    UndirectedGraph undirectedGraph(no_of_vertices, mode);
    for(int i = 0; i < no_of_vertices; i++){
        for(int j = 0; j < no_of_vertices; j++){
            if(matrix.at(i).at(j) != 0){
                undirectedGraph.add(i, j, matrix.at(i).at(j));
            }
        }
    }

    do{
        cout << "-------------------------------------------------------------------------\n";
        cout <<"Select the function to be performed:\n";
        cout << "1.edgeExists\n";
        cout << "2.edges\n";
        cout << "3.vertices\n";
        cout << "4.add\n";
        cout << "5.remove\n";
        cout << "6.degree\n";
        cout << "7.prims algorithm\n";
        cout << "0.Exit\n";
        cout << "-------------------------------------------------------------------------\n";
        int choice;
        cin >> choice;
        if(choice == 0){
            return;
        }

        int src, des, wt;
        switch (choice){
            case 1:
                cout << "enter source, destination vertices\n";
                cin >> src >> des;
                cout << ((undirectedGraph.edgeExists(src, des) == false) ? "false\n" : "true\n");
                break;
        
            case 2:
                cout << "No of edges: " << undirectedGraph.edges() << endl;
                break;
        
            case 3:
                cout << "No of vertices: " << undirectedGraph.vertices() << endl;
                break;

            case 4:
                cout << "Enter the source vertex, destination vertex & weight to be added\n";
                cin >> src >> des >> wt;
                undirectedGraph.add(src, des, wt);
                break;
        
            case 5:
                cout << "Enter the edge to be removed\n";
                cin >> src >> des;
                undirectedGraph.remove(src, des);
                break;
        
            case 6:
                cout << "Enter the vertex whose degree is needed\n";
                int vertex;
                cin >> vertex;
                cout << "Degree of vertex " << vertex << " is " << undirectedGraph.degree(vertex) <<endl;
                break;

            case 7:
                {
                    cout << "MST is:\n";
                    vector<vector<int>> MST = undirectedGraph.Prim(matrix, no_of_vertices);
                    for(auto row : MST){
                        cout << row.at(0) << " " << row.at(1) << " " << row.at(2) << endl;
                    }
                    break;
                }

            default:
                cout << "Invalid Choice\n";
                break;
        }
    } while (true);
}

