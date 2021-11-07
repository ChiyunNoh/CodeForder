#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    int dp[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 0; i < puddles.size(); i++) {
        dp[puddles[i][0] - 1][puddles[i][1] - 1] = 0;
    }
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0) continue;
                if (dp[i][j] == 0) continue;
                dp[i][j] = dp[i][j - 1];
            }
            else if (j == 0) {
                if (dp[i][j] == 0) continue;
                dp[i][j] = dp[i - 1][j];
            }
            else {
                if (dp[i][j] == 0) continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
            dp[i][j] %= 1000000007;
        }
    }

    answer = dp[m - 1][n - 1] % 1000000007;

    return answer;
}