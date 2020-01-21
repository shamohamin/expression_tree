#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include "header.h"
#include <ctype.h>
using namespace std ;


vector<node *> char_holder ;

void reading_from_file() ;
int count(char c,vector<string> &hold_lines);
void char_counter(vector<string> &hold_lines);
bool check_char(char) ;
extern int compress() ;


int main(){
    reading_from_file() ;
    compress() ;
    // for(int i = 0 ; i < char_holder.size() ; i++)
    //     cout << "the char is : " << char_holder.at(i)->c << " the freq is : " << char_holder.at(i)->freq << endl;
    
    return 0;
}

void reading_from_file(){
    string line;
    vector<string> hold_lines ;

    ifstream myfile ("text.txt");

    if (myfile.is_open())
        while ( getline (myfile,line))
            hold_lines.push_back(line) ;
    else
        cout << "Unable to open file"; 

    myfile.close();
    char_counter(hold_lines) ;
}

void char_counter(vector<string> &hold_lines){
    for(int i = 0 ; i < hold_lines.size() ; i++){
        string line = hold_lines.at(i) ;
        for(int j = 0 ; j < line.length() ; j++){
            if(line.at(j) != '_' && check_char(line.at(j))){
                int counter = count(line.at(j) , hold_lines) ;
                string str = "" ;
                str += line.at(j) ;
                node *temp = new node(&str.at(0) , counter) ;
                char_holder.push_back(temp) ;
            }
        } 
    }
}

int count(char c,vector<string> &hold_lines){
    int count = 0 ;

    for(int i = 0 ; i < hold_lines.size() ; i++){
        char *line = &(hold_lines.at(i).at(0)) ;
        for(;*line != '\0' ; line++)
            if(c == *line && *line != '_')
                count++ , *line = '_' ;
    }

    return count ;
}

bool check_char(char c){
    for (int i = 0; i < char_holder.size(); i++)
        if(char_holder.at(i)->c[0] == c)
            return false ;
    return true ;
}