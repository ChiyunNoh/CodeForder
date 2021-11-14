#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    map<string, int> name;
    for (int i = 0; i < gems.size(); i++) {
        name[gems[i]] = 0;
    }
    int num = name.size();//보석 개수
    int cnt = 0;
    for (map<string, int>::iterator iter = name.begin(); iter != name.end(); iter++) {
        name[iter->first] = cnt;
        cnt++;
    }//name 에는 각 이름별 idx가 매칭되어있음. vector에서 찾아서 사용

    vector<int> cart(num, 0);//어피치 장바구니 속 보석 별 개수
    vector<pair<int, int>> direc; // (1, 3) 1번 인덱스에서 시작 3번에서 끝
    int start = 0;
    int end = 0;
    int prev_num = 0;
    string prev_name = "";
    int cart_num = 0;
    bool check = false;
    for (end = 0; end < gems.size(); end++) {
        if (cart_num == num) {
            direc.push_back(make_pair(start, --end));
            prev_num = cart[name[gems[start]]];
            prev_name = gems[start];
            cout << end << endl;
            check = true;
            break;
        }
        if (cart[name[gems[end]]] == 0) { // gems[end] = 이름, name[gems[start]]= 이름의 인덱스
            cart_num++;
            cart[name[gems[end]]]++;

        }
        else {
            cart[name[gems[end]]]++;

        }
    }
    if (!check) {
        if (cart_num == num) {
            direc.push_back(make_pair(start, --end));
            prev_num = cart[name[gems[start]]];
            prev_name = gems[start];
        }
    }



    for (start = 1; start < gems.size(); start++) {
        prev_num--;
        cart[name[gems[start - 1]]]--;
        if (prev_num != 0) {
            direc.push_back(make_pair(start, end));
            prev_num = cart[name[gems[start]]];
            prev_name = gems[start];
        }
        else {
            bool flag = false;
            while (end < gems.size() - 1) {
                end++;
                cart[name[gems[end]]]++;
                if (name[gems[end]] == name[prev_name]) {
                    direc.push_back(make_pair(start, end));
                    prev_num = cart[name[gems[start]]];
                    prev_name = gems[start];
                    flag = true;
                    break;
                }
            }
            if (!flag) break;
        }
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < direc.size(); i++) {
        int sta = direc[i].first;
        int leng = direc[i].second - direc[i].first;
        ans.push_back(make_pair(leng, sta));
    }
    sort(ans.begin(), ans.end());
    answer.push_back(ans[0].second + 1);
    answer.push_back(ans[0].first + ans[0].second + 1);

    return answer;
}