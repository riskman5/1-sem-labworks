#include <iostream>

struct Node_info{
    int key = 0;
    int left;
    int right;


    void set_children(int left, int right) {
            this->left = left;
            this->right = right;
    }

    void set_key(int key){
        this->key = key;
    }
};

int set_current_number = 1;

void set_in_order(Node_info* model_tree, int current){
    if (current != -1){
        set_in_order(model_tree, model_tree[current].left);
        model_tree[current].set_key(set_current_number++);
        set_in_order(model_tree, model_tree[current].right);
    }
}


int main(){
    int n;
    std::cin>>n;

    Node_info model_tree[n];

    int left, right;

    for (int i = 0; i < n; i++) {
        std::cin >> left >> right;
        model_tree[i].set_children(left-1,right-1);
    }

    set_in_order(model_tree, 0);


    for (int i = 0; i < n; i++)
        std::cout<<model_tree[i].key << ' ';
}