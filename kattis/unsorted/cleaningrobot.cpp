#include <bits/stdc++.h>

using namespace std;

#define len(x) (int)(x).size()

template <typename T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, k++) {
			jmp.emplace_back(len(V)-pw*2+1);
			for (int j = 0; j<len(jmp[k]); j++) {
				jmp[k][j] = max(jmp[k-1][j], jmp[k-1][j+pw]);
			}
		}
	}

	T query(int a, int b) {
		assert(a < b);
		int dep = 31 - __builtin_clz(b-a);
		return max(jmp[dep][a], jmp[dep][b-(1 << dep)]);
	}
};

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int n,m,k;
	cin >> n >> m >> k;
	vector<vector<int>> is_obstructed(n, vector<int>(m, false));
	vector<RMQ<int>> row,col;

	for (int i = 0; i<k; i++) {
		int x,y; cin >> x >> y;
		is_obstructed[--x][--y] = 1;
	}

	for (int i = 0; i<n; i++) {
		vector<int> curr_row;
		for (int j = 0; j<m; j++) {
			curr_row.push_back(is_obstructed[i][j]);
		}
		row.emplace_back(curr_row);
	}

	for (int j = 0; j<m; j++) {
		vector<int> curr_col;
		for (int i = 0; i<n; i++) {
			curr_col.push_back(is_obstructed[i][j]);
		}
		col.emplace_back(curr_col);
	}

	int low = 1, high = min(n,m), best = -1;

	auto possible = [&](int mid) -> bool {
		for (int i = 0; i<mid; i++) {
			for (int j = 0; j<mid; j++) {
				if (is_obstructed[i][j]) return false;
			}
		}
		deque<pair<int, int>> q;
		q.emplace_back(0, 0);
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		visited[0][0] = true;
		while (!q.empty()){
			auto [i, j] = q.front();
			q.pop_front();
			if (j + mid < m && !col[j+mid].query(i, i+mid) && !visited[i][j+1]) {
				visited[i][j+1] = true;
				q.emplace_back(i, j+1);
			}
			if (i+mid < n && !row[i+mid].query(j, j+mid) && !visited[i+1][j]) {
				visited[i+1][j] = true;
				q.emplace_back(i+1, j);
			}
		}
		vector<vector<int>> rrow(n, vector<int>(m+1, 0));
		vector<vector<int>> rcol(m, vector<int>(n+1, 0));
		vector<vector<bool>> marked(n, vector<bool>(m, false));

		q.clear();
		for (int x = 0; x<n; x++) {
			for (int y = 0; y<m; y++) {
				if (!visited[x][y]) continue;
				q.emplace_back(x, y);
				marked[x][y] = true;
				for (int i = x; i < x + mid; i++) {
					rrow[i][y]++;
					rrow[i][y+mid]--;
				}
				while (!q.empty()) {
					auto [i, j] = q.front();
					q.pop_front();
					for (int z = 0; z < 4; z++) {
						auto new_x = i+dx[z], new_y = j+dy[z];
						if (new_x < 0 || new_x >= n) continue;
						if (new_y < 0 || new_y >= m) continue;
						if (visited[new_x][new_y] && !marked[new_x][new_y]) {
							
						}
					}
				}
			}
		}
	};

	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (possible(mid)) {
			best = mid;
			low = mid + 1;
		} else {
			high = mid-1;
		}
	}

	cout << best << '\n';
}