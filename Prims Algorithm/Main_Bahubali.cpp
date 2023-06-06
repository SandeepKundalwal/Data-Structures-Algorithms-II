#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"
#include "Utilities.hpp"
using namespace std;

/**
 * Checks if the edge already exists in the MST
*/
bool checkIfEdgeExistsInMST(int src, int des, vector<vector<int>> MST){
    for(auto row : MST){
        if((row.at(0) == src && row.at(1) == des) || (row.at(0) == des && row.at(1) == src)){
            return true;
        }
    }
    return false;
}

/**
 * Splits the _InputFile into rows
*/
vector<int> split(const string row, const char delim){
    string element;
    vector<int> elements_of_row;
    stringstream ss(row);
    while(getline(ss, element, delim)){
        elements_of_row.push_back(stoi(element));
    }
    return elements_of_row;
}

/**
 * Takes the Input Via Terminal
*/
void generateViaTerminal(char mode){
    /**
     * Taking No_Of_Vertices & No_Of_Edges
    */
    int no_of_vertices, no_of_edges;
    cin >> no_of_vertices >> no_of_edges;

    /**
     * Defining the UndirectedGraph
    */
    UndirectedGraph undirectedGraph(no_of_vertices, mode);

    /**
     * Defining a Graph and initializing it with 0
    */
    vector<vector<int>> G;
    for(int i = 0; i < no_of_vertices; i++){
        vector<int> row;
        for(int j = 0; j < no_of_vertices; j++){
            row.push_back(0);
        }
        G.push_back(row);
    }

    /**
     * Adding the weighted edges to the UndirectedGraph and Graph
    */
    int src, des, wt;
    for(int i =0; i < no_of_edges; i++){
        cin >> src >> des >> wt;
        undirectedGraph.add(src, des, wt);
        G.at(src).at(des) = wt;
    }

    /**
     * Using Prims' Algorithm to finding the Minimum Spanning Tree in O(E + ElogV)
    */
    vector<vector<int>> MST = undirectedGraph.Prim(G, no_of_vertices);

    /**
     * Answer that Katappas needs to give to Bahubali
    */
    int no_of_queries;
    cin >> no_of_queries;
    int answer = 0;
    while(no_of_queries--){
        cin >> src >> des;
        if(checkIfEdgeExistsInMST(src, des, MST)){
            answer++;
        }
    }
    cout << "Answer: " << answer;
}

/**
 * Takes the Input Via File by putting the content of the file in vector<vector<int>> and then reading it row-by-row
*/
void generateViaFile(const string _FilePath, char mode){
    vector<vector<int>> read_input_file;
    fstream input_file;
    input_file.open(_FilePath, ios :: in);
    if(input_file.is_open()){
        string row;
        while(getline(input_file, row)){
            read_input_file.push_back(split(row, ' '));
        }
        input_file.close();
    }

    int no_of_vertices = read_input_file.front().at(0);
    int no_of_edges = read_input_file.front().at(1);
    read_input_file.erase(read_input_file.begin());

    UndirectedGraph undirectedGraph(no_of_vertices, 'm');
    
    /**
     * Defining the Graph and initializing it with 0
    */
    vector<vector<int>> G;
    for(int i = 0; i < no_of_vertices; i++){
        vector<int> row;
        for(int j = 0; j < no_of_vertices; j++){
            row.push_back(0);
        }
        G.push_back(row);
    }

    /**
     * Adding weighted edges into the Graph 
    */
    int read_edges_till = no_of_edges;
    for(auto edge_info : read_input_file){
        if(read_edges_till == 0){
            break;
        } else {
            int src = edge_info.at(0);
            int des = edge_info.at(1);
            int wt = edge_info.at(2);
            undirectedGraph.add(src, des, wt);
            G.at(src).at(des) = wt;
            --read_edges_till;
        }
    }

    read_input_file.erase(read_input_file.begin(), read_input_file.begin() + no_of_edges);

    /**
     * Queries to be answered
    */
    int no_of_queries = read_input_file.front().at(0);
    read_input_file.erase(read_input_file.begin());

    /**
     * Using Prims' Algorithm to finding the Minimum Spanning Tree in O(E + ElogV)
    */
    vector<vector<int>> MST = undirectedGraph.Prim(G, no_of_vertices);

    /**
     * Answer that Katappas needs to give to Bahubali
    */
    int answer = 0;
    for(auto query : read_input_file){
        if(checkIfEdgeExistsInMST(query.at(0), query.at(1), MST)){
            answer++;
        }
    }
    cout << "Answer: " << answer;
}

/**
 * Runs the Bahubali-Katappa Problem
*/
int main(){
    string _FilePath;
    cout << "Select input method...\n";
    int choice;
    cout << "1.Enter Via Console\n2.Enter Via File\n";
    cin >> choice;
    char mode;
    switch(choice){
        case 1:
            cout<< "Enter mode: m -> Adjacency Matrix\t l -> Adjacency List\n";
            cin >> mode;
            generateViaTerminal(mode);
            break;

        case 2:
            cout << "Enter file path\n";
            cin >> _FilePath;
            cout << "Enter mode: m -> Adjacency Matrix\t l -> Adjacency List\n";
            cin >> mode;
            generateViaFile(_FilePath, mode);
            break;

        default:
            cout<< "Invalid Choice\n";
            break;
    }
    return 0;
}