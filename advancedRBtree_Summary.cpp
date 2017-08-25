#include <iostream>
#include <queue>

using namespace std;

enum Color {
	RED,
	BLACK
};

struct Node {
	int k;
	struct Node *l, *r, *p;
	enum Color c;
	int size;
	Node(int _k, struct Node *_l, struct Node *_r) :k(_k), c(RED), l(_l), r(_r), p(NULL), size(1){}
	Node():k(-1), c(RED), l(NULL), r(NULL), p(NULL), size(1){}
};

struct RBT {
	struct Node *root;
	struct Node *nil;
	RBT() {
		nil = new Node;
		nil->c = BLACK;
		nil->l = nil;
		nil->r = nil;
		nil->p = nil;
		nil->size = 0;
		root = nil;
	}
};

void leftRotate(struct RBT *rbt, struct Node *n) {
	struct Node *y = n->r;
	if (n->p == rbt->nil) {
		rbt->root = y;
	}
	else {
		if (n->p->l == n) {
			n->p->l = y;
		}
		else {
			n->p->r = y;
		}
	}
	y->p = n->p;
	n->r = y->l;
	y->l->p = n;
	y->l = n;
	n->p = y;

	y->size = n->size;
	n->size = n->l->size + n->r->size + 1;
}

void rightRotate(struct RBT *rbt, struct Node *n) {
	struct Node *y = n->l;
	if (n->p == rbt->nil) {
		rbt->root = y;
	}
	else {
		if (n->p->l = n) {
			n->p->l = y;
		}
		else {
			n->p->r = y;
		}
	}
	y->p = n->p;
	n->p = y;
	n->l = y->r;
	y->r->p = n;
	y->r = n;
	
	y->size = n->size;
	n->size = n->l->size + n->r->size + 1;
}


void fixUp(struct RBT * rbt, struct Node *n) {
	while (n->p->c == RED) {
		if (n->p == n->p->p->l) {
			struct Node *y = n->p->p->r;
			if (y->c == RED) {
				y->c = BLACK;
				n->p->c = BLACK;
				n->p->p->c = RED;
				n = n->p->p;
			}
			else {
				if (n->p->r == n) {
					n = n->p;
					leftRotate(rbt, n);
				}
				n->p->c = BLACK;
				n->p->p->c = RED;
				rightRotate(rbt, n->p->p);
			}
		}
		else {
			struct Node *y = n->p->p->l;
			if (y->c == RED) {
				y->c = BLACK;
				n->p->c = BLACK;
				n->p->p->c = RED;
				n = n->p->p;
			}
			else {
				if (n->p->l == n) {
					n = n->p;
					rightRotate(rbt, n);
				}
				n->p->c = BLACK;
				n->p->p->c = RED;
				leftRotate(rbt, n->p->p);
			}
		}
	}
	rbt->root->c = BLACK;
}

void insert(struct RBT *rbt, int _k) {
	struct Node *n = new struct Node(_k, rbt->nil, rbt->nil);
	struct Node *nc = rbt ->root, *np = rbt->nil;
	while (nc != rbt->nil) {
		nc->size++;
		np = nc;
		if (nc->k <= _k) {
			nc = nc->r;
		}
		else {
			nc = nc->l;
		}
	}
	if (np == rbt->nil) {
		rbt->root = n;
		n->c = BLACK;
		n->p = rbt->nil;
		rbt->nil->r = rbt->root;
		rbt->nil->l = rbt->root;
		return;
	}
	if (np->k <= _k) {
		np->r = n;
		n->p = np;
	}
	else {
		np->l = n;
		n->p = np;
	}
	fixUp(rbt, n);
}

struct Node * search(struct RBT *brt, int v) {
	struct Node *nc = brt -> root;
	while (nc != brt -> nil) {
		if (nc->k == v) {
			break;
		}
		else if (nc->k < v) {
			nc = nc->r;
		}
		else {
			nc = nc->l;
		}
	}
	return nc;
}

void RB_translate(struct RBT *brt, struct Node *u, struct Node *v) {
	if (u->p == brt->nil) {
		brt->root = v;
	}
	else {
		if (u->p->l == u) {
			u->p->l = v;
		}
		else {
			u->p->r = v;
		}
	}
	v->p = u->p;
}

struct Node * minimum(struct RBT *rbt, struct Node *n) {
	if (n == rbt->nil) {
		cout << n->k << " minimum doesn't exists!" << endl;
		return NULL;
	}
	struct Node * nc = n;
	while (nc->l != rbt->nil) {
		nc = nc->l;
	}
	return nc;
}

