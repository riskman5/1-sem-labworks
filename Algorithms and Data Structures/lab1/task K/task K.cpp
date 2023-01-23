#include <iostream>

void quicksort(int *a, int l, int r, int k){
    while (l < r) {
        int i = l;
        int j = r;
        int pivot = a[(l+r)/2];
        while (i <= j) {
            while (a[i] < pivot)
                i++;
            while (a[j] > pivot)
                j--;
            if (i <= j)
                std::swap(a[i++], a[j--]);
        }
        if (j < k)
            l = i;
        if (i > k)
            r = j;
    }
}

int main() {
    int n, k, A, B, C, a1, a2;
    std::cin >> n >> k >> A >> B >> C >> a1 >> a2;
    int* a = new int[n];
    for (int i = 0; i < n; i++){
        if(i == 0)
            a[i] = a1;
        else {
            if (i == 1)
                a[i] = a2;
            else
                a[i] = A * a[i-2] + B * a[i-1] + C;
        }
    }
    quicksort(a,0,n-1, k-1);
    std::cout<<a[k-1];
    return 0;
}
