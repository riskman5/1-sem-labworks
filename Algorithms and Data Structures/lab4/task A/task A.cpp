#include <iostream>

struct Node_info{
    int left = 0;
    int right = 0;
    int parent = -1;

    void set_children(int left, int right){
        this->left = left;
        this->right = right;
    }

    void set_parent(int parent){
        this->parent = parent;
    }

};

int main(){

    int N;
    std::cin>>N;
    Node_info a[N];

    int parent = -1;
    int left, right;
    int trash;
    int maxh = 0;
    int temph;

    for (int i = 0; i < N; i++) {
        parent++;
        std::cin >> trash >> left >> right;
        a[i].set_children(left, right);
        if (left != 0)
            a[left - 1].set_parent(parent);
        if (right != 0)
            a[right - 1].set_parent(parent);
        if (left == 0 && right == 0) {
            temph = 1;
            int j = i;
            while (a[j].parent != -1) {
                j = a[j].parent;
                temph++;
            }
            if (temph> maxh) {
                maxh = temph;
            }
        }
    }
    std::cout<<maxh;
    return 0;
}