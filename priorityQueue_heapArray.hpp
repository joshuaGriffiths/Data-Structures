//==========================================
// Created by Joshua Griffiths on 11/1/16.
// Instructor Boese
// Description: Header file for a priority queue
//              implemented in a heap
// Copyright © 2016 Joshua Griffiths. All rights reserved.
// ==========================================


#ifndef PatientQueue_hpp
#define PatientQueue_hpp

#include <stdio.h>
#include <string>

using namespace std;

struct Patient
{
    int priority;
    std::string name;
    Patient(int _priority, std::string _name)
    {
        priority = _priority;
        name = _name;
    }
};

class PatientQueue
{
public:
   	PatientQueue();
    ~PatientQueue();	// release memory and delete queue
    int size();
    bool isEmpty();
    void enqueue(int priority, std::string name);
    Patient* dequeue();		// returns pointer to patient record and removes from array
    void printList();					// print the array
private:
    void swap(int index1, int index2);	// swap the contents in the array
    Patient *waitlist[100];
    int lastIndex;
};

#endif /* PatientQueue_hpp */
