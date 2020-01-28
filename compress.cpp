#include <iostream>
#include <vector>
#include "header.h"
#include <map>
#include <iterator>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <ostream>
using namespace std;

struct char_freq ;
struct node ;
extern vector<node *> char_holder ;
map<string , char *> code_map;
extern string input_file ;

void min_heapify(vector<node *> &arr , int size , int i);
void parrent_heapify(vector<node *> &arr , int size , int i);
void appoint_code(node *& , int [] , int , int &);
void make_compress_file();
void convert_char_to_code(string , ofstream &) ;
bool check_the_chars(char c);


node *compress(int &size_of_all_bits , int &sum_of_compressed_file){    
    
    vector<node *> hold ;
    copy(char_holder.begin() , char_holder.end() , back_inserter(hold)) ;

    for(int i = char_holder.size() / 2 ; i >= 0 ; i--)
        min_heapify(hold , char_holder.size() , i ) ;
    
    while (hold.size() != 1){
        node *left = hold[0] ;
        hold.erase(hold.begin() , hold.begin() + 1) ;
        node *it = hold.back() ; 
        hold.insert(hold.begin() , it) ;
        hold.pop_back() ;
        min_heapify(hold , hold.size() , 0) ;

        node *right = hold[0] ;
        hold.erase(hold.begin() , hold.begin() + 1) ;
        node * it2 = hold.back() ; 
        hold.insert(hold.begin() , it2) ;
        hold.pop_back() ;
        min_heapify(hold , hold.size() , 0);

        string str = "" ;
        str += to_string(left->freq + right->freq) ;
        node *make = new node(&str.at(0) , left->freq + right->freq) ;
        make->left = left , make->right = right;
        hold.push_back(make) ;
        parrent_heapify(hold , hold.size() , hold.size() - 1) ;
        
    }

    node * root = (struct node *)malloc(sizeof(struct node)) ;
    root = hold.front() ;
    int arr[10000] ;
    
    appoint_code(hold.front() , arr , 0 ,  sum_of_compressed_file) ;

    make_compress_file() ;
    size_of_all_bits = root->freq ;

    return root ;
}

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

void appoint_code(node *&root , int arr[] , int index , int &sum_of_compressed_file){
    if(root->left)
        arr[index] = 0 , appoint_code(root->left , arr , index + 1 , sum_of_compressed_file) ;
    if(root->right)
        arr[index] = 1 , appoint_code(root->right , arr , index + 1 , sum_of_compressed_file) ;
    
    
    if(!(root->left) && !(root->right) && check_the_chars(root->c.at(0))){
        string str = "";
        for (int i = 0; i < index; i++)
            str += to_string(arr[i]) ;

        for(int i = 0 ; i < index ;i++)
            root->code[i] = str.at(i) ;

        root->code[index] = '\0';
        root->num = index ;
        int hold = index * root->freq ;
        sum_of_compressed_file += hold ;
    
        code_map.insert(pair<string , char *>(root->c , root->code)) ;
        
    }
    
}

bool check_the_chars(char c){
    string str = "" ;
    str += c ;
    auto itr = code_map.find(str);

    return itr == code_map.end() ? true : false ;

}

void put_header(ofstream &myfile){
    
    map<string , char *>::iterator itr ;
    for(itr = code_map.begin() ; itr != code_map.end() ; itr++)
        myfile << itr->first << " " << itr->second << endl ;
        
}

void make_compress_file(){
    ofstream compress_file("compressed.txt");
    put_header(compress_file) ;
    string line;
    vector<string> hold_lines ;

    ifstream myfile (input_file) ;

    if (myfile.is_open())
        while (getline (myfile,line))
            convert_char_to_code(line , compress_file) ;
    else
        cout << "Unable to open file"; 

    myfile.close();
    compress_file.close() ;    
}

void convert_char_to_code(string line , ofstream &file){
    for(int i = 0 ; i < line.length() ; i++){
        string str = "" ;
        str += line.at(i) ;
        auto itr = code_map.find(str) ;
        file << itr->second << " ";
    }
    file << endl ;
}