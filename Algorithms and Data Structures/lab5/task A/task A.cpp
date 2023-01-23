#include <iostream>

class Node_info{

private:
    int left = 0;
    int right = 0;
    int parent = -1;
    int height = 0;

public:
    void set_children(int left, int right){
        this->left = left;
        this->right = right;
    }

    void set_parent(int parent){
        this->parent = parent;
    }

    void set_height(int height){
        this->height = height;
    }

    int get_parent(){
        return parent;
    }

    int get_height(){
        return height;
    }

    int get_left(){
        return left;
    }

    int get_right(){
        return right;
    }

};


int main(){
    int n;
    std::cin>>n;

    Node_info a[n];
    int trash, left, right;

    for (int i = 0; i < n; i++){
        std::cin>>trash>>left>>right;
        a[i].set_children(left-1, right-1);
        if (left != 0)
            a[left-1].set_parent(i);
        if (right != 0)
            a[right-1].set_parent(i);
    }

    for (int i = n - 1; i >= 0; i--){
        if (a[i].get_left() != 0 && a[i].get_right() == 0)
            a[i].set_height(a[a[i].get_left()].get_height() + 1);

        else if (a[i].get_left() == 0 && a[i].get_right() != 0)
            a[i].set_height(a[a[i].get_right()].get_height() + 1);

        else if (a[i].get_left() != 0 && a[i].get_right() != 0)
            a[i].set_height(std::max(a[a[i].get_right()].get_height(), a[a[i].get_left()].get_height()) + 1);
    }

    for (int i = 0 ; i < n; i++){
        if (a[i].get_left() == 0  && a[i].get_right() == 0)
            std::cout<<'0'<<'\n';

        else if (a[i].get_left() == 0 && a[i].get_right() != 0)
            std::cout<<a[i].get_height()<<'\n';

        else if (a[i].get_left() != 0 && a[i].get_right() == 0){
            std::cout<<-a[i].get_height()<<'\n';
        }

        else{
            std::cout<<a[a[i].get_right()].get_height() - a[a[i].get_left()].get_height()<<'\n';
        }
    }

    return 0;
}