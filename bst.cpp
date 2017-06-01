#include<iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node{
	int key;
	struct Node *p;
	struct Node *lchild;
	struct Node *rchild;
	Node(int _key, struct Node *_p, struct Node *_lc, struct Node *_rc): key(_key), lchild(_lc), p(_p), rchild(_rc){}
};

class BST{
	public:
		BST(int * _arr, int _num) : arr(_arr), num(_num){
		}
		void InsertValue(int value){
			if(root == NULL){
				root = new struct Node(value, NULL, NULL, NULL);
				return;
			}
			struct Node *com_node = root, *pre_node = NULL;
			while(com_node != NULL){
				pre_node = com_node;
				if(com_node->key > value){
					com_node = com_node->lchild;
				}
				else{
					com_node = com_node->rchild;	
				}
			}
			struct Node *newNode = new struct Node(value, pre_node, NULL, NULL);
			if(pre_node -> key > value){
				pre_node->lchild = newNode;
			}
			else{
				pre_node->rchild = newNode;
			}
		}

		void InOrder(struct Node *cur_node){
			if(cur_node == NULL){
				return;
			}
			if(cur_node->lchild != NULL){
				InOrder(cur_node->lchild);
			}
			cout << cur_node->key << '\t';
			if(cur_node->rchild != NULL){
				InOrder(cur_node->rchild);
			}
		}

		void PreOrder(struct Node *root){
			if(root == NULL){
				return;
			}
			cout << root->key << '\t';
			PreOrder(root->lchild);
			PreOrder(root->rchild);
		}

		void PostOrder(struct Node *root){
			if(root == NULL){
				return;
			}
			PostOrder(root->rchild);
			cout << root->key << '\t';
			PostOrder(root->lchild);
		}

		void CreateBST(){
			for(int i = 0; i < num; i++){
				InsertValue(arr[i]);
			}
		}
		struct Node* Search_Recursively(int value, struct Node * com_node, int *num){
			if (com_node == NULL){
				return NULL;
			}
			else {
				if(com_node->key == value){
					(*num)++;
					Search_Recursively(value, com_node->lchild, num);
					Search_Recursively(value, com_node->rchild, num);
					return com_node;	
				}
				else if(com_node->key > value){
					return Search_Recursively(value, com_node->lchild, num);
				}
				else {
					return Search_Recursively(value, com_node->rchild, num);
				}
			}
		}

		struct Node * Search_NonRecursive(int value, int *occur_num){
			struct Node *cmp_node = root, *pre_node = NULL;
			struct Node *find_node = NULL;
			while(cmp_node != NULL){
				if (cmp_node->key == value){
					if (find_node == NULL){
						find_node = cmp_node;
					}
					(*occur_num) ++;
					cmp_node = cmp_node->rchild;
				}
				else if(cmp_node->key > value){
					cmp_node = cmp_node -> lchild;
				}
				else {
					cmp_node = cmp_node -> rchild;
				}
			}
			return find_node;
		}

		int Minimum_value(int *value){
			struct Node *cur_node = root;
			struct Node *pre_node = NULL;
			while(cur_node != NULL){
				pre_node = cur_node;
				cur_node = cur_node->lchild;
			}
			if (pre_node == NULL){
				return -1;
			}
			*value = pre_node->key;
			return 0;
		}

		int Maximum_value(int *max_value) {
			struct Node *cur_node = root;
			struct Node *pre_node = NULL;
			while(cur_node != NULL){
				pre_node = cur_node;
				cur_node = cur_node -> rchild;
			}
			if(pre_node == NULL){
				return -1;
			}
			*max_value = pre_node -> key;
			return 0;
		}
		struct Node * Maximum_Node(struct Node *node){
			if (node == NULL)
				return node;
			while(node->rchild != NULL){
				node = node->rchild;	
			}
			return node;
		}

