/*
int n,d,c; cin >> n >> d >> c;
	vector<int> start(c);
	vector<bool> infected(n, false);
	for (int i = 0;i<c; i++) {
		cin >> start[i];
		start[i]--;
	}
	vector<pair<int, int>> times(n);
	for (int i = 0; i<n; i++) {
		cin >> times[i].first >> times[i].second;
	}
	set<tuple<int, int, int>> remain_start, remain_end;
	for (int i = 0; i<n; i++) {
		remain_start.emplace(times[i].first, times[i].second, i);
		remain_end.emplace(times[i].second, times[i].first, i);
	}
	queue<int> q;
	for (int i = 0; i<c; i++) {
		remain_start.erase(remain_start.lower_bound(make_tuple(times[start[i]].first, times[start[i]].second, start[i])));
		remain_end.erase(remain_end.lower_bound(make_tuple(times[start[i]].second, times[start[i]].first, start[i])));
		q.push(start[i]);
		infected[start[i]] = true;
	}
	while (d--) {
		q.push(-1);
		while (!q.empty()) {
			auto curr = q.front();
			q.pop();
			if (curr == -1) break;
			while (!remain_start.empty()) {
				auto it = remain_start.lower_bound(make_tuple(times[curr].first, -1, -1));
				if (it == remain_start.end() || get<1>(*it) > times[curr].second) break;
				q.push(get<2>(*it));
				infected[get<2>(*it)] = true;
				remain_end.erase(remain_end.lower_bound(make_tuple(get<1>(*it), get<0>(*it), get<2>(*it))));
				remain_start.erase(it);
			}
			while (!remain_end.empty()) {
				auto it = remain_end.lower_bound(make_tuple(times[curr].first, -1, -1));
				if (it == remain_end.end() || get<1>(*it) > times[curr].second) break;
				q.push(get<2>(*it));
				infected[get<2>(*it)] = true;
				remain_start.erase(remain_start.lower_bound(make_tuple(get<1>(*it), get<0>(*it), get<2>(*it))));
				remain_end.erase(it);
			}
		}
	}

	vector<int> ans;
	for (int i = 0; i<n; i++) {
		if (infected[i]) cout << i+1 << " ";
	}

	cout << '\n';

	return 0;
	*/

#include <bits/stdc++.h>

using namespace std;
int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, d, c;
	cin >> n >> d >> c;
	vector<int> C(c);
	for (int& i : C)
	{
		cin >> i;
		i--;
	}

	vector<pair<int, int>> P(n);
	vector<int> ICC;
	for (auto& [s, t] : P)
	{
		cin >> s >> t;
		ICC.push_back(s);
		ICC.push_back(t);
	}
	sort(begin(ICC), end(ICC));
	ICC.resize(unique(begin(ICC), end(ICC)) - begin(ICC));
	unordered_map<int, int> CC;
	int k = size(ICC);
	for (int i = 0; i < k; i++)
		CC[ICC[i]] = i;
	for (auto& [s, t] : P)
	{
		s = CC[s];
		t = CC[t];
	}
	vector<vector<int>> S(k), T(k);
	for (int i = 0; i < n; i++)
	{
		auto [s, t] = P[i];
		S[s].push_back(i);
		T[t].push_back(i);
	}

	vector<vector<int>> G(n);
	unordered_set<int> R;

	for (int t = 0; t < k; t++)
	{
		while (!S[t].empty())
		{
			int i = S[t].back();
			S[t].pop_back();
			for (int j : R)
			{
				G[i].push_back(j);
				G[j].push_back(i);
			}
			R.insert(i);
		}
		for (int i : T[t])
			R.erase(i);
		T[t].clear();
	}

	queue<pair<int, int>> Q;
	vector<int> D(n, -1);
	for (int i : C)
	{
		Q.emplace(i, 0);
	}
	while (!Q.empty())
	{
		auto [v, d] = Q.front();
		Q.pop();
		if (D[v] >= 0) continue;
		D[v] = d;
		for (int w : G[v])
			if (D[w] == -1)
				Q.emplace(w, d + 1);
	}

	for (int i = 0; i < n; i++)
	{
		if (D[i] <= d && D[i] >= 0)
			cout << i + 1 << ' ';
	}
}