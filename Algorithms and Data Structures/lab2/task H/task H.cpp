#include <iostream>

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    int k;
    std::cin >> n >> k;
    unsigned long sum = 0;
    int a[n];
    int b[k - 1];
    int maximum = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        sum += a[i];
        if (a[i] > maximum) {
            maximum = a[i] - 1;
        }
    }

    unsigned long left = maximum;
    unsigned long right = sum;
    bool slice_places[n];
    int slice_count;
    unsigned long mid;
    unsigned long temp_sum;

    while (right != left + 1) {
        mid = (left + right) / 2;
        temp_sum = 0;
        slice_count = 1;
        for (int i = 0; i < n; i++) {
            if (temp_sum + a[i] <= mid) {
                temp_sum += a[i];
            } else {
                slice_count++;
                temp_sum = a[i];
            }
        }
        if (slice_count > k) {
            left = mid;
        } else
            right = mid;
    }

    temp_sum = 0;
    slice_count = 1;
    for (int i = 0; i < n; i++) {
        if (temp_sum + a[i] <= right) {
            temp_sum += a[i];
            slice_places[i] = false;
        } else {
            slice_count++;
            slice_places[i] = true;
            temp_sum = a[i];
        }
    }


    if (slice_count < k) {
        int i = 1;
        while (slice_count != k) {
            if (!slice_places[i]) {
                slice_places[i] = true;
                slice_count++;
            }
            i++;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (slice_places[i])
            std::cout << i << ' ';
    }

    return 0;
}
