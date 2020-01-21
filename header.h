#ifndef _HEADER_H
#define _HEADER_H

#include <string>
struct char_freq {
    char c ;
    int freq ;

    char_freq(char c , int freq):c(c) , freq(freq){};
    char_freq(){} ;
};  

struct node
{
    node *left ;
    node *right ;
    std::string c ;
    int freq ;
    node(std::string data , int freq ):c(data) , freq(freq)
        , left(nullptr) , right(nullptr){};
    node(){} ;
};



#endif