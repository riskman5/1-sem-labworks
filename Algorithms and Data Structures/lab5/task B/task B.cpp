#include <iostream>

struct Node{
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
    int index;
    int key;

    void set_all(int key, int left_ind, int right_ind, Node* a){
        this->key = key;
        if (left_ind != -1)
            this->left = &a[left_ind];
        if (right_ind != -1)
            this->right = &a[right_ind];
    }

};

int get_height(Node *x) {
    if (x != nullptr)
        return x->height;
    else
        return 0;
}

int bfactor(Node* current_node){
    return get_height(current_node->right) - get_height(current_node->left);
}

Node* rotateleft(Node* current_node){
    Node* new_current_node = current_node->right;
    current_node->right = new_current_node->left;
    new_current_node->left = current_node;
    return new_current_node;
}

Node* rotateright(Node* current_node){
    Node* new_curent_node = current_node->left;
    current_node -> left = new_curent_node->right;
    new_curent_node -> right = current_node;
    return new_curent_node;
}

void pre_order_traversal_set(Node* current_node, int& index) {
    if (current_node != nullptr) {
        current_node->index = index++;
        pre_order_traversal_set(current_node->left, index);
        pre_order_traversal_set(current_node->right, index);
    }
}

void pre_order_traversal_get(Node* current_node){
    if (current_node != nullptr) {
        std::cout << current_node->key << ' ';
        if (current_node->left != nullptr)
            std::cout << current_node->left->index << ' ';
        else
            std::cout << 0 << ' ';

        if (current_node->right != nullptr)
            std::cout << current_node->right->index << '\n';
        else
            std::cout << 0 << '\n';
        pre_order_traversal_get(current_node->left);
        pre_order_traversal_get(current_node->right);
    }
}


int main() {
    int n;
    Node* root;
    std::cin>>n;

    Node a[n];
    int key, left_ind, right_ind;

    for (int i = 0; i < n; i++){
        std::cin>>key>>left_ind>>right_ind;
        a[i].set_all(key, left_ind-1, right_ind-1, a);
    }

    root = &a[0];

    for (int i = n - 1; i >= 0; i--){
        if (a[i].left != nullptr && a[i].right == nullptr)
            a[i].height = a[i].left->height + 1;

        else if (a[i].left == nullptr && a[i].right != nullptr)
            a[i].height = a[i].right->height + 1;

        else if (a[i].left != nullptr && a[i].right != nullptr) {
            if (a[i].left->height > a[i].right->height)
                a[i].height = a[i].left->height + 1;
            else
                a[i].height = a[i].right->height + 1;
        }
    }

    if (bfactor(root -> right) < 0)
        root -> right = rotateright(root->right);
    root = rotateleft(root);

    int index = 1;
    std::cout<<n<<'\n';
    pre_order_traversal_set(root, index);
    pre_order_traversal_get(root);

    return 0;
}
