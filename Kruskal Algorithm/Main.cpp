#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "AdjacencyMatrix.hpp"
#include "UndirectedGraph.hpp"
#include "DirectedGraph.hpp"
using namespace std;


bool checkIfEdgeExistsInMST(int src, int des, vector<vector<int>> MST){
    for(auto row : MST){
        if((row.at(0) == src && row.at(1) == des) || (row.at(0) == des && row.at(1) == src)){
            return true;
        }
    }
    return false;
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

void generateViaFile(const string file_path, char mode){
    vector<vector<int>> read_input_file;
    fstream input_file;
    input_file.open(file_path, ios :: in);
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
    
    vector<Edge> edges;
    int read_edges_till = no_of_edges;
    for(auto edge_info : read_input_file){
        if(read_edges_till == 0){
            break;
        } else {
            int src = edge_info.at(0);
            int des = edge_info.at(1);
            int wt = edge_info.at(2);
            undirectedGraph.add(src, des, wt);
            edges.push_back(Edge(src, des, wt));
            --read_edges_till;
        }
    }

    read_input_file.erase(read_input_file.begin(), read_input_file.begin() + no_of_edges);

    int no_of_queries = read_input_file.front().at(0);
    read_input_file.erase(read_input_file.begin());

    vector<vector<int>> MST = undirectedGraph.Kruskal(edges, no_of_vertices);

    int answer = 0;
    for(auto query : read_input_file){
        if(checkIfEdgeExistsInMST(query.at(0), query.at(1), MST)){
            answer++;
        }
    }
    cout << answer;
}


void generateViaTerminal(char mode){
    int no_of_vertices, no_of_edges;
    cin >> no_of_vertices >> no_of_edges;

    UndirectedGraph undirectedGraph(no_of_vertices, mode);
    vector<Edge> edges;

    int src, des, wt;
    for(int i =0; i < no_of_edges; i++){
        cin >> src >> des >>wt;
        undirectedGraph.add(src, des, wt);
        edges.push_back(Edge(src, des, wt));
    }

    vector<vector<int>> MST = undirectedGraph.Kruskal(edges, no_of_vertices);
    int no_of_queries;
    cin >> no_of_queries;
    int answer;
    while(no_of_queries--){
        cin >> src >> des;
        if(checkIfEdgeExistsInMST(src, des, MST)){
            answer++;
        }
    }
    cout << answer;
}


int main(){
    string file_path;
    cout << "Select input method...\n";
    int choice;
    cout << "1.Enter Via Console\n2.Enter Via File\n";
    cin >> choice;
    char mode;
    switch(choice){
        case 1:
            cout<< "Enter mode : m -> Adjacency Matirix\t l -> Adjacency List\n";
            cin >> mode;
            generateViaTerminal(mode);
            break;
        case 2:
            cout << "Enter file path\n";
            cin >> file_path;
            cout << "Enter mode : m -> Adjacency Matirix\t l -> Adjacency List\n";
            cin >> mode;
            generateViaFile(file_path, mode);
            break;
        default:
            cout<< "Invalid Choice\n";
    }
    return 0;
}

/*
 * For the current input following is the output. (s)
 *
 * 0 2 1
 * 2 4 2
 * 2 3 3
 * 0 1 7
 *
 * Here, ouput is of the format "src des wt".
 * where, src and des are the vertices of the edge which is included in MST and whose weight is wt.
 */
