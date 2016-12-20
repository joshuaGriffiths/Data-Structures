//==========================================
// Created: September 26, 2016 // Joshua Griffiths
// Assighnment 3
// Instructor Boese
// Description: Implementation file of Queue Array
// with, enqueue, dequeue, print and peak functions
// ==========================================

#include "queue_array.hpp"
#include <iostream>
#include <string>
using namespace std;

TodoQueueArray::TodoQueueArray(){
    
    queueFront = 0;//keeps track of front of list
    queueEnd = 0;//keeps track of tail of list
}


void TodoQueueArray::displayMenu(){//void function displays menu to user for use in tester file
    cout << "=====Main Menu=====" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Print" << endl;
    cout << "4. Peek" << endl;
    cout << "5. Quit" << endl;
};

void TodoQueueArray::printQueue(){//function prints out elements in array
    
    if (isEmpty() == true){//checks to see if there is anything in array
        
        cout<< "The queue is empty." <<endl;
    }
    
    else{
        
        for (int i = queueFront; i < queueEnd; i++){//loops through array until end element
            
            if(queue[i]->todo != ""){//if there is something in an array
                
                cout << i << ": " << queue[i]->todo << endl;//prints element in array
            }
            
            else{
                
                cout << i <<": -1" << endl;
            }
        }
    }
    
}

bool TodoQueueArray::isEmpty(){//funcktion checks to see if array is empty
    
    if (queueFront == queueEnd ){//if the head element equall to the tail element
        
        return true;
    }
    
    return false;
}

bool TodoQueueArray::isFull(){//checks to see if array is full
    
    if (queueEnd == 5){//if tail element is greater than five
        
        return true;
    }
    
    return false;
}

void TodoQueueArray::enqueue(string todoItem){//adds element to array
    
    TodoItem * temp = new TodoItem;//creates temp pointer
    temp->todo = todoItem;//sets value to pinter
    if (isFull() == true){
        
        cout<< "The Queue is full, can not enqueue" << endl ;
        return;
    }
    
    else{
        
        if (isEmpty() == true ){//checking if array is empty by postion
            
            queue[queueEnd] = temp;
            queueFront = 0;
            queueEnd = 1;
        }
        
        else{
            
            queue[queueEnd] = temp;
            queueEnd++;
        }
    }
}

TodoItem* TodoQueueArray::peek(){//returns element at the beginning of array
    
    if ((queueFront = NULL)){
        
        cout<< "The queue is empty can not peek." <<endl;
    }
    
    else{
        
        cout << queueFront << endl;
        cout<< queue[queueFront]->todo << endl;
    }
    
    return queue[queueFront];
}


void TodoQueueArray::dequeue(){
    
    if (isEmpty() == true){
        
        cout<< "Queue Empty, can not dequeue. " << endl;
    }
    
    else{
        
        delete queue[queueFront] ;
        cout<< "dequeued: " << queue[queueFront]->todo << endl;
        queueFront++;
        cout<< "Front: " << queueFront << endl;
        cout<< "Back: "<< queueEnd << endl;
    }
}
