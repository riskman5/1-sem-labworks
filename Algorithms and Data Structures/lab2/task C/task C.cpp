#include <iostream>
#include <string>

struct Node{
    char x;
    struct Node *next;
    Node(char x) {
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

    void push_front(char x){
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

    char show_front(){
        if(head!= nullptr)
            return head->x;
        else
            return '0';
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::string str;
    char tempchar = ' ';
    while (getline(std::cin, str)) {
        list list1;
        bool flag = true;
        for(int i = 0; i < str.size(); i++) {
            if (str[i] == '(' || str[i] == '[') list1.push_front(str[i]);
            else if (str[i] == ']') {
                if (list1.show_front() != '[')
                    flag = false;
                list1.pop_front();
            }
            else if (str[i] == ')') {
                if (list1.show_front() != '(')
                    flag = false;
                list1.pop_front();
            }
        }
        if (flag && list1.head == NULL)
            std::cout<<"YES"<<'\n';
        else
            std::cout<<"NO"<<'\n';
    }
    return 0;
}
