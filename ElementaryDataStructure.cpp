#include <iostream>
#include <cstdlib>


#define MAX_SIZE 10

int cells[MAX_SIZE*3];

int empty_list = -1;
int free_list;
#define NEXT(i) cells[i + 1]
#define PREV(i) cells[i + 2]
#define KEY(i) cells[i]



using namespace std;

void init_storage() {
	int i;
	for (i = 0; i < MAX_SIZE * 3; i += 3) {
		NEXT(i) = i + 3;
		if (i > 0) {
			PREV(i) = i - 3;
		}
	}
	NEXT(i) = -1;
	PREV(0) = -1;
	free_list = 0;
}


int Allocate_Object() {
	if (free_list == -1) {
		cerr << "Storage full" << endl;
		exit(1);
	}
	int x = free_list;
	free_list = NEXT(x);
	return x;
}

void Free_Object(int i) {
	NEXT(i) = free_list;
	free_list = i;
}

int cons(int key, int list) {
	int i = Allocate_Object();
	NEXT(i) = list;
	PREV(i) = -1;
	KEY(i) = key;

	if (list != -1) {
		PREV(list) = i;
	}
	return i;
}

void Delete(int l) {
	if (NEXT(l) != -1) {
		PREV(NEXT(l)) = PREV(l);
	}
	if (PREV(l) != -1) {
		NEXT(PREV(l)) = NEXT(l);
	}
	Free_Object(l);
}

/*
int main() {

	return 0;
}
*/