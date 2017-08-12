#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Edge{
    int src,des;
};

struct Graph{
    int V, E;
    struct Edge *edges;
    int e_s;
};

struct Graph * createGraph(int v, int e) {
    struct Graph * graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph -> V = v;
    graph -> E = e;
    graph -> e_s = 0;
    graph -> edges = (struct Edge *) malloc(sizeof(struct Edge) * e);
    return graph;
}

void addEdge(Graph * graph, int v, int w){
    graph->edges[graph->e_s].src = v;
    graph -> edges[graph->e_s].des  = w;
    graph -> e_s ++;
}

int find(int *parent, int v){
    if (parent[v] == -1) {
        return v;
    }
    else 
        return find(parent, parent[v]);
}

void unio(int *parent, int v, int w){
    int x = find(parent, v);
    int y = find(parent, w);
    if (x == y){
        return;
    }
    else {
        parent[x] = y;
    }
}

bool isCyclic(Graph *graph) {
    int *parent = (int *) malloc(sizeof(int) * graph->V);
    memset(parent, -1, graph->V * sizeof(int));
    cout << "parent value" << '\t';
    for(int i = 0; i < graph-> V; i++) {
        cout << parent[i] << '\t';
    }
    cout << endl;
    for(int i = 0; i < graph->E; i++) {
        struct Edge &edge = graph->edges[i];
        int x = find(parent, edge.src);
        int y = find(parent, edge.des);
        if(x == y){
            return true;
        }
        else {
            unio(parent, x, y);
        }
    }
    return false;
}

int main(){
    int V = 3, E = 3;
    struct Graph* graph = createGraph(V, E);

    // add edge 0-1
    
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 2);

    if (isCyclic(graph))
        printf( "graph contains cycle" );
    else
        printf( "graph doesn't contain cycle" );

    return 0;
}
