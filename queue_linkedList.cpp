//==========================================
// Created: September 26, 2016 // Joshua Griffiths
// Assighnment 3
// Instructor Boese
// Description: Implementation file of Queue Linked
// list, enqueue, dequeue, print and peak
// ==========================================

#include "queue_linkedList.hpp"
#include <string>
#include <iostream>
using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList(){
    
    queueFront = NULL;//initializes pointer of front of list to NULL
    queueEnd = NULL;//initializes pointer of end of list to NULL
}

void TodoQueueLinkedList::displayMenu()//void function displays menu to user for use in tester file
{
    cout << "=====Main Menu=====" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Print queue" << endl;
    cout<< "4. Peek" << endl;
    cout<< "5. Quit" << endl;
};

void TodoQueueLinkedList::printQueue(){//function prints out elements in list
    
    TodoItem *temp = queueFront;//create a temporary pointer pointing to front of list to avoid perminatly changing queueFront
    
    if (isEmpty() == true){//checks to see if there is anything in list
        
        cout<< "Queue is empty." << endl;
    }
    
    else{
        
        while (temp != NULL){//loops through list
            
            cout<< ": " << temp->todo << endl;//prints each todo string in list
            temp = temp->next;//changes to next node in list
        }
    }
}

bool TodoQueueLinkedList::isEmpty(){//funcktion checks to see if list is linked list is empty
    
    if (queueFront == NULL){//if the front of the list doesnt have anything in it
        
        return true;
    }
    
    else{
        
        return false;
    }
}
void TodoQueueLinkedList::enqueue(string todoItem){//function adds elements to end of list
    
    TodoItem *temp = new TodoItem; //creates temporary pointer
    temp->todo = todoItem; //sets value for temporary pointer
    temp->next = NULL;//intializes next pointer in node to NULL (importiant for looping)
    
    if (isEmpty()==true){//checks to see if list is empty
        
        queueFront = temp;//sets pointer to front of list to new pointer with elements
    }
    
    else{
        
        queueEnd->next = temp;//inserts temp in to to end of list
    }
    
    queueEnd = temp;//sets pointer to end of list in to new end to the list
    
}
void TodoQueueLinkedList::dequeue(){//function deletes items from front of list and moves queueFront to next position
    
    if (isEmpty()==true){//checks to see if list is empty
        
        cout<< "Queue is empty, can not dequeue item" << endl;
    }
    
    else{
        
        cout<< "Dequeued: " << queueFront->todo <<endl;//prints old front pointer to list
        TodoItem *temp = queueFront;//sets new pointer to old front pontier loation
        queueFront = queueFront->next;//sets front pointer to new head of the list
        delete temp;//deletes old head pointer
    }
}

TodoItem* TodoQueueLinkedList::peek(){//returns head of list
    
    if (isEmpty() == true){//checks to see if list is empty and returns NULL if true
        
        cout<< "The queue is empty, can not peek item." << endl;
        return NULL;
    }
    
    else{
        
        cout<< queueFront->todo << endl;//prints head pointer value
        return queueFront;//returns head pointer
    }
}
