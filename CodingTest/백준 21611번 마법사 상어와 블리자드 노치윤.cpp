#include <vector>
#include <iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
int direc_x[4] = { -1,1,0,0 };
int direc_y[4] = { 0,0,-1,1 };
vector<int> vec = { 0,0,0 };
vector<int> destroy(vector<vector<int>>& nums, int d, int s, int n) {
    int x = (n + 1) / 2 - 1;
    int y = (n + 1) / 2 - 1;
    for (int i = 0; i < s; i++) {
        x += direc_x[d - 1];
        y += direc_y[d - 1];
        if (x < 0 || y < 0 || x >= n || y >= n) break;
        nums[x][y] = 0;
    }//ÆÄ±« ¿Ï·á
    vector<int> temp;
    x = (n + 1) / 2 - 1;
    y = (n + 1) / 2 - 1;
    int move = 1;
    int cnt = 0;
    int order[4] = { 2,1,3,0 };
    for (int i = 0; i < 2 * n; i++) {
        if (x < 0 || y < 0 || x >= n || y >= n) break;
        if (cnt == 2) {
            cnt = 0;
            move++;
        }
        for (int j = 0; j < move; j++) {
            x += direc_x[order[i % 4]];
            y += direc_y[order[i % 4]];
            if (x < 0 || y < 0 || x >= n || y >= n) break;
            if (nums[x][y] != 0) temp.push_back(nums[x][y]);
        }
        cnt++;
    }
    if (temp.size() == 0) {
        return temp;
    }
    int prev_num = temp[0];
    int count_num = 1;
    int destroy_num = 0;

    do {
        destroy_num = 0;
        vector<int> temp2;
        prev_num = temp[0];
        count_num = 1;
        for (int i = 1; i <= temp.size(); i++) {
            if (i == temp.size()) {
                if (count_num < 4) {
                    for (int j = 0; j < count_num; j++) {
                        temp2.push_back(prev_num);
                    }
                }
                else {
                    vec[prev_num - 1] += count_num;
                    destroy_num++;
                }
                break;
            }
            if (prev_num != temp[i]) {
                if (count_num < 4) {
                    for (int j = 0; j < count_num; j++) {
                        temp2.push_back(prev_num);
                    }
                }
                else {
                    vec[prev_num - 1] += count_num;
                    destroy_num++;
                }
                count_num = 1;
                prev_num = temp[i];
            }
            else {
                count_num++;
            }
        }
        temp = temp2;
        if (temp.size() == 0) {
            return temp;
        }
    } while (destroy_num != 0);

    prev_num = temp[0];
    count_num = 1;
    vector<int> ans;
    for (int i = 1; i <= temp.size(); i++) {
        if (i == temp.size()) {
            ans.push_back(count_num);
            ans.push_back(prev_num);
            break;
        }
        if (prev_num != temp[i]) {
            ans.push_back(count_num);
            ans.push_back(prev_num);
            prev_num = temp[i];
            count_num = 1;
        }
        else {
            count_num++;
        }
    }

    if (ans.size() >= n * n) {
        while (ans.size() >= n * n) ans.pop_back();
    }
    return ans;
}

vector<vector<int>> change_dim(vector<int>& ans, int n) {
    vector<vector<int>> answer(n, vector<int>(n, 0));
    int x = (n + 1) / 2 - 1;
    int y = (n + 1) / 2 - 1;
    int move = 1;
    int cnt = 0;
    int order[4] = { 2,1,3,0 };
    int idx = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (x < 0 || y < 0 || x >= n || y >= n || idx >= ans.size()) break;
        if (cnt == 2) {
            cnt = 0;
            move++;
        }
        for (int j = 0; j < move; j++) {
            x += direc_x[order[i % 4]];
            y += direc_y[order[i % 4]];
            if (x < 0 || y < 0 || x >= n || y >= n || idx >= ans.size()) break;
            answer[x][y] = ans[idx];
            idx++;
        }
        cnt++;
    }
    return answer;
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nums;
    for (int i = 0; i < n; i++) {
        vector<int> temp;
        for (int j = 0; j < n; j++) {
            int num;
            scanf("%d", &num);
            temp.push_back(num);
        }
        nums.push_back(temp);
    }
    for (int i = 0; i < m; i++) {
        int d, s;
        scanf("%d", &d);
        scanf("%d", &s);
        vector<int> temp = destroy(nums, d, s, n);
        if (temp.size() == 0) {
            break;
        }
        nums = change_dim(temp, n);
    }

    cout << 1 * vec[0] + 2 * vec[1] + 3 * vec[2] << endl;
}