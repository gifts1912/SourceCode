//
//  main.cpp
//  IntroductionToAlgorithm
//
//  Created by FrankLiu on 2017/8/1.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <set>
#include <list>

using namespace std;


enum Color {Red, Black, Grey};

struct VertexNode{
    int key;
    list<int> edges;
    VertexNode(int _key, list<int> _edges){
        key = _key;
        edges = _edges;
    }
};

class Graph{
public:
    int n;
    struct VertexNode *vertexes = NULL;

public:
    Graph(int n): n(n){
        vertexes = new VertexNode[n + 1];
        vertexes[1] = struct VertexNode(1, list<int>(2, 5));
    }
    
    void BFS(int start_idx){
        if(start_idx >= n){
            cout << "No vertex at index start_idx!" << endl;
            return;
        }
      
        set<int> unvisited;
        for(int i = 0; i < n; i++){
            if (i != start_idx){
                unvisited.insert(i);
            }
        }
        set<int> visited;
        visited.insert(start_idx);
        queue<int> qvn;
        qvn.push(start_idx);
        
        struct VertexNode vn = vertexes[start_idx];
   
        while(!qvn.empty() || !unvisited.empty()){
            if(qvn.empty()){
                qvn.push(*unvisited.begin());
                visited.insert(*unvisited.begin());
                unvisited.erase(unvisited.begin());
            }
            int vn_idx = qvn.front();
            qvn.pop();
            cout << vn_idx << '\t';
            list<int> edges_cur = vertexes[vn_idx].edges;
            for(list<int>::iterator iter = edges_cur.begin(); iter != edges_cur.end(); iter++){
                int vn_next = *iter;
                set<int>::iterator iter_find = visited.find(vn_next);
                if(iter_find == visited.end()){
                    qvn.push(vn_next);
                    visited.insert(vn_next);
                    unvisited.erase(unvisited.find(vn_next));
                }
            }
        }
        cout << endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
