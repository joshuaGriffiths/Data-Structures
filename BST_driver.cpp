//==========================================
// Created by Joshua Griffiths on 10/9/16.
// Instructor Boese
// Description: Driver file for binary search tree
// Copyright © 2016 Joshua Griffiths. All rights reserved.
// ==========================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "binarySearchTree.hpp"

using namespace std;


void handleUserInput(MovieTree *movietree);
void displayMenu();

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage: ";
        cout << argv[0] << "<HW4-Movies.txt>"; cout << endl;
        return 0;
    }
    
    string in_input;
    ifstream infile;
    string in_ranking;
    string in_title;
    string in_year;
    string in_quantity;
    
    
    MovieTree movietree;
    
    infile.open(argv[1]);
    
    if (infile.is_open()){
        while (getline(infile, in_input)){
            
            stringstream ss(in_input);
            
            getline(ss, in_ranking, ',');
            cout << in_ranking << endl;
            
            getline(ss, in_title, ',');
            cout << in_title << endl;
            
            getline(ss, in_year, ',');
            cout << in_year << endl;
            
            getline(ss, in_quantity, ',');
            cout << in_quantity << endl;
            
            int ranking = stoi(in_ranking);
            
            int year = stoi(in_year);
            
            int quantity = stoi(in_quantity);
            
            string title = in_title;
            
            
            movietree.addMovieNode(ranking, title, year, quantity);
        }
        
        handleUserInput(&movietree);
    }
    
    else {
        cout << "did not open" << endl;
    }
}



void handleUserInput(MovieTree *movietree){
    
    bool quit = false;
    string s_input;
    int input;
    
    
    // loop until the user quits
    while (!quit)
    {
        displayMenu();
        
        // read in input, assuming a number comes in
        getline(cin, s_input);
        input = stoi(s_input);
        
        switch (input)
        {
                
            case 1:
            {
                string find_title;
                cout << "Enter name of the Movie you are looking for" << endl;
                getline(cin, find_title);
                movietree->findMovie(find_title);
                
            }
                break;
            case 2:
            {
                string rent_title;
                cout << "Enter name of the movie you want to rent " << endl;
                getline(cin, rent_title);
                movietree->rentMovie(rent_title);
                
            }
                break;
            case 3:
            {
                
                movietree->printMovieInventory();
                
            }
                break;
            case 4:
            {
                string delete_title;
                cout << "Enter name of the Movie you are looking to delete" << endl;
                getline(cin, delete_title);
                movietree->deleteMovieNode(delete_title);
                
                
            }
                break;
            case 5:
            {
                
                int temp = movietree->countMovieNodes();
                cout << "There are " << temp << " movies in invetory" <<endl << endl;
            }
                break;
            case 6:
            {
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                
                
            }
                break;
                
                
            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
    
}



/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Find Movie" << endl;
    cout << "2. Rent Movie" << endl;
    cout << "3. Print Invetory" << endl;
    cout << "4. Delete Movie" << endl;
    cout << "5. Print Invetory Count" <<endl;
    cout << "6. Quit" << endl;
    
}
