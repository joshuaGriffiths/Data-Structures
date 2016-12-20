//==========================================
// Created: September 26, 2016 // Joshua Griffiths
// Assighnment 3
// Instructor Boese
// Description: Implementation file of Stack Array
// with, push, pop, print and peek functions
// ==========================================

#include "stack_array.hpp"
#include <iostream>
#include <string>
using namespace std ;

TodoStackArray::TodoStackArray(){
    
    stackTop = -1 ;
}

void TodoStackArray::displayMenu(){
    
    cout << "=====Main Menu=====" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Print" << endl;
    cout << "4. Peek" << endl;
    cout << "5. Quit" << endl;
}

void TodoStackArray::printStack(){
    
    if (isEmpty() == true){
        
        cout<< "The stack is empty." << endl ;
    }
    
    else{
        
        for (int i = 0; i < stackTop; i++){
            
            if(stack[i]->todo != ""){
                
                cout << i << ": " << stack[i]->todo << endl;
            }
            
            else{
                
                cout << i <<": -1" << endl;
            }
        }
    }
}

bool TodoStackArray::isEmpty(){
    
    if (stackTop == -1){
        
        return true ;
    }
    
    return false ;
}

bool TodoStackArray::isFull(){
    
    if (stackTop >= 5){
        
        return true ;
    }
    
    return false ;
}

void TodoStackArray::push(string todoItem){
    
    if (isFull()==true){
        
        cout<< "The stack is full" << endl ;
    }
    
    else{
        
        TodoItem * temp = new TodoItem ;
        temp->todo = todoItem ;
        stackTop++ ;
        stack[stackTop] = temp ;
    }
}

void TodoStackArray::pop(){
    
    if (stackTop == 0){
        
        cout<< "The stack is empty cannot pop" <<endl <<endl;
    }
    
    else{
        
        stackTop-- ;
        cout<< "popping: " << stack[stackTop]->todo << endl ;
        delete stack[stackTop] ;
    }
}

TodoItem* TodoStackArray::peek(){
    
    if (isEmpty() == true){
        
        cout<< "The stack is empty, cannot peek. " << endl ;
        return stack[stackTop];
    }
    
    else{
        
        cout<< stack[stackTop]->todo << endl ;
        return stack[stackTop] ;
    }
}
