#include <bits/stdc++.h>

using namespace std;
using ll = long long;

typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
typedef pair<ppi, int> ppp;

int N;
queue<ppp> q;
vector<ppi> v;
int ans[100000];

void print(ppp a){
    cout << a.first.first.first << " " << a.first.first.second << " " << a.first.second << " " << a.second << endl;
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++){
        int ti, ci;
        cin >> ti >> ci;
        v.push_back(make_pair(make_pair(ti, ci), 0));
    }
    for(int i = N-1; i >= 0; i--){
        q.push(make_pair(v[i], i));
    }

    int ind = 0;
    while(!q.empty()){
        stack<ppp> s;
        int nxt = q.front().first.second;
        while(!q.empty() && q.front().first.second == nxt){
            ppp p = q.front();
            q.pop();
            //print(p);
            if(p.first.first.second == 0){
                ans[p.second] = p.first.second;
                continue;
            }
            p.first.second += p.first.first.first;
            p.first.first.second--;
            s.push(p);
        }
        if(!q.empty()){
            nxt = q.back().first.second;
            stack<ppp> s2;
            while(!s.empty() && s.top().first.second <= nxt){
                s2.push(s.top());
                s.pop();
                s2.top().first.second = nxt;
            }
            while(!s2.empty()){
                q.push(s2.top());
                s2.pop();
            }
        }
        while(!s.empty()){
            q.push(s.top());
            s.pop();
        }
    }
    for(int i = 0; i < N; i++){
        cout << ans[i] << endl;
    }
    return 0;
}

