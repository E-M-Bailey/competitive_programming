#include <bits/stdc++.h>
using namespace std;

vector<int> A;

bool ok(int l, int r, map<int, deque<int>>& F, set<int>& O) {
    //cerr << "ok " << l << ' ' << r << endl;
    if (l + 1 >= r)
        return true;
    if (O.empty())
        return false;
    /*cerr << l << ' ' << r << endl;
    for (int o : O)
        cerr << ' ' << o;
    cerr << endl;
    for (const auto& [x, f] : F) {
        cerr << x << ":";
        for (int ff : f)
            cerr << ' ' << ff;
        cerr << endl;
    }
    cerr << endl;*/
    int m = F[*O.begin()].front();
    bool L, R;
    if (m > (l + r) / 2) {
        map<int, deque<int>> F2;
        set<int> O2;
        for (int i = m + 1; i < r; i++) {
            F2[A[i]].push_back(i);
            int s = F2[A[i]].size();
            if (s == 1)
                O2.insert(A[i]);
            else if (s == 2)
                O2.erase(A[i]);
        }
        for (int i = r - 1; i >= m; i--) {
            F[A[i]].pop_back();
            int s = F[A[i]].size();
            if (s == 1)
                O.insert(A[i]);
            else if (s == 0) {
                O.erase(A[i]);
                F.erase(A[i]);
            }
        }
        L = ok(l, m, F, O);
        R = ok(m + 1, r, F2, O2);
    }
    else {
        map<int, deque<int>> F2;
        set<int> O2;
        for (int i = l; i < m; i++) {
            F2[A[i]].push_back(i);
            int s = F2[A[i]].size();
            if (s == 1)
                O2.insert(A[i]);
            else if (s == 2)
                O2.erase(A[i]);
        }
        for (int i = l; i <= m; i++) {
            //cerr << "pop " << i << ' ' << A[i] << endl;
            F[A[i]].pop_front();
            int s = F[A[i]].size();
            if (s == 1)
                O.insert(A[i]);
            else if (s == 0) {
                O.erase(A[i]);
                F.erase(A[i]);
            }
        }
        L = ok(l, m, F2, O2);
        R = ok(m + 1, r, F, O);
    }
    bool ans = L && R;
    return ans;
}

void go() {
	int n;
	cin >> n;
	A.resize(n);
    for (int& a : A)
        cin >> a;
    map<int, deque<int>> F;
    set<int> O;
    for (int i = 0; i < n; i++)
        F[A[i]].push_back(i);
    for (int i = 0; i < n; i++)
        if (F[A[i]].size() == 1)
            O.insert(A[i]);
    bool ans = ok(0, n, F, O);
    cout << (ans ? "non-boring" : "boring") << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--)
		go();
}
