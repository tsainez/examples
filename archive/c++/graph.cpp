//
//  graph.cpp
//
//  Created by Anthony Sainez on 11 December 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   I used several StackOverflow resources. 
//

#include <map>
#include <list>
#include <iostream>
#include <string>
#include <queue>    // Required for queue object
#include <climits>  // Required for INT_MAX

using namespace std;

// From Graph.cpp
struct Graph {
    list<string> vertices;
    map<pair<string,string>,int> edges;
    void PrintOut(void);
    void AddEdge(string,string,int);
    bool FindVertex(string);
    int FindEdgeCost(string vert1, string vert2);
    int IsReachable(string vert1, string vert2);
};

void Graph::PrintOut() {
    // To iterate over a list you need an iterator object...
    // This is one way to make use of the Graph struct that was given to us
    list<string>::iterator it;
    map<pair<string,string>,int>::iterator eit;
    
    for(it = vertices.begin(); it != vertices.end(); it++)
    cout << *it << endl;
    
    for(eit = edges.begin(); eit != edges.end(); eit++)
    cout << (*eit).first.first << " " << (*eit).first.second << " " << (*eit).second << endl;
}

void Graph::AddEdge(string vert1, string vert2, int weight) {
    pair<string,string> key = make_pair(vert1,vert2);
    edges[key] = weight;
}

bool Graph::FindVertex(string vert1) {
    list<string>::iterator it;
    
    for(it = vertices.begin(); it != vertices.end(); it++) {
        if(vert1.compare(*it) == 0){
            return true;
        }
    }
    
    return false; // Iterated through every vertex, no match, return false.
}

int Graph::FindEdgeCost(string vert1, string vert2) {
    // Traverse the map, then check if the edge exists,
    // and return the value
    map<pair<string,string>,int>::iterator eit;
    pair<string,string> key = make_pair(vert1,vert2);
    eit = edges.find(key);
    
    if (eit != edges.end()){
        return edges.find(key)->second;
    }
    
    return -1;
}

int Graph::IsReachable(string vert1, string vert2) {
    // Prerequisite requirement
    if(vert1 == vert2)
        return 0;
    
    // Variable declaration section
    string u;
    
    map<pair<string,string>,int>::iterator eit;
    map<pair<string,string>,int>::iterator jeit;
    map<pair<string,string>,int> adjList;
    map<string,int> Visit;
    map<string, int> Dmap;
    
    list<string>::iterator it;
    list<string>::iterator lit;
    
    queue<string> tempQueue;
    
    int n = vertices.size();
    
    tempQueue.push(vert1);
    
    for(it = vertices.begin(); it != vertices.end(); it++) {
        for(lit = vertices.begin(); lit != vertices.end(); lit++){
            pair<string,string> key = make_pair(*it,*lit);
            
            if(edges.count(key) > 0){
                adjList[key] = 1;
            } else {
                adjList[key] = 0;
            }
        }
    }
    
    for(it = vertices.begin(); it != vertices.end(); it++){
        Visit[*it] = 0;
        Dmap[*it] = INT_MAX;
    }
    
    Dmap[vert1] = 0;
    
    while(!tempQueue.empty()) {
        u = tempQueue.front();
        tempQueue.pop();
        
        for(it = vertices.begin(); it != vertices.end(); it++) {
            if(u.compare((*it)) == 0) {
                Visit[*it] = 1;
            }
            
            pair<string,string> pedge = make_pair(u, *it);
            
            if(adjList[pedge] == 1) {
                if(Visit[*it] == 0) {
                    Visit[*it] = 1;
                    Dmap[*it] = Dmap[u] + 1;
                    if((*it).compare(vert2) == 0) {
                        return Dmap[*it];
                    }
                    tempQueue.push(*it);
                }
            } // endif
        } //endfor
    } //endwhile
    
    return -1;
}

int main() {
    Graph G;
    
    string input;
    
    // Input vertices
    cin >> input;
    
    while(input.compare("END") != 0){
        G.vertices.push_back(input);
        cin >> input;
    }
    
    // Input edges
    string input2;
    int weight;
    cin >> input;
    
    while(input.compare("END") != 0){
        cin >> input2;
        cin >> weight;
        G.AddEdge(input,input2, weight);
        cin >> input;
    }
    
    G.PrintOut();
    
    int opCode;
    
    cin >> opCode;
    while(opCode != 0){
        if(opCode == 1){
            cin >> input;
            if(G.FindVertex(input) == 0){
                cout << 0 << "\n";}
            else
                cout << 1 << "\n";
        }
        
        if(opCode == 2){
            cin >> input;
            cin >> input2;
            cout << G.FindEdgeCost(input,input2) << "\n";
        }

        if(opCode == 3){
            cin >> input;
            cin >> input2;
            cout << G.IsReachable(input,input2) << "\n";
        }
        
        cin >> opCode;
    }
    
    return 0;
}
