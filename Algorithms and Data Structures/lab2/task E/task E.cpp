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
    void push_front(int x){
        Node* node = new Node(x);
        node-> next = head;
        head = node;
        if (tail == nullptr)
            tail = node;
    }

    void pop_front(){
        if (head == nullptr)
            return;
        if (head == tail){
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* node = head;
        head = node -> next;
        delete node;
    }
    int show_front(){
        if(head!= nullptr)
            return head->x;
        else return 0;
    }
};

int main() {
    list list1;
    list maximums;
    std::ios_base::sync_with_stdio(false);
    int tempint = 0;
    char tempchar = ' ';
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin>>tempchar;
        if (tempchar == '+'){
            std::cin>>tempint;
            list1.push_front(tempint);
            if (tempint >= maximums.show_front())
                maximums.push_front(tempint);
        }
        else if (tempchar == 'm') {
            std::cin>>tempchar;
            std::cin>>tempchar;
            if(maximums.head != nullptr)
                std::cout<<maximums.show_front()<<'\n';
        }
        else{
            if (list1.show_front() == maximums.show_front()){
                list1.pop_front();
                maximums.pop_front();
            }
            else
                list1.pop_front();
        }
    }
    return 0;
}
