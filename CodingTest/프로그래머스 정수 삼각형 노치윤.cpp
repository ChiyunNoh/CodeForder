#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    vector<vector<int>> dp = triangle;
    for (int i = 0; i < dp.size() - 1; i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = dp.size() - 2; i >= 0; i--) {
        for (int j = 0; j < dp[i].size(); j++) {
            if (dp[i + 1][j] > dp[i + 1][j + 1]) dp[i][j] = triangle[i][j] + dp[i + 1][j];
            else dp[i][j] = triangle[i][j] + dp[i + 1][j + 1];
        }
    }
    answer = dp[0][0];
    return answer;
}