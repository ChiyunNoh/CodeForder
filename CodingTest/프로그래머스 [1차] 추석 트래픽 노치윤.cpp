#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int solution(vector<string> lines) {
    int answer = 0;
    vector<vector<int>> time_list;
    for (int i = 0; i < lines.size(); i++) {
        istringstream iss(lines[i]);
        string s1, s2, s3;
        iss >> s1 >> s2 >> s3;
        string temp = "";
        int time = 0;
        int during = 0;

        time += stoi(s2.substr(0, 2)) * 3600000; 
        time += stoi(s2.substr(3, 2)) * 60000;
        time += stoi(s2.substr(6, 2)) * 1000;
        time += stoi(s2.substr(9));
        for (int j = 0; j < s3.length(); j++) {
            if (s3[j] != 's') temp += s3[j];
            else {
                during = stod(temp) * 1000;
            }
        }
        vector<int> vec;
        vec.push_back(time - during + 1);
        vec.push_back(time);
        time_list.push_back(vec);

    }
    for (int i = 0; i < time_list.size(); i++) {
        int start = 0; int finish = 0; int max = 0;
        start = time_list[i][0] + 1 - 1000;
        finish = time_list[i][0] + 1;
        for (int j = i; j < time_list.size(); j++) {
            if (time_list[j][0] <= finish && time_list[j][1] >= start) max += 1;
        }
        if (max > answer) answer = max;

        max = 0;
        start = time_list[i][1] - 1;
        finish = time_list[i][1] - 1 + 1000;
        for (int j = i; j < time_list.size(); j++) {
            if (time_list[j][0] <= finish && time_list[j][1] >= start) max += 1;
        }
        if (max > answer) answer = max;
    }
    return answer;
}

