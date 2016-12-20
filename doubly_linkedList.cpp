//==========================================
// Created: August 23, 2016 // Joshua Griffiths
// Instructor Boese
// Description: Implementation file for a doubly
//              linked list
// ==========================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "doubly_linkedList.hpp"

using namespace std;

struct city
{
    string 	name; 			// name of the city
    city 	*next; 			// pointer to the next city
    int 	numberMessages; // how many messages passed through this city
    string 	message; 		// message we are sending accross
};

city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{

    city *head = NULL;
    
    head = handleUserInput(head);
    printPath(head);
    head = deleteEntireNetwork(head);
    if (head == NULL)
        cout << "Path cleaned" << endl;
    else
        printPath(head);
    
    cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head the start of the linked list
 * @return the start of the linked list
 * Do NOT modify
 */
city* handleUserInput(city *head)
{
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
                // print all nodes
            case 1: 	//rebuild network
                head = loadDefaultSetup(head);
                printPath(head);
                break;
                
            case 2:		// print path
                printPath(head);
                break;
                
            case 3: //message is read in from file
            {
                string cityReceiver;
                cout << "Enter name of the city to receive the message: " << endl;
                getline(cin, cityReceiver);
                
                cout << "Enter the message to send: " << endl;
                string message;
                getline(cin, message);
                
                transmitMsg(head, cityReceiver, message);
            }
                break;
                
            case 4:
            {
                string newCityName;
                string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);
                
                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);
                
                // find the node containing prevCity
                city *tmp = NULL;
                if(prevCityName !="First")
                    tmp = searchNetwork(head, prevCityName);
                // add the new node
                head = addCity(head, tmp, newCityName);
                printPath(head);
            }
                break;
                
            case 5: 	// delete city
            {
                string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                head = deleteCity(head, city);
                printPath(head);
            }
                break;
                
            case 6: 	// delete network
                head = deleteEntireNetwork(head);
                break;
                
            case 7: 	// quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;
                
            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
    return head;
}

/*
 * Purpose: Add a new city to the network
 *   between the city *previous and the city that follows it in the network.
 * @param head pointer to start of the list
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName )
{
    
    if (previous == NULL){
        
        if (head == NULL){//Will triger first time network is built
            
            head = new city;//creates a memmory location for the head of our list to point to
            head->next = NULL;//sets the head's next pointer to NULL
            head->name = cityName;//sets the head's name to cityName
            head->numberMessages=0;//initializes new head's number of messages to zero
            cout << "  new: " << cityName << endl;//prints the name of the head pointer
        }
        
        else{//there exists a head but we want to make a new head
            
            city * newHead = new city;//creates a memmory location for our new head
            newHead -> next = head;//our new head's next pointer will point to the old head location
            newHead ->name = cityName;//sets the new head's name to whatever the user inputs
            newHead->numberMessages = 0;//initializes new head's number of messages to zero
            cout << "prev: " << head->name << "  new: " << newHead->name << endl; // prints old head's name
            return newHead;//allows change of head of list outside this function
            
        }
    }
    
    else {//inserts a node in to the middle or end of the last
        
        
        city * cityNameptr = new city;//creates a memmory location for our new pointer to point to
        cityNameptr->next = NULL;//initializes the new pointer's next pointer to NULL (just to be safe)
        cityNameptr->next = previous->next;//assighns the new pointers next pointer to the old node's next memmory location (essentially points to the next node in the list after the previous)
        previous->next = cityNameptr;//sets the original nodes next pointer to the location of the new node
        cityNameptr -> name = cityName;//sets the new nodes name to cityName
        cityNameptr->numberMessages = 0;//initializes new head's number of messages to zero
        
        //prints out previous nodes name and new nodes name
        cout << "prev: " << previous->name << "  new: " << cityNameptr->name << endl;
    }
    
    return head; //return of head which is unchanged
}

/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param ptr head of the list
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *ptr, string cityName)
{
    city * temp = ptr;//create a temporary pointer that points at the same memmory location as the head
    
    while (temp != NULL) {//while temp doesnt equall NULL (allows us to loop through our linked list)
        
        if (temp->name == cityName){//if node name equalls cityName
            
            return temp; //return the pointer to that node
            
        }
        else {
            
        }
        temp = temp ->next; //points the temp ptr to the next node in the list
    }
    return NULL;//if loop through entire list without finding a node name that matches a cityName return NULL
}

/*
 * Purpose: deletes all cities in the network starting at the head city.
 * @param ptr head of list
 * @return NULL as the list is empty
 */
city* deleteEntireNetwork(city *ptr)
{
    
    city * temp = ptr;//create a temporary pointer that points at the same memmory location as the head
    
    while (temp != NULL){//while temp doesnt equall NULL (allows us to loop through our linked list)
        
        cout << "deleting: " << ptr->name << endl;//print out that nodes name
        ptr = ptr->next;//sets pointer to point at the next node in the list (avoids deleting head before looping through list)
        delete ptr; // frees memmory location of node
        temp = ptr;//exits while loop
    }

    delete ptr;//frees memmory location of head of the list
    
    cout << "Deleted network" << endl;
    
    return NULL;//returns NULL
}

