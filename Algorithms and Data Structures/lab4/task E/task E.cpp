#include <iostream>
#include <string>

struct Node{
    std::string key;
    Node* left;
    Node* right;

    bool studs[3] = {false};

    Node(std::string key){
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

struct Binary_tree {
    Node *root;

    Binary_tree() {
        this->root = nullptr;
    }

    Node* search(Node* node, std::string temp_key){
        Node* temp_node = node;

        if (temp_node == nullptr || temp_node -> key == temp_key){
            return temp_node;
        }

        if (temp_key < temp_node->key)
            return search(temp_node->left, temp_key);

        else
            return search(temp_node->right, temp_key);
    }

    Node* add(std::string temp_key){
        Node* newnode = new Node(temp_key);
        if (root == nullptr){
            root = newnode;
            return newnode;
        }
        else{
            Node* tempnode = root;
            while(true){
                if (newnode->key > tempnode->key){
                    if(tempnode->right != nullptr)
                        tempnode = tempnode->right;
                    else{
                        tempnode->right = newnode;
                        return newnode;
                    }
                }
                else{
                    if(tempnode->left != nullptr)
                        tempnode = tempnode->left;
                    else{
                        tempnode->left = newnode;
                        return newnode;
                    }
                }
            }
        }
    }
};


int main(){
    Binary_tree binaryTree;

    std::string file_name;

    int tasks_count;
    int temp_int;
    std::cin>>tasks_count;
    uint64_t code = 0;
    std::string code_name;

    int studs[3] = {tasks_count * 3, tasks_count * 3, tasks_count * 3};



    for (int i = 0; i < 3; i++){
        for (int j = 0; j < tasks_count; j++){
            std::cin>>file_name;

            if (binaryTree.search(binaryTree.root, file_name) == nullptr) {
                (binaryTree.add(file_name))->studs[i] = true;
                if ((binaryTree.add(file_name))->studs[(i+1) % 3] && !((binaryTree.add(file_name))->studs[(i+2) % 3])){
                    studs[i] -= 2;
                    studs[(i + 1) % 3] -= 2;
                }
                else if ((binaryTree.add(file_name))->studs[(i+2) % 3] && !((binaryTree.add(file_name))->studs[(i+1) % 3])){
                    studs[i] -= 2;
                    studs[(i + 2) % 3] -= 2;
                }
                else if ((binaryTree.add(file_name))->studs[(i+1) % 3] && (binaryTree.add(file_name))->studs[(i+2) % 3]){
                    studs[i] -= 3;
                    studs[(i + 1) % 3] -= 1;
                    studs[(i + 2) % 3] -= 1;
                }
            }

            else {
                (binaryTree.search(binaryTree.root, file_name))->studs[i] = true;
                if ((binaryTree.search(binaryTree.root, file_name))->studs[(i+1) % 3] && !((binaryTree.search(binaryTree.root, file_name))->studs[(i+2) % 3])){
                    studs[i] -= 2;
                    studs[(i + 1) % 3] -= 2;
                }
                else if ((binaryTree.search(binaryTree.root, file_name))->studs[(i+2) % 3] && !((binaryTree.search(binaryTree.root, file_name))->studs[(i+1) % 3])){
                    studs[i] -= 2;
                    studs[(i + 2) % 3] -= 2;
                }
                else if ((binaryTree.search(binaryTree.root, file_name))->studs[(i+1) % 3] && (binaryTree.search(binaryTree.root, file_name))->studs[(i+2) % 3]){
                    studs[i] -= 3;
                    studs[(i + 1) % 3] -= 1;
                    studs[(i + 2) % 3] -= 1;
                }

            }
        }
    }

    for (int i = 0; i < 3; i++){
        std::cout<<studs[i]<<" ";
    }

    return 0;
}