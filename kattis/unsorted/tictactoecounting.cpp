#include <bits/stdc++.h>

using namespace std;

constexpr int iinf = 1e9 + 10;

int main() {
	vector<bool> visited(19683, false), visited2(19683, false);
	vector<bool> x_win(19683, false), y_win(19683, false);
	vector<int> x_dist(19683, 0), y_dist(19683, 0);

	vector<int> board(9);

	visited[0] = true;
	deque<int> q{0};

	auto check_win = [&](int h, int v) {
		for (int ptr = 8; ptr >= 0; ptr--) {
			board[ptr] = h % 3;
			h /= 3;
		}
		if (board[0] == v && board[4] == v && board[8] == v) return true;
		if (board[2] == v && board[4] == v && board[6] == v) return true;
		for (int i = 0; i<3; i++) {
			if (board[i * 3] == v &&  board[i * 3 + 1] == v && board[i * 3 + 2] == v) return true;
			if (board[i] == v && board[i + 3] == v && board[6 + i] == v) return true;
		}
		return false;
	};

	auto turn = [&](int hh) {
		int x = 0, y = 0;
		for (int i = 0; i<9; i++) {
			if (hh % 3 == 1) y++;
			else if (hh % 3 == 2) x++;
			hh /= 3;
		}
		return x == y ? 2 : 1;
	};

	auto print_board = [&](int h) {
		vector<int> bb;
		for (int i = 0; i<9; i++) {
			bb.push_back(h % 3);
			h /= 3;
		}
		reverse(bb.begin(), bb.end());
		for (int i = 0; i<9; i++) {
			cout << bb[i] << " ";

		}

		cout << '\n';
	};


	while (!q.empty()) {
		auto curr = q.front();
		q.pop_front();

		if (check_win(curr, 2)) {
			x_win[curr] = true;
			continue;
		}
		if (check_win(curr, 1)) {
			y_win[curr] = true;
			continue;
		}
		
		int temp = curr, p = 1;
		for (int i = 0; i<9; i++) {
			if (temp % 3 == 0) {
				int nxt_state = curr + p * turn(curr);
				if (!visited[nxt_state]) {
					visited[nxt_state] = true;
					q.push_back(nxt_state);
				}	
			}
			temp /= 3;
			p *= 3;
		}
	}

	q.clear();
	for (int i = 0; i<19683; i++) {
		if (visited[i] && x_win[i]) {
			q.push_back(i);
			x_dist[i] = 1;
			visited2[i] = true;
		}
	}

	while (!q.empty()) {
		auto curr = q.front();
		q.pop_front();

		int curr_turn = 3 - turn(curr);

		int temp = curr, p = 1;
		for (int i = 0; i<9; i++) {
			if (temp % 3 == curr_turn) {
				int nxt_state = curr - p * curr_turn;
				if (visited[nxt_state]) {
					x_dist[nxt_state] += x_dist[curr];
					if (!visited2[nxt_state]) {
						visited2[nxt_state] = true;
						q.push_back(nxt_state);
					}	
				}
				
			}
			temp /= 3;
			p *= 3;
		}
	}

	q.clear();
	for (int i = 0; i<19683; i++) {
		visited2[i] = false;
		if (visited[i] && y_win[i]) {
			q.push_back(i);
			visited2[i] = true;
			y_dist[i] = 1;
		}
	}

	while (!q.empty()) {
		auto curr = q.front();
		q.pop_front();

		int curr_turn = 3 - turn(curr);

		int temp = curr, p = 1;
		for (int i = 0; i<9; i++) {
			if (temp % 3 == curr_turn) {
				int nxt_state = curr - p * curr_turn;
				if (visited[nxt_state]) {
					y_dist[nxt_state] += y_dist[curr];
					if (!visited2[nxt_state]) {
						visited2[nxt_state] = true;
						q.push_back(nxt_state);
					}	
				}	
			}
			temp /= 3;
			p *= 3;
		}
	}


	int t; cin >> t;

	auto encode = [&](const string& s) -> int {
		int ret = 0;
		for (int i = 0; i<9; i++) {
			ret *= 3;
			if (s[i] == 'O') ret++;
			else if (s[i] == 'X') ret += 2;
		}
		return ret;
	};



	while (t--) {
		string s; cin >> s;

		auto h = encode(s);
		cerr << h << '\n';
		if (!visited[h]) cout << -1 << " " << -1 << '\n';
		else {
			cout << x_dist[h] << " " << y_dist[h] << '\n';
		}


	}
}