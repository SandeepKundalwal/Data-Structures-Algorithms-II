#include "sorting.hpp"

template<class Item> void Sort<Item> :: insertionSort(LinearList<Item>& A, int low, int high){
    //to handle empty array
    if(A.length() == 0){
        return;
    }
    /* Move elements of arr[0..i-1],  
    that are greater than key, to one 
    position ahead of their 
    current position */
    for(int i = low; i < high; i++){
        int j = i;
        while((j - 1) >= 0 && A.operator[](j) < A.operator[](j - 1)){
            int temp = A.operator[](j - 1);
            A.operator[](j - 1) = A.operator[](j);
            A.operator[](j) = temp;
            j--;
        }
    }
}

template<class Item> void Sort<Item> :: mergeSort(LinearList<Item>& A, int low, int high){
    if(low < high){
        int midElement = low + (high - low)/2;  //find the middle element of the array, so that we can divide the array into two parts

        /*recursively divide untill only a single element remmains as a single element is already sorted */
        mergeSort(A, low, midElement);
        mergeSort(A, midElement + 1, high);
        //merge the arrays
        mergeArrays(A, low, midElement, high);
    }
}

template<class Item> void mergeArrays(LinearList<Item>& A, int low, int mid, int high){
    int m = mid - low + 1;
    int n = high - mid;

    //creating temporary subarrays
    LinearList<Item> leftSubArray = LinearList<Item>(m);
    LinearList<Item> rightSubArray = LinearList<Item>(n);

    //initializing left subarray
    for(int i = 0; i < m; i++){
        leftSubArray.operator[](i) = A.operator[](low + i);
    }
    //initializing right subarray
    for(int j = 0; j < n; j++){
        rightSubArray.operator[](j) = A.operator[](mid + 1 + j);
    }

    auto indexOfLeftSubArray = 0, indexOfRightSubArray = 0;
    int indexOfMergedArray = low;

    //placing the elements into the final array
    while(indexOfLeftSubArray < m && indexOfRightSubArray < n){
        if(leftSubArray.operator[](indexOfLeftSubArray) <= rightSubArray.operator[](indexOfRightSubArray)){
            A.operator[](indexOfMergedArray) = leftSubArray.operator[](indexOfLeftSubArray++);
        } else {
            A.operator[](indexOfMergedArray) = rightSubArray.operator[](indexOfRightSubArray++);
        }
        indexOfMergedArray++;
    }

    //in case if the right subarray is empty and there are elements remaining in left subarray
    while(indexOfLeftSubArray < m){
        A.operator[](indexOfMergedArray++) = leftSubArray.operator[](indexOfLeftSubArray++);
    }

    //in case if the left subarray is empty and there are elements remaining in right subarray
    while(indexOfRightSubArray < n){
        A.operator[](indexOfMergedArray++) = rightSubArray.operator[](indexOfRightSubArray++);
    }

    //free up memory of the temporaray arrays
    leftSubArray.~LinearList();
    rightSubArray.~LinearList();

}

template<class Item> void Sort<Item> :: quickSort(LinearList<Item>& A, int low, int high){
    if(low < high){
        int pivot = partition(A, low, high); //finding the pivot index of the array
        //recursively sorting the left part of the array 
        quickSort(A, low, pivot - 1);
        //recursivley sorting the right part of the array
        quickSort(A, pivot + 1, high);
    }
}

template<class Item> int partition(LinearList<Item>& A, int low, int high){
    int pivot = A.operator[](low); //pivot element

    //finding the correct position of the pivot element
    int count = 0;
    for(int i = low + 1; i <= high; i++){
        if(A.operator[](i) <= pivot){
            count++;
        }
    }
    //placing the pivot element at its correct index
    int pivotIndex = low + count;
    swapElements(A, pivotIndex, low);

    int i = low, j = high;
    
    //sorting right and left part of the pivot element
    while(i < pivotIndex && j > pivotIndex){
        //left side of the pivot element should contain elements that are less than or equals to pivot element
        while(A.operator[](i) <= pivot){
            i++;
        }
        //right side of the pivot element should contain elements that are greater than pivot element
        while(A.operator[](j) > pivot){
            j--;
        }

        if(i < pivotIndex && j > pivotIndex){
            swapElements(A, i++, j--);
        }
    }
    return pivotIndex;
}

template<class Item> void swapElements(LinearList<Item>& A, int m, int n){
    Item temp = A.operator[](m);
    A.operator[](m) = A.operator[](n);
    A.operator[](n) = temp;
}