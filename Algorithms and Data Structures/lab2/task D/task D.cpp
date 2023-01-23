#include <iostream>
#include <string>

struct Node{
    int x;
    struct Node *next;
    Node(int x) {
        this -> x = x;
        this -> next = nullptr;
    }
};

struct list{
    Node* head;
    Node* tail;

    list(){
        this -> head = nullptr;
        this -> tail = nullptr;
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
    std::ios_base::sync_with_stdio(false);
    std::string str;
    while (std::cin >> str) {
        int temp = 0;
        if (str != "-" && str != "+" && str != "*")
            list1.push_front(std::stoi(str));
        else if(str == "+"){
            temp += list1.show_front();
            list1.pop_front();
            temp += list1.show_front();
            list1.pop_front();
            list1.push_front(temp);
        }
        else if(str == "-"){
            temp -= list1.show_front();
            list1.pop_front();
            temp += list1.show_front();
            list1.pop_front();
            list1.push_front(temp);
        }
        else if(str == "*"){
            temp+=1;
            temp *= list1.show_front();
            list1.pop_front();
            temp *= list1.show_front();
            list1.pop_front();
            list1.push_front(temp);
        }
    }
    std::cout<<list1.show_front();
    return 0;
}
