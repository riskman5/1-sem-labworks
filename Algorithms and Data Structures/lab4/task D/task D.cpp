#include <iostream>
#include <string>

struct Node{
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(int key){
        this -> key = key;
    }

};

struct BinaryTree{
    Node* root = nullptr;

    void insert(Node* current_node, int x){

        Node* newnode = new Node(x);

        if (root == nullptr){
            root = newnode;
            return;
        }

        while (current_node != nullptr){
            if ((current_node -> key) < (newnode -> key)){
                if (current_node->right != nullptr)
                    current_node = current_node->right;
                else{
                    newnode->parent = current_node;
                    current_node->right = newnode;
                    break;
                }
            }

            else if ((current_node->key) > (newnode->key)){
                if (current_node->left != nullptr)
                    current_node = current_node -> left;
                else{
                    newnode->parent = current_node;
                    current_node->left = newnode;
                    break;
                }
            }
            else
                break;
        }
    }

    void del(int x){
        Node* node_to_delete = exists(root, x);

        if (node_to_delete == nullptr)
            return;

        Node* parent = node_to_delete->parent;


        if (node_to_delete -> left == nullptr && node_to_delete -> right == nullptr){
            if (parent == nullptr){
                root = nullptr;
                delete node_to_delete;
                return;
            }
            if (parent -> left == node_to_delete)
                parent -> left = nullptr;
            if (parent -> right == node_to_delete)
                parent -> right = nullptr;
        }

        else if ((node_to_delete -> left == nullptr) != (node_to_delete->right == nullptr)) {
            if (node_to_delete->left == nullptr) {
                if (parent == nullptr){
                    root = node_to_delete -> right;
                    root->parent = nullptr;
                    delete node_to_delete;
                    return;
                }
                else if (parent->left == node_to_delete)
                    parent->left = node_to_delete->right;
                else
                    parent->right = node_to_delete->right;
                node_to_delete->right->parent = parent;
            }

            else{
                if (parent == nullptr){
                    root = node_to_delete -> left;
                    root->parent = nullptr;
                    delete node_to_delete;
                    return;
                }
                else if (parent->left == node_to_delete){
                    parent->left = node_to_delete->left;
                }
                else
                    parent->right = node_to_delete->left;
                node_to_delete->left->parent = parent;
            }
        }

        else{
            Node* treasure = next(node_to_delete, node_to_delete->key);
            node_to_delete->key = treasure->key;

            if (treasure->parent->left == treasure){
                treasure->parent->left = treasure->right;
                if (treasure->right != nullptr)
                    treasure->right->parent = treasure->parent;
            }
            else{
                treasure->parent->right = treasure -> right;
                if (treasure->right != nullptr)
                    treasure->right->parent = treasure->parent;
            }
        }
    }

    Node* exists(Node* current_node, int x){
        if (current_node == nullptr || x == current_node->key){
            return current_node;
        }
        if (x < current_node->key)
            return exists(current_node->left, x);
        else
            return exists(current_node->right, x);
    }

    Node* next(Node* current_node, int x){
        Node* treasure = nullptr;

        while (current_node != nullptr){
            if (current_node->key > x){
                treasure = current_node;
                current_node = current_node->left;
            }
            else
                current_node = current_node->right;
        }
        return treasure;
    }

    Node* prev(Node* current_node, int x){
        Node* treasure = nullptr;

        while (current_node != nullptr){
            if (current_node->key >= x){
                current_node = current_node->left;
            }
            else {
                treasure = current_node;
                current_node = current_node->right;
            }
        }
        return treasure;
    }
};

int main(){
    BinaryTree binaryTree;
    std::string command;
    int key;

    while(std::cin >> command){
        std::cin >> key;

        if (command == "insert")
            binaryTree.insert(binaryTree.root, key);

        if (command == "exists") {
            if (binaryTree.exists(binaryTree.root, key) != nullptr)
                printf("%s\n", "true");
            else
                printf("%s\n", "false");
        }

        if (command == "delete")
            binaryTree.del(key);

        if (command == "prev") {
            if (binaryTree.prev(binaryTree.root, key) != nullptr)
                printf("%d\n", (binaryTree.prev(binaryTree.root, key))->key);
            else
                printf("%s\n", "none");
        }

        if (command == "next") {
            if (binaryTree.next(binaryTree.root, key) != nullptr)
                printf("%d\n", (binaryTree.next(binaryTree.root, key))->key);
            else
                printf("%s\n", "none");
        }
    }

    return 0;
}