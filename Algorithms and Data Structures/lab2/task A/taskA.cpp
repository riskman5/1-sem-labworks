#include <iostream>
struct Node{
    int x;
    struct Node *next;
    Node(int x) {
        this->x = x;
        this->next = nullptr;
    }
};

struct list{
    Node* head;
    Node* tail;

    list(){
        this->head = nullptr;
        this->tail = nullptr;
    }

    void push_back(int x){
        Node* node = new Node(x);
        if (head == nullptr){
            head = node;
        }
        if (tail != nullptr) {
            tail->next = node;
        }
        tail = node;
    }

    void pop_back(){
        if (tail == nullptr){
            return;
        }
        if (head == tail){
            printf("%d\n", tail->x);
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* node = head;
        while(node->next != tail){
            node = node -> next;
        }
        printf("%d\n", tail->x);
        delete tail;
        tail = node;
    }

    void push_front(int x){
        Node* node = new Node(x);
        node->next = head;
        head = node;
        if (tail == nullptr) tail = node;
    }

    void pop_front(){
        if (head == nullptr)
            return;
        if (head == tail){
            printf("%d\n", head->x);
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        printf("%d\n", head->x);
        Node* node = head;
        head = node -> next;
        delete node;
    }
};

int main() {
    list list1;
    int tempint = 0;
    char tempchar = ' ';
    std::ios_base::sync_with_stdio(false);
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin>>tempchar;
        if (tempchar == '+'){
            std::cin>>tempint;
            list1.push_back(tempint);
        }
        else {
            list1.pop_front();
        }
    }
    return 0;
}
