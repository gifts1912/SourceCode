#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>


using namespace std;

struct Node {
	Node(int value) {
		key = value;
		parent = NULL;
		left = NULL;
		right = NULL;
	}
	int key;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

class RedBlackTree {
private:
	struct Node *root;
	struct Node *nil = new struct Node(-1);

public:
	RedBlackTree():root(NULL){}

	void Left_Rotation(struct Node *x) {
		struct Node *y = x->right;
		x->right = y->left;
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		}
		else if (x->parent->left == x) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		if (y->left != NULL) {
			y->left->parent = x;
		}
		y->left = x;
		x->parent = y;
	}

	void Right_Rotation(struct Node *x) {
		struct Node *y = x->left;
		x->left = y->right;
		y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		}
		else if (x->parent->left == x) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}
	
};

class BinarySearchTree {
private:
	struct Node *root;

public:
	BinarySearchTree() :root(NULL) {}

	void Add_Node(int value) {
		struct Node * node = new struct Node(value);
		if (root == NULL) {
			root = node;
			return;
		}

		struct Node *pNode = root;
		while (true) {
			if (pNode->key >= value) {
				if (pNode->left != NULL) {
					pNode = pNode->left;
				}
				else {
					pNode->left = node;
					node->parent = pNode;
					return;
				}
			}
			else {
				if (pNode->right != NULL) {
					pNode = pNode->right;
				}
				else {
					pNode->right = node;
					node->parent = pNode;
					return;
				}
			}
		}

	}

	void Tree_Delete(int value) {
		struct Node * pNode = Search(value);
		if (pNode == NULL) {
			return;
		}
		struct Node *preNode = NULL;
		if (pNode->left == NULL && pNode->right == NULL) {
			preNode = pNode->parent;
			if (preNode == NULL) {
				root = NULL;
				return;
			}
			if (preNode->left == pNode) {
				preNode->left = NULL;
			}
			else {
				preNode->right = NULL;
			}
			return;
		}
		else if ((pNode->left != NULL && pNode->right == NULL) || (pNode->right != NULL && pNode->left == NULL)) {
			preNode = pNode->parent;
			if (preNode == NULL) {

			}
			else {
				if (pNode->left != NULL) {
					if (preNode->left == pNode) {
						preNode->left = pNode->left;
					}
					else {
						preNode->right = pNode->left;
					}
				}
				else {
					if (preNode->left == pNode) {
						preNode->left = pNode->right;
					}
					else
						preNode->right = pNode->right;
				}
			}
		}
		else {
			struct Node *succ_node = Successor(value);
			pNode->key = succ_node->key;
			if (succ_node->parent->left == succ_node) {
				succ_node->parent->left = succ_node->right;
			}
			else {
				succ_node->parent->right = succ_node->right;
			}
		}
	}

	void Tree_LayerOut() {
		queue<struct Node *> queues;
		queues.push(root);
		while (!queues.empty()) {
			struct Node *curNode = queues.front();
			cout << curNode->key << " ";
			if (curNode->left != NULL) {
				queues.push(curNode->left);
			}
			if (curNode->right != NULL) {
				queues.push(curNode->right);
			}
		}
	}

	struct Node * Search(int value) {
		struct Node *pNode = root;
		while (pNode != NULL) {
			if (pNode->key == value) {
				break;
			}
			else if (pNode->key < value) {
				pNode = pNode->right;
			}
			else {
				pNode = pNode->left;
			}
		}
		return pNode;
	}

	void In_Order_Recursive(struct Node *root) {
		if (root == NULL) {
			return;
		}
		In_Order_Recursive(root->left);
		cout << root->key << " ";
		In_Order_Recursive(root->right);
	}

