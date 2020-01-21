#include <iostream>
#include <fstream>
#include <ostream>
#include <map>
#include <ctype.h>
#include <vector>
#include <iterator>
using namespace std ;

map <char , string> _code_map ;
vector<string> _line_holder;

void read_file();
void make_map(string) ;


void decompressed(){

    try{
        read_file();
    }catch(const char *e){
        cout << e ;
    }
    

    map<char , string >::iterator itr ;
    for(itr = _code_map.begin() ; itr != _code_map.end() ; itr++)
        cout << itr->first << "  code is : " << itr->second << endl ;
    

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
    
    _code_map.insert(pair<char , string>(_char , code_str)) ;
            
}

void make_decompressed_file(){
    
}
