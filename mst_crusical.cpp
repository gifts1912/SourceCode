#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct Edge{
    int src,dest, weight;
};

struct Graph{
    int V, E;
    struct Edge *edge;
    int e_s;
    Graph(int _v, int _e) {
        V = _v;
        E = _e;
    }
};

struct Subset{
    int parent;
    int rank;
};

struct Graph * createGraph(int v, int e) {
    struct Graph * graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph -> V = v;
    graph -> E = e;
    graph -> e_s = 0;
    graph -> edge = (struct Edge *) malloc(sizeof(struct Edge) * e);
    return graph;
}

void addEdge(Graph * graph, int v, int w, int wei){
    graph->edge[graph->e_s].src = v;
    graph -> edge[graph->e_s].dest  = w;
    graph -> edge [graph->e_s].weight = wei;
    graph -> e_s ++;
}

void outGraph(Graph *graph) {
    for(int i = 0; i < graph -> E; i++) {
        struct Edge &edge = graph->edge[i];
        cout << edge.src << ":" << edge.dest << ":" << edge.weight << '\t';
    }
    cout << endl;
}

int find(struct Subset *parent, int v){
    if (parent[v].parent == v) {
        return v;
    }
    else 
        return find(parent, parent[v].parent);
}

void unio(struct Subset *parent, int v, int w){
    int x = find(parent, v);
    int y = find(parent, w);
    if(x != y) {
        if(parent[x].rank < parent[y].rank) {
            parent[x].parent = y;
        }
        else if (parent[x].rank > parent[y].rank) {
            parent[y].parent = x;
        }
        else {
            parent[x].parent = y;
            parent[x].rank++;
        }
    }
}

bool isCyclic(Graph *graph) {
    struct Subset * parent  = (struct Subset *) malloc(graph->V * sizeof(struct Subset));
    for(int i = 0;i < graph->V; i++) {
        parent[i].parent = i;
        parent[i].rank = 0;
    }
    for(int i = 0; i < graph->E; i++) {
        struct Edge &edge = graph->edge[i];
        int x = find(parent, edge.src);
        int y = find(parent, edge.dest);
        if(x == y){
            return true;
        }
        else {
            unio(parent, x, y);
        }
    }
    return false;
}

bool weightAscending(const struct Edge &e1, const struct Edge &e2) {
    return e1.weight <= e2.weight;
}
void CruscalMST_V2(Graph * graph) {
    struct Edge *result = (struct Edge*)malloc((graph -> V - 1) * sizeof(struct Edge));

    sort(graph -> edge, graph->edge + graph->E, weightAscending);


    struct Subset * parents = (struct Subset *) malloc (graph -> V * sizeof(struct Subset));
    for(int i = 0; i < graph -> V; i++) {
        parents[i].parent = i;
        parents[i].rank = 0;
    }
    int e= 0, i = 0;
    while(e <= graph -> V - 1) {
        if(i == graph -> E ) {
            break;
        }
        struct Edge &edge = graph->edge[i++];
        int x = find(parents, edge.src);
        int y = find(parents, edge.dest);
        if(x != y) {
            unio(parents, x, y);
            result[e++] = edge; 
        }
    }

    if(e == graph->V - 1) {
        cout << "MST find successfully!" << endl;
    }
    else
        cout << "MST not found!" <<endl;
    for(int i = 0;i < e; i++) {
        cout << result[i].src << ":" << result[i].dest << ":" << result[i].weight << '\t';
    }
    cout << endl;
}
void CruscalMST(Graph * graph) {

    Graph *mst = (Graph *) malloc (sizeof(struct Graph) * graph -> V);
    mst -> V = graph -> V;
    mst -> E = 0;
    mst -> edge = (struct Edge *) malloc(sizeof(struct Edge) * (graph -> V - 1));


    sort(graph -> edge, graph->edge + graph->E, weightAscending);

    for(int i = 0; i < graph -> E; i++) {
        int e_n = mst->E;
        if(e_n == mst->V -1) {
            break;
        }
        mst->edge[e_n] = graph -> edge[i];
        mst->E = e_n + 1;
        if(isCyclic(mst)) {
            mst->E = e_n;
        }
    }

    if(mst -> E == mst->V- 1) {
        cout << "MST find successfully!" << endl;
    }
    else
        cout << "MST not found!" <<endl;
    outGraph(mst);
}


int main(){
    int V =4, E = 5;
    struct Graph* graph = createGraph(V, E);

    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;


    /*
       if (isCyclic(graph))
       printf( "graph contains cycle" );
       else
       printf( "graph doesn't contain cycle" );

       cout << endl;
       */
    //CruscalMST(graph);
    CruscalMST_V2(graph);
    return 0;
}
