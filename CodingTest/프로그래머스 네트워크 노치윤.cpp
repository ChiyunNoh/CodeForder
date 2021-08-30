#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;
void make_link(set<int>& link, queue<int>& BFS, vector<vector<int>>& computers) {
    int num = BFS.front();
    link.insert(num);//mark num th computer visited
    for (int i = 0; i < computers[num].size(); i++) {
        if (computers[num][i] == 1) {
            if (link.find(i) == link.end()) {//if not visited ith computer
                BFS.push(i);
            }
        }
    }
    BFS.pop();
}
int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    set<int> link;
    queue<int> BFS;

    for (int i = 0; i < computers.size(); i++) {
        if (link.size() == 0 || link.find(i) == link.end()) {//if not visited ith computer
            BFS.push(i);
            answer++;
            while (BFS.size() != 0) {
                make_link(link, BFS, computers);
            }
        }
    }
    return answer;
}