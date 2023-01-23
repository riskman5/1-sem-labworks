#include <iostream>
void merge(int*a, int left, int mid, int right){
    int key1 = 0;
    int key2 = 0;
    int* result = new int[right - left];

    while(left + key1 < mid && mid + key2 < right){
        if(a[left + key1] < a[mid + key2]){
            result[key1 + key2] = a[left + key1];
            key1++;
        }
        else{
            result[key1+key2] = a[mid + key2];
            key2++;
        }
    }

    while(left + key1 < mid){
        result[key1 + key2] = a[left + key1];
        key1++;
    }

    while(mid + key2 < right){
        result[key1 + key2] = a[mid + key2];
        key2++;
    }

    for(int i = 0; i < key1+key2; i++)
        a[left+i] = result[i];
}

void mergesort(int*a, int left, int right) {
    if (left + 1 >= right)
        return;
    else {
        int mid = (left + right) / 2;
        mergesort(a, left, mid);
        mergesort(a, mid, right);
        merge(a, left, mid, right);

    }
}

int main() {
    int a[100000];
    int n;
    std::cin>>n;
    for(int i = 0; i < n; i++)
        std::cin>>a[i];
    mergesort(a, 0, n);
    for (int i = 0; i < n; i++)
        std::cout<<a[i]<<' ';
    return 0;
}
