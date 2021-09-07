#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    sort(times.begin(), times.end());
    long long lo = 0;
    long long hi = n * (long long)times.back();
    while (lo != hi) {
        long long mid = (lo + hi) / 2;
        long long pass = 0;
        for (int i = 0; i < times.size(); i++) {
            pass += mid / times[i];
        }
        if (pass >= n) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    return lo;
}