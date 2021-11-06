#include <string>
#include <vector>
#include <algorithm>


using namespace std;

string time_plus(string t, int m) {
    string s_hour = t.substr(0, 2);
    string s_min = t.substr(3);

    int hour = stoi(s_hour);
    int min = stoi(s_min);

    min += m;
    if (min >= 60) {
        hour += (min / 60);
        min %= 60;
    }

    s_hour = to_string(hour);
    if (hour < 10) {
        s_hour = "0" + s_hour;
    }
    s_min = to_string(min);
    if (min < 10) {
        s_min = "0" + s_min;
    }
    return s_hour + ":" + s_min;
}

string time_minus(string t, int m) {
    string s_hour = t.substr(0, 2);
    string s_min = t.substr(3);

    int hour = stoi(s_hour);
    int min = stoi(s_min);

    min -= m;
    if (min < 0) {
        hour -= 1;
        min += 60;
    }

    s_hour = to_string(hour);
    if (hour < 10) {
        s_hour = "0" + s_hour;
    }
    s_min = to_string(min);
    if (min < 10) {
        s_min = "0" + s_min;
    }
    return s_hour + ":" + s_min;
}

vector<string> bustime(int n, int t) {
    vector<string> bus;
    string s = "09:00";
    bus.push_back(s);
    for (int i = 1; i < n; i++) {
        s = time_plus(s, t);
        bus.push_back(s);
    }

    return bus;

}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    sort(timetable.begin(), timetable.end());
    vector<string> bus = bustime(n, t);
    int bus_idx = 0;
    int crew_idx = 0;
    bool flag = false;
    while (true) {
        string s_bus = bus[bus_idx];
        if (bus_idx == bus.size() - 1) {
            for (int i = 0; i < m - 1; i++) {
                if (crew_idx == timetable.size()) {
                    answer = bus.back();
                    flag = true;
                    break;
                }
                if (timetable[crew_idx] <= s_bus) {
                    crew_idx++;
                }
                else break;
            }
            if (flag) break;
            if (crew_idx == timetable.size()) {
                answer = bus.back();
                flag = true;
                break;
            }
            if (timetable[crew_idx] <= s_bus) answer = time_minus(timetable[crew_idx], 1);
            else {
                answer = s_bus;
            }
            break;
        }
        for (int i = 0; i < m; i++) {
            if (crew_idx == timetable.size()) {
                answer = bus.back();
                flag = true;
                break;
            }
            if (timetable[crew_idx] <= s_bus) {
                crew_idx++;
            }
            else break;
        }
        if (flag) break;
        bus_idx++;
    }

    return answer;
}