//==========================================
// Created by Joshua Griffiths on 11/1/16.
// Instructor Boese
// Description: Implementation file for a graph
// Copyright © 2016 Joshua Griffiths. All rights reserved.
// ==========================================
#include "graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addEdge(string v1, string v2, int dist)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.distance = dist;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == n)
        {
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = n;
        v.district=-1;
        v.ID = vertices.size();
        v.visited=false;
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].district << ":" <<vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout << vertices[i].adj[j].v->name;
            cout << " (" << vertices[i].adj[j].distance << " miles)";
            if (j != vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}

void Graph::assignDistricts()
{
    // Starting district numbers at 1
    int distID = 1;
    
    // For each of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if (vertices[i].district == -1)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
    }
}

void Graph::BFTraversalLabel(std::string startingCity, int distID)
{
    queue<vertex*> q;
    // Label all as unvisited.
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
    // Find the starting node and enqueue it.
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == startingCity)
        {
            // set current vertex to be visited.
            vertices[i].visited = true;
            vertices[i].district = distID;
            q.push(&vertices[i]);
            break;
        }
    }
    // Now do the rest of the search.
    while (q.empty() != true)
    {
        vertex * temp = q.front();		// get the next one from the queue
        q.pop();		// remove that one from the queue
        
        for(unsigned i = 0; i < temp->adj.size(); i++){
            
            if(temp->adj[i].v->visited == false){
                
                temp->adj[i].v->visited = true;
                temp->adj[i].v->district = distID;
                q.push(temp->adj[i].v);
            }
        }
    }
}

vertex * Graph::findVertex(std::string name)
{
    // add code here
    
    //NOT NEEDED FOR THIS IMPLEMENTATION
    
    for(unsigned i = 0; i < vertices.size();i++){
        
        if(vertices[i].name == name){
            
            return &vertices[i];
        }
    }
    
    return NULL;
}

/*void Graph::Dijkstra(string sourceVertex, string destinationVertex){
    
    vertex * start;
    vertex * end;
    
    //find the two vertices
    //intialize the "vertices"
    for(unsigned i = 0; i < vertices.size();i++){
        
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;//because we dont know the path yet
        vertices[i].previous = NULL;
        
        if(vertices[i].name == sourceVertex){
            
            start = &vertices[i];
        }
        
        if(vertices[i].name == destinationVertex){
            
            end = &vertices[i];
        }
    }
        //start dijkstra
        start->visited = true;//start vertex is solved
        start->distance = 0;
        vector< vertex * > solved;
        vector< vertex * > path;//for later use
        
        solved.push_back(start); //add starting vertex to vector
        adjVertex * v; //to go through neighbors
        vertex * u;//record teh current solved vertex with shortest distance
        vertex * minVert;//record current min vertex
        vertex * prev;//previous vertex of current vertex with shortest path
        
        while(!end->visited){
            
            int minDist = INT_MAX;
            //go through the solved vertices
            for(unsigned i = 0; i < solved.size();i++){
                
                u = solved[i];
                //go through adjacent vertex of "u"
                for(unsigned j = 0; j < u->adj.size(); j++){
                    
                    v = &u->adj[j];
                    
                    if(!v->v->visited){
                        
                        int dist = u->distance + v->weight;
                        
                        if (dist < minDist){
                            
                            minDist = dist;
                            minVert = v->v;
                            prev = u;
                        }
                    }
                }
            }
            
            solved.push_back(minVert);
            minVert->distance = minDist;
            minVert->previous = prev;
            minVert->visited = true;
        }
        
        cout <<"Shortest Path" << endl;
        vertex * vert = end;
        
        while(vert != NULL){
            
            path.push_back(vert);
            vert = vert->previous;
        }
        
        for(unsigned i = 0; i < path.size();i++){
            
            if(i == path.size()-1){
                
                cout << path[0]->name;
            }
            
            else{
                
                cout << path[path.size()-i-1]->name << " - ";
            }
        }
        
        cout << endl;
        cout << "Minimum Distance: " << solved[solved.size()-1]->distance << endl;
    }*/
