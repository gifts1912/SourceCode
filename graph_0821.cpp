#include <iostream>
#include <limits>
#include <cstdio>

#define V 4
using namespace std;

const int INI = numeric_limits<int>::max();

void FloydWarshall(int matrix[][V]) {
	int out[V][V];
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

int main() {
 int graph[V][V] = { { 0,   5,  INI, 10 },
	{ INI, 0,   3, INI },
	{ INI, INI, 0,   1 },
	{ INI, INI, INI, 0 }
	};

	FloydWarshall(graph);
	getchar();
	return 0;

}
