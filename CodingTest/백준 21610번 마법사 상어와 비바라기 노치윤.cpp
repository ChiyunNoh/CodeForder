#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
int move_y[8] = { -1,-1,0,1,1,1,0,-1 };
int move_x[8] = { 0,-1,-1,-1,0,1,1,1 };
void move_cloud(vector<pair<int, int>>& cloud, int move, int cnt, int n) {
    vector<pair<int, int>> new_cloud;
    for (int i = 0; i < cloud.size(); i++) {
        int x = cloud[i].first + (move_x[move - 1] * cnt);
        int y = cloud[i].second + (move_y[move - 1] * cnt);
        if (x >= n) {
            x %= n;
        }
        if (y >= n) {
            y %= n;
        }
        if (x < 0) {
            while (x < 0) {
                x += n;
            }
        }
        if (y < 0) {
            while (y < 0) {
                y += n;
            }
        }
        new_cloud.push_back(make_pair(x, y));
    }
    cloud = new_cloud;
}
void revise_cloud(vector<pair<int, int>>& cloud, vector<vector<int>>& nums) {
    vector<vector<int>> check(nums.size(), vector<int>(nums.size(), 0));
    vector<pair<int, int>> new_cloud;
    for (int i = 0; i < cloud.size(); i++) {
        check[cloud[i].first][cloud[i].second] = 1;
    }
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size(); j++) {
            if (check[i][j] == 0) {
                if (nums[i][j] >= 2) {
                    nums[i][j] -= 2;
                    new_cloud.push_back(make_pair(i, j));
                }
            }
        }
    }
    cloud = new_cloud;
}
int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
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
    vector<pair<int, int>> cloud;
    cloud.push_back(make_pair(n - 1, 0));
    cloud.push_back(make_pair(n - 1, 1));
    cloud.push_back(make_pair(n - 2, 0));
    cloud.push_back(make_pair(n - 2, 1));
    for (int i = 0; i < m; i++) {
        int move, cnt;
        scanf("%d", &move);
        scanf("%d", &cnt);
        move_cloud(cloud, move, cnt, n);
        for (int j = 0; j < cloud.size(); j++) {
            int x = cloud[j].first;
            int y = cloud[j].second;
            nums[x][y] += 1;
        }
        for (int j = 0; j < cloud.size(); j++) {
            int x = cloud[j].first;
            int y = cloud[j].second;
            if (x - 1 >= 0 && y - 1 >= 0 && nums[x - 1][y - 1] > 0) nums[x][y]++;
            if (x - 1 >= 0 && y + 1 < n && nums[x - 1][y + 1] > 0) nums[x][y]++;
            if (x + 1 < n && y - 1 >= 0 && nums[x + 1][y - 1] > 0) nums[x][y]++;
            if (x + 1 < n && y + 1 < n && nums[x + 1][y + 1] > 0) nums[x][y]++;
        }
        revise_cloud(cloud, nums);
    }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer += nums[i][j];
        }
    }
    cout << answer << endl;


}