		struct Node *Minmum_Node(struct Node *node){
			if (node == NULL){
				return NULL;
			}
			while(node -> lchild != NULL){
				node = node -> lchild;
			}
			return node;
		}

		struct Node *Predecessor_v2(struct Node *node){
			if (node == NULL){
				return node;
			}
			if(node -> lchild != NULL){
				return Maximum_Node(node -> lchild);
			}
			struct Node *par_node = node -> p;
			while(par_node != NULL && par_node -> lchild == node){
				node = par_node;
				par_node = par_node -> p;
			}
			return par_node;
		}

		struct Node * Predecessor(struct Node *node){
			struct Node *cur_node = node;
			struct Node *pre_node = NULL;
			if(cur_node->lchild != NULL){
				pre_node = Maximum_Node(cur_node->lchild);	
			}
			else {
				struct Node *parent_node = node->p;
				if (parent_node == NULL){
					return parent_node;
				}
				if(parent_node -> lchild == cur_node){
					struct Node * pp_node = parent_node -> p;
					while(pp_node != NULL && pp_node -> lchild == parent_node){
						parent_node = pp_node;
						pp_node = parent_node -> p;
					}
					return pp_node;
				}
				else{
					return cur_node -> p;
				}
			}
		}
		int Delete_Node(struct Node *node) {
			if (node == NULL) {
				return -1;
			}
			if (node->lchild == NULL && node->rchild == NULL) {
				if (node->p != NULL) {
					if (node->p->lchild == node) {
						node->p->lchild = NULL;
					}
					else {
						node->p->rchild = NULL;
					}
					return 0;
				}
				else {
					root = NULL;
					return -1;
				}
			}
			else if (node->lchild == NULL || node->rchild == NULL) {
				struct Node *parent_node = node->p;
				if (parent_node == NULL) {
					root = node->lchild == NULL ? node->rchild : node->lchild;
					delete node;
					return 0;
				}
				else {
					struct Node *no_null_node = node->lchild == NULL ? node->rchild : node->lchild;
					if (parent_node->lchild == node) {
						parent_node->lchild = no_null_node;
					}
					else {
						parent_node->rchild = no_null_node;
					}
					no_null_node->p = parent_node;
				}
				delete node;
				return 0;
			}
			else {
				struct Node *successor_node = Successor(node);
				node->key = successor_node->key;
				while (successor_node->lchild != NULL && successor_node->rchild != NULL) {
					successor_node = Successor(successor_node);
				}
				struct Node *no_null_node = successor_node->lchild != NULL ? successor_node->lchild : successor_node->rchild;
				struct Node *parent_node = successor_node->p;
				if (parent_node == NULL) {
					root = no_null_node;
				}
				else {
					if (parent_node->lchild == successor_node) {
						parent_node->lchild = no_null_node;
					}
					else {
						parent_node->rchild = no_null_node;
					}
					no_null_node->p = parent_node;
				}
				delete successor_node;
				return 0;
			}
		}

		struct Node *Successor(struct Node *node){
			if(node == NULL){
				return node;
			}
			if (node->rchild != NULL){
				return Minmum_Node(node->rchild);
			}
			struct Node * p_node = node -> p;
			while(p_node != NULL && p_node -> lchild != node){
				node = p_node;
				p_node = p_node -> p;
			}
			return p_node;
		}

