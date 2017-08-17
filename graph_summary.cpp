#include <iostream>
#include <queue>
#include <stack>
#include <limits>


using namespace std;

struct AdjListNode{
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

struct Graph *initGraph(int V){
    Graph *graph = (struct Graph *) malloc (sizeof(struct Graph));
    graph -> V = V;
    graph -> array = (struct AdjList *) malloc (sizeof(struct AdjList) * V);
    for(int i = 0; i < V; i++){
        graph -> array[i].head = NULL;
    }
    return graph;
};

void addEdge(Graph *graph, int src, int dest, int weight){
    struct AdjListNode* aln = (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    aln -> dest = dest;
    aln -> weight = weight;
    aln -> next = graph -> array[src].head;
    graph -> array[src].head = aln;
}
void outGraph(Graph *graph){
    cout << "Graph struct output!" << endl;
    for(int i = 0; i < graph -> V; i++){
        cout << i << " : "; 
        struct AdjListNode *n_p = graph -> array[i].head;
        while(n_p) {
            cout << n_p -> dest << '\t';
            n_p = n_p -> next;
        }
        cout << endl;
    }
    cout << endl;
}
void graphBFS(Graph *graph){
    bool *visited = new bool[graph -> V];
    for(int i = 0;i  < graph -> V; i++){
        visited[i] = false;
    }
    queue<int> vertices;
    cout << "Breath first search: " << endl;
    for(int i = 0; i < graph ->V; i++){
        if(visited[i]){
            continue;
        }
        vertices.push(i);
        while(!vertices.empty()){
            int v = vertices.front();
            vertices.pop();
            visited[i] = true;
            cout << v << '\t';
            struct AdjListNode *n_p = graph -> array[v].head;
            while(n_p != NULL){
                if (visited[n_p->dest] == false){
                    vertices.push(n_p -> dest);
                }
                n_p = n_p -> next;
            }
        }
        cout << endl;
    }
    cout << endl;
}

void dfs(Graph *graph, int i, bool *visited){
    visited[i] = true;
    cout << i << '\t';
    struct AdjListNode *n_p = graph -> array[i].head;
    while(n_p != NULL){
        int dest = n_p -> dest;
        if(visited[dest] == false){
            dfs(graph, dest, visited);
        }
        n_p = n_p -> next;
    }
}
void graphDFS(Graph *graph){
    bool *visited = new bool[graph->V];
    for(int i = 0; i < graph->V; i ++){
        visited[i] = false;
    }
    visited[0] = false;
    cout << "DFS searching for graph: " << endl;
    for(int i = 0; i < graph -> V; i++){
        if (visited[i] == false){
            dfs(graph, i, visited);
        }
    }
    cout << endl;
}

enum Color{WHITE, BLACK, GRAY};

void DFS_LogisticSort(Graph * graph, Color *vertices_color, int i, stack<int> &sort_res){
    vertices_color[i] = GRAY;
    struct AdjListNode *n_p = graph->array[i].head;
    while(n_p) {
        int dest = n_p -> dest;
        if(vertices_color[dest] == BLACK){
            DFS_LogisticSort(graph, vertices_color, dest, sort_res);
        }
        n_p = n_p -> next;
    }
    vertices_color[i] = WHITE;
    sort_res.push(i);
}

void logisticSort(Graph *graph){
    stack<int> sort_res;
    enum Color *vertices_color = new enum Color[graph -> V];
    for(int i = 0; i < graph -> V; i++){
        vertices_color[i] = BLACK;
    }

    for(int i = 0; i < graph -> V; i++){
        if(vertices_color[i] == BLACK){
            DFS_LogisticSort(graph, vertices_color, i, sort_res);
        }
    }

    cout << "Logistic sorting" <<endl;
    while(!sort_res.empty()){
        int v = sort_res.top();
        sort_res.pop();
        cout << v << '\t';
    }
    cout << endl;
}
bool detectCycleUtil(Color *colors, int i, Graph *graph) {
    colors[i] = GRAY;
    AdjListNode *n_p = graph -> array[i].head;
    while(n_p){
        int dest = n_p -> dest;
        if(colors[dest] == GRAY){
            return true;
        }
        else if(colors[dest] == WHITE){
            return detectCycleUtil(colors, dest, graph);
        }
        n_p = n_p -> next;
    }
    colors[i] = BLACK;
    return false;
}

bool detectCycle(Graph *graph){
    Color *colors = new enum Color[graph -> V];
    for(int i = 0; i < graph -> V; i++){
        colors[i] = WHITE;
    }
    for(int i = 0; i < graph -> V; i++){
        if(colors[i] == WHITE){
            bool flag = detectCycleUtil(colors, i, graph);
            if (flag){
                return true;
            }
        }
    }
    return false;
}
void topologicalSortUtil(Graph *graph, int i , bool *visited, stack<int> &res){
    visited[i] = true;
    struct AdjListNode *n_p = graph->array[i].head;
    while(n_p){
        if(!visited[i]){
            topologicalSortUtil(graph, n_p -> dest, visited, res);
        }
        n_p = n_p -> next;
    }
    res.push(i);
}
void topologicalSort(Graph *graph, stack<int> &topo_res){
    bool *visited = new bool[graph -> V];
    for(int i = 0; i < graph->V; i++){
        visited[i] = false;
    }
    for(int i = 0;i < graph->V; i++){
        if(!visited[i]){
            topologicalSortUtil(graph, i, visited, topo_res);
        }
    }
}
void longestPath(Graph *graph, int s){
    stack<int> topo_sort;
    bool *visited = new bool[graph -> V];
    for(int i = 0;i < graph -> V; i++){
        visited[i] = false;
    }
    topologicalSort(graph, topo_sort);
    int NINFINIT = numeric_limits<int>::min();
    int *dis = new int[graph->V];
    int *parents = new int[graph->V];
    for(int i = 0; i < graph->V; i++){
        dis[i] = NINFINIT;
        parents[i] = -1;
    }
    dis[s] = 0;
    while(!topo_sort.empty())
    {
        int src = topo_sort.top();
        topo_sort.pop();
        struct AdjListNode *aln = graph->array[src].head;
        while(aln){
            int dest = aln->dest;
            int weight = aln -> weight;
            if(dis[src] != NINFINIT && dis[dest] < dis[src] + weight){
                dis[dest] = dis[src] + weight;
                parents[dest] = src;
            }
            aln = aln->next;
        }
    }
    
    for(int i = 0; i < graph->V; i++){
        cout << i << " : " << dis[i] << '\t';
    }
    cout << endl;
}

void DFS_SCC(Graph *g, int i, Color * color){
    color[i] = GRAY;
    AdjListNode * np = g -> array[i].head;
    while(np){
        int dest = np-> dest;
        if(color[dest] == WHITE){
            DFS_SCC(g, dest, color);
        }
        np = np -> next;
    }
    color[i] = BLACK;
    cout << i << '\t';
}
void strongConnectComponents(Graph *graph){
    // lostic sort
    stack<int> logistic_sort;
    topologicalSort(graph, logistic_sort);
    
    // reverse arcs of graph generate.
    Graph *rg = initGraph(graph -> V);
    for(int i = 0; i < graph -> V; i++){
        struct AdjListNode *n_p = graph->array[i].head;
        while(n_p) {
            int src = n_p -> dest;
            addEdge(rg, src, i, n_p->weight);
            n_p = n_p -> next;
        }
    }

    outGraph(rg);

    Color *colors = new Color[graph -> V];
    for(int i = 0; i < graph -> V; i++){
        colors[i] = WHITE;
    }
    cout << "strong connect components" << endl;
    while(!logistic_sort.empty()){
        int dest = logistic_sort.top();
        logistic_sort.pop();
        for(int i = 0; i < graph -> V; i++){
            if(colors[i] == WHITE){
                DFS_SCC(rg, i, colors);
                cout << endl;
            }
        }
    }
    
}
int main(){
    Graph *g = initGraph(5);
    addEdge(g, 1, 0, 1);
    addEdge(g, 0, 2, 1);
    addEdge(g, 2, 1, 1);
    addEdge(g, 0, 3, 1);
    addEdge(g, 3, 4, 1);
    /*
    Graph *g = initGraph(6);
    addEdge(g, 5, 2, 1);
    addEdge(g, 5, 0, 1);
    addEdge(g, 4, 0, 1);
    addEdge(g, 4, 1, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 1, 1);
    */

    /*
    Graph *g = initGraph(4);
    addEdge(g, 0, 1, 1);
    addEdge(g, 0, 2, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 0, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 3, 1);
    */

    outGraph(g);

    /*
       graphBFS(g);
       graphDFS(g);
       logisticSort(g);
       */
    /*
    bool cycleFlag = detectCycle(g);
    cout << "Have cycle: " << cycleFlag << endl;
    */

//    longestPath(g, 2);   
    strongConnectComponents(g);
    return 0;
}
