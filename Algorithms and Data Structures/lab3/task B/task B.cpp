#include <iostream>
void siftdown(int* a, int i, int n){
    int j = i;
    if ((2 * i + 1) < n && a[j] < a[2 * i + 1])
        j = 2 * i + 1;
    if ((2 * i + 2) < n && a[j] < a[2 * i + 2])
        j = 2 * i + 2;
    if (j != i){
        std::swap(a[j], a[i]);
        siftdown(a, j, n);
    }
}

void buildheap(int* a, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        siftdown(a, i, n);
}

void heapsort(int* a, int n){
    buildheap(a, n);
    for (int i = n-1; i >= 0; i--){
        std::swap(a[0], a[i]);
        siftdown(a, 0, i);
    }
}

int main(){
    int n;
    std::cin>>n;
    int a[n];
    for (int i = 0; i < n; i++)
        std::cin>>a[i];

    heapsort(a, n);

    for (int i = 0; i < n; i++)
        std::cout<<a[i]<<" ";

    return 0;
}