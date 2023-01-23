#include <iostream>

int left_binsrc(int* a, int targ, int left, int right){
    while(left < right){
        int mid = (left + right) / 2;
        if (a[mid] >= targ)
            right = mid;
        else
            left = mid + 1;
    }
    if(a[left] == targ)
        return left+1;
    else
        return -1;
}

int right_binsrc(int* a, int targ, int left, int right) {
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (a[mid] <= targ)
            left = mid;
        else
            right = mid - 1;
    }
    if (a[left] == targ)
        return right+1;
    else
        return -1;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin>>n;
    int* a = new int[n];
    for (int i = 0; i < n; i++){
        std::cin>>a[i];
    }

    int m;
    std::cin>>m;
    int* b = new int[m];
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    for (int i = 0; i < m; i++) {
        std::cout << left_binsrc(a, b[i], 0, n - 1) << ' ' << right_binsrc(a, b[i], 0, n - 1) << '\n';
    }
    return 0;
}