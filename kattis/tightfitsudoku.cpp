#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    vector<vector<string>> grid(6, vector<string>(6));

    vector<vector<bool>> used_row(6, vector<bool>(10, false));
    vector<vector<bool>> used_col(6, vector<bool>(10, false));

    auto mark = [&](int r, int c, int val) -> void {
        used_row[r][val] = used_col[c][val] = true;
    };

    for (int i = 0; i<6; i++) {
        for (int j = 0; j<6; j++) {
            cin >> grid[i][j];
            if (grid[i][j].size() == 1 && grid[i][j] != "-") {
                int val = stoi(grid[i][j]);
                mark(i, j, val);
            } else if (grid[i][j].size() == 3) {
                if (grid[i][j][0] != '-') mark(i, j, stoi(grid[i][j].substr(0, 1)));
                if (grid[i][j][2] != '-') mark(i, j, stoi(grid[i][j].substr(2, 1)));
            }
        }
    }

    bool solved = false;

    function<void(int)> solve = [&](int idx) {
        if (solved) return;
        if (idx >= 36) {
            for (int i = 0; i<6; i++) {
                for (int j = 0; j<6; j++) {
                    cout << grid[i][j] << " ";
                }
                cout << '\n';
            }
            solved = true;
            return;
        }
        int i = idx / 6, j = idx % 6;
        if (grid[i][j].size() == 1) {
            if (grid[i][j] != "-") {
                solve(idx + 1);
                if (solved) return;
            }
            else {
                for (int x = 1; x <= 9; x++){
                    if (used_row[i][x] || used_col[j][x]) continue;
                    grid[i][j] = to_string(x);
                    used_row[i][x] = used_col[j][x] = true;
                    solve(idx + 1);
                    if (solved) return;
                    used_row[i][x] = used_col[j][x] = false;
                    grid[i][j] = "-";
                }
            }

        }
        else if (grid[i][j].size() == 3) {
            if (grid[i][j][0] == '-' && grid[i][j][2] == '-') {
                for (int x = 1; x <= 9; x++) {
                    for (int y = x+1; y <= 9; y++) {
                        if (used_row[i][x] || used_row[i][y]) continue;
                        if (used_col[j][x] || used_col[j][y]) continue;
                        grid[i][j] = to_string(x) + "/" + to_string(y);
                        used_row[i][x] = used_row[i][y] = true;
                        used_col[j][x] = used_col[j][y] = true;
                        solve(idx + 1);
                        if (solved) return;
                        used_row[i][x] = used_row[i][y] = false;
                        used_col[j][x] = used_col[j][y] = false;
                        grid[i][j] = "-/-";
                    }
                }
            }
            else if (grid[i][j][0] == '-') {
                int y = grid[i][j][2] - '0';
                for (int x = 1; x < y; x++) {
                    if (used_row[i][x] || used_row[i][y]) continue;
                    if (used_col[j][x] || used_col[j][y]) continue;
                    grid[i][j] = to_string(x) + "/" + to_string(y);
                    used_row[i][x] = used_row[i][y] = true;
                    used_col[j][x] = used_col[j][y] = true;
                    solve(idx + 1);
                    if (solved) return;
                    used_row[i][x] = used_row[i][y] = false;
                    used_col[j][x] = used_col[j][y] = false;
                    grid[i][j] = "-/-";
                }
            }
            else if (grid[i][j][2] == '-') {
                int x = grid[i][j][0] - '0';
                for (int y = x+1; y <= 9; y++) {
                    if (used_row[i][x] || used_row[i][y]) continue;
                    if (used_col[j][x] || used_col[j][y]) continue;
                    grid[i][j] = to_string(x) + "/" + to_string(y);
                    used_row[i][x] = used_row[i][y] = true;
                    used_col[j][x] = used_col[j][y] = true;
                    solve(idx + 1);
                    if (solved) return;
                    used_row[i][x] = used_row[i][y] = false;
                    used_col[j][x] = used_col[j][y] = false;
                    grid[i][j] = "-/-";
                }
            }
            else {
                solve(idx + 1);
                if (solved) return;
                return;
            }
        }

    };

    solve(0);
}
