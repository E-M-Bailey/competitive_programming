#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> A(n);
	for (int& a : A)
		cin >> a;
	int s = accumulate(A.begin(), A.end(), 0);
	if (s % 2 || *max_element(A.begin(), A.end()) > s / 2) {
		cout << "no";
		return 0;
	}

	vector<int> I;
	I.reserve(s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < A[i]; j++)
			I.push_back(i + 1);
	/*{
		vector<int> J(s);
		for (int i = 0; i < s / 2; i++) {
			J[i * 2] = I[i];
			J[i * 2 + 1] = I[i + s / 2];
		}
		I = move(J);
	}*/

	cout << "yes";
	for (int i = 0; i < s / 2; i++)
        cout << endl << I[i] << ' ' << I[i + s / 2];

    /*
	int i = 0, j = 0;
	vector<pair<int, int>> ans;
	while (s) {
		while (i < n && A[i] == 0)
			i++;
		while (j < n && A[j] == 0)
			j++;
		if (i == j)
			j++;
		if (j >= n) {
			cout << "no";
			return 0;
		}
		ans.emplace_back(i + 1, j + 1);
		A[i]--;
		A[j]--;
		s -= 2;
	}
	cout << "yes";
	for (auto [i, j] : ans)
		cout << endl << i << ' '  << j;*/
}
