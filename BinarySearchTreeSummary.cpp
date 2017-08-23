#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
	int key;
	struct Node *l = NULL;
	struct Node *p = NULL;
	struct Node *r = NULL;
	struct Node(int _key, struct Node *_l, struct Node *_r, struct Node *_p) : key(_key), l(_l), r(_r), p(_p) {}
	struct Node(int _key) : key(_key), l(NULL), r(NULL), p(NULL) {}
};

struct BST {
	struct Node *root = NULL;
};



void insertNode(int k, struct BST *bst) {
	struct Node * n = new struct Node(k);
	struct Node *c = bst->root, *p = NULL;
	while (c != NULL) {
		p = c;
		if(c->key <= k){
			c = c->r;
		}
		else {
			c = c->l;
		}
	}
	if (p == NULL) {
		bst->root = n;
	}
	else if (p->key > k) {
		p->l = n;
		n->p = p;
	}
	else {
		p->r = n;
		n->p = p;
	}
}

struct Node * maxiMum(struct Node *root) {
	if (root == NULL) {
		return NULL;
	}
	struct Node *p, *c = root;
	while (c != NULL) {
		p = c;
		c = c->r;
	}
	return p;
}

struct Node * miniMum(struct Node *root) {
	if (root == NULL) {
		return NULL;
	}
	struct Node *p, *c = root;
	while (c != NULL) {
		p = c;
		c = c->l;
	}
	return p;
}


struct Node * search(struct BST *bst, int k) {
	struct Node *c = bst->root;
	while (c != NULL && c->key != k) {
		if (c->key < k) {
			c = c->r;
		}
		else {
			c = c->l;
		}
	}
	return c;
}

void translate(struct BST *bst, struct Node *u, struct Node *v) {
	if (u->p != NULL) {
		if (u->p->l == u) {
			u->p->l = v;
		}
		else {
			u->p->r = v;
		}
	}
	else {
		bst->root = v;
	}
	if (v != NULL) {
		v->p = u->p;
	}
}

void deleteNode(struct BST *bst, struct Node *d) {
	if (bst->root == NULL) {
		return;
	}
	struct Node *c = bst->root;
	if (d->l == NULL) {
		translate(bst, d, d->r);
	}
	else if (d->r == NULL) {
		translate(bst, d, d->l);
	}
	else {
		struct Node * s = miniMum(d->r);
		if (s != d->r) {
			translate(bst, s, s->r);
			d->r->p = s;
			s->r = d->r;	
		}
		translate(bst, d, s);
		s->l = d->l;
		d->l->p = s;
	}
}


void layerOut(struct BST *bst) {
	queue <struct Node *> q;
	if (bst->root != NULL) {
		q.push(bst->root);
	}
	while (!q.empty()) {
		struct Node *c = q.front();
		q.pop();
		cout << c->key << '\t';
		if (c->l != NULL) {
			q.push(c->l);
		}
		if (c->r != NULL) {
			q.push(c->r);
		}
	}
	cout << endl;
}

struct Node * predecessor(struct BST *bst, struct Node *n) {
	if (n == NULL) {
		return n;
	}
	if (n->l != NULL) {
		return maxiMum(n->l);
	}
	else {
		struct Node * n_p = n->p;
		while (n_p != NULL && n_p->l == n) {
			n = n_p;
			n_p = n->p;
		}
		return n_p;
	}
	return NULL;
}

struct Node *successor(struct BST *bst, struct Node *n) {
	if (n == NULL) {
		return n;
	}
	if (n->r != NULL) {
		return miniMum(n->r);
	}
	else {
		struct Node *n_p = n->p;
		while (n_p != NULL && n_p->r == n) {
			n = n_p;
			n_p = n->p;
		}
		return n_p;
	}
	return NULL;
}

struct Node ** intervelNode(struct BST *bst, int k) {
	struct Node *n_p = NULL, *c = bst->root;
	while (c != NULL && c->key != k) {
		n_p = c;
		if (c->key < k) {
			c = c->r;
		}
		else {
			c = c->l;
		}
	}
	struct Node **pre_pos = new struct Node * [2];
	if (c == NULL) {
		pre_pos[0] = predecessor(bst, n_p);
		pre_pos[1] = successor(bst, n_p);
	}
	else {
		pre_pos[0] = predecessor(bst, c);
		pre_pos[1] = successor(bst, c);
	}
	return pre_pos;
}

int main() {

	BST  *bst = new struct BST;
	bst->root = NULL;
	int arr[] = {50, 30, 20, 40, 70, 60, 80};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		insertNode(arr[i], bst);
	}
	cout << "BST structure is :" << endl;
	layerOut(bst);
	struct Node * m = maxiMum(bst->root);
	cout << "Maximum number is :" << m->key << endl;
	
	/*
	struct Node ** pre_pos = intervelNode(bst, 65);
	if (pre_pos[0] != NULL) {
		cout << "Predecessor is : " << pre_pos[0]->key << endl;
	}
	else {
		cout << "Predecessor is not exists" << endl;
	}

	if (pre_pos[1] != NULL) {
		cout << "Successor is :" << pre_pos[1]->key << endl;
	}
	else {
		cout << "Successor is not exists!" << endl;
	}
	*/

	
	int k = -1;
	cin >> k;
	while (k != -1) {
		/*
		struct Node *s = search(bst, k);
		cout << "Search result key is : " << s->key << endl;
		//deleteNode(bst, s);
		//layerOut(bst);
		//struct Node *c = predecessor(bst, s);
		struct Node *c = successor(bst, s);
		if (c == NULL) {
			cout << "predecessor not exists!" << endl;
		}
		else
			cout << "predecessor key is :" << c->key << endl;
		
		*/
		struct Node ** arr = intervelNode(bst, k);
		if (arr[0] != NULL) {
			cout << "Predecessor is : " << arr[0]->key << endl;
		}
		else {
			cout << "Predecessor is not exists" << endl;
		}

		if (arr[1] != NULL) {
			cout << "Successor is :" << arr[1]->key << endl;
		}
		else {
			cout << "Successor is not exists!" << endl;
		}

		cin >> k;
	}

	//getchar();
	return 0;
}