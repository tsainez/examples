//
//  minimumSpanningTree.cpp
//
//  Created by Anthony Sainez on 11 December 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   I used some prior code I wrote in an earlier class taken.
//          The specific code can be viewed at the following link:
//          https://github.com/tsainez/examples/blob/master/c%2B%2B/Sorting.cpp
//

#include <iostream>
#include <vector>   // Required for vectors
#include <utility>  // Required for make_pair function
#include <queue>    // Required for priority_queue object
#include <climits>  // Required for INT_MAX

using namespace std;

// Global variable declaration section
// Keeping track of adjacents, visited, key and parents.
// 1000 is an arbitrary number.
vector<pair<int, int>> adjacents[1000];
bool visited[1000];
int key[1000];
int parent[1000];

// Prim's Algorithm based on psuedocode.
void prims(int n) {
    // From last lab, recall that priority queue requires a functor to define the sorting pattern.
    // In this case we will use std::greater to create a min priority queue.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> >priorityQueue;
    
    // First, create a priority queue that holds the respective vertices in place.
    priorityQueue.push(pair<int,int>(0,0));
    
    for(int i = 0; i < n; i++) {
        key[i] = INT_MAX; //after inserting the source as 0 utilizing priorityQueue, initialize all keys to INT_MAX
        parent[i] = 0;
        
    }
    
    while(!priorityQueue.empty()) {
        int u = priorityQueue.top().second;  //Min key vertex, u = min() by key value
        priorityQueue.pop();
        visited[u] = true;

        for(int i = 0; i < adjacents[u].size(); i++) {
            int v = adjacents[u][i].first;
            int w = adjacents[u][i].second;
            
            if(!visited[v] && key[v]>w) {
                // Considering smaller weight with respect to vertex
                key[v] = adjacents[u][i].second;
                priorityQueue.push(pair<int,int>(w,v));
                parent[v] = u;
            }
        }
    }
    
    for(int i = 1; i < n; i++)
        cout << parent[i] << endl;
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    
    // Create graph
    int u, v, w;
    
    for(int i = 0; i < m; i++) {
        cin >> u;
        cin >> v;
        cin >> w;
        
        adjacents[u].push_back(make_pair(v,w));
        adjacents[v].push_back(make_pair(u,w));
    }
    
    prims(n);
    
    return 0;
}
