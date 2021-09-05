#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(int N, int number) {
    int answer = -1;
    if (N == number) return 1;
    vector<vector<int>> dp;
    vector<int> one = { N };
    dp.push_back(one);
    for (int i = 1; i < 8; i++) {
        vector<int> temp;
        string num(i + 1, (char)(N + 48));
        temp.push_back(stoi(num));
        int idx_1 = 0;
        int idx_2 = i - 1;
        while (idx_2 >= 0) {
            for (int j = 0; j < dp[idx_2].size(); j++) {
                for (int k = 0; k < dp[idx_1].size(); k++) {
                    temp.push_back(dp[idx_2][j] + dp[idx_1][k]);
                    temp.push_back(dp[idx_2][j] - dp[idx_1][k]);
                    temp.push_back(dp[idx_2][j] * dp[idx_1][k]);
                    if (dp[idx_1][k] != 0) {
                        temp.push_back(dp[idx_2][j] / dp[idx_1][k]);
                    }
                }
            }
            idx_1++;
            idx_2--;
        }

        if (find(temp.begin(), temp.end(), number) != temp.end()) {
            answer = i + 1;
            break;
        }
        dp.push_back(temp);
    }

    return answer;
}