	void In_Order_Iterative() {
		struct Node *pos = root;
		struct Node *pre = NULL;
		if (pos == NULL)
			return;
		while (true) {
			if (pre == NULL) {
				if (pos->left != NULL) {
					pos = pos->left;
					continue;
				}
				cout << pos->key << " ";
				if (pos->right != NULL) {
					pre = NULL;
					pos = pos->right;
					continue;
				}
			}
			else {
				if (pre == pos->left) {
					cout << pos->key << " ";
					if (pos->right != NULL) {
						pre = NULL;
						pos = pos->right;
						continue;
					}
				}
			}

			if (pos->parent != NULL) {
				pre = pos;
				pos = pos->parent;
			}
			else {
				return;
			}
		}
	}
	void In_Order_Stack() {
		struct Node * pNode = root;
		if (pNode == NULL) {
			return;
		}
		stack<struct Node*> nodes;
		while (true) {
			while (pNode != NULL) {
				nodes.push(pNode);
				pNode = pNode->left;
			}
			while (!nodes.empty()) {
				struct Node *curNode = nodes.top();
				cout << curNode->key << " ";
				nodes.pop();
				if (curNode->right != NULL) {
					pNode = curNode->right;
					break;
				}
				else {
					continue;
				}
			}
			if (nodes.empty() && pNode == NULL) {
				break;
			}
		}
	}
	struct Node *Precessor(int value) {
		struct Node *pNode = Search(value);
		if (pNode == NULL) {
			return NULL;
		}
		if (pNode->left != NULL) {
			return Tree_Maximum(pNode->left);
		}
		struct Node *preNode = pNode->parent;
		while (preNode != NULL && preNode->left == pNode) {
			pNode = preNode;
			preNode = pNode->parent;
		}
		return preNode;
	}

	struct Node * Successor(int value) {
		struct Node *pNode = Search(value);
		if (pNode == NULL) {
			return NULL;
		}
		if (pNode->right != NULL) {
			return Tree_Minimum(pNode->right);
		}
		struct Node *preNode = pNode->parent;
		while (preNode != NULL && preNode->right == pNode) {
			pNode = preNode;
			preNode = pNode->parent;
		}
		return preNode;
	}

	struct Node* Tree_Minimum(struct Node *root) {
		struct Node *pNode = root;
		while (pNode->left != NULL) {
			pNode = pNode->left;
		}
		cout << "Minimum value: " << pNode->key << endl;
		return pNode;
	}

	struct Node * Tree_Maximum(struct Node *root) {
		struct Node *pNode = root;
		while (pNode->right != NULL) {
			pNode = pNode->right;
		}
		cout << "Maximum value: " << pNode->key << endl;
		return pNode;
	}

	void In_Order_Stack_v2() {
		struct Node * pNode = root;
		stack<struct Node *> nodes;
		while (true) {
			while (pNode != NULL) {
				nodes.push(pNode);
				if (pNode->left != NULL) {
					pNode = pNode->left;
				}
				else {
					break;
				}
			}
			while (!nodes.empty() && nodes.top()->right == NULL) {
				pNode = nodes.top();
				cout << pNode->key << " ";
				nodes.pop();
			}
			if (nodes.empty()) {
				break;
			}
			else {
				pNode = nodes.top();
				cout << pNode->key << " ";
				nodes.pop();
				pNode = pNode->right;
			}
		}
	}

	void In_Order() {
		//In_Order_Iterative();
		In_Order_Stack();
		//In_Order_Stack_v2();
		//In_Order_Iterative_v2();
	}

};


int main() {
	BinarySearchTree bst;
	int values[] = { 3, 4, 5, 1, 2, 10, 6, 9, 8, 12, 7, 11 };
	for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
		bst.Add_Node(values[i]);
	}

	bst.In_Order();
	cout << endl;

	cout << "Tree delete 2" << endl;
	bst.Tree_Delete(2);
	bst.In_Order();
	cout << endl;
	/*
	struct Node * pNode = bst.Search(18);
	if (pNode == NULL) {
		cout << "Null" << endl;
	}
	else {
		cout << pNode->key << endl;
	}

	//bst.Tree_Minimum();
	//bst.Tree_Maximum();
	cout << endl << "Successor" << endl;
	pNode = bst.Successor(7);
	if (pNode == NULL) {
		cout << "Null" << endl;
	}
	else
		cout << pNode->key << endl;

	cout << endl << "Precessor" << endl;
	pNode = bst.Precessor(1);
	if (pNode == NULL) {
		cout << "Null" << endl;
	}
	else
		cout << pNode->key << endl;
	*/
	getchar();
	return 0;
}