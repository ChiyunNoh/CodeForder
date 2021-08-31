#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
bool compare(string a, string b) {//1개만 다른가
    int num = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != b[i]) num++;
        if (num > 1) return false;
    }
    if (num == 0) return false;
    return true;
}
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    vector<bool> visited(words.size(), false);
    if (find(words.begin(), words.end(), target) == words.end()) return 0;
    queue<string> q;
    q.push(begin);
    string a = begin;
    int prev = 1;
    while (true) {
        int cnt = 0;
        for (int k = 0; k < prev; k++) {
            for (int i = 0; i < words.size(); i++) {
                if (!visited[i] && compare(a, words[i])) {
                    cnt++;
                    q.push(words[i]);
                    visited[i] = true;
                    if (words[i] == target) return ++answer;
                }
            }
            q.pop();
            a = q.front();
        }
        prev = cnt;
        answer++;
    }

    return answer;
}