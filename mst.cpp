#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <cstdlib>
#include <set>
#include <map>
#include <utility>
#include <tuple>
#include <sstream>
#include <cstdio>
#include <list>
#include <limits>
#include "/usr/include/boost/algorithm/string.hpp"

using namespace std;

enum Color{
    White,
    Gray,
    Black
};

struct Edge {
    string key_b;
    string key_e;
    float weight;
    Edge(string _key_b, string _key_e, float _w): key_b(_key_b), key_e(_key_e), weight(_w){

    }
};

struct Vertex{
    Color color;
    string key;
    int idx;
    Vertex *parent;
    list<Edge> edges;
};


struct Graph{
    vector<Vertex> vertices;
    map<string, int> key_idx;
};

void graph_output(Graph *graph){
    for(Vertex vt : graph -> vertices){
        cout << vt.key << " : ";
        for(Edge edge : vt.edges) {
            cout << edge.key_b << '-' << edge.key_e << '-' << edge.weight << ' ';
        }
        cout << endl;
    }
}


int graph_construct(Graph *graph, string fn){
    ifstream fr(fn);
    if(!fr.is_open()){
        cout << fn << " open failed!" << endl;
        return -1;
    }
    string line;
    stringstream ss;
    set<string> keys;
    vector< tuple<string, string, float> > edges;
    while(!fr.eof()){
        getline(fr, line);
        boost::algorithm::trim(line);
        if(line == ""){
            continue;
        }
        
        /*
        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of("\t"));
        if(tokens.size() != 3){
            cout <<  "file content not legal: " << line << endl;
            return -1;
        }
        string key_b = tokens[0];
        string key_e = tokens[1];
        float weight = stof(tokens[2]);
        */
        string key_b, key_e;
        float weight;
        
        ss.str(line);
        ss >> key_b >> key_e >> weight;
        ss.str("");
        ss.clear();
        keys.insert(key_b);
        keys.insert(key_e);
        edges.push_back(make_tuple(key_b, key_e, weight));
    }
    fr.close();

    int idx = 0;
    for(string key:keys){
        graph->key_idx[key] = idx;
        Vertex vt;
        vt.key = key;
        vt.idx = idx;
        graph->vertices.push_back(vt);
        idx ++;
    }
    // add edges into graph
    for (tuple<string, string, float> edge : edges) {
        int idx_b = graph -> key_idx[get<0>(edge)];
        int idx_e = graph -> key_idx[get<1>(edge)];
        Edge edge_f(get<0>(edge), get<1>(edge), get<2>(edge));
        graph -> vertices[idx_b].edges.push_back(edge_f);

        if (idx_b != idx_e) {
            Edge edge_r(get<1>(edge), get<0>(edge), get<2>(edge));
            graph -> vertices[idx_e].edges.push_back(edge_r);
        }
    }

    graph_output(graph);

}

int Prim(Graph *graph) {
    //remove parallel and loops edges.
    for(Vertex &vt: graph->vertices) {
        map<string, pair<float, list<Edge>::iterator> > key_min_weight;
        for(list<Edge>::iterator iter = vt.edges.begin(); iter != vt.edges.end();) {
            string key = iter -> key_e;
            if(key == vt.key) {
                iter = vt.edges.erase(iter);
                continue;
            }
            float weight = iter-> weight;
            if (key_min_weight.find(key) == key_min_weight.end()){
                key_min_weight[key] = make_pair(weight, iter);
                iter++;
            }
            else {
                pair<float, list<Edge>::iterator> wei_iter_pre = key_min_weight[key];
                if(wei_iter_pre.first <= weight) {
                    iter = vt.edges.erase(iter);
                    continue;
                }
                else {
                    key_min_weight[key] = make_pair(weight, iter);
                    iter++;
                    vt.edges.erase(wei_iter_pre.second);
                    continue;
                }
            }
        }
    }

    cout << "After remove all looops and paraless : " << endl;
    graph_output(graph);
    cout << endl;

    // arbitirally select andy vertex as root
    Graph * mst = new Graph();
    vector<Vertex> &T = mst -> vertices;
    Vertex v = graph -> vertices[0];
    v.edges.clear();
    T.push_back(v);
    set<string> keys;
    keys.insert(v.key);
    mst -> key_idx.clear();
    
    int cur_idx = 0;
    mst -> key_idx[v.key] = cur_idx++;

    //grow the MST through add safe edge one by one.
    while(T.size() < graph -> vertices.size()) {
        pair<string, pair<float, string> > key_min_wei("", make_pair(numeric_limits<float>::max(), ""));
        for(string key : keys){
            int idx = graph -> key_idx[key];
            for(Edge edge : graph -> vertices[idx].edges) {
                if(keys.find(edge.key_e) == keys.end()) {
                    if(key_min_wei.second.first > edge.weight) {
                        key_min_wei.first = edge.key_e;
                        key_min_wei.second.first = edge.weight;
                        key_min_wei.second.second = key;
                    }
                }
            }
        }

        string added_key = key_min_wei.second.second;
        Vertex &vt = T[mst->key_idx[added_key]];
        vt.edges.push_back(Edge(added_key, key_min_wei.first, key_min_wei.second.first));

        string new_key = key_min_wei.first;
        Vertex new_vt = graph -> vertices[graph->key_idx[new_key]];
        new_vt.edges.clear();
        T.push_back(new_vt);
        mst -> key_idx[new_key] = cur_idx++;
        keys.insert(new_key);
    }
    
    cout << "Mininmus spanning tree" << endl;
    graph_output(mst);

    return 0;
}

int main(){
    string fn = "./mst_data.tsv";
    Graph *graph = new Graph();
    int flag = graph_construct(graph, fn);
    if (flag == -1){
        cout << "Graph_construct fail!" << endl;
        return -1;
    }

    Prim(graph);

    free(graph);

}
