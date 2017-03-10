#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;


enum Color {
	Red,
	Black
};
struct Node {
	int key;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
	Color col = Red;
	struct Node(int _key, Color _col, struct Node* _nil) : key(_key), col(_col), parent(_nil), left(_nil), right(_nil) {
	}
};


class Red_Black_Tree {
private:
	struct Node *nil = new struct Node(-1, Black, NULL);
	struct Node *root = nil;

public:
	void Tree_Insert(int _key) {
		struct Node *preNode = nil;
		struct Node *curNode = root;
		while (curNode != nil) {
			preNode = curNode;
			if (curNode->key < _key) {
				curNode = curNode->right;
			}
			else {
				curNode = curNode->left;
			}
		}
		struct Node *newNode = new struct Node(_key, Red, nil);
		if (preNode == nil) {
			root = newNode;
			newNode->col = Black;
		}
		else {
			newNode->parent = preNode;
			if (preNode->key >= _key) {
				preNode->left = newNode;
			}
			else {
				preNode->right = newNode;
			}
			Tree_Fix(newNode);
		}
	}

private:
	void Left_Rotation(struct Node *curNode) {
		struct Node * rcNode = curNode->right;
		rcNode->parent = curNode->parent;
		if (curNode->parent == nil) {
			root = rcNode;
		}
		if (curNode->parent->left = curNode) {
			curNode->parent->left = rcNode;
		}
		else {
			curNode->parent->right = rcNode;
		}

		if (rcNode->left != nil) {
			rcNode->left->parent = curNode;
		}
		curNode->right = rcNode;

		rcNode->left = curNode;
		curNode->parent = rcNode;
	}

	void Right_Rotation(struct Node* curNode) {
		struct Node *lcNode = curNode->left;
		lcNode->parent = curNode->parent;
		if (curNode->parent == nil) {
			root = lcNode;
		}
		if (curNode->parent->left == curNode) {
			curNode->parent->left = lcNode;
		}
		else {
			curNode->parent->right = lcNode;
		}
		curNode->left = lcNode->right;
		if (lcNode->right != nil) {
			lcNode->right->parent = curNode;
		}
		lcNode->right = curNode;
		curNode->parent = lcNode;
	}



	void Tree_Fix(struct Node * curNode) {
		while (curNode->parent->col == Red) {
			struct Node * pNode = curNode->parent;
			struct Node* gpNode = curNode->parent->parent;
			struct Node *uncleNode;
			if (gpNode->left == pNode) {
				uncleNode = gpNode->right;
				if (uncleNode->col == Red) {
					//case 1
					pNode->col = Black;
					uncleNode->col = Black;
					gpNode->col = Red;
					curNode = gpNode;
				}
				else {
					if (pNode->right == curNode) {
						Left_Rotation(pNode);
						curNode = pNode;
						pNode = curNode->parent;
					}
					pNode->col = Black;
					gpNode->col = Red;
					Right_Rotation(gpNode);
				}
			}
			else {
				uncleNode = gpNode->left;
				if (uncleNode->col == Red) {
					//case1
					pNode->col = Black;
					uncleNode->col = Black;
					gpNode->col = Red;
					curNode = gpNode;
				}
				else {
					//case2 & case3
					if (pNode->left == curNode) {
						Right_Rotation(pNode);
						curNode = pNode;
						pNode = curNode->parent;
					}
					pNode->col = Black;
					gpNode->col = Red;
					Left_Rotation(gpNode);
				}
			}
		}
		root->col = Black;
	}

	void Tree_LayerOut() {
		queue<struct Node*> nodes;
		nodes.push(root);
		struct Node *curNode;
		while (!nodes.empty()) {
			curNode = nodes.front();
			nodes.pop();
			cout << curNode->key << ":" << curNode->col << " ";
			if (curNode->left != NULL) {
				nodes.push(curNode->left);
			}
			if (curNode->right != NULL) {
				nodes.push(curNode->right);
			}
		}
		cout << endl;
	}
public:
	void Init_RBT(int *arr, int n) {
		for (int i = 0; i < n; i++) {
			Tree_Insert(arr[i]);
		}
		
		Tree_LayerOut();
	}
};

int main() {
	int arr[] = { 11, 2, 14, 1, 7, 15, 5, 8, 4 };
	Red_Black_Tree rbt;
	rbt.Init_RBT(arr, sizeof(arr)/sizeof(arr[1]));
	return 0;
}