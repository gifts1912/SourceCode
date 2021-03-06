/*************************************************************************
	> File Name: graph_v2.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 01 Aug 2016 05:48:20 PM DST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <utility>
#include <set>
#include <string>
#include <cstdlib>
#include  "/usr/include/boost/algorithm/string.hpp"

using namespace std;


enum Color {
	White,
	Black,
	Grey
};

struct Vertex{
	int key;
	Color color;
	Vertex *parent;
	int discovery;
    Vertex(int _key = -1):key(_key){}
};

struct Graph{
	vector<Vertex> vertexes;
	vector< vector<Vertex *> > edges;
};



void breadth_first_search(Graph & graph, Vertex * start){
	for(int i = 0; i < graph.vertexes.size(); i++){
		graph.vertexes[i].color = White;
	}
	start -> color = Grey;
	start -> parent = NULL;
	start -> discovery = 0;

	queue<Vertex *> qu;
	qu.push(start);
	while(!qu.empty()){
		Vertex * v = qu.front();
		qu.pop();
		int id = v->key;
		for(Vertex * v_ele: graph.edges[id]){
			if (v_ele -> color == White){
				v_ele -> color = Grey;
				v_ele -> parent = v;
				v_ele -> discovery = v->discovery + 1;
				qu.push(v_ele);
			}
		}
		v -> color = Black;
		cout << id <<  "\t";
	}
}

vector<string> split(const string &text, char sep){
	vector<string> terms;
	int start_pos = 0, end_pos;
	while((end_pos = text.find(sep, start_pos)) != string::npos){
		string term = text.substr(start_pos, end_pos - start_pos);
		terms.push_back(term);
		start_pos = end_pos + 1;
	}
	terms.push_back(text.substr(start_pos));
	return terms;
}

void graph_add_edges(Graph *graph, vector<string>& edges){
	int max_idx = -1;
	vector< pair<int, int> > edge_points;
	for (string edge: edges){
		vector<string> tokens;
		boost::split(tokens, edge, boost::is_any_of("\t"));
		int begin_vertex_idx = atoi(tokens[0].c_str());
		if(max_idx < begin_vertex_idx){
			max_idx = begin_vertex_idx;
		}
		int end_vertex_idx = atoi(tokens[1].c_str());
		if(max_idx < end_vertex_idx){
			max_idx = end_vertex_idx;
		}
		edge_points.push_back(make_pair(begin_vertex_idx, end_vertex_idx));
	}
	set<int> created_id;
    for (int i = 0; i < max_idx + 2; i++){
        Vertex vt_cur(-1);
        vector<Vertex*> vec;
        (graph -> vertexes).push_back(vt_cur);
        (graph -> edges).push_back(vec);
    }
	//graph -> edges = vector< vector<Vertex *> > (max_idx+1, NULL);
	for(pair<int, int> edge_pair: edge_points){
		if(created_id.find(edge_pair.first) == created_id.end()){
			graph -> vertexes[edge_pair.first].key = edge_pair.first;
		}
		if(created_id.find(edge_pair.second) == created_id.end()){
			graph -> vertexes[edge_pair.second].key = edge_pair.second;
		}
		(graph -> edges)[edge_pair.first].push_back(&(graph->vertexes[edge_pair.second]));
	}
	cout << "Graph output begin" << endl;
    int i = 0;
    for(Vertex vt : (graph->vertexes)){
        cout << vt.key << '\t';
        for(Vertex *vt_p : (graph->edges)[vt.key]){
            cout << vt_p -> key << ",";
        }
        cout << endl;
    }
    cout << "Graph output end!" <<endl;
}

void init_graph(Graph *graph, string fn){	
	ifstream fr(fn, ifstream::in);
	string line;
	vector<string> edges;
	while(!fr.eof()){
		getline(fr, line);
		line.erase(line.find_last_not_of(" \n\r\t") + 1);
		edges.push_back(line);
	}
	fr.close();

	graph_add_edges(graph, edges);
}
void shortest_path(Graph &graph,  Vertex *b, Vertex *e){
    if (e == NULL){
        cout << "Not exists path!" << endl;
        return;
    }
    if(e == b){
        cout << b -> key << endl;
        return;
    }
    else {
        cout << e->key << '\t';
        shortest_path(graph, b, e->parent);
    }

}

int main(){
	Graph *graph = new Graph();
	string fn = "./edges_pairs.tsv";
	cout << "init_graph started!" << endl;
	init_graph(graph, fn);
	cout << "init_graph finished!" << endl;
	cout << "bfs started!" << endl;
	breadth_first_search(*graph, &(graph->vertexes[1]));
	cout << "bread_first_secarh run finished!" << endl;

    int start_idx, end_idx;
    cin >> start_idx >> end_idx;
    cout << "from: " << start_idx << " to: " << end_idx << endl;
    shortest_path(*graph, &(graph->vertexes[start_idx]), &(graph->vertexes[end_idx]));
    cout << endl;
}

