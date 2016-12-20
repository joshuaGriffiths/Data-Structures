
//==========================================
// Created by Joshua Griffiths on 10/9/16.
// Instructor Boese
// Description: Implementation file for binary search tree
// Copyright © 2016 Joshua Griffiths. All rights reserved.
// ==========================================

#include "binarySearchTree.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

MovieTree::MovieTree(){//constructor intializes root private variable to NULL
    
    root = NULL;
}

//******************************************
// Private member function of MovieTree class
// Param: string of title you are searching
// Return: Pointer to movie node
//==========================================

MovieNode* MovieTree::search(std::string title){
    
    if(root->title == title){//if title you are searching for is the root of the tree
        
        return root;
    }
    
    MovieNode * temp = root;//creates a temporary node that has all the data of root
    
    while(temp !=NULL){
        
        if(temp->title.compare(title)<0){//if temp title comes before searching title alphabetically
            
            temp = temp->rightChild;//goes to next node in the tree on the right side
        }
        
        else if (temp->title == title){//if temp title is equall to searching title
            
            return temp;//exits function, returns pointer to movie node you are searching
            
        }
        
        else if(temp->title.compare(title)>0){//if temp title comes after searching title alphabetically
            
            temp = temp->leftChild;//goes to next node in the tree on the left side
            
        }
        
        else {//logic check
            
            cout << " Logic Error, Shouldnt ever happen";
            exit(1);
        }
    }
    
    return temp;//NULL if movie title isnt found
}



//******************************************
// Public accesor function of MovieTree class
// Calls Private member function:
// printMovieInvetory
//==========================================

void MovieTree::printMovieInventory(){//
    
    printMovieInventory(root);
}



//******************************************
// Private member function of MovieTree class
// Param: MovieNode pointer (root)
// Prints Tree in order alphabetically
//==========================================

void MovieTree::printMovieInventory(MovieNode * node){
    
    if (root == NULL) {//if tree is empty
        
        cout << "Tree is Empty" << endl;
        return;//exit function
    }
    else if(node != NULL){
        printMovieInventory(node->leftChild);//calls function again (with left node)
        
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Year:" << node->year << endl;
        cout << "Quantity:" << node->quantity << endl;
        
        printMovieInventory(node->rightChild); // calls function again with right node
    }
}



//******************************************
// Public member function of MovieTree class
// Param: string from user input
// Displays movie information for specific movie
//==========================================

void MovieTree::findMovie(std::string title){
    
    MovieNode * temp = search(title);//assighns a temp variable with the node of movie user is searching
    
    if(temp == NULL){
        
        cout << " Movie Not Found" << endl;
        
    }
    
    else if (temp->title == title){//prints found movie information
        
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << temp->ranking << endl;
        cout << "Title:" << temp->title << endl;
        cout << "Year:" << temp->year << endl;
        cout << "Quantity:" << temp->quantity << endl;
        
    }
    
    else cout << "Movie Not Found" << endl;
    
}



//******************************************
// Public member function of MovieTree class
// Param: string from user input
// Displays movie information for specific movie
// and adjust quantity of movie rented
//==========================================

void MovieTree::rentMovie(std::string title){
    
    MovieNode * temp = search(title);//assighns a temp variable with the node of movie user is searching
    
    if(temp == NULL){
        
        cout << " Movie Not Found" << endl << endl;
        
    }
    
    else if (temp->title == title){//prints found movie information
        
        temp->quantity--;//adjust quantity of movie by -1
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << temp->ranking << endl;
        cout << "Title:" << temp->title << endl;
        cout << "Year:" << temp->year << endl;
        if( temp->quantity < 0){//if quantity is -1 or less
            
            cout << "Movie Out Of Stock" << endl;
            deleteMovieNode(title);//deletes movie from invetory
        }
        
        else cout << "Updated Quantity:" << temp->quantity << endl;
    }
    
    else cout<< " Movie Not Found" << endl << endl;
}



//******************************************
// Public member function of MovieTree class
// Param: ranking , title, release year, quantitiy
// Adds movie node in to tree alphabetically
//==========================================

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    
    MovieNode * temp = root;//creates a temporary node that has all the data of root of tree
    MovieNode * temp2 = NULL;//nessecary for loops
    
    if (temp == NULL){//if tree is empty
        
        //CREATES A ROOT
        root = new MovieNode;
        root->ranking = ranking;
        root->title = title;
        root->year = releaseYear;
        root->quantity = quantity;
        root->leftChild = NULL;
        root->rightChild = NULL;
        root->parent = NULL;
        return;
    }
    
    while(temp!= NULL){//loops through the tree (either left or right side)
        
        if(temp->title.compare(title)<0){
            temp2 = temp;//keeps track of the node right before the end of the tree(NULL)
            temp = temp->rightChild; //runs you to the last node in the right branches
            
        }
        else{
            temp2 = temp;//keeps track of the node right before the end of the tree(NULL)
            temp = temp->leftChild;//runs you to the last node in the right branches
        }
    }
    
    if (temp == NULL && temp2->title.compare(title)<0){//adds node to the right side of the last node in the tree (on the right side or left side depending on previous while loop)
        
        //Add Node to right of last node in the tree
        temp = new MovieNode;
        temp->ranking = ranking;
        temp->title = title;
        temp->year = releaseYear;
        temp->quantity = quantity;
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        temp->parent = temp2;
        temp2->rightChild = temp;
    }
    
    else {
        //Adds node to the left side of the last node in the tree
        temp= new MovieNode;
        temp->ranking = ranking;
        temp->title = title;
        temp->year = releaseYear;
        temp->quantity = quantity;
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        temp->parent = temp2;
        temp2->leftChild = temp;
        
    }
    
}


