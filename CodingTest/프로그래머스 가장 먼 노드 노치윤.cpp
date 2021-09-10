#include <string>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    vector<int> vec;
    vector<vector<int>> info(n, vec);
    sort(edge.begin(), edge.end());
    for (int i = 0; i < edge.size(); i++) { //연결된 노드 모두 저장
        vector<int> temp = edge[i];
        info[temp[0] - 1].push_back(temp[1]);
        info[temp[1] - 1].push_back(temp[0]);
    }

    vector<int> cnt(n, 0);
    deque<int> BFS;
    BFS.push_back(1);
    cnt[0] = 1;
    int max = 1;
    while (BFS.size() != 0) {
        int first = BFS.front();
        for (int j = 0; j < info[first - 1].size(); j++) {
            if (cnt[info[first - 1][j] - 1] == 0) {
                cnt[info[first - 1][j] - 1] = cnt[first - 1] + 1;
                if (max < cnt[info[first - 1][j] - 1]) max = cnt[info[first - 1][j] - 1];
                BFS.push_back(info[first - 1][j]);
            }
            else {//만약 방문한 노드인데 더 가까운 거리가 존재하면 업데이트
                if (cnt[info[first - 1][j] - 1] > cnt[first - 1] + 1) {
                    cnt[info[first - 1][j] - 1] = cnt[first - 1] + 1;
                }
            }
        }
        BFS.pop_front();
    }

    for (int i = 0; i < cnt.size(); i++) {
        if (cnt[i] == max) answer++;
    }
    return answer;
}