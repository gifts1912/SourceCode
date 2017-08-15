//
//  dijstra_algorithm.hpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/15.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#ifndef dijstra_algorithm_hpp
#define dijstra_algorithm_hpp

#include <stdio.h>

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
};

struct AdjList{
    struct AdjListNode *head;
};

struct Graph{
    int V;
    struct AdjList *array;
};

struct Graph * createGraph(int V);
struct AdjListNode * newAdjListNode(int dest, int weight);
void addEdge(struct Graph *graph, int src, int dest, int weight);
void outGraph(Graph *graph);
void dijstra(Graph *graph);
void dijstra(struct Graph *graph, int s);



#endif /* dijstra_algorithm_hpp */
