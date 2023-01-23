#include iostream
#include string

struct Node {
    Node right = nullptr;
    Node left = nullptr;
    stdstring key;
    int height = 0;
    bool studs[3] = {false};

    Node(stdstring key) {
        this-key = key;
    }
};

struct AVLtree {
    Node root = nullptr;

    int get_height(Node x) {
        if (x != nullptr)
            return x-height;
        else
            return 0;
    }

    void fixheight(Node current_node) {
        if (get_height(current_node-left)  get_height(current_node-right))
            current_node-height = get_height(current_node-left) + 1;
        else
            current_node-height = get_height(current_node-right) + 1;
    }

    int bfactor(Node current_node) {
        return get_height(current_node-right) - get_height(current_node-left);
    }

    Node rotateleft(Node current_node) {
        Node new_current_node = current_node-right;
        current_node-right = new_current_node-left;
        new_current_node-left = current_node;
        fixheight(current_node);
        fixheight(new_current_node);
        return new_current_node;
    }

    Node rotateright(Node current_node) {
        Node new_current_node = current_node-left;
        current_node-left = new_current_node-right;
        new_current_node-right = current_node;
        fixheight(current_node);
        fixheight(new_current_node);
        return new_current_node;
    }

    Node balance(Node current_node) {
        fixheight(current_node);
        if (bfactor(current_node) == 2) {
            if (bfactor(current_node-right)  0)
                current_node-right = rotateright(current_node-right);
            return rotateleft(current_node);
        }

        if (bfactor(current_node) == -2) {
            if (bfactor(current_node-left)  0)
                current_node-left = rotateleft(current_node-left);
            return rotateright(current_node);
        }

        return current_node;
    }

    Node insert(Node current_node, stdstring key)
    {
        if (current_node == nullptr)
            return new Node(key);
        if (key  current_node-key)
            current_node-left = insert(current_node-left, key);
        else
            current_node-right = insert(current_node-right, key);
        return balance(current_node);
    }

    Node search(Node current_node, stdstring x) {
        if (current_node == nullptr  x == current_node-key) {
            return current_node;
        }
        if (x  current_node-key)
            return search(current_node-left, x);
        else
            return search(current_node-right, x);
    }
};

int clear_count = 0;

void clear(stdstring str){
    bool a[128] = {false};
    for (int i = 0; i  str.size(); i++){
        if (!a[(char)str[i]]){
            clear_count++;
            a[(char)str[i]] = true;
        }
    }
}


int main() {
    AVLtree avl;

    int n;
    stdcinn;

    stdstring str;

    for (int i = 0; i  n; i++){
        stdcinstr;
        if (avl.search(avl.root, str) == nullptr){
            avl.root = avl.insert(avl.root, str);
        }
        else{
            clear(avl.search(avl.root, str)-key);
        }
    }

    stdcoutclear_count;
}