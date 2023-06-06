#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"
#include "DirectedGraph.hpp"
using namespace std;

vector<vector<int>> generateMatrixViaTerminal(const int& no_of_vertices){
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

vector<int> split(const string row, const char delim){
    string element;
    vector<int> elements_of_row;
    stringstream ss(row);
    while(getline(ss, element, delim)){
        elements_of_row.push_back(stoi(element));
    }
    return elements_of_row;
}

vector<vector<int>> generateMatrixViaFile(const string file_path){
    vector<vector<int>> matrix;
    fstream input_file;
    input_file.open(file_path, ios :: in);
    if(input_file.is_open()){
        string row;
        while(getline(input_file, row)){
            matrix.push_back(split(row, ' '));
        }
        input_file.close();
    }
    return matrix;
}

void performFunctions(vector<vector<int>> matrix, int no_of_vertices, char mode){
    UndirectedGraph undirectedGraph(no_of_vertices, mode);
    vector<Edge> edges;
    for(int i = 0; i < no_of_vertices; i++){
        for(int j = i; j < no_of_vertices; j++){
            if(matrix.at(i).at(j) != 0){
                undirectedGraph.add(i, j, matrix.at(i).at(j));
                edges.push_back(Edge(i, j, matrix.at(i).at(j)));
            }
        }
    }
    
    do{
        cout << "-------------------------------------------------------------------------\n";
        cout <<"Select the function to be performed: \n";
        cout << "1.edgeExists\n";
        cout << "2.edges\n";
        cout << "3.vertices\n";
        cout << "4.add\n";
        cout << "5.remove\n";
        cout << "6.degree\n";
        cout << "7.kruskal\n";
        cout << "0.Exit\n";
        cout << "-------------------------------------------------------------------------\n";
        int choice;
        cin >> choice;
        if(choice == 0){
            return;
        }

        int src, des, wt;
        switch (choice)
        {
        case 1:
            cout << "enter source, destination vertices\n";
            cin >> src >> des;
            cout << ((undirectedGraph.edgeExits(src, des) == false) ? "false\n" : "true\n");
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
                cout << "MST is :\n";
                vector<vector<int>> MST = undirectedGraph.Kruskal(edges, no_of_vertices);
                for(auto row : MST){
                    for(auto col : row){
                        cout << col << " ";
                    }   
                    cout << endl;
                }
                break;
            }
            
        
        default:
            cout << "Invalid Choice\n";
            break;
        }
    } while (true);
}

int main(){
    string file_path;
    int no_of_vertices;
    vector<vector<int>> matrix;
    cout << "Select input method...\n";
    int choice;
    cout << "1.Enter Via Console\n2.Enter Via File\n";
    cin >> choice;
    char mode;
    switch(choice){
        case 1:
            cout<< "Enter mode : m -> Adjacency Matirix\t l -> Adjacency List\n";
            cin >> mode;
            cout << "Enter number of vertices:\n";
            cin >> no_of_vertices;
            matrix = generateMatrixViaTerminal(no_of_vertices);
            performFunctions(matrix, no_of_vertices, mode);
            break;
        case 2:
            cout << "Enter file path\n";
            cin >> file_path;
            cout << "Enter mode : m -> Adjacency Matirix\t l -> Adjacency List\n";
            cin >> mode;
            matrix = generateMatrixViaFile(file_path);
            no_of_vertices = matrix.size();
            performFunctions(matrix, no_of_vertices, mode);
            break;
        default:
            cout<< "Invalid Choice\n";
    }

    return 0;
}