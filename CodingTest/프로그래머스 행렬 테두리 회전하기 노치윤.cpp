#include <string>
#include <vector>
#include <iostream>
using namespace std;
int rotate(vector<int> qury, vector<vector<int>>& matrix) {
    int a = qury[0] - 1;
    int b = qury[1] - 1;
    int c = qury[2] - 1;
    int d = qury[3] - 1;
    int num = matrix[a][b];
    int min = num;
    for (int i = a + 1; i <= c; i++) {
        matrix[i - 1][b] = matrix[i][b];
        if (min > matrix[i][b]) min = matrix[i][b];
    }
    for (int i = b + 1; i <= d; i++) {
        matrix[c][i - 1] = matrix[c][i];
        if (min > matrix[c][i]) min = matrix[c][i];
    }
    for (int i = c - 1; i >= a; i--) {
        matrix[i + 1][d] = matrix[i][d];
        if (min > matrix[i][d]) min = matrix[i][d];
    }
    for (int i = d - 1; i > b; i--) {
        matrix[a][i + 1] = matrix[a][i];
        if (min > matrix[a][i]) min = matrix[a][i];
    }
    matrix[a][b + 1] = num;
    return min;
}
vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    vector<vector<int>> matrix(rows, vector<int>(columns, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = (i)*columns + j + 1;
        }
    }
    for (int i = 0; i < queries.size(); i++) {
        answer.push_back(rotate(queries[i], matrix));
    }
    return answer;
}