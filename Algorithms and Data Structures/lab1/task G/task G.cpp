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

void mergesort(int* a, int left, int right) {
    if (left + 1 >= right)
        return;
    int mid = (left + right) / 2;
    mergesort(a, left, mid);
    mergesort(a, mid, right);
    merge(a, left, mid, right);
}

int main() {
    int a1[100000];
    int a2[100000];
    int n1;
    int n2;
    std::cin >> n1;
    for (int i = 0; i < n1; i++)
        std::cin >> a1[i];


    std::cin >> n2;
    for (int i = 0; i < n2; i++)
        std::cin >> a2[i];


    mergesort(a1, 0, n1);
    mergesort(a2, 0, n2);

    int key1 = 0;
    int key2 = 0;
    bool flag = true;
    while (key1 < n1 || key2 < n2) {
        if (a1[key1] == a2[key2]) {
            key1++;
            key2++;
        }
        else {
            if (a1[key1] == a2[key2 - 1]) {
                while (a1[key1] == a2[key2 - 1])
                    key1++;
            }
            else {
                if (a1[key1 - 1] == a2[key2]) {
                    while (a1[key1 - 1] == a2[key2])
                        key2++;
                }
                else {
                    flag = false;
                    break;
                }
            }
        }
    }
    if(flag)
        std::cout<<"YES";
    else
        std::cout<<"NO";
    return 0;
}
