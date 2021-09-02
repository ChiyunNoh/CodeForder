#include <vector>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int find(int num, vector<int>& box) {
    if (box[num] == num) return num;
    else {
        return box[num] = find(box[num], box);
    }
}
int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    vector<int> box(n + 1, -1);
    for (int i = 0; i < n + 1; i++) {
        box[i] = i;
    }
    while (m--) {
        int a, b, c;
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);
        int group1 = find(b, box);
        int group2 = find(c, box);
        if (a == 0) {
            if (group1 != group2) {
                box[group2] = group1;
            }
        }
        else {
            if (group1 != group2) printf("NO\n");
            else printf("YES\n");
        }
    }
}