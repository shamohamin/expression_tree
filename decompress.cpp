#include <iostream>
#include <fstream>
#include <ostream>
#include <map>
#include <ctype.h>
#include <vector>
#include <iterator>
#include "chilkat/include/CkCrypt2.h"
#include "chilkat/include/CkGlobal.h"
using namespace std ;

map <string , char> _code_map ;
vector<string> _line_holder;
extern const char * HASHKEY ;
 
void read_file();
void make_map(string , fstream &) ;
void make_decompressed_file(string line , ofstream &file);


void decompressed(){

    CkCrypt2 crypt ;

    crypt.put_CryptAlgorithm("eas") ;
    crypt.put_KeyLength(256);
    crypt.put_PaddingScheme(0);
    crypt.SetEncodedKey(HASHKEY,"hex");

    CkGlobal glob;
    bool success = glob.UnlockBundle("Anything for 30-day trial");
    if (success != true) {
        std::cout << glob.lastErrorText() << "\r\n";
        return;
    }

    int status = glob.get_UnlockStatus();

    char *inFile = "/home/amin/Documents/huffman_tree/compressed.txt.en";
    char *outFile = "/home/amin/Documents/huffman_tree/compressed.txt" ;
    success = crypt.CkDecryptFile(inFile,outFile);
    if(!success)
        cout << crypt.lastErrorText() << endl ;
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
            !isdigit(line.at(0)) ? make_map(line , file) : _line_holder.push_back(line) ;
    else
        throw "file is corrupted" ;
    
    file.close();
}

void make_map(string line , fstream &file){
    char _char ;
    char * code ;
    string code_str = "" ;

    // cout << line <<  "  asdasdasdasdasdsadsadsad  " ;
    // exit(1) ;  
    // for(int i = 2 ; i < line.length() ;i++)
        // code_str += line.at(i) ;
    // crypt.put_CryptAlgorithm("eas") ;
    // crypt.put_KeyLength(256);
    // crypt.put_PaddingScheme(0);
    // crypt.SetEncodedKey(HASHKEY,"hex");
    // crypt.SetEncodedKey(HASHKEY,"hex");
    // crypt.put_HashAlgorithm("sha256");
    // crypt.put_UuMode("666");
    

    _char = line.at(0) ;
    // string l = "";
    // int i = 0 ;
    // while (getline(file , l))
    // {
        // if (i == 3) break ;
        // code_str += l;    
        // i++ ;
    // }
        

    for(int i = 2 ; i < line.length() ; i++)
        code_str += line.at(i) ;
    // cout << code_str << endl;
    // cout << "+++++++++++++++" << endl;
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
