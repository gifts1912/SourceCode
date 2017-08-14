//
//  BellmanDell.h
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/13.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#ifndef BellmanDell_h
#define BellmanDell_h
#include <iostream>
#include <list>

using namespace std;

struct NodeState{
    int d;
    int p;
};

struct Edge{
    int src, dest, weight;
    Edge(int _s, int _d, int _w) : src(_s), dest(_d), weight(_w){}
};

class Graph{
private:
    int V, E;
    list< Edge> edges;
    
public:
    Graph(int _v, int _e);
    
    Graph(int _v): V(_v) {}
    void addEdge(int s, int d, int w);
    
    void BellmanFord_SP(int s);
    
    void outGraph(string flag);
    
    list<int> toplogicSort(list<Edge> * vertices);
    
    struct NodeState * DAG(int s);
};



#endif /* BellmanDell_h */
