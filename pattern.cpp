#include <iostream>
#include <string>
#include <queue>

using namespace std;

enum Color{Red, Black};

struct Node{
    int key;
    struct Node *p;
    struct Node *lchild;
    struct Node *rchild;
    Color color;
    Node(int _key, struct Node *_p, struct Node *_lchild, struct Node *_rchild, Color _color):key(_key), p(_p), lchild(_lchild), rchild(_rchild), color(_color){}

};

class RBT{
    public:
        struct Node *root;
        struct Node *nill;

    public:
        RBT(){
            nill = new struct Node(-1, NULL, NULL, NULL, Black);
            root = nill;
            nill -> lchild = root;
            nill -> rchild = root;
        }

        int Left_Rotate(struct Node * x_node){
            struct Node *y_node = x_node -> rchild;
            y_node -> p = x_node -> p;
            if(x_node -> p == nill){
                root = y_node;
            }
            else if (x_node == x_node->p->lchild){
                x_node->p->lchild = y_node;
            }
            else{
                x_node->p->rchild = y_node;
            }

            x_node -> lchild = y_node -> rchild;
            if(y_node -> rchild != nill){
                y_node -> rchild -> p = x_node;
            }

            y_node -> rchild = x_node;
            x_node -> p = y_node;

            return 0;
        }

        int Right_Rotate(struct Node * x_node){
            struct Node *y_node = x_node -> rchild;
            y_node -> p = x_node -> p;
            if(x_node -> p == nill){
                root = y_node;
            }
            else if(x_node == x_node -> p -> lchild){
                x_node -> p -> lchild = y_node;
            }
            else {
                x_node -> p -> rchild = y_node;
            }

            x_node -> rchild = y_node -> lchild;
            if(y_node->lchild != nill){
                y_node -> lchild -> p = x_node;
            }

            y_node -> lchild = x_node;
            x_node -> p = y_node;

            return 0;
        }

        void Fix_Up( struct Node * node){
            while(node -> p -> color == Red){
                struct Node *uncle_node;
                if(node -> p ->p -> lchild == node->p){
                    uncle_node = node->p->p -> rchild;
                    if(uncle_node -> color == Red){
                        node->p ->color = Black;
                        node->p -> p -> color = Red;
                        node = node->p->p;
                    }
                    else if(uncle_node -> color == Black){
                        if(node -> p -> rchild == node){
                            node = node->p;
                            Left_Rotate(node);
                        }
                        node -> p -> color = Black;
                        node -> p -> p -> color = Red;
                        Right_Rotate(node->p->p);
                    }
                }
                else{
                    uncle_node = node -> p -> p -> lchild;
                    if (uncle_node -> color == Red) {
                        node -> p -> color = Black;
                        uncle_node -> color = Black;
                        node->p -> p -> color = Red;
                        node = node -> p -> p;
                    }
                    else {
                        if (node == node -> p -> lchild){
                            Right_Rotate(node);
                            node = node -> rchild;
                        }

                        node -> p -> color = Black;
                        node -> p -> p -> color = Red;
                        Left_Rotate(node -> p);
                    }

                }
            }
            root->color = Black;
        }

        void Insert_Value( int value){
            struct Node * new_node = new struct Node(value, NULL, nill, nill, Red);
            struct Node *cmp_node = root, *pre_node = nill;
            while(cmp_node != nill){
                pre_node = cmp_node;
                if (cmp_node -> key >= value){
                    cmp_node = cmp_node -> lchild;
                }
                else {
                    cmp_node = cmp_node -> rchild;
                }
            }
            if(pre_node == nill){
                root = new_node;
                root -> p = nill;
            }
            else if(pre_node -> key >= value){
                pre_node -> lchild = new_node;
            }
            else {
                pre_node -> rchild = new_node;
            }
            new_node -> p = pre_node;

            Fix_Up(new_node);
        }

        void Layer_Out(){
            if (root == nill) {
                return;
            }
            queue<struct Node *> nodes;
            nodes.push(root);
            struct Node *cur_node;
            if (!nodes.empty()){
                cur_node = nodes.front();
                cout << cur_node -> key << '\t';
                if(cur_node -> lchild != nill) {
                    nodes.push(cur_node -> lchild);
                }
                else {
                    nodes.push(cur_node -> rchild);
                }
                nodes.pop();
            }
        }

};


int main(){
    RBT rbt;
    int arr[] = {7, 4, 11, 3, 6, 9, 18, 2, 14, 19, 12, 17, 22, 20};
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        rbt.Insert_Value(arr[i]);
        cout << arr[i] << " tree: ";
        rbt.Layer_Out();
    }
    return 0;
}