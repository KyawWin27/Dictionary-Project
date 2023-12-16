/*Kyaw Win
Csci 135
Project 1 task A
Dictionary Using Arrays
*/

#include <iostream>
#include <fstream>
using namespace std;
    
const int g_MAX_WORDS = 1000;
int g_word_count = 0;
    
    string g_words[g_MAX_WORDS];
    string g_definitions[g_MAX_WORDS];
    string g_pos[g_MAX_WORDS];
    
    void readWords(string filename){
        ifstream fin(filename);
        if(fin.fail()){
            cerr<<"File cannot be opened for reading."<<endl;
            exit(1);
        } 
        
        string words, pos, colon, definitions; 
        while(fin >> words >> pos >> colon){
            getline(fin, definitions);
            g_words[g_word_count] = words;
            g_pos[g_word_count] = pos;
            g_definitions[g_word_count] = definitions.substr(1);
            g_word_count++;
        } 
    }