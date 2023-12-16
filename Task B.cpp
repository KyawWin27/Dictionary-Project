/*Kyaw Win
Project task B
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
    
    int getIndex(string word){
        for(int i = 0; i < g_word_count; i++){
            if(g_words[i] == word){
                return i;
                
            }
           
        }
        return -1;
    }
    
    string getDefinition(string word){
        int index;
        index = getIndex(word);
        if(index != -1){
            return g_definitions[index];
        }
            return "NOT_FOUND";
        }
    
    
    string getPOS(string word){
        int dex;
        dex = getIndex(word);
        if(dex != -1){
            return g_pos[dex];
        }
            return "NOT_FOUND"; 
        }
    
    int countPrefix(string prefix){
        int number = 0;
        for(int i = 0; i < g_word_count; i++){
            if(g_words[i].find(prefix) == 0){
                number++;
                
            }
            
        }
        return number;
    }
