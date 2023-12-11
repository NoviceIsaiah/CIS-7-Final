/* 
 * File:   main.cpp
 * Author: Isaiah
 * 
 * Purpose: Create a program that represent a given graph including all of
 * the vertices, edges, and weights between each vertex. Then calculate the
 * lowest-cost and shortest distance between certain locations such as Riverside
 * Peris, Hemet, and Moreno Valley. 
 */

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

struct Node{ //Node structure 
    int value, cost; //Value or the vertex and cost; Riverside = 0, Moreno Valley = 1,
                     //Hemet = 2, Parris = 3.
    Node* next;      // Points to the next node
};

struct Edge{ //Edge structure
    int src, dest, weight; //Source node, destination node, and weight for edge
};

class Graph{   //Graph class 
    int verts; //Number of vertices in a graph
    
    Node* adjListNode(int val, Node* head, int weight){ //Function to create adjacency list
        Node* newNode = new Node;
        newNode->value = val;    //The value is set to its initial destination
        newNode->next = head;     //Points to head Node or next Node
        newNode->cost = weight;   //Weight of edge via traveling to next node
        
        return newNode; //Returns new node
    }
public:
    Node** head; //Array of pointers that represent adjacency list
    
    void printVariations(Graph g);
    
    Graph(Edge edges[],int verts, int edgeCount){ //Graph constructor
        head = new Node*[verts]; //Allocate memory for head pointers (based on amount of vertices
        this->verts = verts;     //This graphs amount of vertices are set
        
        for(int i=0; i < verts; ++i){ //Fills in allocated memory
           head[i] = nullptr; //Fills with nullptr
        }
        for (unsigned i = 0; i < edgeCount; i++){ //Goes thru adjacency list and fills it in
            int src = edges[i].src;               //Source is edge source
            int dest = edges[i].dest;             //Destination is next node
            int weight = edges[i].weight;         //Weight is set for edge

            //Insert in the beginning
            Node* newNode = adjListNode(dest, head[src], weight);

            //Points head pointer to new node
            head[src] = newNode;
        }
    }
public:
    ~Graph(){ //Deconstructor for graph class
        for (int i = 0; i < verts; i++) delete[] head[i];
        delete[] head;
    }
};

void printList(Node* ptr, int i){ //Print function 
    while (ptr != nullptr){
        cout << "(" << i << ", " << ptr->value
            << ", " << ptr->cost << ") ";

        ptr = ptr->next;
    }
    cout << endl;
}

void Graph::printVariations(Graph g) {
    vector<int> cities(verts - 1); //Creates vector with size of 3
    
    for (int i = 1; i < verts; ++i) { //Starts at next city since Riverside is always our starting point
        cities[i - 1] = i; //City value is set to i. City[0] = 1, City[1] = 2, etc...
    }

    do {
        cout << "Riverside -> "; //Always starts in Riverside
        
        int totalWeight = 0;
        
        for (int i = 0; i < verts - 1; ++i) {
            int fromCity = cities[i];
            int toCity = cities[i + 1];
            
            cout << fromCity << " -> ";
            
            // Find the edge weight between fromCity and toCity
            Node* current = head[fromCity-1];
            while (current && current->value != toCity && (current->next != nullptr)) {
                current = current->next;
            }
            if (current) {
                totalWeight += current->cost;
            }
        }
        cout << "Riverside (Total Weight: " << totalWeight << ")\n";//Always ends in Riverside
    } while (next_permutation(cities.begin(), cities.end()));
}

//Program starts here----------------------------------------------------------
int main(){ //Main driver function
    const int startPos = 0;   //Starting position is always Riverside
    const int numOfVerts = 4; //Total number of vertices
    
    Edge edges[] = { //Array showing adjacency list
        {0,1,16},{0,2,33},{0,3,24},{1,0,16},{1,2,26},{1,3,18},
        {2,0,33},{2,1,26},{2,3,30},{3,0,24},{3,1,18},{3,2,30}
    };

    int edgeCount = sizeof(edges)/sizeof(edges[0]); //Size of edge array
    
    Graph graph(edges,numOfVerts,edgeCount); //Creates instance of a graph using
                                             //value found above
    
    cout << "Adjacency List" << endl;
    for (int i = 0; i < numOfVerts; i++)     //Prints adjacency list
    {
        // print all neighboring vertices of vertex i
        printList(graph.head[i], i);
    }
    
    cout << endl;
    
    graph.printVariations(graph);
    
    return 0; //Exit driver
}