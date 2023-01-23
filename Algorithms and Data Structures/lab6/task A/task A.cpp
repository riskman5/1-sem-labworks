#include <iostream>

struct Node{
    int key;
    Node* next;
    Node(int x){
        key = x;
        next = nullptr;
    }

};

struct List{
    Node* head;
    Node* tail;

    List(){
        head = nullptr;
        tail = nullptr;
    }

    void push_front(int x){
        Node* node = new Node(x);
        node-> next = head;
        head = node;
        if (tail == nullptr) tail = node;
    }

    bool pop_front(){
        if (head == nullptr) return false;
        if (head == tail){
            std::cout<<head->key<<' ';
            delete tail;
            head = nullptr;
            tail = nullptr;
            return false;
        }
        std::cout<<head->key<<' ';
        Node* node = head;
        head = node -> next;
        delete node;
        return true;
    }

    int show_front(){
        if (head != nullptr)
            return head->key;
        return 1000000001;
    }
};

int main() {
    int n;
    std::cin>>n;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
        b[i] = 0;
    int max_length = 0;

    for (int i = 0; i < n; i++){
        std::cin>>a[i];
        int max_before = 0;
        for (int j = 0; j < i; j++){
            if (a[i] > a[j] && b[j] > max_before)
                max_before = b[j];
        }
        b[i] = max_before + 1;
        if (b[i] > max_length)
            max_length = b[i];
    }

    List stack;

    std::cout << max_length<<'\n';

    while (max_length != 0){
        for (int i = 0; i < n; i++){
            if (b[i] == max_length && a[i] < stack.show_front()){
                stack.push_front(a[i]);
                max_length--;
                break;
            }
        }
    }

    while(stack.pop_front()){};

    return 0;
}
