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
//#include "BellmanDell.h"
#include "dijstra_algorithm.hpp"

using namespace std;




int main() {
    
    int V = 9;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
    outGraph(graph);
    
    dijstra(graph, 0);

    return 0;
}

