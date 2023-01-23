#include <iostream>

struct Node {
    Node *right = nullptr;
    Node *left = nullptr;
    int key;
    int height = 1;

    Node(int key) {
        this->key = key;
    }
};

struct AVLtree {
    Node *root = nullptr;

    int get_height(Node *x) {
        if (x != nullptr)
            return x->height;
        else
            return 0;
    }

    void fixheight(Node *current_node) {
        if (get_height(current_node->left) > get_height(current_node->right))
            current_node->height = get_height(current_node->left) + 1;
        else
            current_node->height = get_height(current_node->right) + 1;
    }

    int bfactor(Node *current_node) {
        return get_height(current_node->right) - get_height(current_node->left);
    }

    Node *rotateleft(Node *current_node) {
        Node *new_current_node = current_node->right;
        current_node->right = new_current_node->left;
        new_current_node->left = current_node;
        fixheight(current_node);
        fixheight(new_current_node);
        return new_current_node;
    }

    Node *rotateright(Node *current_node) {
        Node *new_current_node = current_node->left;
        current_node->left = new_current_node->right;
        new_current_node->right = current_node;
        fixheight(current_node);
        fixheight(new_current_node);
        return new_current_node;
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

    Node *find_max(Node* current_node){
        if (current_node -> right != nullptr)
            return find_max(current_node->right);
        else{
            return current_node;
        }
    }

    Node *del_max(Node* current_node){
        if (current_node -> right == nullptr)
            return current_node->left;
        current_node->right = del_max(current_node->right);
        return balance(current_node);
    }


    Node *del(Node *current_node, int x) {
        if (current_node == nullptr)
            return nullptr;

        if (x < current_node->key)
            current_node->left = del(current_node->left, x);

        else if (x > current_node->key)
            current_node->right = del(current_node->right, x);

        else {
            Node *help_node_1 = current_node->left;
            Node *help_node_2 = current_node->right;
            delete current_node;
            if (help_node_1 == nullptr)
                return help_node_2;
            Node *help_node_3 = find_max(help_node_1);
            help_node_3->left = del_max(help_node_1);
            help_node_3->right = help_node_2;
            return balance(help_node_3);
        }
        return balance(current_node);
    }
};

int main(){
    AVLtree avltree;
    int n;
    std::cin>>n;
    char operation;
    int key;
    for (int i = 0; i < n; i++){
        std::cin>>operation>>key;
        if (operation == 'A'){
            if(avltree.search(avltree.root, key) == nullptr)
                avltree.root = avltree.insert(avltree.root, key);
            std::cout<<avltree.bfactor(avltree.root)<<'\n';
        }
        if (operation == 'D'){
            avltree.root = avltree.del(avltree.root, key);
            if(avltree.root != nullptr)
                std::cout<<avltree.bfactor(avltree.root)<<'\n';
            else
                std::cout<<0<<'\n';
        }
        if (operation == 'C'){
            if(avltree.search(avltree.root, key) != nullptr)
                std::cout<<"Y"<<'\n';
            else
                std::cout<<"N"<<'\n';
        }
    }
    return 0;
}