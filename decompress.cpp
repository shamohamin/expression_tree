#include <iostream>
#include <fstream>
#include <ostream>
#include <map>
#include <ctype.h>
#include <vector>
#include <iterator>
using namespace std ;

map <string , char> _code_map ;
vector<string> _line_holder;

void read_file();
void make_map(string) ;
void make_decompressed_file(string line , ofstream &file);


void decompressed(){

    try{
        read_file();
    }catch(const char *e){
        cout << e ;
    }
        
    ofstream file ("decompressed.txt") ;
    if(file.is_open())
        for(int i = 0 ; i < _line_holder.size() ; i++)
            make_decompressed_file(_line_holder.at(i) , file) , file << endl ;
    else
        throw "file is crrupted !!!!!!!!!!!!!!!!";

    file.close();

}

void read_file(){
    fstream file("compressed.txt");
    string line;

    if(file.is_open())
        while (getline(file , line))
            !isdigit(line.at(0)) ? make_map(line) : _line_holder.push_back(line) ;

    else
        throw "file is corrupted" ;
    

    file.close();
}

void make_map(string line){
    char _char ;
    char * code ;
    string code_str = "" ;

    _char = line.at(0) ;
    for(int i = 2 ; i < line.length() ; i++)
        code_str += line.at(i) ;
    
    _code_map.insert(pair<string , char>(code_str , _char)) ;
            
}

void make_decompressed_file(string line , ofstream &file){
    int pos = 0;
    string str = "" ;
    auto itr = _code_map.find("");
 
    for(int i = 0 ; i < line.length() ; i++)
        if(line.at(i) == ' '){
            str = "" ;
            for(int k = pos ; k < i ; k++)
                str += line.at(k) ;
            itr = _code_map.find(str) , file << itr->second , pos = i + 1;
        }
}
