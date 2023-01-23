#include <iostream>
#include <string>

struct Node {
    Node *right = nullptr;
    Node *left = nullptr;
    std::string key;
    int height = 0;
    bool studs[3] = {false};

    Node(std::string key) {
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

    Node *insert(Node *current_node, std::string key)
    {
        if (current_node == nullptr)
            return new Node(key);
        if (key < current_node->key)
            current_node->left = insert(current_node->left, key);
        else
            current_node->right = insert(current_node->right, key);
        return balance(current_node);
    }

    Node *search(Node *current_node, std::string x) {
        if (current_node == nullptr || x == current_node->key) {
            return current_node;
        }
        if (x < current_node->key)
            return search(current_node->left, x);
        else
            return search(current_node->right, x);
    }
};


int main() {
    AVLtree avl;

    std::string file_name;

    int tasks_count;
    std::cin >> tasks_count;
    std::string code_name;

    int studs[3] = {tasks_count * 3, tasks_count * 3, tasks_count * 3};


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < tasks_count; j++) {
            std::cin >> file_name;

            if (avl.search(avl.root, file_name) == nullptr) {
                avl.root = (avl.insert(avl.root, file_name));
                avl.search(avl.root, file_name)->studs[i] = true;
                if ((avl.search(avl.root, file_name))->studs[(i + 1) % 3] &&
                    !((avl.search(avl.root, file_name))->studs[(i + 2) % 3])) {
                    studs[i] -= 2;
                    studs[(i + 1) % 3] -= 2;
                } else if ((avl.search(avl.root, file_name))->studs[(i + 2) % 3] &&
                           !((avl.search(avl.root, file_name))->studs[(i + 1) % 3])) {
                    studs[i] -= 2;
                    studs[(i + 2) % 3] -= 2;
                } else if ((avl.search(avl.root, file_name))->studs[(i + 1) % 3] &&
                           (avl.search(avl.root, file_name))->studs[(i + 2) % 3]) {
                    studs[i] -= 3;
                    studs[(i + 1) % 3] -= 1;
                    studs[(i + 2) % 3] -= 1;
                }
            } else {
                (avl.search(avl.root, file_name))->studs[i] = true;
                if ((avl.search(avl.root, file_name))->studs[(i + 1) % 3] &&
                    !((avl.search(avl.root, file_name))->studs[(i + 2) % 3])) {
                    studs[i] -= 2;
                    studs[(i + 1) % 3] -= 2;
                } else if ((avl.search(avl.root, file_name))->studs[(i + 2) % 3] &&
                           !((avl.search(avl.root, file_name))->studs[(i + 1) % 3])) {
                    studs[i] -= 2;
                    studs[(i + 2) % 3] -= 2;
                } else if ((avl.search(avl.root, file_name))->studs[(i + 1) % 3] &&
                           (avl.search(avl.root, file_name))->studs[(i + 2) % 3]) {
                    studs[i] -= 3;
                    studs[(i + 1) % 3] -= 1;
                    studs[(i + 2) % 3] -= 1;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
        std::cout << studs[i] << " ";

    return 0;
}

