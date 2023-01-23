#include <iostream>

struct Node_info{
    int key = 0;
    int left = 0;
    int right = 0;
    int i_left_child = -1;
    int i_right_child = -1;

    int left_border = 0;
    int right_border = 0;

    void set_key_children(int key, int left, int right){
        this->key = key;
        this->left = left;
        this->right = right;
    }

    void set_parent_to_left(int parent){
        this->i_left_child = parent;
    }

    void set_parent_to_right(int parent){
        this->i_right_child = parent;
    }

    void set_interval(int left_border, int right_border){
        this->left_border = left_border;
        this->right_border = right_border;
    }

};

int main(){
    int N;
    scanf("%d", &N);
    Node_info a[N];

    int parent = -1;
    int left, right;
    int key;
    bool flag = true;

    a[0].set_interval(-1000000001, 1000000001);

    for (int i = 0; i < N; i++) {
        parent++;
        scanf("%d%d%d", &key, &left, &right);
        a[i].set_key_children(key, left, right);
        if (left != 0) {
            a[left - 1].set_parent_to_left(parent);
            a[left - 1].set_interval(a[i].left_border, key);
        }

        if (right != 0) {
            a[right - 1].set_parent_to_right(parent);
            a[right - 1].set_interval(key, a[i].right_border);
        }

        if ((a[i].left_border >= key) || (key >= a[i].right_border)){
            flag = false;
            break;
        }
    }

    if(flag)
        printf("%s", "YES");
    else
        printf("%s", "NO");

    return 0;
}