/* sends messages from file */
void transmitMsg(city *head, string receiver, string message)
{
    if(head == NULL)//if there isnt a head to the list yet
    {
        cout << "Empty list" << endl;
        return;
    }
    
    city * temp = head;//creates a temp ptr and points it to the same location as head
    
    city * recievingCityPtr = searchNetwork(head, receiver);//creates a temp ptr and points it to the same location as the reciever pointer points to
    
    if (searchNetwork(head, receiver) == NULL){
        
        // if the city dosn't exist, nothing we can do.
        // 		use this output statement
        cout << "City does not exist." << endl;
    }
    
    else{//if searchNetwork finds a memmory location in the list
        
        while (temp != recievingCityPtr->next){//while temp pointer doesnt equal the node after the recieving city (allows us to stop at the reciving ptr node)
            
            temp->message = message;//set nodes message to message
            temp->numberMessages++;//increment the nodes numberMessages by one
            
            cout << temp->name << " [# messages passed: " << temp->numberMessages << "] received: " << temp->message << endl;
            
            temp = temp-> next;//points temp pointer to next node in the list
            
        }
    }
}

/*
 * Purpose: delete the city in the network with the specified name.
 * @param head first node in list
 * @param cityName name of the city to delete in the network
 * @return head node of list
 */
city* deleteCity(city *head, string cityName)
{
    
    city * temp = head;//creates a temp ptr and points it to the same location as head
    city * temp2 = head->next;//creates a temp ptr and points it to the next node after head
    
    if (searchNetwork(head, cityName) == NULL){
        
        // if the city dosn't exist, nothing we can do.
        // 		use this output statement
        cout << "City does not exist." << endl;
    }
    
    else{//if searchCity finds a node in the lists whose name matches cityName
        
        while (temp2 != NULL){//while next node in the list doesnt equall node
            
            if (temp2->name == cityName){//if next node in the lists name equall to cityName
                
                temp->next = temp2->next;//sets temps next pointer to point at the next node after the one we want to delete
                delete temp2;//frees the memmory location that temp2 held
                break;//exits the loop
                
            }
            else if( temp -> name == cityName){//if you want to delete the head of the list
                
                head = head ->next;//changes head to point at the next node in the list
                //Leaks a little memmory shouldnt be a problem unless you delete 1000 + Heads to list
                break;//exits the loop
                
            }
            
            temp = temp2;//sets temp to point at the next node in the list
            temp2 = temp2 ->next;//sets temp2 to point at the next node in the list
        }
        
    }
    
    return head;//returns head to modify head outside of the function
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void printPath(city *ptr)
{
    cout << "== CURRENT PATH ==" << endl;

    if (ptr == NULL){//if head is equall to NULL
        cout << "nothing in path" << endl;
    }
    else{
    
       city * temp = ptr;//sets temp pointer to same memmory location location as head
        
        while (temp != NULL) {//while temp does not equall to NULL
            
            cout << temp->name << " -> "; //prints out node name (assumes head exists and has a head->name)
            temp = temp->next; //points temp to next node in the list
            
        }
        
        cout << "NULL" << endl << "===" << endl<<endl<<endl;
    }
    
}

/*
 * Purpose: populates the network with the predetermined cities
 * @param head start of list
 * @return head of list
 */
city* loadDefaultSetup(city *head)
{
    
    head = deleteEntireNetwork(head);//deletes list before it is rebuilt and sets head to NULL
    head = addCity(head,NULL,"Los Angeles");//creates a head to the linked list and sets head memmory location to same memmory location as Los Angeles node
    city * LAptr = searchNetwork(head, "Los Angeles");//sets a new pointer to same memmory location as Los Angeles
    addCity(head,LAptr,"Pheonix");//creates node int the linked list to pheonix
    city * PHNXptr = searchNetwork(head, "Pheonix");//sets a new pointer to same memmory location as Pheonix node
    addCity(head,PHNXptr,"Denver");//creates node in the linked list to Denver
    city * DENptr = searchNetwork(head, "Denver");//sets a new pointer to same memmory location as Denver node
    addCity(head,DENptr,"Dallas");//creates node in the linked list to Dallas
    city * DALptr = searchNetwork(head, "Dallas");//sets a new pointer to same memmory location as Dallas node
    addCity(head,DALptr,"Atlanta");//creates node in the linked list to Atlanta
    city * ATLptr = searchNetwork(head, "Atlanta");//sets a new pointer to same memmory location as Atlanta node
    addCity(head,ATLptr,"New York");//creates node in the link list to New york
    
    return head;//returns head from the list in this program will be the same memmory location as Los Angeles node
    
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}
