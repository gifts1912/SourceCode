//
//  main.cpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/13.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include <iostream>
#include <list>
#include <utility>
#include <limits>
#include <cstdlib>
#include <iterator>
#include "BellmanDell.h"

using namespace std;


const int INIFINIT = numeric_limits<int>::max();

Graph::Graph(int _v, int _e):V(_v), E(_e){
}


void Graph::addEdge(int s, int d, int w){
    edges.push_back(Edge(s, d, w)); // direction graph;
    return;
}

void Graph::outGraph(string flag){
    cout << "graph output for " << flag << " :" << endl;
    for(Edge ele : edges) {
        cout << ele.src << ":"<<ele.dest<<":"<< ele.weight << '\t';
    }
    cout << endl;
}



enum Color {WHITE, GRAY, BALCK};


void DFS(list<Edge> * vertices, Color * colors, list<int> &sort, int i) {
    colors[i] = GRAY;
    for (Edge edge : vertices[i]){
        int dest = edge.dest;
        if(colors[dest] == WHITE) {
            DFS(vertices, colors, sort, dest);
        }
    }
    colors[i] = BALCK;
    sort.push_front(i);
}

list<int> Graph::toplogicSort(list<Edge> * vertices){
    list<int> sort;
    Color *colors = new Color[V];
    for(int i = 0;i < V; i++){
        colors[i] = WHITE;
    }
    
    for(int i =  0;i < V; i++) {
        if(colors[i] == WHITE) {
            DFS(vertices, colors, sort, i);
        }
    }
    
    cout << "Toplogic sort output: ";
    for(int ele :  sort) {
        cout << ele << '\t';
    }
    cout  << endl;
    
    
    return sort;
}


struct NodeState * Graph::DAG(int s){
    list<Edge> * vertices = new list<Edge> [V];
    for(Edge edge : edges){
        int src = edge.src;
        vertices[src].push_back(edge);
    }
    list<int> toplogic_sort = toplogicSort(vertices);
    
    struct NodeState *dis = new struct NodeState[V];
    for(int i = 1; i < V; i++) {
        dis[i].d = INIFINIT;
        dis[i].p = NULL;
    }
    list<int>::iterator iter = toplogic_sort.begin();
    advance(iter, s);
    if (iter == toplogic_sort.end()) {
        cout << "satated after end" << endl;
        return NULL;
    }
    dis[*iter++].d = 0;
    
    for(; iter != toplogic_sort.end(); iter++ ) {
        for(Edge edge : vertices[*iter]){
            int dest = edge.dest;
            if(dis[edge.src].d != INIFINIT && dis[edge.src].d + edge.weight < dis[dest].d){
                dis[dest].d = dis[edge.src].d + edge.weight;
            }
        }
    }
    
    for(int i =0; i < V; i++){
        printf("%d:%d\t", i, dis[i].d);
    }
    cout << endl;
    
    return dis;
    
}


void Graph::BellmanFord_SP(int s){
    pair<int, int>  * d_p = new pair<int, int>[V];
    for(int i = 0; i < V; i++) {
        d_p[i].first = INIFINIT;
        d_p[i].second = -1;
    }
    d_p[s].first = 0;
    
    for(int i = 1; i <= V; i++){
        for (Edge edge : edges){
            if (d_p[edge.src].first != INIFINIT && d_p[edge.src].first + edge.weight < d_p[edge.dest].first){
                d_p[edge.dest].first = d_p[edge.src].first + edge.weight;
                d_p[edge.dest].second = edge.src;
            }
        }
    }
    
    //Judge weather have negetive wegiht cycle
    for(Edge edge: edges){
        if(d_p[edge.dest].first != INIFINIT && d_p[edge.src].first + edge.weight < d_p[edge.dest].first){
            cout << "Cycle exists! " << endl;
            return;
        }
    }
    
    cout << "Minist path found : " << endl;
    for(int i = 0;i < V; i++) {
        printf("%d %d \n", i, d_p[i].first);
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    /*
    Graph graph(5, 8);
    // add edge 0-1 (or A-B in above figure)
    graph.addEdge(0,1, -1);

    
    // add edge 0-2 (or A-C in above figure)
    graph.addEdge(0, 2, 4);
   
    
    // add edge 1-2 (or B-C in above figure)
    graph.addEdge(1, 2, 3);
    
    // add edge 1-3 (or B-D in above figure)
    graph.addEdge(1, 3, 2);
    
    // add edge 1-4 (or A-E in above figure)
    graph.addEdge(1, 4, 2);
    
    // add edge 3-2 (or D-C in above figure)
    graph.addEdge(3, 2, 5);
    
    // add edge 3-1 (or D-B in above figure)
    graph.addEdge(3, 1, 1);

    
    // add edge 4-3 (or E-D in above figure)
    graph.addEdge(4, 3, -3);

    graph.outGraph("Graph construct : ");
    graph.BellmanFord_SP(0);
    */
    
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    g.DAG(0);
    
    
    return 0;
}
