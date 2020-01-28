#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "header.h"
#include <ctype.h>
using namespace std ;


vector<node *> char_holder ;
string input_file ;

void reading_from_file();
int count(char c,vector<string> &hold_lines);
void char_counter(vector<string> &hold_lines);
bool check_char(char) ;
extern node * compress(int & , int &) ;
void display();
extern void display_tree(node *root , float x , float y ,float vgap , float hgap);
node *root ;
extern void decompressed() ;


void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f) ; }

int main(int argc , char *argv[]){

    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    // glutInitWindowSize(2000,2000);
    // glutCreateWindow("Huffman Tree");

    char *hold = &argv[1][0] ;
    for(;*hold != '\0';hold++)
        input_file += *hold ;

    input_file += ".txt" ;

    reading_from_file() ;
    int size_of_total = 0 ;
    int size_of_compressed_file = 0 ;
    ::root = compress(size_of_total , size_of_compressed_file) ;
    size_of_total *= 8 ;
    cout << size_of_total << " size of all the bits" << endl ;
    cout << size_of_compressed_file << " size of comprssed FILE" << endl ;
    
    double precent = (double)size_of_compressed_file / (double)size_of_total ;
    cout << "precent is : " << precent << endl ;

    try{
        decompressed() ;
    }catch(const char *e){
        cout << e ;
    }
        


    // setup();
    // glutDisplayFunc(display);
    // glutMainLoop();
    return 0;
}

void reading_from_file(){
    string line;
    vector<string> hold_lines ;
    
    ifstream myfile (input_file) ;

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
            if(check_char(line.at(j))){
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
            if(c == *line)
                count++ ;
    }

    return count ;
}

bool check_char(char c){
    for (int i = 0; i < char_holder.size(); i++)
        if(char_holder.at(i)->c[0] == c)
            return false ;
    return true ;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);

    // display_tree(::root , 0.05 ,0.9 , 0.4 , 0.4) ;

    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}
