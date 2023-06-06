// Purpose: 
// Author: 
// Date of Creation: 
// Bugs:

#ifndef UFDS_
#define UFDS_ 1

namespace cs514 {

#include<vector>

class UFDS {
  // Private attributes and functions for class
  // If you want to add any more variables, please add them
  // and give a valid reason for their use.
  // DO NOT DELETE ANY OF THE MEMBERS FROM BELOW
  // YOU NEED TO USE THEM ALL.

  // node in consideration for union find data structure
  // stores parent and rank for each vertex
  // You may add new members to the node, with explanation as to
  // why the members were necessary.
  class node {
    public:
      int parent;
      int rank;
  };


  public:
    vector<node> vertex;
    // Create an empty union find data structure with N isolated sets.
    UFDS(const unsigned int& N){
      vertex.reserve(N);
    }

    // Default constructor
    ~UFDS(){

    }

    // Make a new set with N vertices with all sets being disjoint
    void make_set (const unsigned int& N){
      for(int i = 0; i < N; i++){
        node new_node = node();
        new_node.rank = i;
        new_node.parent = i;
        vertex.push_back(new_node);
      }
    }

    // Return the representative / parent of set consisting of object x.
    int find_set (const unsigned int& x){
      int representativeSet = vertex.at(x).parent;
      return representativeSet;
    }
    
    // Unite sets containing objects x and y.
    void union_set (const unsigned int& x, const unsigned int& y){
      for(int i = 0; i < vertex.size(); i++){
        if(vertex.at(i).parent == y){
            vertex.at(i).parent = vertex.at(x).parent;
        }
      }
    }
    
    // Are objects x and y in the same set?
    bool is_same_set (const unsigned int& x, const unsigned int& y){
      int representativeX = find_set(x);
      int representativeY = find_set(y);
      return (representativeX == representativeY);
    }

    // Return the number of disjoint sets.
    int num_disjoint_sets(){
      int frequency[vertex.size()];
      for(int i = 0; i < vertex.size(); i++){
          frequency[i] = 0;
      }

      int representativeSet;
      for(int i = 0; i < vertex.size(); i++){
          representativeSet = vertex.at(i).parent;
          frequency[representativeSet]++;
      }

      int countDisjointSet = 0;
      for(int i = 0; i < vertex.size(); i++){
          if(frequency[i] != 0){
              countDisjointSet++;
          }
      }
      return countDisjointSet;
    }
    
    // Return the size of the set containing object x.
    int size_set (const unsigned int& x){
      int setSize = 0;
      int representativeSet = vertex.at(x).parent;
      for(int i = 0; i < vertex.size(); i++){
          if(vertex.at(i).parent == representativeSet){
              setSize++;
          }
      }
      return setSize;
    }
  };    
}

#endif  /* UFDS_ */
