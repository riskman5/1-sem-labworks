#include <iostream>
#include <string>
void radix(std::string* a, int n, int m, int k){
    int temp_ascii;
    for (int j = m-1; j >= 0; j--){
        k--;
        int alph[26] = {0};
        std::string temp[n];

        for (int i = 0; i < n; i++){
            temp_ascii = a[i][j];
            alph[temp_ascii - 97]++;
        }

        for (int i = 1; i < 26; i++)
            alph[i] += alph[i-1];

        for (int i = n-1; i >= 0; i--){
            temp_ascii = a[i][j];
            temp[alph[temp_ascii - 97] - 1] = a[i];
            alph[temp_ascii - 97]--;
        }

        for (int i = 0; i < n; i++)
            a[i] = temp[i];
        if (k == 0)
            return;
    }
}

int main() {
    int n;
    int m;
    int k;
    std::cin>>n>>m>>k;
    std::string a[n];
    std::string b;

    for (int i = 0; i < n; i++){
        std::cin >> b;
        a[i] = b;
    }

    radix(a, n, m, k);

    for (int i = 0; i<n; i++)
        std::cout<<a[i]<<'\n';

    return 0;
}
