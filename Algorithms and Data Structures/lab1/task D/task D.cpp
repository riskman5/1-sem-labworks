#include <iostream>

int main() {
    int n;
    bool flag = false;
    std::cin >> n;
    int a[1000];
    for (int i = 0; i < n; i++)
        std::cin>>a[i];
    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key){
            flag = true;
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
        if (flag){
            for (int i = 0; i < n; i++)
                std::cout<<a[i]<<' ';
            std::cout<<std::endl;
        }
        flag = false;
    }
    return 0;
}
