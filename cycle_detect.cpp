#include <iostream>
#include <list>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

class Graph{
    private:
        int V;
        bool isCyclicUtil(int i, bool *visited, bool * recStack, int V);
        bool isCyclicUtilColor(int i, Color *color, int V);
        list<int> *adj;
    public:
        Graph(int _v);
        void addEdge(int v, int w);
        bool isCyclic();
        bool isCyclicColor();
        ~Graph();
};

Graph::Graph(int _v):V(_v){
    adj = new list<int> [V];
}
Graph::~Graph(){
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

bool Graph::isCyclicUtil(int i, bool *visited, bool * recStack, int V){
    if(visited[i] == false){
        visited[i] = recStack[i] = true;
        for(int j : adj[i]) {
            if(visited[j]){
                return true;
            }
            else if(isCyclicUtil(j, visited, recStack, V)){
                return true;
            }
        }
    }
    recStack[i] = false;
    return false;
}

bool Graph::isCyclicUtilColor(int i, Color *color, int V){
    color[i] = GRAY;
    for(int j : adj[i]) {
        if(color[j] == GRAY) {
            return true;
        }
        else if(color[j] == WHITE && isCyclicUtilColor(j, color, V)) {
            return true;
        }
    }
    color[i] = BLACK;
    return false;
}

bool Graph::isCyclicColor(){
    Color *color = new Color[V];
    for(int i = 0;i < V; i++) {
        color[i] = WHITE;
    }
    for(int i = 0; i < V; i++) {
        if (color[i] == WHITE) {
            if(isCyclicUtilColor(i, color, V)) {
                return true;
            }
        }
    }
    free(color);
    return false;
}

bool Graph::isCyclic(){
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0;i < V; i++) {
        visited[i] = recStack[i] = false;
    }
    for(int i = 0; i < V; i++) {
        if(isCyclicUtil(i, visited, recStack, V)) {
            return true;
        }
    }
    free(visited);
    free(recStack);
    return false;
}

int main(){
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    if(g.isCyclicColor())
    //if(g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    return 0;
}
