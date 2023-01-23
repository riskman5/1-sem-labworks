#include <iostream>

int main() {
    int n;
    std::cin>>n;
    int a[n];
    for (int i = 0; i < n; i++)
        std::cin>>a[i];
    bool flag = true;

    for(int i = 0; i < n/2; i++){
        if (2*i + 1 < n && a[2*i+1] < a[i]){
            flag = false;
            break;
        }
        if (2*i + 2 < n && a[2*i+2] < a[i]){
            flag = false;
            break;
        }
    }

    if (flag)
        std::cout<<"YES";
    else
        std::cout<<"NO";
    return 0;
}
