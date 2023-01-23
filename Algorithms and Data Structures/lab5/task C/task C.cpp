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

    Node(int key){
        this->key = key;
    }

    Node(){}
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

void fixheight(Node *current_node) {
    if (get_height(current_node->left) > get_height(current_node->right))
        current_node->height = get_height(current_node->left) + 1;
    else
        current_node->height = get_height(current_node->right) + 1;
}


Node* rotateleft(Node* current_node){
    Node* new_current_node = current_node->right;
    current_node->right = new_current_node->left;
    new_current_node->left = current_node;
    fixheight(current_node);
    fixheight(new_current_node);
    return new_current_node;
}

Node* rotateright(Node* current_node){
    Node* new_current_node = current_node->left;
    current_node -> left = new_current_node->right;
    new_current_node -> right = current_node;
    fixheight(current_node);
    fixheight(new_current_node);
    return new_current_node;
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

Node *balance(Node *current_node) {
    fixheight(current_node);
    if (bfactor(current_node) == 2) {
        if (bfactor(current_node->right) < 0)
            current_node->right = rotateright(current_node->right);
        return rotateleft(current_node);
    }

    if (bfactor(current_node) == -2) {
        if (bfactor(current_node->left) > 0)
            current_node->left = rotateleft(current_node->left);
        return rotateright(current_node);
    }

    return current_node;
}

Node *insert(Node *current_node, int key)
{
    if (current_node == nullptr)
        return new Node(key);
    if (key < current_node->key)
        current_node->left = insert(current_node->left, key);
    else
        current_node->right = insert(current_node->right, key);
    return balance(current_node);
}

Node *search(Node *current_node, int x) {
    if (current_node == nullptr || x == current_node->key) {
        return current_node;
    }
    if (x < current_node->key)
        return search(current_node->left, x);
    else
        return search(current_node->right, x);
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

    std::cin>>key;
    if (search(root, key) == nullptr)
        root = insert(root, key);
    int index = 1;

    std::cout<<n+1<<'\n';
    pre_order_traversal_set(root, index);
    pre_order_traversal_get(root);

    return 0;
}
