#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits>
#include <cstdlib>
 


using namespace std;

const int V = 4;
const int INI = numeric_limits<int>::max();
// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};
 
// a structure to represent a connected, directed and 
// weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    struct Edge* edge;
    int **weight;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = 
         (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = 
       (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}

int* BellmanFord(Graph *graph, int s){
	int V = graph->V;
    int *dis = new int[V];
    for(int i = 0; i < V; i++){
        dis[i] = INI;
    }
    dis[s] = 0;
    
    for(int i = 0; i < V; i++){
        for(int e = 0; e < graph -> E; e++){
			struct Edge edge = graph->edge[e];
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            if(dis[src] != INI && weight != INI && dis[src] + weight < dis[dest]){
                dis[dest] = dis[src] + weight;
            }
        }
    }
 
    return dis;
}
int minNode(int *dis, bool *sht, int V){
    int min_dis = INI;
    int min_idx = -1;
    for(int i = 0; i < V; i++){
        if(!sht[i] && min_dis > dis[i]){
            min_dis = dis[i];
            min_idx = i;
        }
    }
    return min_idx;
}

int* Dijkstra_utility(Graph *graph, int s, int *h){
    int *dis = new int[graph->V];
    bool *spt = new bool[graph->V];
    for(int i = 0; i < graph -> V; i++){
        dis[i] = INI;
        spt[i] = false;
    }
    dis[s] = 0;
    
    int ** weight = graph -> weight;
    for(int i = 0; i < graph -> V; i++){
        int u = minNode(dis, spt, graph ->V);
        spt[u] = true;
        for(int v = 0; v < graph -> V; v++){
            if(dis[u] != INI){
                int weight = graph -> weight[u][v] + h[u] - h[v];
                if(weight != INI && dis[v] > dis[u] + weight){
                    dis[v] = dis[u] + weight;
                }
            }    
        }
    }
    return dis;
}

void graphWeightGen(Graph *graph){
    graph -> weight = (int **) malloc(graph -> V * sizeof(int *));
    for(int i = 0; i < graph->V; i++){
        graph->weight[i] = (int *) malloc(graph -> V * sizeof(int));
    }
    for(int i = 0; i < graph->V; i++){
        for(int j = 0; j < graph->V; j++){
            if(i == j){
                graph->weight[i][j] = 0;
            }
            else
                graph->weight[i][j] = INI;
        }
    }

    for(int i = 0; i < graph->E; i++){
        struct Edge edge = graph->edge[i];
        int src = edge.src;
        int dest = edge.dest;
        graph->weight[src][dest] = edge.weight;
    }
    
    cout << "Graph matrix is : " << endl;
    for(int i = 0; i < graph->V; i++){
        for(int j = 0; j < graph->V; j++){
            cout << graph->weight[i][j] << '\t';
        }
        cout <<endl;
    }
    cout <<endl;
}

void Dijkstra(Graph *graph, int *h){
    int **dis = new int *[graph ->V];
    for(int i = 0;i < graph -> V; i++){
        dis[i] = new int[graph->V];
    }
    for(int i = 0; i < graph->V; i++){
        for(int j = 0; j < graph->V; j++){
            dis[i][j] = INI;
        }
    }
    
    for(int i = 0; i < graph->V; i++){
        int *dis_cur = Dijkstra_utility(graph, i, h);
        for(int j = 0; j < graph -> V; j++){
            dis[i][j] = dis_cur[j];
        }
    }
    
    cout << "Dijkstra output is :" << endl;
    for(int i = 0; i < graph -> V - 1; i++){
        for(int j = 0; j < graph -> V -1 ; j++){
            cout << dis[i][j] << '\t';
        }
        cout << endl;
    }
}

void addNewVertex(Graph *graph){
    int nn = graph -> V;
    (graph -> V)++;
    graph -> E += graph -> V;
    graph->edge = (struct Edge *) realloc((void *) graph->edge, sizeof(struct Edge) * graph -> E);
    for(int i = 0; i < nn; i++){
        graph -> edge[nn].src = nn;
        graph -> edge[nn].dest = i;
        graph -> edge[nn].weight = 0;
    }
}



void FloydWarshall(int matrix[][V]) {
	int **out = (int **) malloc(sizeof(int*) * V);
    for(int i = 0;i < V; i++){
        out[i] = (int *) malloc(sizeof(int) * V);
    }

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			out[i][j] = matrix[i][j];
		}
	}
	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (out[i][k] != INI && out[k][j] != INI && out[i][j] > out[i][k] + out[k][j])
					out[i][j] = out[i][k] + out[k][j];
			}
		}
	}

	cout << "Floyd Warshell algorithm output: " << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
        
			cout << out[i][j] << '\t';
		}
		cout << endl;
	}
}


void Johnson(Graph *graph){
    addNewVertex(graph);
    //output(graph);
    int *h = BellmanFord(graph, graph->V - 1);
    cout << "Bellman Frod output is : " << endl;
    for(int i = 0; i < graph->V; i++){
        cout << h[i] << '\t';
    }
    cout << endl;

    graphWeightGen(graph);
    
    Dijkstra(graph, h);
}

int main()
{
    /* Let us create the graph given in above example */
    int v = 5;  // Number of vertices in graph
    int e = 8;  // Number of edges in graph
    struct Graph* graph = createGraph(v, e);
 
    // add edge 0-1 (or A-B in above figure)
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 5;
   
    // add edge 0-2 (or A-C in above figure)
    graph->edge[1].src = 0;
    graph->edge[1].dest = 3;
    graph->edge[1].weight = 10;
 
    // add edge 1-2 (or B-C in above figure)
    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;
 
    // add edge 1-3 (or B-D in above figure)
    graph->edge[3].src = 2;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 1;

    
    int graphV2[V][V] = { { 0,   5,  INI, 10 },
	{ INI, 0,   3, INI },
	{ INI, INI, 0,   1 },
	{ INI, INI, INI, 0 }
	};

    FloydWarshall(graphV2);
   // BellmanFord(graph, 0);
	Johnson(graph);
    return 0;
}
