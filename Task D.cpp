
/*Kyaw Win
Csci 135
Project task D
Dictionary Admin Operations
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
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
    
    bool addWord(string word, string definition, string pos){
        if(g_word_count >= g_MAX_WORDS || getIndex(word) != -1){
            return false;
        } 
        g_words[g_word_count] = word;
        g_definitions[g_word_count] = definition;
        g_pos[g_word_count] = pos;
        g_word_count++;
        return true;
    }
    
    bool editWord(string word, string definition, string pos){
        int index = getIndex(word);
        if(index == -1){
            return false;
        }
        g_definitions[index] = definition;
        g_pos[index] = pos;
        return true;
    }
    
    bool removeWord(string word){
        if(getIndex(word) == -1){
            return false;
        }
        int index = getIndex(word);
        g_words[index] = g_words[g_word_count-1];
        g_pos[index] = g_pos[g_word_count-1];
        g_definitions[index] = g_definitions[g_word_count-1];
        g_words[g_word_count-1] = "";
        g_pos[g_word_count-1] = "";
        g_definitions[g_word_count-1] = "";
        g_word_count--;
        
        return true;
    }
    
    string getRandomWord() {
        srand((unsigned) time(NULL));
        int index = rand() % g_word_count;
        return g_words[index];
    }
    
    string maskWord(string word){
        string hidden_word = "";
        for(int i = 0; i < word.length(); i++){
            hidden_word += "_";
            
        }
        return hidden_word;
      
    }
    
    int getTries(int difficulty){
        int tries; 
        if(difficulty == 0){
            tries = 9;
            
        }
        else if(difficulty == 1){
            tries = 7;
        }
        else{
            tries = 5;
        }
    return tries;
    }
    
    void printAttempts(int tries, int difficulty){
        int attempts = getTries(difficulty);
        for(int i = 0; i < attempts; i++){
            if(i < tries){
                cout<< "O";
            }
            else{
                cout<<"X";
            }
        }
    }
    
    bool revealLetter(string word, char letter, string &current){
        bool exist = false;
        for(int i = 0; i < word.length(); i++){
            if(word[i] == letter){
                exist = true;
                current[i] = letter; 
            }
        }
        
    return exist;
    }
    
    // game-loop for Hangman
void gameLoop() {
    int difficulty, tries;
    string word, current;
    char letter;
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout <<  "0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
        cin >> difficulty;
        while (difficulty < 0 || difficulty > 3) {
            cout <<  "Enough horseplay >_< !\n0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
            cin >> difficulty;
        }
        if (difficulty == 3) {
            cout << "If you're hangry, go grab a bite! See what I did there?" << endl;
            break;
        }
        word = getRandomWord();
        current = maskWord(word);
        tries = getTries(difficulty);
        while (tries != 0) {
            cout << "Life: ";
            printAttempts(tries, difficulty);
            cout << endl << "Word: "<< current << endl;
            cout << "Enter a letter: ";
            cin >> letter;
            
            if (!revealLetter(word, letter, current)) {
                tries--;
            }
            if (current == word) {
                break;
            }
            if (tries == 2) {
                cout << "The part of speech of the word is "<< getPOS(word) << endl;
            }
            if (tries == 1) {
                cout << "Definition of the word: " << getDefinition(word) << endl;
            }
        }
        if (tries == 0) {
            cout << "The word is \"" << word << "\". Better luck next time! You're getting the ..ahem.. hang of it." << endl;
        }
        else {
            cout << "Congrats!!!" << endl;
        }
    }
}
