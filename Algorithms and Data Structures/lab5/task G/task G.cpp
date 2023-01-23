#include <iostream>

struct Node {
    int key;
    int left = -1;
    int right = -1;

    void set_control_interval(int left, int right){
        this->left = left;
        this->right = right;
    }
};

int nearest_degree(int x){
    int nearest = 1;

    while (nearest < x){
        nearest*=2;
    }

    return nearest;
}

void set_control(Node* a, int i, int left, int right, int n){
    a[i].key = 0;
    if (i < n - 1)
        a[i].set_control_interval(left, right);
    else
        a[i].set_control_interval(i,i);
    if (left < right) {
        set_control(a, i*2+1, left, (left+right)/2, n);
        set_control(a, i*2+2, (left+right)/2 + 1, right, n);
    }
}

void update(Node*a, int i, int x){
    if (x + a[i].key < 0)
        x = -a[i].key;
    while(i > 0){
        a[i].key += x;
        i = (i-1)/2;
    }
    a[0].key+=x;
}

int count_sum(Node *a, int i, int left, int right){
    if (a[i].left > right || a[i].right < left)
        return 0;

    if (a[i].left >= left && a[i].right <= right)
        return a[i].key;

    return count_sum(a, i*2+1, left, right) + count_sum(a, i*2+2, left, right);
}

int main(){
    int n;
    int q;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin>>n>>q;

    n = nearest_degree(n);
    Node a[2*n-1];
    a[0].set_control_interval(n-1, 2*n-2);

    set_control(a, 0, n-1, 2*n-2, n);

    char oper;
    int index, x_or_ind;

    for (int i = 0; i < q; i++){
        std::cin>>oper>>index>>x_or_ind;
        if (oper == '+'){
            update(a, n + index - 2, x_or_ind);
        }

        if (oper == '-'){
            update(a, n + index - 2, -x_or_ind);
        }

        if (oper == '?'){
            std::cout<<count_sum(a, 0, n+index-2, n+x_or_ind-2)<<'\n';
        }
    }
}