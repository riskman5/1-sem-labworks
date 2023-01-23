#include <iostream>

int main() {
    int S, N;
    std::cin>>S>>N;
    int bars[N];
    for (int i = 0; i < N; i++)
        std::cin>>bars[i];
    int dp[N+1][S+1];
    for (int i = 0; i < S+1; i++)
        dp[0][i] = 0;
    for (int j = 0; j < N+1; j++)
        dp[j][0] = 0;

    for (int i = 1; i < N+1; i++){
        for (int j = 1; j < S+1; j++){
            int to_compare = (j-bars[i-1] >= 0) ? dp[i-1][j-bars[i-1]] : 0;
            if (bars[i-1] <= j)
                dp[i][j] = std::max(dp[i-1][j], bars[i-1] + to_compare);
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    std::cout<<dp[N][S];
    return 0;
}
