#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include "seqLinearList.cpp"
#include "sorting.cpp"
using namespace std;


LinearList<int> getInput(string directory, string name, int i, string order){
    LinearList<int> linearList = LinearList<int>(stoi(name));
    string path = directory + to_string(i + 1) + order + name + ".txt";
    fstream newFile;
    int j=0;
    newFile.open(path, ios :: in);
    if(newFile.is_open()){
        string element;
        while(getline(newFile, element)){
            linearList.insert(j, stoi(element));
            j++;
        }
        newFile.close();
    }
    return linearList;
}
int main(){     
    int choice;
    Sort<int> sortArray = Sort<int>();
    int files[] = {500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000,5000000};
    string finalPath;
    cout<<"=====================================================\n \t\t\t MENU \n";
    cout<<"===================================================== \n";
    cout<<"1. Sort Ascending Order Data Using Quick Sort\n";
    cout<<"2. Sort Ascending Order Data Using Randomized Quick Sort\n";
    cout<<"3. Sort Descending Order Data Using Quick Sort\n";
    cout<<"4. Sort Descending Order Data Using Randomized Quick Sort\n";
    cout<<"5. Sort Unsorted Data Using Quick Sort\n";
    cout<<"6. Sort Unsorted Order Data Using Randomized Quick Sort\n";
    cout<<"7. Exit\n";
    cin>>choice;
    switch(choice){
        case 1 : 
                finalPath = "Data\\Data_in_AscendingOrder\\";
                for(int i = 0; i < 9; i++){
                    string order = "acendingData";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.quickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 2: 
                finalPath = "Data\\Data_in_AscendingOrder\\";
                for(int i = 0; i < 9; i++){
                    int index = 0;
                    string order = "acendingData";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.randomizedQuickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 3: 
                finalPath = "Data\\Data_in_DecendingOrder\\";
                for(int i = 0; i < 9; i++){
                    int index = 0;
                    string order = "descendingData";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.quickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 4: 
                finalPath = "Data\\Data_in_DecendingOrder\\";
                for(int i = 0; i < 9; i++){
                    int index = 0;
                    string order = "descendingData";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.randomizedQuickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 5: 
                finalPath = "Data\\UnsortedData\\";
                for(int i = 0; i < 9; i++){
                    int index = 0;
                    string order = "data";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.quickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 6: 
                finalPath = "Data\\UnsortedData\\";
                for(int i = 0; i < 9; i++){
                    int index = 0;
                    string order = "data";
                    LinearList<int> linearList = getInput(finalPath, to_string(files[i]), i, order);   
                    auto start = std :: chrono :: high_resolution_clock :: now();
                    sortArray.quickSort(linearList, 0, linearList.length() - 1);
                    auto finish = std :: chrono :: high_resolution_clock :: now();
                    auto nanoseconds = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(finish - start);
                    cout<<"For "<<files[i]<<" elements\tComputation Time : "<<nanoseconds.count()<<" ns"<<endl;
                }
                break;
        case 7 : 
                break;
        default: 
                cout<<"Invalid choice. Exiting..";
                break;
    }
    return 0;
}
