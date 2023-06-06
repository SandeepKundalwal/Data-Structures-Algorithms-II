#include <iostream>
#include "seqLinearList.cpp"
#include "sorting.cpp"
using namespace std;

template<class Item> void printList(LinearList<Item>& linearList){
    for(int i = 0; i < linearList.length(); i++){
        cout<<linearList[i]<<" ";
    }

}

template <class Item> void performAction(int choice, LinearList<Item>& linearList, Sort<Item>& sortArray){
    switch(choice){
        case 1 : cout<<"Enter the position and the element you want to enter"<<endl;
        int a, b;
        cin>>a>>b;
        linearList.insert(a, b);
        break;
        case 2 : cout<<"Enter the k-th element you want to delete "<<endl;
        int c;
        cin>>c;
        linearList.deleteElement(c);
        break;
        case 3 : cout<<"Enter the element you want to search "<<endl;
        int d;
        cin>>d;
        cout<<"Element is at position: "<<linearList.search(d)<<endl;
        break;
        case 4 : cout<<"Enter the index and the element you want to find "<<endl;
        int e, f;
        cin>>e>>f;
        if(linearList.find(e,f)){
            cout<<"Element found.\n";
        } else {
            cout<<"Element not found.\n";
        }
        break;
        case 5 : cout<<"Maximum Size of the list is "<<linearList.maxSize()<<endl;
        break;
        case 6 : cout<<"Current Size of the list is "<<linearList.length()<<endl;
        break;
        case 7 : cout<<"Enter the position of the element you want to return ";
        int index;
        cin>>index;
        cout<<linearList.returnListElement(index)<<endl;
        break;
        case 8 :
        if(linearList.isEmpty()){
            cout<<"List is empty.\n";
        } else {
            cout<<"List is not empty.\n";
        }
        break;
        case 9 : sortArray.insertionSort(linearList, 0, linearList.length());
        break;
        case 10 : sortArray.mergeSort(linearList, 0, linearList.length() - 1);
        break;
        case 11 : sortArray.quickSort(linearList, 0, linearList.length() - 1);
        break;
        default : cout<<"Invalid choice.";
        return;
    }
    cout<<"Current List Elements are : "<<endl;
    printList(linearList);
}


int main(){
    int maximumListSize, choice;
    cout<<"Enter Maximum Size of the List "<<endl;
    cin>>maximumListSize;
    LinearList<int> linearList = LinearList<int>(maximumListSize);
    Sort<int> sortArray = Sort<int>();
    do{
        cout<<"\n-----------------------------------------------------\n";
        cout<<"Enter Your Choice : \n";
        cout<<"0.Exit \n";
        cout<<"1.Insert Element after k-th element \n";
        cout<<"2.Delete k-th element \n";
        cout<<"3.Search an element \n";
        cout<<"4.Find an element \n";
        cout<<"5.Maximum Size of the List \n";
        cout<<"6.Current Size of the List \n";
        cout<<"7.Return List Element \n";
        cout<<"8.Is List Empty? \n";
        cout<<"9.Perfom Insertion Sort \n";
        cout<<"10.Perform Merge Sort \n";
        cout<<"11.Perform Quick Sort \n";
        cout<<"----------------------------------------------------\n";

        cin>>choice;
        if(choice == 0){
            return 0;
        }
        performAction(choice, linearList, sortArray);
    } while(true);
    return 0;
}

