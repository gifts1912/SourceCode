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
		curNode->right = rcNode->left;
		if (rcNode->left != nil) {
			rcNode->left->parent = curNode;
		}

		rcNode->parent = curNode->parent;
		if (curNode->parent == nil) {
			root = rcNode;
		}
		else if (curNode->parent->left = curNode) {
			curNode->parent->left = rcNode;
		}
		else {
			curNode->parent->right = rcNode;
		}

		rcNode->left = curNode;
		curNode->parent = rcNode;
	}

	void Right_Rotation(struct Node* curNode) {
		struct Node *lcNode = curNode->left;
		curNode->left = lcNode->right;
		if (lcNode->right != nil) {
			lcNode->right->parent = curNode;
		}
		lcNode->parent = curNode->parent;
		if (curNode->parent == nil) {
			root = lcNode;
		}
		else if (curNode->parent->left == curNode) {
			curNode->parent->left = lcNode;
		}
		else {
			curNode->parent->right = lcNode;
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


	void Transplate(struct Node *uNode, struct Node *vNode) {
		if (uNode->parent == nil) {
			root = vNode;
		}
		else if (uNode->parent->left == uNode) {
			uNode->parent->left = vNode;
		}
		else {
			uNode->parent->right = vNode;
		}
		vNode->parent = uNode->parent;
	}

	struct Node *Tree_Successor(struct Node *subRoot) {
		struct Node *preNode = nil;
		struct Node *curNode = subRoot;
		while (curNode != nil) {
			preNode = curNode;
			curNode = curNode->left;
		}
		return preNode;
	}

	void RB_Tree_FixUp(struct Node *curNode) {
		while (curNode != root && curNode->col == Black) {
			if (curNode->parent->left == curNode) {
				struct Node *siblingNode = curNode->parent->right;
				if (siblingNode->col == Red) {
					curNode->parent->col = Red;
					siblingNode->col = Black;
					Left_Rotation(curNode->parent);
					siblingNode = curNode->parent->right;
				}
				if (siblingNode->left->col == Black && siblingNode->right->col == Black) {
					curNode = curNode->parent;
					siblingNode->col = Red;
				}
				else {
					if (siblingNode->right->col == Black) {
						siblingNode->left->col = Black;
						siblingNode->col = Red;
						Right_Rotation(siblingNode);
						siblingNode = curNode->parent->right;
					}
					siblingNode->col = curNode->parent->col;
					curNode->parent->col = Black;
					Left_Rotation(curNode->parent);
					siblingNode->right->col = Black;
					curNode = root;
				}
			}
			else {
				struct Node *siblingNode = curNode->parent->left;
				if (siblingNode->col == Red) {
					curNode->parent->col = Red;
					siblingNode->col = Black;
					Right_Rotation(curNode->parent);
					siblingNode = curNode->parent->left;
				}
				if (siblingNode->left->col == Black && siblingNode->right->col == Black) {
					siblingNode->col = Red;
					curNode = curNode->parent;
				}
				else {
					if (siblingNode->left->col == Black) {
						siblingNode->right->col = Black;
						siblingNode->col = Red;
						Left_Rotation(siblingNode);
						siblingNode = curNode->parent->left;
					}
					siblingNode->col = curNode->parent->col;
					siblingNode->left->col = Black;
					curNode->parent->col = Black;
					Right_Rotation(curNode->parent);
					curNode = root;
				}
			}
		}
		curNode->col = Black;
	}
	struct Node *Tree_Search(int value) {
		struct Node *curNode = root;
		while (curNode != nil) {
			if (curNode->key == value) {
				break;
			}
			else if (curNode->key < value) {
				curNode = curNode->right;
			}
			else {
				curNode = curNode->left;
			}
		}
		return curNode;
	}

public:
	void Tree_LayerOut() {
		queue<struct Node*> nodes;
		nodes.push(root);
		struct Node *curNode;
		while (!nodes.empty()) {
			curNode = nodes.front();
			nodes.pop();
			cout << curNode->key << ":" << curNode->col << " ";
			if (curNode->left != nil) {
				nodes.push(curNode->left);
			}
			if (curNode->right != nil) {
				nodes.push(curNode->right);
			}
		}
		cout << endl;
	}

	void Init_RBT(int *arr, int n) {
		for (int i = 0; i < n; i++) {
			Tree_Insert(arr[i]);
		}

		Tree_LayerOut();
	}

	void Tree_Delete(int value) {
		struct Node *delNode = Tree_Search(value);
		struct Node *curNode = delNode;
		enum Color repNodeOriCol = curNode->col;
		struct Node *replaceNode;
		if (curNode->left == nil) {
			replaceNode = curNode->right;
			Transplate(curNode, replaceNode);
		}
		else if (curNode->right == nil) {
			replaceNode = curNode->left;
			Transplate(curNode, replaceNode);
		}
		else {
			replaceNode = Tree_Successor(curNode->right);
			struct Node *repChildNode = replaceNode->right;
			if (replaceNode->parent == curNode) {
				repChildNode->parent = replaceNode;
			}
			else {
				Transplate(replaceNode, repChildNode);
				replaceNode->right = curNode->right;
				replaceNode->right->parent = replaceNode;
			}
			Transplate(curNode, replaceNode);
			replaceNode->left = curNode->left;
			replaceNode->left->parent = replaceNode;
			repNodeOriCol = replaceNode->col;
		}
		if (repNodeOriCol == Black) {
			RB_Tree_FixUp(replaceNode);
		}
	}
};

int main() {
	int arr[] = { 11, 2, 14, 1, 7, 15, 5, 8, 4 };
	Red_Black_Tree rbt;
	rbt.Init_RBT(arr, sizeof(arr) / sizeof(arr[1]));
	rbt.Tree_Delete(11);
	rbt.Tree_LayerOut();
	getchar();
	
	return 0;
}
