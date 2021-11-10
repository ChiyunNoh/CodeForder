#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, int> genre_num;
    map<string, int> num; //장르별 번호 갯수 저장
    for (int i = 0; i < genres.size(); i++) {
        if (genre_num.find(genres[i]) == genre_num.end()) {
            num[genres[i]] = 1;
            genre_num[genres[i]] = plays[i];
        }
        else {
            num[genres[i]]++;
            genre_num[genres[i]] += plays[i];
        }
    }
    map<int, string> sort_M;
    vector<string> s_genre;
    for (map<string, int>::iterator iter = genre_num.begin(); iter != genre_num.end(); iter++) {
        sort_M[iter->second] = iter->first;
    }

    for (map<int, string>::reverse_iterator iter = sort_M.rbegin(); iter != sort_M.rend(); iter++) {
        s_genre.push_back(iter->second);
    }

    for (int i = 0; i < s_genre.size(); i++) {
        if (num[s_genre[i]] != 1) {
            int max = 0;
            int max_idx = -1;
            int min = 0;
            int min_idx = -1;
            for (int j = 0; j < genres.size(); j++) {
                if (genres[j] == s_genre[i]) {
                    if (max == 0 && min == 0) {
                        max = plays[j];
                        max_idx = j;
                        continue;
                    }
                    else if (plays[j] > max) {
                        min = max;
                        min_idx = max_idx;
                        max = plays[j];
                        max_idx = j;
                    }
                    else if (plays[j] <= max && plays[j] > min) {
                        min = plays[j];
                        min_idx = j;
                    }
                    else if (plays[j] == min && min_idx == max_idx) {
                        min = plays[j];
                        min_idx = j;
                    }
                }
            }
            answer.push_back(max_idx);
            answer.push_back(min_idx);
        }
        else {
            for (int j = 0; j < genres.size(); j++) {
                if (genres[j] == s_genre[i]) {
                    answer.push_back(j);
                    break;
                }
            }
        }
    }

    return answer;
}