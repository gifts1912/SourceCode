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
#include  "/usr/include/boost/algorithm/string.hpp"

using namespace std;

const Length = 1000;

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
	Vertex(int _key): key(_key){
	}
};

struct Graph{
	vector<Vertex> vertexes;
	vector< vector<Vertex *> > edges;
};



void breadth_first_search(Graph & graph, Vertex * start){
	for(int i = 0; i < graph.Vertexes.size(); i++){
		if (graph.Vertexes[i].key == start -> key){
			graph.Vertexes[i].color = Black;
		}
		else
			graph.Vertexes[i].color = White;
	}
	start.color = Grey;
	start.parent = NULL;
	start.discovery = 0;

	queue<Vertex *> qu;
	qu.push_back(start);
	while(!qu.empty()){
		Vertex * v = qu.front();
		qu.pop_front();
		int id = v->key;
		for(Vertex * v_ele: edges[id]){
			if (v_ele -> color == White){
				v_ele -> color = Grey;
				v_ele -> parent = v;
				v_ele -> discovery = v->discovery + 1;
				qu.push_back(v_ele);
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

void graph_add_edges(Graph *graph, vector<string> edges){
	set<int> vertex_stored;
	vector< pair<int, int> > edge_points;
	for (string edge: edges){
		vector<string> tokens;
		boost::split(tokens, line, boost::is_any_of("\t"));
		int begin_vertex_idx = int(tokens[0]);
		int end_vertex_idx = int(tokens[1]);
		tokens_set.insert(begin_vertex);
		tokens_set.insert(end_vertex);
		vector<Vertex> begin_vertex_iter = vertex_stored.find(begin_vertex_idx);
		if(begin_vertex_iter == vertex_stored.end()){
			Vertex vertex_b(begin_vertex);
			graph->vertexes.push_back(vertex_b);
		}
		
		vector<Vertex> end_vertex_iter = vertex_stored.find(end_vertex_idx);
		if(end_vertex_iter == vertex_stored.end()) {
			Vertex vertex_e(end_vertex);
			graph->vertexes.push_back(vertex_e);
		}
		
		edge_points.push_back(make_pair(begin_vertex, end_vertex));
	}
	
}

void init_graph(Graph *graph, string fn){	
	ifstream fr = ifstream(fn);
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

int main(){
	Graph *graph;
	string fn = "./edges_pairs.tsv";
	init_graph(graph, fn);
}

