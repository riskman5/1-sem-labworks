#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int a[1000];
    for (int i = 0; i < n; i++)
        std::cin>>a[i];
    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key){
            a[j+1] = a[j];
            j-=1;
        }
        a[j+1] = key;
    }
    for (int i = 0; i < n; i++){
        std::cout << a[i] <<' ';
    }
    return 0;
}
