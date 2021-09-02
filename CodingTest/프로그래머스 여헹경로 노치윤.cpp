#include <string>
#include <vector>
#include <algorithm>
using namespace std;


bool cmp(vector<string> a, vector<string> b) {
    if (a[0] < b[0]) return true;
    else if (a[0] > b[0]) return false;
    else {
        if (a[1] < b[1]) return true;
        else return false;
    }
}

void DFS(vector<bool>& visited, vector<string>& temp, vector<vector<string>>& tickets, int n, int& end) {
    for (int i = 0; i < tickets.size(); i++) {
        if (temp.back() == tickets[i][0] && !visited[i]) {
            temp.push_back(tickets[i][1]);
            visited[i] = true;
            if (n == tickets.size()) {
                end = 1;
                return;
            }
            DFS(visited, temp, tickets, n + 1, end);
            if (end == 1) return;
            visited[i] = false;
            temp.pop_back();
        }
    }
}
vector<string> solution(vector<vector<string>> tickets) {
    sort(tickets.begin(), tickets.end(), cmp);

    vector<string> answer;

    vector<bool> visited(tickets.size(), false);

    vector<string> temp;
    temp.push_back("ICN");
    int end = 0;
    DFS(visited, temp, tickets, 1, end);


    return temp;
}