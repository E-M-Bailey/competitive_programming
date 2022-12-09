#include <bits/stdc++.h>
using namespace std;

template<typename T>
constexpr T MAX = numeric_limits<T>::max();

int64_t n, m;
vector<vector<pair<int64_t, int64_t>>> G;

vector<int64_t> sssp(int64_t s) {
    vector<int64_t> D(n, MAX<int64_t> / 2);
    priority_queue<pair<int64_t, int64_t>> PQ;
    vector<bool> V(n);
    PQ.emplace(0, s);
    D[0] = s;
    while (!PQ.empty()) {
        auto [d, v] = PQ.top();
        PQ.pop();
        if (V[v]) continue;
        d *= -1;
        D[v] = d;
        V[v] = true;
        for (auto [w, wt] : G[v]) {
            int64_t d2 = wt + d;
            //cerr << "(" << v << ' ' << w << ' ' << wt << ' ' << d << ' ' << d2 << ')' << endl;
            if (V[w])
                continue;
            PQ.emplace(-d2, w);
        }

    }
    return D;
}

void go() {
	int64_t h1, s1, h2, s2;
	cin >> h1 >> s1 >> h2 >> s2;
	h1--;
	s1--;
	h2--;
	s2--;
	G.clear();
	G.resize((size_t)n);
	unordered_map<int, unordered_set<int>> ME;
	for (int64_t i = 0; i < m; i++) {
		int64_t u, v, t;
		cin >> u >> v >> t;
		u--;
		v--;
		//if (u > v)
        //    swap(u, v);
        //if (ME[u].find(v) != ME[u].end())

		G[u].emplace_back(v, t);
		G[v].emplace_back(u, t);
		//ME[u].insert(v);
		//ME[v].insert(u);
	}

	/*if (s1 == s2) {
        cout << -1 << endl;
        return;
	}*/

	vector<int64_t> H1 = sssp(h1), S1 = sssp(s1), H2 = sssp(h2), S2 = sssp(s2);
	int64_t d1 = H1[s1], d2 = H2[s2];
	vector<bool> V1(n), V2(n);
	for (int64_t i = 0; i < n; i++) {
        V1[i] = H1[i] + S1[i] == d1;
        V2[i] = H2[i] + S2[i] == d2;
	}

	/*cerr << "-" << endl;
	for (int i = 0; i < n; i++) {
        cerr << H1[i] << ' ' << H2[i] << endl;
	}
	cerr << endl;*/

    int64_t ans = 0;
    for (int64_t i = 0; i < n; i++) {
        if (!V1[i] || !V2[i]) continue;
        int64_t a = H1[i], b = H2[i];
        if (i == s1) a = max(a, b);
        if (i == s2) b = max(a, b);
        ans += a == b;
    }

    vector<unordered_map<int64_t, int64_t>> E1(n), E2(n);
    for (int64_t v = 0; v < n; v++) {
        for (auto [w, wt] : G[v]) {
            if (V1[v] && V1[w] && wt == H1[w] - H1[v])
                E1[v].emplace(w, wt);
            if (V2[v] && V2[w] && wt == H2[w] - H2[v])
                E2[v].emplace(w, wt);
        }
    }

    for (int64_t v = 0; v < n; v++) {
        for (auto [w, wt] : E1[v]) {
            if (H1[v] == H2[v] && E2[v].find(w) != E2[v].end()) {
                cout << -1 << endl;
                return;
                //ans++;
            }
            if (E2[w].find(v) == E2[w].end()) continue;
            int64_t a = H1[v], b = a + wt, c = H2[w], d = c + wt;
            //cerr << v << ' ' << w << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
            if (b > c && a < d)
                ans++;
        }
    }
    cout << ans << endl;
}

int main() {
	while (cin >> n >> m && n)
		go();
}
