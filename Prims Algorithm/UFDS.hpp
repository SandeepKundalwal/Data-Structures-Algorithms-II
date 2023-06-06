// Purpose: 
// Author: 
// Date of Creation: 
// Bugs:

#ifndef UFDS_
#define UFDS_ 1

#include "seqLinearList.hpp"

namespace cs514 {

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

  LinearList<node> vertex;

  public:
    // Create an empty union find data structure with N isolated sets.
    UFDS(const unsigned int& N);

    // Default constructor
    ~UFDS();

    // Make a new set with N vertices with all sets being disjoint
    void make_set (const unsigned int& N);

    // Return the representative / parent of set consisting of object x.
    int find_set (const unsigned int& x);
    
    // Unite sets containing objects x and y.
    void union_set (const unsigned int& x, const unsigned int& y);
    
    // Are objects x and y in the same set?
    bool is_same_set (const unsigned int& x, const unsigned int& y);

    // Return the number of disjoint sets.
    int num_disjoint_sets();
    
    // Return the size of the set containing object x.
    int size_set (const unsigned int& x); 
  };    
}

#endif  /* UFDS_ */
