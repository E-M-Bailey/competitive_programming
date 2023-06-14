#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<string> parse_line(const string& line) {
	vector<string> ret;
	string buff = "";
	for (const auto& c : line) {
		if (isdigit(c) || isupper(c) || islower(c)) buff += c;
		else if (!buff.empty()) {
			ret.push_back(buff);
			buff = "";
		}
	}
	if (!buff.empty()) ret.push_back(buff);
	return ret;
} 

int main() {
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);

	vector<vector<int>> graph;
	int sz = 0;
	vector<string> names;
	unordered_map<string, int> to_idx;
	vector<bool> is_bug;
	auto find_or_add = [&](const string& name) {
		if (to_idx.find(name) != to_idx.end()) return to_idx[name];
		graph.emplace_back();
		names.push_back(name);
		to_idx[name] = sz;
		is_bug.push_back(false);
		return sz++;
	};

	int curr_node = -1;
	int entry = -1;

	string line;
	while (getline(cin, line)) {
		if (line == "") break;
		auto parsed = parse_line(line);
		if (parsed[0] == "N") {
			curr_node = find_or_add(parsed[1]);
			if (entry == -1) entry = curr_node;
		} else if (parsed[0] == "BUG") {
			is_bug[curr_node] = true;
		} else {
			assert(parsed[0] == "UE");
			auto neighbor = find_or_add(parsed[1]);
			graph[curr_node].push_back(neighbor);
		}
	}

	queue<int> q;
	vector<int> dist(sz, 1e9 + 10), parent(sz, -1);
	q.push(entry);
	dist[entry] = 0;
	while (!q.empty()) {
		auto curr = q.front(); q.pop();
		for (const auto& neighbor : graph[curr]) {
			if (dist[neighbor] > dist[curr] + 1) {
				dist[neighbor] = dist[curr] + 1;
				parent[neighbor] = curr;
				q.push(neighbor);
			}
		}
	}
	vector<string> ret;
	for (int i = 0; i<sz; i++) {
		if (!is_bug[i]) continue;
		int curr = i;
		while (curr != -1) {
			ret.push_back(names[curr]);
			curr = parent[curr];
		}
		break;
	}
	reverse(begin(ret), end(ret));
	for (const auto& elem : ret) {
		cout << elem << '\n';
	}
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out