void deleteFixUp(struct RBT *rbt, struct Node *n) {
	while (n != rbt->root && n->c == BLACK) {
		if (n = n->p->l) {
			struct Node * s = n->p->r;
			if (s->c == RED) {
				s->c = BLACK;
				n->p->c = RED;
				leftRotate(rbt, n->p);
				s = n->p->r;
			}
			if (s->l->c == BLACK && s->r->c == BLACK) {
				s->c = RED;
				n = n->p;
			}
			else {
				if (s->l->c == RED) {
					s->l->c = BLACK;
					s->c = RED;
					leftRotate(rbt, s);
					s = s->p;
				}
				s->c = n->p->c;
				s->r->c = BLACK;
				n->p->c = BLACK;
				leftRotate(rbt, n->p);
				n = rbt->root;
			}
		}
		else {
			struct Node *s = n->p->r;
			if (s->c == RED) {
				s->c = BLACK;
				n->p->c = RED;
				rightRotate(rbt, n->p);
				s = n->p->l;
			}
			if (s->l->c == BLACK && s->r->c == BLACK) {
				s->c = RED;
				n = n->p;
			}
			else {
				if (s->r->c == RED) {
					s->c = RED;
					s->r->c = BLACK;
					leftRotate(rbt, s);
					s = s->p;
				}
				s->l->c = BLACK;
				s->c = n->p->c;
				n->p->c = BLACK;
				rightRotate(rbt, n->p);
				n = rbt->root;
			}
		}
	}
	n->c = BLACK;
}

void deleteNode(struct RBT *brt, int v) {
	struct Node *n = search(brt, v);
	if (n == brt -> nil) {
		cout << v << " not found in RB tree!" << endl;
		return;
	}

	struct Node *y = n;
	struct Node * x;
	Color y_c_o = y->c;
	if (y->r == brt->nil) {
		x = y->l;
		RB_translate(brt, y, x);
	}
	else if (y->l == brt->nil) {
		x = y->r;
		RB_translate(brt, y, x);
	}
	else {
		y = minimum(brt, n->r);
		y_c_o = y->c;
		x = y->r;
		if (y->p == n) {
			x->p = y;
		}
		else {
			RB_translate(brt, y, x);
			y->r = n->r;
			y->r->p = y;
		}
		y->l = n->l;
		y->l->p = y;
		y->size = n->size;
		RB_translate(brt, n, y);
		y->c = n->c;
	}
	
	struct Node *n_u = x->p;
	while (n_u != brt->nil) {
		n_u->size--;
		n_u = n_u->p;
	}
	if(y_c_o == BLACK)
		deleteFixUp(brt, x);
}

void outLayer(struct RBT *rbt) {
	queue<struct Node *> nq;
	if (rbt->root != rbt->nil) {
		nq.push(rbt->root);
	}
	cout << "Out layer of RB tree is :" << endl;
	while (!nq.empty()) {
		struct Node *c = nq.front();
		nq.pop();
		cout << c->k << ':' << c->c << ':' <<  c->size << '\t';
		if (c->l != rbt->nil) {
			nq.push(c->l);
		}
		if (c->r != rbt->nil) {
			nq.push(c->r);
		}
	}
	cout << endl;
}

struct Node *searchithNode(struct RBT *rbt, int k) {
	struct Node *n_c = rbt->root;
	while (n_c != rbt->nil) {
		if (n_c -> l -> size + 1 == k) {
			return n_c;
		}
		else if (n_c->l->size + 1 < k) {
			n_c = n_c->r;
			k = k - n_c->l->size - 1;
		}
		else {
			n_c = n_c->l;
		}
	}
	cout << "kth node doesn't exist!" << endl;
	return NULL;
}

int searchNodeSeq(struct RBT *rbt, struct Node *n) {
	int ith = n->l->size + 1;
	while (n != rbt->nil) {
		if ( n->p != rbt->nil && n == n->p->r) {
			ith += n->p->l->size + 1;
		}
		n = n->p;
	}
	return ith;
}

int main() {
	struct RBT *rbt = new struct RBT();
	//int arr[] = { 'B' , 'A', 'D', 'C', 'E' };
	int arr[] = { 7, 3, 18, 10, 22, 8, 11, 26 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		insert(rbt, arr[i]);
	}
	outLayer(rbt);
	
	struct Node * ith_n = searchithNode(rbt, 2);
	if(ith_n != NULL)
		cout << "The ith value in red black tree is: " << ith_n->k << endl;

	int ith = searchNodeSeq(rbt, ith_n);
	if (ith != -1)
		cout << "Node is the " << ith << " position!" << endl;


	int k = 20;
	cin >> k;
	while (k != -1) {
		deleteNode(rbt, k);
		outLayer(rbt);

		struct Node * ith_n = searchithNode(rbt, 2);
		if (ith_n != NULL)
			cout << "The ith value in red black tree is: " << ith_n->k << endl;

		int ith = searchNodeSeq(rbt, ith_n);
		if (ith != -1)
			cout << "Node is the " << ith << " position!" << endl;

		cin >> k;
	}
	

	return 0;
}