		int Delete_Node_V2(struct Node *node){
			struct Node *parent_node;
			if (node == NULL){
				return -1;
			}
			if(node->lchild == NULL){
				parent_node = node->p;
				if(parent_node == NULL){
					root = node -> rchild;
					delete node;
					return 0;
				}
				if(parent_node->lchild == node){
					parent_node -> lchild = node -> rchild;
				}
				else{
					parent_node -> rchild = node -> rchild;
				}
				if(node->rchild != NULL){
					node->rchild->p = parent_node;
				}
				delete node;
				return 0;
			}
			else if (node -> lchild != NULL & node ->rchild == NULL){
				parent_node = node->p;
				if(parent_node == NULL){
					root = node->lchild;	
					delete node;
					return 0;
				}
				if(parent_node -> lchild == node){
					parent_node -> lchild = node->lchild;
				}
				else {
					parent_node -> rchild = node -> lchild;
				}
				if(node -> lchild != NULL){
					node -> lchild -> p = parent_node;
				}
				delete node;
				return 0;
			}
			else {
				struct Node *successor_node = Successor(node);
				if(successor_node == node->rchild) {
					parent_node = node->p;
					if(parent_node == NULL){
						root = node->rchild;
						delete node;
						return 0;
					}
					if(parent_node -> lchild == node){
						parent_node -> lchild = node -> rchild;
					}
					else {
						parent_node -> rchild = node -> rchild;
					}
					if (node->rchild != NULL){
						node->rchild -> p = parent_node;
					}
					delete node;
					return 0;
				}
				else{
					struct Node *successor_right = successor_node -> rchild;
					parent_node = successor_node-> p;
					if (parent_node == NULL){
						root = successor_right;
					}
					if(parent_node->lchild == successor_node){
						parent_node->lchild = successor_right;
					}
					else {
						parent_node->rchild = successor_right;
					}
					if(successor_right != NULL){
						successor_right -> p = parent_node;
					}
					node -> key = successor_node -> key;
					delete node;
					return 0;
				}
			}
		}
	public:
		struct Node *root = NULL;
	private:
		int *arr;
		int num;
};


int main(){
	int arr[] = { 6, 5, 7, 2, 5, 12, 9, 8 };
	BST bst(arr, sizeof(arr)/sizeof(arr[0]));
	cout << "create bst!" <<endl;
	bst.CreateBST();

	cout << "InOrder output!" << endl;
	bst.InOrder(bst.root);
	cout << endl;

	cout << "PreOrder output!" << endl;
	bst.PreOrder(bst.root);
	cout << endl;

	cout << "PostOrder output!" << endl;
	bst.PostOrder(bst.root);
	cout << endl;
	/*
	   int value;
	   string line;
	   while(getline(cin, line)){
	   int num = 0;
	   stringstream ss(line);
	   ss >> value;
	   cout << "Search: " << value << endl;
	//struct Node * search_node = bst.Search_Recursively(value, bst.root, &num);
	struct Node * search_node = bst.Search_NonRecursive(value, &num);
	if(search_node != NULL){
	cout << "Success " << search_node->key << " num: " << num << endl;
	}
	else {
	cout << "Not found!" << endl;
	}
	}
	*/

	int minimum;
	bool b = bst.Minimum_value(&minimum);
	if(!b){
		cout << "Minium_value is: " << minimum << endl;
	}

	int maximum;
	b = bst.Maximum_value(&maximum);
	if(!b){
		cout << "Maxium_value is: " << maximum << endl;
	}

	int value;
	string line;
	while(getline(cin, line)){
		stringstream ss(line);
		ss >> value;
		int num = 0;
		struct Node *search_node = bst.Search_NonRecursive(value, &num);
		if(search_node != NULL)
			cout << value << " Value foud success " << search_node->key << endl;
		else{
			cout << value << " Not found! Input a valid value!" << endl;	
			continue;
		}

		//struct Node *predecessor_node = bst.Predecessor(search_node);
		struct Node *predecessor_node = bst.Predecessor_v2(search_node);
		if(predecessor_node != NULL){
			cout << "Predecessor value is: " << predecessor_node->key << endl;
		}
		else {
			cout << "Predecessor not exists!" << endl;
		}

		/*
		   struct Node *successor_node = bst.Successor(search_node);
		   if(successor_node != NULL){
		   cout << "successor value is: " << successor_node->key << endl;
		   }
		   else {
		   cout << "successor not exists!" << endl;
		   }
		   */
	}
	return 0;
}
