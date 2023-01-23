#include <iostream>

void quicksort(int *a, int l, int r){
    int i = l;
    int j = r;
    int pivot = a[(l+r)/2];
    while(i<=j){
        while(a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
            std::swap(a[i++], a[j--]);
    }
    if (l < i)
        quicksort(a, l, j);
    if (r > j)
        quicksort(a,i,r);
}

int main() {
    int n;
    std::cin>>n;
    int a[100000];
    for (int i = 0; i<n; i++)
        std::cin>>a[i];
    quicksort(a,0,n-1);
    for (int i = 0; i < n; i++)
        std::cout<<a[i]<<' ';
    return 0;
}
