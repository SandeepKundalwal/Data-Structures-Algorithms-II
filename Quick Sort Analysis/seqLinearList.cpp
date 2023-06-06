#include "seqLinearList.hpp"


/* Default constructor. 
   Should create an empty list that not contain any elements*/
template<class Item> LinearList<Item> :: LinearList(){
    element = new Item[0];
    MaxSize = 0;
    len = 0;
}

//This constructor should create a list containing MaxSize elements. You can intialize the elements with any values.
template<class Item> LinearList<Item> :: LinearList(const int& MaxListSize){
    element = new Item[MaxListSize];
    MaxSize = MaxListSize;
    len = 0;
}

/* Destructor. 
Must free all the memory contained by the list */
template<class Item> LinearList<Item> :: ~LinearList(){
    delete [] element;
    len = 0;
}

/* Indexing operator.
 * It should behave the same way array indexing does. i.e,
 * LinearList L;
 * L[0] should refer to the first element;
 * L[1] to the second element and so on.
*/
template<class Item> Item& LinearList<Item> :: operator[](const int& i){
    return element[i];
}

/* Returns true if the list is empty, false otherwise.*/
template<class Item> bool LinearList<Item> :: isEmpty(){
    return (len == 0 ? true : false);
}

/* Returns the actual length (number of elements) in the list.*/
template<class Item> int LinearList<Item> :: length(){
    return len;
}

//Returns the maximum size of the list.
template<class Item> int LinearList<Item> :: maxSize(){
    return MaxSize;
}

// Returns the k-th element of the list. 
template<class Item> Item LinearList<Item> :: returnListElement(const int k){
    return this->operator[](k - 1);
}

/* Set x to the k-th element and 
return true if k-th element is present otherwise return false.
*/
template<class Item> bool LinearList<Item> :: find(const int k, const Item& x){
    return (this->operator[](k) == x ? true : false);
}

/* Search for x and 
return the position if found, else return 0.
*/
template<class Item> int LinearList<Item> :: search(const Item& x){
    for(int i = 0; i < len; i++){
        if(this->operator[](i) == x){
            return i + 1;
        }
    }
    return 0;
}

// Set x to the k-th element and delete that k-th element.
template<class Item> void LinearList<Item> :: deleteElement(const int k){
    if(k > len){
        cout<<"k-th element doesn't exist."<<endl;
        return;
    }

    for(int i = (k - 1); i <= (len - 1); i++){
        this->operator[](i) = this->operator[](i + 1);
    }
    len--;
}
    

// Insert x after k-th element.
template<class Item> void LinearList<Item> :: insert(const int k, const Item& x){
    if(len == MaxSize){
        cout<<"Overflow. Cannot insert\n";
        return;
    }

    if(k > len){
        cout<<"Given index is greater than current list length of "<<len<<" cannot insert.\n";
    }

    for(int i = len; i >= k; i--){
        this->operator[](i) = this->operator[](i - 1);
    }
    this->operator[](k) = x;
    len++;
}
