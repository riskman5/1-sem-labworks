#include <iostream>

void merge(int* a, int* b, int left, int mid, int right){
    int key1 = 0;
    int key2 = 0;
    int* result = new int[right - left];
    int* result_sec = new int[right - left];
    while (left + key1 < mid && mid + key2 < right) {
        if (a[left + key1] < a[mid + key2]) {
            result[key1 + key2] = a[left + key1];
            result_sec[key1 + key2] = b[left + key1];
            key1++;
        }
        else {
            result[key1 + key2] = a[mid + key2];
            result_sec[key1 + key2] = b[mid + key2];
            key2++;
        }
    }

    while (left + key1 < mid) {
        result[key1 + key2] = a[left + key1];
        result_sec[key1 + key2] = b[left + key1];
        key1++;
    }

    while (mid + key2 < right) {
        result[key1 + key2] = a[mid + key2];
        result_sec[key1 + key2] = b[mid + key2];
        key2++;
    }

    for (int i = 0; i < key1 + key2; i++) {
        a[left + i] = result[i];
        b[left + i] = result_sec[i];
    }
}


void mergesort(int* a, int* b, int left, int right) {
    if (left + 1 >= right)
        return;
    int mid = (left + right) / 2;
    mergesort(a, b, left, mid);
    mergesort(a, b,mid, right);
    merge(a, b, left, mid, right);
}

int main() {
    int n;
    int a[100000];
    int b[100000];
    std::cin>>n;
    for (int i = 0; i < n; i++)
        std::cin>>a[i]>>b[i];
    mergesort(b, a,0,n);
    mergesort(a,b,0,n);
    unsigned int total_count = 0;
    int i = 0;
    int temp_left = 0;
    int temp_right = 0;
    while (i < n){
        if(a[i] > temp_right){
            total_count += b[i] - a[i] + 1;
            temp_right = b[i];
        }
        else{
            if (a[i] <= temp_right && b[i] > temp_right){
                total_count+= b[i]  - a[i]  - (temp_right - a[i]);
                temp_right = b[i];
            }
        }
        while(i < n && a[i] == a[i+1])
            i++;
        i++;
    }
    std::cout<<total_count;

    return 0;
}
