//==========================================
// Created by Joshua Griffiths on 11/1/16.
// Instructor Boese
// Description: Implementation file for a priority queue
//              implemented in a heap
// Copyright © 2016 Joshua Griffiths. All rights reserved.
// ==========================================

#include "priorityQueue_heapArray.hpp"
#include <iostream>

using namespace std;

PatientQueue::PatientQueue(){
    
    lastIndex = 0;
    
}

bool PatientQueue::isEmpty(){
    
    if(lastIndex == 0)
        return true;
    
    else return false;
    
}

void PatientQueue::enqueue(int priority,std::string name){
    
    Patient * newPatient = new Patient(priority, name);
    
    if (isEmpty() == true){
        
        int hole = ++lastIndex;
        waitlist[hole] = newPatient;
        cout << "Adding "<< priority << " " << name << endl <<  "===" << endl;
        printList();
        return;
    }
    
    lastIndex++;
    
    Patient * parent = waitlist[lastIndex/2];
    
    waitlist[lastIndex]= newPatient;
    
    if ( waitlist[lastIndex] -> priority < parent->priority){
        
        swap(lastIndex, lastIndex/2);
    }
    
    cout << "===" << endl << "Adding "<< priority << " " << name << endl << "===";
    printList();
}

void PatientQueue::swap(int index1, int index2){
    
    Patient * temp = waitlist[index1];
    
    waitlist[index1]= waitlist[index2];
    
    waitlist[index2] = temp;
    
    
}

int PatientQueue::size(){
    
    return lastIndex;
}

void PatientQueue::printList(){
    
    
    cout << " Patients Waiting " <<endl;
    
    if (isEmpty()==true){
        
        cout << " No One Waiting "<< endl << "===" << endl;
        
    }
    
    else{
        
        for(int i = 1; i <= lastIndex; i++){
            
            cout <<"[" << waitlist[i]->priority << "] " << waitlist[i]->name  << endl;
        }
    }
}

Patient* PatientQueue::dequeue(){
    
    Patient * del = waitlist[1];
    cout << " Processing " << waitlist[1]->priority << " " << waitlist[1]->name << endl;
    
    if(lastIndex == 1){
        
        waitlist[1] = NULL;
        lastIndex--;
        
    }
    
    else if(isEmpty()==true) return NULL;
    
    else{
        
        
        waitlist[1]=waitlist[lastIndex];
        waitlist[lastIndex]= NULL;
        lastIndex--;
        
        if(waitlist[1]->priority < waitlist[2]->priority){
            
            swap(1,2);
            
        }
        
        else if (waitlist[1]->priority < waitlist[3]->priority){
            
            swap(1, 3);
            
        }
    }
    
    return del;
}

PatientQueue::~PatientQueue(){
    
    cout << "===" << endl << "We're CLOSING! Deleting Patient Queue!" << endl;
    
    for (int i = 1; i < lastIndex; i++){
        
        cout << "Removing " << waitlist[i]->name << " from queue." << endl;
        
    }
    
    delete[] *waitlist;
}
