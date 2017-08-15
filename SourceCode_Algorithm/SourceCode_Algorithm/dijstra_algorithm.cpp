//
//  dijstra_algorithm.cpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/15.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include "dijstra_algorithm.hpp"
#include <iostream>
#include <limits>

using namespace std;

struct Graph * createGraph(int V){
    Graph * graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph -> V = V;
    graph -> array = (struct AdjList *) malloc (V * sizeof(struct AdjList));
    for(int i =0 ;i < V; i++){
        graph -> array[i].head = NULL;
    }
    return graph;
}


struct AdjListNode * newAdjListNode(int dest, int weight){
    struct AdjListNode * aln = (struct AdjListNode*) malloc (sizeof(struct AdjListNode));
    aln -> dest  = dest;
    aln -> weight = weight;
    aln -> next = NULL;
    return aln;
}

void addEdge(struct Graph *graph, int src, int dest, int weight){
    struct AdjListNode * aln = newAdjListNode(dest, weight);
    aln -> next = graph -> array[src].head;
    graph -> array[src].head = aln;
    
    // undirected graph
    aln = newAdjListNode(src, weight);
    aln -> next = graph->array[dest].head;
    graph->array[dest].head = aln;
}

void outGraph(struct Graph *graph) {
    cout << "The graph structure is : " << endl;
    for(int i = 0; i < graph->V; i++) {
        cout << i << '\t';
        struct AdjListNode *head = graph->array[i].head;
        while(head != NULL){
            cout << head -> dest << ":" << head -> weight << '\t';
            head = head -> next;
        }
        cout << endl;
    }
    cout << endl;
}

struct statusNode{
    int dis;
    int parent;
    bool visited;
};

const int INFINITE = numeric_limits<int>::max();

int getMin(struct statusNode *sn, int V){
    int min = INFINITE;
    int min_pos = -1;
    bool visisted_flag = false;
    for(int i = 0; i < V; i++){
        if(sn[i].visited == false && min >= sn[i].dis){
            visisted_flag = true;
            min_pos = i;
            min = sn[i].dis;
        }
    }
    if(visisted_flag == false){
        cout << "no visited" << endl;
    }
    return min_pos;
}

bool haveNoVisisted(struct statusNode *  sn, int V){
    for(int i = 0; i < V; i++){
        if (sn[i].visited == false) {
            return true;
        }
    }
    return false;
}

void dijstra(struct Graph *graph, int s){
    struct statusNode * sn = (struct statusNode *) malloc (graph -> V * sizeof(struct statusNode));
    for(int i = 0;i < graph -> V; i++) {
        sn[i].dis = INFINITE;
        sn[i].parent = NULL;
        sn[i].visited = false;
    }
    sn[s].dis = 0;
  
    while(haveNoVisisted(sn, graph-> V)){
        int min_src = getMin(sn, graph -> V);
        if (min_src == -1){
            cout << "min_src == -1" << endl;
            return;
        }
        sn[min_src].visited = true;
        struct AdjListNode * aln = graph -> array[min_src].head;
        while(aln != NULL) {
            int dest = aln->dest;
            if(sn[dest].dis > sn[min_src].dis + aln -> weight) {
                sn[dest].dis = sn[min_src].dis + aln -> weight;
                sn[dest].parent = min_src;
            }
            aln = aln -> next;
        }
    }
    
    cout << "Dijstra distance is : " ;
    for(int i = 0; i < graph -> V; i++){
        cout << i << ":" << sn[i].dis << '\t';
    }
    
    cout << endl;
    
}


