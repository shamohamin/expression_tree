#include <iostream>
#include <vector>
#include "header.h"
using namespace std;

struct char_freq ;
struct node ;
extern vector<node *> char_holder ;

void sort(vector<node> &hold);
void min_heapify(vector<node *> &arr , int size , int i);
void parrent_heapify(vector<node *> &arr , int size , int i);
void pre_order(node *) ;

int compress(){    
    
    vector<node *> hold ;

    copy(char_holder.begin() , char_holder.end() , back_inserter(hold)) ;
    // for(int i = 0 ; i < char_holder.size() ; i++)
        // cout << "adadadh", hold[i] = (struct node *)malloc(sizeof(struct node)) , hold[i] = char_holder[i] ;
    int size = char_holder.size() ;
    for(int i = char_holder.size() / 2 ; i >= 0 ; i--)
        min_heapify(hold , size , i ) ;
     
    for(int i = 0 ; i < char_holder.size() ; i++)
        cout << "the char is : " << hold[i]->c << " the freq is : " << hold[i]->freq << endl;
    cout << "*****************************************" << endl ;
    while (hold.size() != 2){
        node *left = hold[0] ;
        hold.erase(hold.begin() , hold.begin() + 1) ;
        node *it = hold.back() ; 
        hold.insert(hold.begin() , it) ;
        hold.pop_back() ;
        min_heapify(hold , size , 0) ;
        // for(int i = 0 ; i < hold.size() ; i++)
        // cout << "the char is : " << hold[i]->c << " the freq is : " << hold[i]->freq << endl;
        // exit(1); 
        node *right = hold[0] ;
        hold.erase(hold.begin() , hold.begin() + 1) ;
        it = hold.back() ; 
        hold.insert(hold.begin() , it) ;
        hold.pop_back() ;
        min_heapify(hold , size , 0);

        string str = "" ;
        str += to_string(left->freq + right->freq) ;
        node *make = new node(&str.at(0) , left->freq + right->freq) ;
        make->left = left , make->right = right;
        hold.push_back(make) ;
        parrent_heapify(hold , hold.size() , hold.size() - 1) ;
        for(int i = 0 ; i < hold.size() ; i++)
            cout << "the char is : " << hold[i]->c << " the freq is : " << hold[i]->freq << endl;
        cout << "*****************************************" << endl ;
        // exit(1); 
    }
    
    for(int i = 0 ; i < hold.size() ; i++)
        cout << "the char is : " << hold[i]->c << " the freq is : " << hold[i]->freq << endl;
    node *right = hold.back() ;
    node *left = hold.front() ;
    hold.clear() ;
    string str = "" ;
    str += to_string(left->freq + right->freq) ;
    node *make = new node(&str.at(0) , left->freq + right->freq) ;
    make->left = left , make->right = right ;
    pre_order(make) ;


    return 2 ;
}

void pre_order(node *root){
    if(root != nullptr)
        cout << root->c << "......" , pre_order(root->left) , pre_order(root->right) ;
}

// void sort(vector<char_freq> &hold){
//     for(int i = 0 ; i < hold.size() ; i++)
//         for(int j = 0 ; j < hold.size() - 1; j++)
//             if(hold.at(j).freq < hold.at(j+1).freq)
//                 swap(hold.at(j) , hold.at(j+1)) ;
// }


void min_heapify(vector<node *> &arr , int size , int i){
    int left = 2 * i + 1 ;
    int right = 2 * i + 2; 
    int min = i ;


    if(left < size && arr[left]->freq < arr[min]->freq) min = left ; 
    if(right < size && arr[right]->freq < arr[min]->freq) min = right ;

    if(min != i)
        swap(arr[i] , arr[min]) , min_heapify(arr , size , i) ;

}

void parrent_heapify(vector<node *> &arr , int size , int i){
    int parrent = ( i - 1 ) / 2 ;

    if(parrent > 0 && arr[i] < arr[parrent]) 
        swap(arr[parrent] , arr[i]) , parrent_heapify(arr , size , parrent) ;
}