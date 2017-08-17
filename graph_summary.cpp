#include <iostream>
#include <queue>
#include <stack>


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
int main(){
    Graph *g = initGraph(6);
    addEdge(g, 5, 2, 1);
    addEdge(g, 5, 0, 1);
    addEdge(g, 4, 0, 1);
    addEdge(g, 4, 1, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 1, 1);

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

    bool cycleFlag = detectCycle(g);
    cout << "Have cycle: " << cycleFlag << endl;
    return 0;
}
