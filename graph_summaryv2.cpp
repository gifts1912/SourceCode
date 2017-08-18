int INFINIT = numeric_limits<int>::max();

void sp_mat(Graph *g){
    int **c = new int[g->V][g->V];
    for(int i = 0; i <g->V; i++){
        for(int j = 0; j < g->V; j++){
            if(i == j){
                c[i][j] = 0;
            }
            else{
                c[i][j] = INFINIT;
            }
        }
    }
    for(int i = 0; i < g->V; i++){
        for (int j = 0; j <g->V; j++){
            for(int k = 0; k <g->V; k++){
                c[i][j] = min(c[i][j], c[i][k] + g -> metric[k][j]);
            }
        }
    }
    
    cout <<"Pair shortest path metrix:" <<endl;
    for(int i = 0; i < g->V; i++){
        for(int j = 0; j <g->V; j++){
            cout << c[i][j] <<'\t';
        }
        cout <<endl;
    }
    cout <<endl;
}
struct Graph{
    int V;
    int **metric;
};
int main(){
    int v = 4;
    Graph *graph = new Graph(4);
    graph -> V = v;
    graph -> metric = new int[graph->V][graph->V];
    graph ->metric = { {0,   5,  INF, 10},
                        {INF, 0,   3, INF},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0}
                      };
    
    sp_mat(graph);
}
