//==========================================
// Created: September 26, 2016 // Joshua Griffiths
// Assighnment 3
// Instructor Boese
// Description: Implementation file of Stack Linked
// list with, push, pop, print and peek functions
// ==========================================

#include "stack_linkedList.hpp"
#include<iostream>
#include <string>
using namespace std ;

TodoStackLinkedList::TodoStackLinkedList(){
    
    stackHead = NULL;//creates head pointer
}

void TodoStackLinkedList::displayMenu() {//displays menu for use in tester function
    cout << "=====Main Menu=====" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Print" << endl;
    cout << "4. Peek" << endl;
    cout << "5. Quit" << endl;
};

void TodoStackLinkedList::printStack(){//prints the list stack
    
    TodoItem * temp = stackHead;//creates a temporary pointer to avoid changing head
    
    if (isEmpty()==true){//makes sure there is somehting in the list
        
        cout<< "The stack is empty" << endl;
    }
    
    else{
        
        while (temp != NULL){//loops through list
            
            cout<< ": " << temp->todo << endl;//prints temp string value
            temp = temp->next;//sets temp to next node in list
        }
    }
}

bool TodoStackLinkedList::isEmpty(){//checks head pointer to see if list is empty
    
    if (stackHead == NULL){//if head pointer is equall to null
        
        return true;
    }
    
    return false;
}

void TodoStackLinkedList::push(string todoItem){//adds node top of stack
    
    TodoItem * temp = new TodoItem;//crates a temporary pointer
    temp->todo = todoItem;//sets the value in temp pointer
    
    if (stackHead == NULL){//if list is empty
        
        temp->todo = todoItem ;//sets the value in teh temp pointer
        temp->next = NULL;//sets the value in the temp pointer next to NULL
        stackHead = temp;//sets head pointer to point at where temp is pointing
    }
    
    else{
        
        temp->todo = todoItem;//sets the value of temp pointer
        temp->next = stackHead;//sets value of temp pointers next to point at where head of list is pointing
        stackHead = temp;//sets head of list to point to new node at top of list
    }
}
void TodoStackLinkedList::pop(){//eliminates node at the top of the list
    
    if (isEmpty() == true){
        
        cout<< "The stack is empty can not pop" << endl;
    }
    
    else{
        
        cout<< "Popping: " << stackHead->todo << endl;
        TodoItem *temp = stackHead;//creates temp pointer and points it at where head is pointing
        stackHead = stackHead->next;// points head at next element in list
        delete temp;//deletes first element in the list
    }
}

TodoItem* TodoStackLinkedList::peek(){//returns value at head of the list
    
    if (isEmpty()==true){
        
        cout<< "The stack is empty can not peek." << endl;
    }
    
    else{
        
        cout<< "Top of stack is: " << stackHead->todo << endl;
    }
    return stackHead;//return head
}
