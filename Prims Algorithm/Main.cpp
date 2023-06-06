#include<iostream>
#include<string>
#include<vector>
#include "Utilities.hpp"
using namespace std;

/**
 * Run the functions associated with Undirected Graph
*/
int main(){   
    Utilities utility;
    string _FilePath;
    int no_of_vertices;
    vector<vector<int>> matrix;
    cout << "Select input method...\n";
    int choice;
    cout << "1.Enter Via Console\n2.Enter Via File\n";
    cin >> choice;
    char mode;
    switch(choice){
        case 1:
            cout<< "Enter mode : m -> Adjacency Matrix\t l -> Adjacency List\n";
            cin >> mode;
            cout << "Enter number of vertices:\n";
            cin >> no_of_vertices;
            cout << "Enter elements of the matrix:\n";
            /**
             * Generating Graph using Terminal
            */
            matrix = utility._GenerateMatrixViaTerminal(no_of_vertices);
            utility._PerformOperation(matrix, no_of_vertices, mode);
            break;

        case 2:
            cout << "Enter mode : m -> Adjacency Matrix\t l -> Adjacency List\n";
            cin >> mode;
            cout << "Enter File Path\n";
            cin >> _FilePath;
            cout << "Enter number of vertices: ";
            cin >> no_of_vertices;
            /**
             * Generating Graph using File
            */
            matrix = utility._GenerateMatrixViaFile(_FilePath, no_of_vertices);
            utility._PerformOperation(matrix, no_of_vertices, mode);
            break;
            
        default:
            cout << "Invalid Choice\n";
            break;
    }
    return 0;
}