//******************************************
// Public member function of MovieTree class
// Param: title
// Deletes movie from binary tree
//==========================================

void MovieTree::deleteMovieNode(std::string title){
    
    MovieNode * temp = search(title);//assighns a temp variable with the node of movie user is searching
    
    if(temp == NULL){
        
        cout << " Movie Not Found" << endl << endl;
    }
    
    else{
        
        if (temp->rightChild == NULL && temp->leftChild == NULL){//deleteing node with no children
            
            
            if (temp->parent->rightChild == temp){//if node is a right child of its parent
                
                temp->parent->rightChild = NULL;//reset node to NULL
                delete temp;//delete node
                
                return;
            }
            
            else{//if node is a left child of its parent
                
                temp->parent->leftChild = NULL;//reset node to NULL
                delete temp;//delete node
                
                return;
            }
        }
        
        else if(temp->rightChild == NULL){//if node being deleted has a left child
            
            if (temp->parent->leftChild == temp){//if node being deleted is a left child
                
                temp->parent->leftChild = temp->leftChild;//set parents of left child to deletenode left child
                temp->leftChild->parent = temp->parent;//set new parent to old parent
                delete temp;
            }
            
            else{//if node being deleted is a right child
                
                temp->parent->rightChild = temp->leftChild;//set parents of right child to deletenode left child
                temp->leftChild->parent = temp->parent;//set new parent to old parent
                delete temp;
            }
        }
        
        else if(temp->leftChild == NULL){//if node being deleted has a right child
            
            if (temp->parent->rightChild == temp){//if node being deleted is a right child
                
                temp->parent->rightChild = temp->rightChild;//set parents of right child to deletenode right child
                temp->rightChild->parent = temp->parent;//set new parent to old parent
                delete temp;
            }
            
            else{//if node being deleted is a left child
                
                temp->parent->leftChild = temp->rightChild;//set parents of left child to deletenode right child
                temp->rightChild->parent = temp->parent;//set new parent to old parent
                delete temp;
            }
        }
        
        else{//if node being deleted has two children
            
            MovieNode * min = treeMinimum(temp->rightChild);//should be minimum value of right subtree
            
            if (temp->parent->rightChild == temp){//if node being deleted is a right child
                
                temp->parent->rightChild = min;//set parents of right child to min value of right subtree
                temp->rightChild->parent = min->parent;//set new parent to parent of min value of right subtree
                delete temp;
            }
            else{//if node being deleted is a left child
                
                temp->parent->leftChild = min;//set parents of left child to min value of right subtree
                temp->leftChild->parent = min->parent;//set new parent to parent of min value of right subtree
                delete temp;
            }
        }
    }
}


MovieNode* MovieTree::treeMinimum(MovieNode *node){
    
    if (node == root){//returns the min value on the right subtree
        
        MovieNode * temp = node->rightChild;//sets node to rightchild of root
        
        while( temp->leftChild != NULL){
            
            temp = temp->leftChild;//gets min value of right subtree
        }
        
        return temp;//returns the min value on the right subtree
    }
    
    else if(node->parent->rightChild == node){//if node is a right child of its parent
        
        MovieNode * temp = node->rightChild;//get right child of node
        
        while(temp->leftChild != NULL){
            
            temp = temp->leftChild;
        }
        return temp;
    }
    
    else {//if node is a left child of its parent
        
        MovieNode * temp = node->leftChild;
        
        while (temp->rightChild != NULL){
            
            temp = temp->rightChild;//gets largest value of left subtree
        }
        
        return temp;
    }
}
//Doesnt work
void MovieTree::countMovieNodes(MovieNode *node, int *c){//needs work
    
    if(node == NULL){
        
        //cout << "Tree is empty" << endl;
    }
    
    else {
        
        countMovieNodes(node->leftChild, c);
        *c = *c + 1;//not going to work
        countMovieNodes(node->rightChild, c);
    }
}

int MovieTree::countMovieNodes(){
    
    int temp = 0;
    countMovieNodes(root, &temp);
    
    return temp;
}


MovieTree::~MovieTree(){
    
    DeleteAll(root);
};//destructor

//DOESNT WORK
void MovieTree::DeleteAll(MovieNode * node){
    
    if (node->leftChild != NULL)
        DeleteAll(node->leftChild);
    if(node->rightChild != NULL)
        DeleteAll(node->rightChild);
    delete node;
    return;
}
