#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int a[1000];
    for (int i = 0; i < n; i++){
        std::cin>>a[i];
    }
    int num, place;
    std::cin >> num >> place;
    for (int i = n; i >= place - 1; i--){
        a[i+1] = a[i];
    }
    a[place-1] = num;
    for (int i = 0; i < n+1; i++){
        std::cout << a[i] <<' ';
    }
    return 0;
}
