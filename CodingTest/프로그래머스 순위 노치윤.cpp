#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<int>> vec(n, vector<int>(n, 0));
    for (int i = 0; i < results.size(); i++) {
        vec[results[i][0] - 1][results[i][1] - 1] = 1;
    }

    for (int k = 0; k < n; k++) {
        vector<vector<int>> temp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (vec[i][j] || (vec[i][k] && vec[k][j]) == 1) {
                    temp[i][j] = 1;
                }
            }
        }
        vec = temp;
    }

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += vec[i][j];
            sum += vec[j][i];
        }
        if (sum == n - 1) answer++;
    }
    return answer;
}