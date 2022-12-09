#include <bits/stdc++.h>

using namespace std;
using ll = long long;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;

void solve(vector<pld>& v, ld s) {
    if (v.size() <= 1) return;
    vector<pld> q1, q2, q3, q4;
    ld s2 = s / 2;
    for (auto [x, y] : v) {
        if (x < s2 && y < s2) {
                q1.emplace_back(y, x);
        }
        else if (x < s2) {
            q2.emplace_back(x, y - s2);
        }
        else if (y > s2) {
            q3.emplace_back(x - s2, y - s2);
        }
        else {
            q4.emplace_back(s2 - y, s - x);
        }
    }
    solve(q1, s2);
    solve(q2, s2);
    solve(q3, s2);
    solve(q4, s2);
    v.clear();
    for (auto [x, y] : q1)
        v.emplace_back(y, x);
    for (auto [x, y] : q2)
        v.emplace_back(x, y + s2);
    for (auto [x, y] : q3)
        v.emplace_back(x + s2, y + s2);
    for (auto [x, y] : q4)
        v.emplace_back(s - y, s2 - x);
}
/*
void solve(vector<pii> &v, ld x1, ld y1, ld x2, ld y2, int rot, int f){
    if(v.size() <= 1) return;
    vector<pii> q1, q2, q3, q4;
    ld xm = (x1+x2)/2;
    ld ym = (y1+y2)/2;
    for(pii p : v){
        if(p.first < xm && p.second < ym){
            q1.push_back(p);
        }
        else if(p.first < xm) q2.push_back(p);
        else if(p.second < ym) q4.push_back(p);
        else q3.push_back(p);
    }
    for (auto& [x, y] : q1) {

    }


    solve(q1, x1, y1, xm, ym, (rot-f+4)%4, f*-1);
    solve(q2, x1, ym, xm, y2, rot, f);
    solve(q3, xm, ym, x2, y2, rot, f);
    solve(q4, xm, y1, x2, ym, (rot+f+4)%4, f*-1);
    vector<pii> t;
    for(int i = 0; i < 4-rot; i++){
        swap(q1, t);
        swap(q2, q1);
        swap(q3, q2);
        swap(q4, q3);
        swap(t, q4);
    }
    if(f == -1){
        swap(q1, t);
        swap(q4, q1);
        swap(q4, t);
        swap(q2, t);
        swap(q2, q3);
        swap(q3, t);
    }
    v.clear();
    for(pii p : q1){
        v.push_back(p);
    }
    for(pii p : q2){
        v.push_back(p);
    }
    for(pii p : q3){
        v.push_back(p);
    }
    for(pii p : q4){
        v.push_back(p);
    }
}*/

int N, S;
int main() {
    cin >> N >> S;
    vector<pld> v;

    for(int i = 0; i < N; i++){
        int x, y;
        cin >> x >> y;
        v.push_back(make_pair(x, y));
    }/*
    for(int i = 0; i <= S; i++){
        for(int e = 0; e <= S; e++){
            v.push_back(make_pair(i, e));
        }
    }*/
    solve(v, S);
    //solve(v, 0, 0, S, S, 0, 1);
    for(pii p : v){
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
