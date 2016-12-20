//==========================================
// Created: August 23, 2016 // Joshua Griffiths
// Instructor Boese
// Description: Counts unique words in a file
// outputs the top most common words
// ==========================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "fileManipulation.hpp"

using namespace std;

struct wordItem {// struct to store word + count combinations
    
    string word;//object atribute of type string named word
    int count;//object atribute of type int named count
};

/*
 * Function name: getStopWords
 * Purpose: read stop word list from file and store into vector
 * @param ignoreWordFile - filename (the file storing ignore words)
 * @param _vecIgnoreWords - store ignore words from the file (pass by reference)
 * @return - none
 * Note: The number of words is fixed to 50
 */
void getStopWords(char* ignoreWordFileName, vector<string>& _vecIgnoreWords);

/*
 * Function name: isCommonWord
 * Purpose: to see if a word is a common word
 * @param word - a word (which you want to check if it is a common word)
 * @param _vecIgnoreWords - the vector type of string storing ignore/common words
 * @return - true (if word is a common word), or false (otherwise)
 */
bool isCommonWord(string word, vector<string>& _vecIgnoreWords);

/*
 * Function name: printTopN
 * Purpose: to print the top N high frequency words
 * @param wordItemList - a pointer that points to an array of wordItems
 * @param topN - the number of top frequency words to print
 * @return none
 */
void printTopN(wordItem wordItemList[], int topN);

/*
 * Function name: getTotalNumberNonCommonWords
 * Purpose: to print the total number of non-common words.
 * @param wordItemList - a pointer that points to an array of wordItems
 * @param arraysize
 * @return int
 */
int getTotalNumberNonCommonWords(wordItem wordItemList[], int arraysize);

const int STOPWORD_LIST_SIZE = 50;

int main(int argc, char* argv[]){
    
    vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);//creates vector called vecIgnoreWords
    
    //verify we have the correct # of parameters, else throw error msg & return
    
    if (argc != 4) {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>"; cout << endl;
        return 0;
    }
    
    getStopWords(argv[3], vecIgnoreWords);//call to function getStopWords with third argument from comand line as parameter
    
    wordItem* Uniqueword;//create pointer of type wordItem named Uniqueword
    int capacity = 100;//create variable called capacity set it equall to 100
    Uniqueword = new wordItem[capacity]; //Pointer Uniqueword points to begining of an array of structs with a certain capacity
    ifstream infile;//creates input file stream variable
    int topN = atoi(argv[1]);//converts second argument of type char* to type int
    
    infile.open(argv[2]);//opens second arg from comand line
    
    if (infile.is_open()) {//fucntion checks to see if file opened
        
        int numDoublings = 0; //variable keeps track of how many times array capacity has been doubled
        int numUniqueWords = 0;//variable keeps track of how many unique words there are
        string line; //variable will hold a line of file in the form of a sring
        string word;// variable will hold a word from the file in the form of a string
        int size =0;//variable keeps track of size of the array
        
        while(getline(infile, line)){//while loop uses get line function to input lines from file in to file variable
            
            stringstream ss(line);//creates a stringstream variable to break up the lines by whitespace
            
            while(ss >> word){//while loop to input words from file in to string variable word
                
                if (isCommonWord(word,vecIgnoreWords) == false) {//if statement checks to see if isCommonWord function returns false
                    
                    bool found = false;//creates a bool variable called found and initates that variable to false
                    
                    for(int a = 0; a < size; a++){//for loop iterates over the entire size of the array
                        
                        if ( Uniqueword[a].word == word) {//if statment tests to see if object atribute in array is equall to string from file
                            
                            found = true;//changes bool variable to true
                            Uniqueword[a].count++;//increments object atribute in array by one
                            
                        }
                        
                    }
                    
                    if (found == false){//checks to see if word from file has been seen before if it hasnt:
                        
                        numUniqueWords++;//incrments variable by one
                        Uniqueword[size].count = 1;//sets the count of the struct in the array to one
                        Uniqueword[size].word = word;//coppies word from file in to array of structs
                        size++;//increments the size of the array by one
                        
                        if (size >= capacity) {//checks to see if the size of the array is bigger thatn the capacity
                            
                            wordItem *temp = Uniqueword;//creates a temp pointer to old array memmory location
                            capacity = capacity * 2;//doubles capacity
                            Uniqueword = new wordItem[capacity];//creates new memmory location with double the capacity
                            for(int y=0; y < size;y++){//for loops iterates over the size of the array
                                
                                Uniqueword[y] = temp[y];//coppies over all the structs from the old location into the new location
                            
                            }
                            
                            numDoublings++;//increments the variabel by one
                            delete []temp;//delets structs from old memmory location
                            
                        }
                        
                    }
                    
                }
                
            }
        }
        //SORT DYNAMICALLY ALLOCATED ARRAY BASED ON COUNT OF EACH STRUCT
        sort(Uniqueword, Uniqueword + capacity, [](wordItem const &a, wordItem const &b){ return a.count > b.count; });//sorts Hw1.txt by count
        
        infile.close();//closes file
        
        //OUTPUT
        printTopN(Uniqueword, topN);
        cout <<  "Array doubled: " << numDoublings << endl;
        cout <<  "#"<<endl;
        cout <<  "Unique non-common words: " << numUniqueWords << endl;
        cout <<  "#"<<endl;
        cout << "Total Non Common Words: " << getTotalNumberNonCommonWords(Uniqueword, size) <<endl;
        
    }
    
    else cout << "File not found" << endl << endl;
    
    return 0;
}

void getStopWords(char* ignoreWordFileName, vector<string>& _vecIgnoreWords) {
    
    ifstream filename;//creates input filestream variable
    
    filename.open(ignoreWordFileName);//function opens file
    
    if (filename.is_open()){//checks to see if file is open
        
        string store;//variable to store strings from the file
        
        for (int i=0; i < 50; i++){//for loop iterates 50 times
            
            getline(filename, store);//getline function takes each line from the file and copies it in to string variable store
            
            _vecIgnoreWords.push_back(store);//vector function pushback adds strings to vector _vecIgnoreWords
            
        }
        
        filename.close();//function closes file
    }
    
    else cout << "File not found" << endl << endl;
}

bool isCommonWord(string word, vector<string>& _vecIgnoreWords) {
    
    if(find(_vecIgnoreWords.begin(), _vecIgnoreWords.end(), word) == _vecIgnoreWords.end()){//vector function checks to see if any strings from common words match words from hunger games file
        
        return false;//if no words have been found return false
    }
    
    else return true;//if a word has been found return true
}

void printTopN(wordItem wordItemList[], int topN) {
    
    for(int i = 0; i <= topN; i++){//for loop iterates N times
        cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;//prints out i'th value for each object atribute of the struct in the array
    }
    
    cout <<  "#" << endl;
    
    return;
}

int getTotalNumberNonCommonWords(wordItem wordItemList[], int arraysize){
    
    int count = 0 ;//creates variable called count
    int total = 0;//creates variable called total
    
    for(int i = 0; i < arraysize; i++){//iterates over the size of the array
        count = wordItemList[i].count;//intializes the count variable to the ith value of the object atribute of the struct in the array
        
        total += count;//intializes the total to the previous total plus the count of the new array
    }
    
    return total;//returns total count of all the structs added up 
    
}
